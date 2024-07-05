/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file pca9959_drv.c
 * @brief The pca9959_drv.c file implements the PCA9959 LED driver interfaces.
 */

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "pca9959_drv.h"
#include "gpio_driver.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------

uint8_t pca9959_spiRead_CmdBuffer[PCA9959_SPI_MAX_MSG_SIZE] = {0};
uint8_t pca9959_spiRead_DataBuffer[PCA9959_SPI_MAX_MSG_SIZE] = {0};
uint8_t pca9959_spiWrite_CmdDataBuffer[PCA9959_SPI_MAX_MSG_SIZE] = {0};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------

void PCA9959_SPI_ReadCmdPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
	spiCmdParams_t *pSlaveCmd = pCmdOut;

	uint8_t *pWBuff = pca9959_spiRead_CmdBuffer;
	uint8_t *pRBuff = pca9959_spiRead_DataBuffer;

	/* Formatting for Read command of PCA9959 LED driver. */
	*(pWBuff) = ( offset << 1) | PCA9959_SPI_RD_CMD;  /* offset is the internal register address of the sensor at which Read is performed. */
	*(pWBuff + 1) = PCA9959_ALL_BIT_ONE;

	/* Create the slave read command. */
	pSlaveCmd->size = size + PCA9959_SPI_CMD_LEN;
	pSlaveCmd->pWriteBuffer = pWBuff;
	pSlaveCmd->pReadBuffer = NULL;
}

void PCA9959_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
	spiCmdParams_t *pSlaveCmd = pCmdOut;

	uint8_t *pWBuff = pca9959_spiRead_CmdBuffer;
	uint8_t *pRBuff = pca9959_spiRead_DataBuffer;

	/* Formatting for Read command of PCA9959 LED driver. */
	*(pWBuff) =  PCA9959_ALL_BIT_ONE;

	/* Create the slave read command. */
	pSlaveCmd->size = size + PCA9959_SPI_CMD_LEN;
	pSlaveCmd->pWriteBuffer = pWBuff;
	pSlaveCmd->pReadBuffer = pRBuff;
}

void PCA9959_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer)
{
	spiCmdParams_t *pSlaveCmd = pCmdOut;

	uint8_t *pWBuff = pca9959_spiWrite_CmdDataBuffer;

	/* Formatting for Write command of PCA9959 LED driver. */
	*(pWBuff) = ( offset << 1) & PCA9959_SPI_WR_CMD; /* offset is the internal register address of the sensor at which write is performed. */

	/* Copy the slave write command */
	memcpy(pWBuff + PCA9959_SPI_CMD_LEN, pWritebuffer, size);

	/* Create the slave command. */
	pSlaveCmd->size = size + PCA9959_SPI_CMD_LEN;
	pSlaveCmd->pWriteBuffer = pWBuff;
	pSlaveCmd->pReadBuffer = NULL;
}

int32_t PCA9959_SPI_Initialize(pca9959_spi_sensorhandle_t *pSensorHandle,
		ARM_DRIVER_SPI *pBus, uint8_t index,
		void *pSlaveSelect)
{
	int32_t status;
	uint8_t reg;
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/*! Check the input parameters. */
	if ((pSensorHandle == NULL) || (pBus == NULL) || (pSlaveSelect == NULL))
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Initialize the sensor handle. */
	pSensorHandle->pCommDrv = pBus;
	pSensorHandle->slaveParams.pReadPreprocessFN = PCA9959_SPI_ReadPreprocess;
	pSensorHandle->slaveParams.pWritePreprocessFN = PCA9959_SPI_WritePreprocess;
	pSensorHandle->slaveParams.pReadCmdPreprocessFN = PCA9959_SPI_ReadCmdPreprocess;
	pSensorHandle->slaveParams.pTargetSlavePinID = pSlaveSelect;
	pSensorHandle->slaveParams.spiCmdLen = PCA9959_SPI_CMD_LEN;
	pSensorHandle->slaveParams.ssActiveValue = PCA9959_SS_ACTIVE_VALUE;
	pSensorHandle->deviceInfo.deviceInstance = index;
	pSensorHandle->deviceInfo.functionParam = NULL;
	pSensorHandle->deviceInfo.idleFunction = NULL;

	/* Initialize the Slave Select Pin. */
	pGPIODriver->pin_init(pSlaveSelect, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
	if (pSensorHandle->slaveParams.ssActiveValue == SPI_SS_ACTIVE_LOW)
	{
		pGPIODriver->set_pin(pSlaveSelect);
	}
	else
	{
		pGPIODriver->clr_pin(pSlaveSelect);
	}

	pSensorHandle->isInitialized = true;
	return SENSOR_ERROR_NONE;
}

void PCA9959_SPI_SetIdleTask(pca9959_spi_sensorhandle_t *pSensorHandle,
		registeridlefunction_t idleTask,
		void *userParam)
{
	pSensorHandle->deviceInfo.functionParam = userParam;
	pSensorHandle->deviceInfo.idleFunction = idleTask;
}


int32_t PCA9959_SPI_ReadData(pca9959_spi_sensorhandle_t *pSensorHandle,
		const registerreadlist_t *pReadList,
		uint8_t *pBuffer)
{
	int32_t status;

	/*! Validate for the correct handle and register read list.*/
	if ((pSensorHandle == NULL) || (pReadList == NULL) || (pBuffer == NULL))
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before reading sensor data.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/*! Parse through the read list and read the data one by one. */
	status = Sensor_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			pReadList, pBuffer);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_READ;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Deinit(pca9959_spi_sensorhandle_t *pSensorHandle, void *pResetPin)
{
	int32_t status;
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Set Reset pin Low for PCA9959_RESET_DELAY_MS (Trigger device reset)*/
	pGPIODriver->clr_pin(pResetPin);
	BOARD_DELAY_ms(PCA9959_RESET_DELAY_MS);
	pGPIODriver->set_pin(pResetPin);

	/*! De-initialize sensor handle. */
	pSensorHandle->isInitialized = false;

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_OE_Pin_Init(void *pOePin)
{
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/* Initialize OE pin and set its default state */
	pGPIODriver->pin_init(pOePin, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
	pGPIODriver->set_pin(pOePin);

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_Reset_Pin_Init(void *pResetPin)
{
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/* Initialize Reset pin and set its default state */
	pGPIODriver->pin_init(pResetPin, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
	pGPIODriver->set_pin(pResetPin);

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SW_EN_Pin_Init(void *pSwEnPin)
{
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/* Initialize SW Enable pin and set its default state */
	pGPIODriver->pin_init(pSwEnPin, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
	pGPIODriver->clr_pin(pSwEnPin);

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_Reset(void *pResetPin)
{
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/* Set Reset pin Low for PCA9959_RESET_DELAY_MS */
	pGPIODriver->clr_pin(pResetPin);
	BOARD_DELAY_ms(PCA9959_RESET_DELAY_MS);
	pGPIODriver->set_pin(pResetPin);

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_Output_Enable(void *pOePin)
{
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/* Set OE pin Low */
	pGPIODriver->clr_pin(pOePin);

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_Output_Disable(void *pOePin)
{
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/* Set OE pin High */
	pGPIODriver->set_pin(pOePin);

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_Set_Imax_30MA(void *pImaxPin)
{
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/* Set SwEn pin High */
	pGPIODriver->set_pin(pImaxPin);

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_Set_Imax_20MA(void *pImaxPin)
{
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	/* Set SwEn pin Low */
	pGPIODriver->clr_pin(pImaxPin);

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Enable_Auto_SwitchOff(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Enable auto switch off on error */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE2 ,(uint8_t)(autoDisableOn << PCA9959_AUTO_SWITCH_OFF_DIS_SHIFT) , PCA9959_AUTO_SWITCH_OFF_DIS_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Disable_Auto_SwitchOff(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Disable auto switch off on error */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE2 ,(uint8_t)(autoDisableOff << PCA9959_AUTO_SWITCH_OFF_DIS_SHIFT) , PCA9959_AUTO_SWITCH_OFF_DIS_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Enable_Sleep(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Enable Sleep (Oscillator on) */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE1 ,(uint8_t)(lowPowerMode << PCA9959_SLEEP_SHIFT) , PCA9959_SLEEP_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Disable_Sleep(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Disable Sleep (Oscillator off) */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE1 ,(uint8_t)(normalMode << PCA9959_SLEEP_SHIFT ) , PCA9959_SLEEP_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Check_OvTemp(pca9959_spi_sensorhandle_t *pSensorHandle, TempCondition *tempcondition)
{
	int32_t status;
	PCA9959_MODE_2 Mode2_Reg;

	/*! Validate for the correct handle */
	if ((pSensorHandle == NULL) || (tempcondition == NULL))
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* check over temperature */
	status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE2 , PCA9959_REG_SIZE_BYTE, (uint8_t *)&Mode2_Reg);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	*tempcondition = Mode2_Reg.b.overtemp;

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Use_Ceralock_For_Grad_Ctl(pca9959_spi_sensorhandle_t *pSensorHandle)
{

	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Enable Ceralock Resonator b/w OSCIN and OSCUT for external clock */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE1 ,(uint8_t)(ceraLock << PCA9959_CLK20M_TYP_SHIFT) , PCA9959_CLK20M_TYP_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Use_ExtClk_For_Grad_Ctl(pca9959_spi_sensorhandle_t *pSensorHandle)
{

	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Disable Ceralock Resonator b/w OSCIN and OSCUT for external clock */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE1 ,(uint8_t)(externalClock << PCA9959_CLK20M_TYP_SHIFT) , PCA9959_CLK20M_TYP_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Enable_Turn_On_Delay(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Enable Turn on Delay  */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE1 ,(uint8_t)(OffsetDelayEnable << PCA9959_OFFSET_DIS_SHIFT) , PCA9959_OFFSET_DIS_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Disable_Turn_On_Delay(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Disable Turn on Delay */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE1 ,(uint8_t)(OffsetDelayDisable << PCA9959_OFFSET_DIS_SHIFT) , PCA9959_OFFSET_DIS_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Clear_Error(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/*  clear Error */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE2 ,(uint8_t)( PCA9959_CLRERR << PCA9959_CLRERR_SHIFT) , PCA9959_CLRERR_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Check_Error(pca9959_spi_sensorhandle_t *pSensorHandle, ErrorState *errorstate)
{
	int32_t status;
	PCA9959_MODE_2 Mode2_Reg;

	/*! Validate for the correct handle */
	if ((pSensorHandle == NULL) || (errorstate == NULL))
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/*  check Error */
	status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE2 , PCA9959_REG_SIZE_BYTE, (uint8_t *)&Mode2_Reg);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	*errorstate = Mode2_Reg.b.error;

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_LED_Get_Error_Type(pca9959_spi_sensorhandle_t *pSensorHandle, LedNum lednum, LedErrorType *lederrortype)
{
	int32_t status;
	uint8_t lederr;

	/*! Validate for the correct handle */
	if ((pSensorHandle == NULL) || (lederrortype == NULL))
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Get LED Channel error type */
	status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			(PCA9959_EFLAG0 + (lednum / 4)) , PCA9959_REG_SIZE_BYTE, &lederr);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	*lederrortype = ((lederr >> ((lednum % 4) * 2)) & PCA9959_LED_ERROR_TYPE_MASK);

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Check_Valid_Ext_Clk_Presence(pca9959_spi_sensorhandle_t *pSensorHandle, ExClkPrs *exclkprs)
{
	int32_t status;
	PCA9959_MODE_2 Mode2_Reg;
	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Check Presence of 20MHz External Clock */
	status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_MODE2, PCA9959_REG_SIZE_BYTE, (uint8_t *)&Mode2_Reg);

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	*exclkprs =  Mode2_Reg.b.exclkprs;

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_TStep_Duration_Control(pca9959_spi_sensorhandle_t *pSensorHandle,TStepSelect tstepselect)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Set Time Step Value for duration control */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_GRID_DUR ,(uint8_t)(tstepselect << PCA9959_GRID_DUR_TSTEP_SHIFT ) , PCA9959_GRID_DUR_TSTEP_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_DurCnt_Duration_Control(pca9959_spi_sensorhandle_t *pSensorHandle,durCount durcnt)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Set duration counter for duration control */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_GRID_DUR ,(uint8_t)(durcnt) , PCA9959_GRID_DUR_DURCNT_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Start_Gradation(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Start Gradation */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_GRD_CTL ,(uint8_t)(gradStart << PCA9959_GRID_CTL_GRD_EN_SHIFT) , PCA9959_GRID_CTL_GRD_EN_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Stop_Gradation(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Stop Gradation */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_GRD_CTL ,(uint8_t)(gradStop << PCA9959_GRID_CTL_GRD_DIS_SHIFT) , PCA9959_GRID_CTL_GRD_DIS_MASK);
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Gradation_Mode(pca9959_spi_sensorhandle_t *pSensorHandle, GradOperation gradOperation)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Set Gradation Mode (One-shot/Recurrence) */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_GRD_CTL ,(uint8_t)(((gradOperation == singleShot) ? singleShot : continuous) << PCA9959_GRID_CTL_GRD_MODE_SHIFT) , PCA9959_GRID_CTL_GRD_MODE_MASK);

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Side_Configuration(pca9959_spi_sensorhandle_t *pSensorHandle, SideConfiguration sideConfiguration)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Side Configuration (side0/side1) */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_SIDE_CTL ,(uint8_t)(((sideConfiguration == side0) ? side0 : side1) << PCA9959_SIDE_CTL_SIDE_CFG_SHIFT) , PCA9959_SIDE_CTL_SIDE_CFG_MASK);

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Side_Execute(pca9959_spi_sensorhandle_t *pSensorHandle, SideExecute sideExecute)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Side Execution (side0/side1) */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_SIDE_CTL ,(uint8_t)(((sideExecute == executeSide0) ? executeSide0 : executeSide1)  << PCA9959_SIDE_CTL_SIDE_EXE_SHIFT) , PCA9959_SIDE_CTL_SIDE_EXE_MASK);

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Page_Select(pca9959_spi_sensorhandle_t *pSensorHandle, PageSelect pageSelect)
{
	int32_t status;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Page Select (page0 for gradation configuration and page1 for channel configuration) */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_PAGE_SEL ,(uint8_t)(((pageSelect == page0) ? page0 : page1) << PCA9959_PAGE_SEL_SHIFT) , PCA9959_PAGE_SEL_MASK);

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Grid_Group_Configuration(pca9959_spi_sensorhandle_t *pSensorHandle, GroupNumber groupnumber, GridGroupConf gridgroupconf,endGrid end)
{
	int32_t status;
	uint8_t shift;
	uint8_t mask;
	uint8_t temp;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	switch(groupnumber)
	{
	case group0:   /* Group 0 */
	{
		shift = PCA9959_GROUP0_SHIFT;
		mask = PCA9959_GROUP0_MASK;
		break;
	}
	case group1:   /* Group 1 */
	{
		shift = PCA9959_GROUP1_SHIFT;
		mask = PCA9959_GROUP1_MASK;
		break;
	}
	case group2:   /* Group 2 */
	{
		shift = PCA9959_GROUP2_SHIFT;
		mask = PCA9959_GROUP2_MASK;
		break;
	}
	case group3:  /* Group 3 */
	{
		shift = PCA9959_GROUP3_SHIFT;
		mask = PCA9959_GROUP3_MASK;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}


	switch(gridgroupconf)
	{
	case ledinGyOff:  /* LED in group y in off */
	{
		temp = PCA9959_GDXX_GY_CFG1;
		break;
	}
	case presetCurrent1:  /* Preset Current 1 */
	{
		temp = PCA9959_GDXX_GY_CFG2;
		break;
	}
	case presetCurrent2:  /* Preset Current 2 */
	{
		temp = PCA9959_GDXX_GY_CFG3;
		break;
	}
	case presetCurrent3:  /* Preset Current 3 */
	{
		temp = PCA9959_GDXX_GY_CFG4;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}

	/* Grid-Group Configuration for grids range ( Grids (0-63) Groups (0-3) ) */
	for(int grid=0;grid<=end;grid++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				PCA9959_GRID0 + grid ,(uint8_t)(temp << shift) , mask);

	}

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_All_Grid_Group_Configuration(pca9959_spi_sensorhandle_t *pSensorHandle, GroupNumber groupnumber,GridGroupConf gridgroupconf,endGrid end)
{
	int32_t status;
	uint8_t shift;
	uint8_t mask;
	uint8_t temp;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	switch(groupnumber)
	{
	case group0:  /* Group 0 */
	{
		shift = PCA9959_GROUP0_SHIFT;
		mask = PCA9959_GROUP0_MASK;
		break;
	}
	case group1:  /* Group 1 */
	{
		shift = PCA9959_GROUP1_SHIFT;
		mask = PCA9959_GROUP1_MASK;
		break;
	}
	case group2:   /* Group 2 */
	{
		shift = PCA9959_GROUP2_SHIFT;
		mask = PCA9959_GROUP2_MASK;
		break;
	}
	case group3: /* Group 3 */
	{
		shift = PCA9959_GROUP3_SHIFT;
		mask = PCA9959_GROUP3_MASK;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}


	switch(gridgroupconf)
	{
	case ledinGyOff:  /* LED in group y is off */
	{
		temp = PCA9959_GDXX_GY_CFG1;
		break;
	}
	case presetCurrent1:  /* Preset Current 1 */
	{
		temp = PCA9959_GDXX_GY_CFG2;
		break;
	}
	case presetCurrent2:  /* Preset Current 2 */
	{
		temp = PCA9959_GDXX_GY_CFG3;
		break;
	}
	case presetCurrent3:  /* Preset Current 3 */
	{
		temp = PCA9959_GDXX_GY_CFG4;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}

	/* All Grid-Group Configuration ( Grids (0-63) Groups (0-3) ) */
	for(int grid = 0; grid <= end;grid++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				PCA9959_GRID0 + grid ,(uint8_t)(temp << shift) , mask);
	}

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Range_Grid_Group_Configuration(pca9959_spi_sensorhandle_t *pSensorHandle, GroupNumber groupnumber,GridGroupConf gridgroupconf,endGrid end)
{
	int32_t status;
	uint8_t shift;
	uint8_t mask;
	uint8_t temp;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	switch(groupnumber)
	{
	case group0:  /* Group 0 */
	{
		shift = PCA9959_GROUP0_SHIFT;
		mask = PCA9959_GROUP0_MASK;
		break;
	}
	case group1:  /* Group 1 */
	{
		shift = PCA9959_GROUP1_SHIFT;
		mask = PCA9959_GROUP1_MASK;
		break;
	}
	case group2:   /* Group 2 */
	{
		shift = PCA9959_GROUP2_SHIFT;
		mask = PCA9959_GROUP2_MASK;
		break;
	}
	case group3: /* Group 3 */
	{
		shift = PCA9959_GROUP3_SHIFT;
		mask = PCA9959_GROUP3_MASK;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}


	switch(gridgroupconf)
	{
	case ledinGyOff:  /* LED in group y is off */
	{
		temp = PCA9959_GDXX_GY_CFG1;
		break;
	}
	case presetCurrent1:  /* Preset Current 1 */
	{
		temp = PCA9959_GDXX_GY_CFG2;
		break;
	}
	case presetCurrent2:   /* Preset Current 2 */
	{
		temp = PCA9959_GDXX_GY_CFG3;
		break;
	}
	case presetCurrent3: /* Preset Current 3 */
	{
		temp = PCA9959_GDXX_GY_CFG4;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}

	/* Grid-Group Configuration for grids range ( Grids (0-63) Groups (0-3) ) */
	for(int i=0;i<=end;i++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				PCA9959_GRID0 + i ,(uint8_t)(temp << shift) , mask);

	}
	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Individual_LED_Channel_Enable(pca9959_spi_sensorhandle_t *pSensorHandle, LedNum lednum)
{
	int32_t status;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL) && (lednum > PCA9959_MAX_CHANNELS) )
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Enable Individual LEDs (0-23) */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_CH0_CFG1 + 4 * lednum ,(uint8_t)(ledOutputEnable << CHX_CFG1_CHX_EN_SHIFT) , CHX_CFG1_CHX_EN_MASK);


	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Individual_LED_Channel_Disable(pca9959_spi_sensorhandle_t *pSensorHandle, LedNum lednum)
{
	int32_t status;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL) )
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Disable Individual LEDs (0-23) */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			(PCA9959_CH0_CFG1 + (4 * lednum)) ,(uint8_t)(ledOutputDisable << CHX_CFG1_CHX_DIS_SHIFT) , CHX_CFG1_CHX_DIS_MASK);


	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_All_LED_Channel_Enable(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;
	uint8_t ledChannels;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL) )
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Enable All LEDs (0-23) */
	for(int led = 0; led <= PCA9959_MAX_CHANNELS;led++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				(PCA9959_CH0_CFG1 + (4*led)) ,(uint8_t)(ledOutputEnable << CHX_CFG1_CHX_EN_SHIFT) , CHX_CFG1_CHX_EN_MASK);
	}

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Range_LED_Channel_Enable(pca9959_spi_sensorhandle_t *pSensorHandle,startLed start, endLed end)
{


	int32_t status;
	uint8_t ledChannels;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL) )
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Enable LEDs in range (0-23) */
	for(int led = start; led <= end;led++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				(PCA9959_CH0_CFG1 + (4*led)) ,(uint8_t)(ledOutputEnable << CHX_CFG1_CHX_EN_SHIFT) , CHX_CFG1_CHX_EN_MASK);
	}

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_All_LED_Channel_Disable(pca9959_spi_sensorhandle_t *pSensorHandle)
{
	int32_t status;
	uint8_t ledChannels;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL) )
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}


	/* Disable All LEDs (0-23) */
	for(int led = 0; led <= PCA9959_MAX_CHANNELS ;led++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				(PCA9959_CH0_CFG1 + (4*led)) ,(uint8_t)(ledOutputDisable << CHX_CFG1_CHX_DIS_SHIFT) , CHX_CFG1_CHX_DIS_MASK);
	}


	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_Range_LED_Channel_Disable(pca9959_spi_sensorhandle_t *pSensorHandle,startLed start, endLed end)
{
	int32_t status;
	uint8_t ledChannels;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL) )
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Disable LEDs in range (0-23) */
	for(int led = start; led <= end;led++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				(PCA9959_CH0_CFG1 + (4*led)) ,(uint8_t)(ledOutputDisable << CHX_CFG1_CHX_DIS_SHIFT) , CHX_CFG1_CHX_DIS_MASK);
	}


	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_LED_ChannelX_Group_Assignment(pca9959_spi_sensorhandle_t *pSensorHandle, CHxgroupAssign chxgroupassign, LedNum lednum)
{
	int32_t status;
	uint8_t temp;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL) && (lednum > PCA9959_MAX_CHANNELS))
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	switch(chxgroupassign)
	{
	case assignLEDToGroup0:  /* Assign LED to Group 0 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP0;
		break;
	}
	case assignLEDToGroup1:  /* Assign LED to Group 1 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP1;
		break;
	}
	case assignLEDToGroup2:   /* Assign LED to Group 2 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP2;
		break;
	}
	case assignLEDToGroup3: /* Assign LED to Group 3 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP3;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}

	/* Assign Individual LEDs to a particular group */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			PCA9959_CH0_CFG1 + 4 * lednum ,(uint8_t)(temp << CHX_CFG1_CHX_GRP_ASSIGN_SHIFT) , CHX_CFG1_CHX_GRP_ASSIGN_MASK);

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}


int32_t PCA9959_SPI_All_LED_ChannelX_Group_Assignment(pca9959_spi_sensorhandle_t *pSensorHandle, CHxgroupAssign chxgroupassign)
{
	int32_t status;
	uint8_t temp;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL))
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	switch(chxgroupassign)
	{
	case assignLEDToGroup0:  /* Assign LED to Group 0 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP0;
		break;
	}
	case assignLEDToGroup1:  /* Assign LED to Group 1 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP1;
		break;
	}
	case assignLEDToGroup2:   /* Assign LED to Group 2 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP2;
		break;
	}
	case assignLEDToGroup3: /* Assign LED to Group 3 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP3;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}
	/* Assign All LEDs to a particular group */
	for(int led = 0; led <= PCA9959_MAX_CHANNELS;led++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				PCA9959_CH0_CFG1 + 4 * led ,(uint8_t)(temp << CHX_CFG1_CHX_GRP_ASSIGN_SHIFT) , CHX_CFG1_CHX_GRP_ASSIGN_MASK);
	}


	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Range_LED_ChannelX_Group_Assignment(pca9959_spi_sensorhandle_t *pSensorHandle, CHxgroupAssign chxgroupassign,startLed start, endLed end)

{
	int32_t status;
	uint8_t temp;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL))
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	switch(chxgroupassign)
	{
	case assignLEDToGroup0:  /* Assign LED to Group 0 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP0;
		break;
	}
	case assignLEDToGroup1:  /* Assign LED to Group 1 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP1;
		break;
	}
	case assignLEDToGroup2:   /* Assign LED to Group 2 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP2;
		break;
	}
	case assignLEDToGroup3: /* Assign LED to Group 3 */
	{
		temp = PCA9959_ASSIGN_LED_TO_GROUP3;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}

	/* Assign LEDs in x-y range to a particular group */
	for(int led = start; led <= end;led++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				(PCA9959_CH0_CFG1 + (4 * (led))) ,(uint8_t)(temp << CHX_CFG1_CHX_GRP_ASSIGN_SHIFT) , CHX_CFG1_CHX_GRP_ASSIGN_MASK);
	}


	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;

}

int32_t PCA9959_SPI_LED_Channel_PresetCurrent(pca9959_spi_sensorhandle_t *pSensorHandle, LedNum lednum, LedBrightness brightness,PresetCurrent presetcurrent)
{
	int32_t status;
	uint8_t reg,mask;

	/*! Validate for the correct handle */
	if ( (pSensorHandle == NULL) && (lednum <= PCA9959_MAX_CHANNELS) )
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	switch(presetcurrent)
	{
	case presetCurrent1:   /* Preset Current 1 */
	{
		reg = PCA9959_CH0_CFG2;
		mask = CHX_CFG2_MASK;
		break;
	}
	case presetCurrent2:    /* Preset Current 2 */
	{
		reg = PCA9959_CH0_CFG3;
		mask = CHX_CFG3_MASK;
		break;
	}
	case presetCurrent3:  /* Preset Current 3 */
	{
		reg = PCA9959_CH0_CFG4;
		mask = CHX_CFG4_MASK;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}
	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	/* Set Preset Current Values for Individual LED channels */
	status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
			(reg + (4 * (lednum))) ,(uint8_t)(brightness) , mask);

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}



int32_t PCA9959_SPI_All_LED_Channel_PresetCurrent(pca9959_spi_sensorhandle_t *pSensorHandle, LedBrightness brightness,PresetCurrent presetcurrent)
{
	int32_t status;
	uint8_t reg,mask;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL )
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	switch(presetcurrent)
	{
	case pc1:  /* Preset Current 1 */
	{
		reg = PCA9959_CH0_CFG2;
		mask = CHX_CFG2_MASK;
		break;
	}
	case pc2:    /* Preset Current 2 */
	{
		reg = PCA9959_CH0_CFG3;
		mask = CHX_CFG3_MASK;
		break;
	}
	case pc3:  /* Preset Current 3 */
	{
		reg = PCA9959_CH0_CFG4;
		mask = CHX_CFG4_MASK;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}

	/* Set Preset Current Values for all LED channels */
	for(int led = 0; led <= PCA9959_MAX_CHANNELS;led++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				(reg + (4 * led)) ,(uint8_t)(brightness) , mask);
	}

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

int32_t PCA9959_SPI_Range_LED_Channel_PresetCurrent(pca9959_spi_sensorhandle_t *pSensorHandle, LedBrightness brightness,PresetCurrent presetcurrent,startLed start, endLed end)
{
	int32_t status;
	uint8_t reg,mask;

	/*! Validate for the correct handle */
	if (pSensorHandle == NULL )
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	/*! Check whether sensor handle is initialized before triggering sensor reset.*/
	if (pSensorHandle->isInitialized != true)
	{
		return SENSOR_ERROR_INIT;
	}

	switch(presetcurrent)
	{
	case pc1:  /* Preset Current 1 */
	{
		reg = PCA9959_CH0_CFG2;
		mask = CHX_CFG2_MASK;
		break;
	}
	case pc2:   /* Preset Current 2 */
	{
		reg = PCA9959_CH0_CFG3;
		mask = CHX_CFG3_MASK;
		break;
	}
	case pc3: /* Preset Current 3 */
	{
		reg = PCA9959_CH0_CFG4;
		mask = CHX_CFG4_MASK;
		break;
	}
	default:
	{
		return SENSOR_ERROR_INVALID_PARAM;
		break;
	}
	}

	/* Set Preset Current Values for LED channels in range */
	for(int led = start; led <= end;led++)
	{
		status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
				(reg + (4 * led)) ,(uint8_t)(brightness) , mask);
	}

	if (ARM_DRIVER_OK != status)
	{
		return SENSOR_ERROR_WRITE;
	}

	return SENSOR_ERROR_NONE;
}

