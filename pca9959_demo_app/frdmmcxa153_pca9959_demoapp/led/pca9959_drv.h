/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file pca9959_drv.h
 * @brief The pca9959_drv.h file describes the PCA9959 driver interface and structures.
 */

#ifndef PCA9959_DRV_H_
#define PCA9959_DRV_H_

/* Standard C Includes */
#include <stdint.h>

/* ISSDK Includes */
#include "sensor_io_i2c.h"
#include "sensor_io_spi.h"
#include "register_io_i2c.h"
#include "register_io_spi.h"
#include "pca9959.h"

/*--------------------------------
** Enum: SLEEPCONTROL
** @brief Normal mode / Low-power mode
** ------------------------------*/
typedef enum SLEEPCONTROL
{
	normalMode  = 0x00,                   /* Normal mode */
	lowPowerMode = 0x01,                  /* Low-power mode (Oscillator off)*/
}SleepControl;

/*--------------------------------
** Enum: OFFSETDISABLE
** @brief offset delay of 50ns
** ------------------------------*/
typedef enum OFFSETDISABLE
{
	delayOffset = 0x00,                      /* 50 ns delay offset between channel(x) and channel(x+1) */
	nodelayOffset = 0x01,                   /* no delay offset */
}OffsetDisable;

/*--------------------------------
** Enum: CLK20MTYP
** @brief 20MHz CeraClock or External Clock for gradation control
** ------------------------------*/
typedef enum CLK20MTYP
{
	ceraLock= 0x00,                        /* Use 20MHz ceraclock */
	externalClock = 0x01,                   /* use 20MHz External Clock */
}Clk20MTyp;


/*--------------------------------
** Enum: AUTOSWITCHOFF
** @brief Auto Led channel output off on error
** ------------------------------*/
typedef enum AUTO_SWITCHOFF
{
	autoDisableOn = 0x00,                  /* Turned off when open/short detected */
	autoDisableOff = 0x01,                 /* won’t be turned off when open/short detected */
}AutoSwitchOff;

/*--------------------------------
** Enum: CLRERROR
** @brief Clear Errors
** ------------------------------*/
typedef enum CLRERROR
{
	autoClear = 0x00,                  /* self clear after write 1 */
	manualClear = 0x01,                 /* Write 1 to clear all error status bits in EFLAGn register and ERROR (bit 6) */
}ClrError;

/*--------------------------------
** Enum: EXCLKPRS
** @brief External clock presence
** ------------------------------*/
typedef enum EXCLKPRS
{
	extClockAbsent = 0x00,                  /* no valid external clock presented */
	extClockPresent = 0x01,                 /*external clock detected in correct range */
}ExClkPrs;

/*--------------------------------
** Enum: ERRORSTATE
** @brief Led channel output error state
** ------------------------------*/
typedef enum ERRORSTATE
{
	errorNotDetected = 0x00,                /* Error Not detected */
	errorDetected = 0x01,                   /* Error detected */
}ErrorState;

/*--------------------------------
** Enum: TEMPCONDITION
** @brief Operating temperature condition
** ------------------------------*/
typedef enum TEMPCONDITION
{
	underTemp = 0x00,                  /* under temperature condition */
	overTemp = 0x01,                   /* over temperature condition */
}TempCondition;

/*--------------------------------
** Enum: TSTEPSELECT
** @brief TStep Select
** ------------------------------*/
typedef enum TSTEPSELECT
{
	twoAndHalfMicroSeconds = 0x00,               /* 2.5 Micro Second */
	fiveMicroSeconds = 0x01,               		 /* 5 Micro Second */
	tenMicroSeconds = 0x02,                		 /* 10 Micro Second */
	twentyMicroSeconds = 0x03,                   /* 20 Micro Second */
}TStepSelect;

/*--------------------------------
** Enum: GRADCONTROL
** @brief Gradation Control
** ------------------------------*/
typedef enum GRADCONTROL
{
	gradStop = 0x00,                        /* Gradation stop  */
	gradStart = 0x01,                       /* Gradation start */
}GradControl;

/*--------------------------------
** Enum: GRADOPERATION
** @brief Gradation Operation (Single / Continuous) shot
** ------------------------------*/
typedef enum GRADOPERATION
{
	singleShot = 0x00,                       /* Single shot operation */
	continuous = 0x01,                       /* Continuous operation  */
}GradOperation;

/*--------------------------------
** Enum: SIDECONFIGURATION
** @brief Side configuration (side0/side1)
** ------------------------------*/
typedef enum SIDECONFIGURATION
{
	side0 = 0x00,                       /* side 0 */
	side1 = 0x01,                       /* side 1  */
}SideConfiguration;

/*--------------------------------
** Enum: SIDEEXECUTE
** @brief Side Execute (side0/side1)
** ------------------------------*/
typedef enum SIDEEXECUTE
{
	executeSide0 = 0x00,                       /* side 0 */
	executeSide1 = 0x01,                       /* side 1 */
}SideExecute;

/*--------------------------------
** Enum: PAGESELECT
** @brief select Page0 for Grid configuration, Page 1 for channel configuration
** ------------------------------*/
typedef enum PAGESELECT
{
	page0 = 0x00,                       /* page 0 */
	page1 = 0x01,                       /* page 1 */
}PageSelect;

/*--------------------------------
** Enum: GRIDGROUPCONF
** @brief GRID0-63_Group1-4 settings
** ------------------------------*/
typedef enum GRIDGROUPCONF
{
	ledinGyOff = 0x00,                   /* Led in Group y is off */
	presetCurrent1 = 0x01,               /* preset current 1 */
	presetCurrent2 = 0x02,               /* preset current 2 */
	presetCurrent3 = 0x03,               /* preset current 3 */
}GridGroupConf;


/*--------------------------------
** Enum: PRESETCURRENT
** @brief Preset Current (1-3)
** ------------------------------*/
typedef enum PRESETCURRENT
{
	pc1 = 0x01,               /* preset current 1 */
	pc2 = 0x02,               /* preset current 2 */
	pc3 = 0x03,               /* preset current 3 */
}PresetCurrent;


/*--------------------------------
** Enum: CHXEN
** @brief CH0-23 Output Enable/Disable
** ------------------------------*/
typedef enum CHXEN
{
	ledOutputDisable = 0x00,             /* LED Output Disable */
	ledOutputEnable = 0x01,             /* LED Output Enable */
}CHxEn;

/*--------------------------------
** Enum: CHXGRPASSIGN
** @brief CH0-23 Group Assignment
** ------------------------------*/
typedef enum CHXGRPASSIGN
{
	assignLEDToGroup0 = 0x00,             			/* group 0 */
	assignLEDToGroup1 = 0x01,             			/* group 1 */
	assignLEDToGroup2 = 0x02,             			/* group 2 */
	assignLEDToGroup3 = 0x03,             			/* group 3 */
}CHxgroupAssign;


/*--------------------------------
** Enum: GROUPNUMBER
** @brief Group Number
** ------------------------------*/
typedef enum GROUPNUMBER
{
	group0 = 0x00,             			/* group 0 */
	group1 = 0x01,             			/* group 1 */
	group2 = 0x02,             			/* group 2 */
	group3 = 0x03,             			/* group 3 */
}GroupNumber;

/*--------------------------------
** Enum: OFFSETDIS
** @brief 50ns turn on delay between channel(x) and channel(x+1)
** ------------------------------*/
typedef enum OFFSETDIS
{
	OffsetDelayEnable = 0x00,             /* LED Offset Delay Enable  */
	OffsetDelayDisable = 0x01,            /* LED Offset Delay Disable */
}OffsetDis;

/*--------------------------------
** Enum: LEDERRORTYPE
** @brief Led channel output error
** ------------------------------*/
typedef enum LEDERRORTYPE
{
	noError = 0x00,                  /* In normal operation and no errorn */
	shortCircuit = 0x01,             /* Detected LED short-circuit condition */
	openCircuit = 0x02,              /* Detected LED open-circuit condition */
}LedErrorType;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief This defines the sensor specific information for SPI.
 */
typedef struct
{
    registerDeviceInfo_t deviceInfo;      /*!< SPI device context. */
    ARM_DRIVER_SPI *pCommDrv;             /*!< Pointer to the spi driver. */
    bool isInitialized;                   /*!< Whether sensor is intialized or not.*/
    spiSlaveSpecificParams_t slaveParams; /*!< Slave Specific Params.*/
} pca9959_spi_sensorhandle_t;


/*! @def    PCA9959_SPI_MAX_MSG_SIZE
 *  @brief  The MAX size of SPI message. */
#define PCA9959_SPI_MAX_MSG_SIZE               (64)

/*! @def    PCA9959_SPI_CMD_LEN
 *  @brief  The size of the Sensor specific SPI Header. */
#define PCA9959_SPI_CMD_LEN                    (1)

/*! @def    PCA9959_SS_ACTIVE_VALUE
 *  @brief  Is the Slave Select Pin Active Low or High. */
#define PCA9959_SS_ACTIVE_VALUE                SPI_SS_ACTIVE_LOW

/*! @def    PCA9959_SPI_WR_CMD
 *  @brief  write command of PCA9959 LED Driver */
#define PCA9959_SPI_WR_CMD                     (0xFE)

/*! @def    PCA9959_SPI_RD_CMD
 *  @brief  Read command of PCA9959 LED Driver */
#define PCA9959_SPI_RD_CMD                     (0x01)

/*! @def    PCA9959_MAX_LED_PORT
 *  @brief  Maximum LED Driver port */
#define PCA9959_MAX_LED_PORT                   (23)

/*! @def    PCA9959_RESET_DELAY_MS
 *  @brief  Reset Delay MS */
#define PCA9959_RESET_DELAY_MS                 (0x0A)

/*! @def    PCA9959_ALL_BIT_ONE
 *  @brief  All Bit One  */
#define PCA9959_ALL_BIT_ONE                    (0xFF)


/*! @def    PCA9959_REG_SIZE_BYTE
 *  @brief  Register Size  */
#define PCA9959_REG_SIZE_BYTE                  (0x01)


/*! @def    PCA9959_MAX_GRIDS
 *  @brief  64 grids  */
#define PCA9959_MAX_GRIDS					   (63)


/*! @def    PCA9959_MAX_GROUPS
 *  @brief  4 gorups  */
#define PCA9959_MAX_GROUPS					   (4)


/*! @def    PCA9959_MAX_CHANNELS
 *  @brief  24 channels  */
#define PCA9959_MAX_CHANNELS				   (23)


/*! @def     PCA9959_ASSIGN_LED_TO_GROUP0
 *  @brief   PCA9959 Assign LED to group 0 */
#define PCA9959_ASSIGN_LED_TO_GROUP0   			(0x00)

/*! @def     PCA9959_ASSIGN_LED_TO_GROUP1
 *  @brief   PCA9959 Assign LED to group 0 */
#define PCA9959_ASSIGN_LED_TO_GROUP1   			(0x01)

/*! @def     PCA9959_ASSIGN_LED_TO_GROUP2
 *  @brief   PCA9959 Assign LED to group 0 */
#define PCA9959_ASSIGN_LED_TO_GROUP2  			(0x02)

/*! @def    PCA9959_ASSIGN_LED_TO_GROUP3
 *  @brief   PCA9959 Assign LED to group 0 */
#define PCA9959_ASSIGN_LED_TO_GROUP3  			(0x03)


/*! @def     PCA9959_GDXX_GY_CFG1
 *  @brief   PCA9959 LED in Group y is off */
#define  PCA9959_GDXX_GY_CFG1   				(0x00)

/*! @def     PCA9959_GDXX_GY_CFG2
 *  @brief   PCA9959 Drive preset current1 set in corresponding register CHx_CFG2 to LED */
#define PCA9959_GDXX_GY_CFG2   					(0x01)

/*! @def     PCA9959_GDXX_GY_CFG3
 *  @brief   PCA9959 Drive preset current1 set in corresponding register CHx_CFG3 to LED */
#define PCA9959_GDXX_GY_CFG3  					(0x02)

/*! @def    PCA9959_GDXX_GY_CFG4
 *  @brief   PCA9959 Drive preset current1 set in corresponding register CHx_CFG4 to LED */
#define PCA9959_GDXX_GY_CFG4  					(0x03)

/*! @def    PCA9959_CLRERR
 *  @brief  Clear Error */
#define PCA9959_CLRERR                          (0x01)

/*! @def    PCA9959_LED_ERROR_TYPE_MASK
 *  @brief  LED error clear Mask */
#define PCA9959_LED_ERROR_TYPE_MASK             (0x03)

/* Led Brightness */
typedef uint8_t LedBrightness;

/* Led NUmber */
typedef uint8_t LedNum;

/* grid NUmber */
typedef uint8_t GDxxGy;

/* group NUmber */
typedef uint8_t groupNum;

/* duration counter */
typedef uint8_t durCount;

/* grid number */
typedef uint8_t gridNum;

/* Starting Grid for Range Configuration */
typedef uint8_t startGrid;

/* Ending Grid for Range Configuration */
typedef uint8_t endGrid;

/* Starting LED for Range Configuration */
typedef uint8_t startLed;

/* Ending LED for Range Configuration */
typedef uint8_t endLed;


/*******************************************************************************
 * APIs
 ******************************************************************************/

/*! @brief       Preprocesses a read command for the PCA9959 LED Driver.
 *  @details     Prepares a read command to be sent to the sensor.
 *  @param[in]   pCmdOut  		Pointer to the command output buffer.
 *  @param[in]   offset   		Offset for the read command.
 *  @param[in]   size     		Size of the read command.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant  No
 */
void PCA9959_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size);

/*! @brief       Preprocesses a write command for the PCA9959 LED Driver.
 *  @details     Prepares a write command to be sent to the sensor.
 *  @param[in]   pCmdOut  		Pointer to the command output buffer.
 *  @param[in]   offset  		Offset for the write command.
 *  @param[in]   size     		Size of the write command.
 *  @param[in] 	 pWritebuffer 	Pointer to the buffer containing data to be written.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant  No
 */
void PCA9959_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer);

/*! @brief       Initializes the PCA9959 LED Driver.
 *  @details     Initializes the PCA9959 LED Driver and its handle.
 *  @param[in]   pSensorHandle  Pointer to sensor handle structure.
 *  @param[in]   pBus  			Pointer to CMSIS API compatible SPI bus object.
 *  @param[in]   index     		Index of the sensor.
 *  @param[in] 	 pSlaveSelect 	Pointer to the slave select pin.
 *  @constraints This should be the first API to be called.
 *				 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Initialize() returns the status
 */
int32_t PCA9959_SPI_Initialize(pca9959_spi_sensorhandle_t *pSensorHandle, ARM_DRIVER_SPI *pBus, uint8_t index, void *pSlaveSelect);

/*! @brief       Sets an idle task for the PCA9959 LED Driver.
 *  @details     Sets a function to be called when the sensor is in idle state.
 *  @param[in]   pSensorHandle  	Pointer to sensor handle structure.
 *  @param[in]   idleTask  			Function Pointer to the idle task.
 *  @param[in]   userParam     		Pointer to user defined parameter for the idle task.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 */
void PCA9959_SPI_SetIdleTask(pca9959_spi_sensorhandle_t *pSensorHandle, registeridlefunction_t idleTask, void *userParam);

/*! @brief       Configures the PCA9959 LED Driver.
 *  @details     Initializes the PCA9959 LED Driver and its handle.
 *  @param[in]   pSensorHandle  	Pointer to sensor handle structure.
 *  @param[in]   pRegWriteList      Pointer to the list of register write operations.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Configue() returns the status.
 */
int32_t PCA9959_SPI_Configure(pca9959_spi_sensorhandle_t *pSensorHandle, const registerwritelist_t *pRegWriteList);

/*! @brief       De-initializes the PCA9959 LED Driver.
 *  @details     De-initializes the PCA9959 LED Driver and its handle.
 *  @param[in]   pSensorHandle  	Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return     ::PCA9959_SPI_Deinit() returns the status.
 */
int32_t PCA9959_SPI_Deinit(pca9959_spi_sensorhandle_t *pSensorHandle, void *pResetPin);

/*! @brief      Initialize PCA9959 OE pin.
*  @details     make OE pin as output and set its default state to high .
*  @param[in]   pOePin  	   Pointer to gpioHandleKSDK_t.
*  @constraints No
*  @reentrant   No
*  @return      ::PCA9959_OE_Pin_Init() returns the status.
*/
int32_t PCA9959_OE_Pin_Init(void *pOePin);

/*! @brief       Initialize PCA9959 RESET pin.
 *  @details     make Reset pin as output and set its default state to high .
 *  @param[in]   pOePin  	   Pointer to gpioHandleKSDK_t.
 *  @constraints No
 *  @reentrant   No
 *  @return      ::PCA9959_Reset_Pin_Init() returns the status.
 */
int32_t PCA9959_Reset_Pin_Init(void *pResetPin);

/*! @brief       Initialize PCA9959 SW EN pin.
 *  @details     make SW EN pin as output and set its default state to clear .
 *  @param[in]   pOePin  	   Pointer to gpioHandleKSDK_t.
 *  @constraints No
 *  @reentrant   No
 *  @return      ::PCA9959_SW_EN_Pin_Init() returns the status.
 */
int32_t PCA9959_SW_EN_Pin_Init(void *pSwEnPin);

/*! @brief       Reset PCA9959.
 *  @details     Set Reset pin as low for PCA9959_RESET_DELAY_MS.
 *  @param[in]   pOePin  	   Pointer to gpioHandleKSDK_t.
 *  @constraints This can be called any number of times only after PCA9959_Reset_Pin_Init().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reentrant   No
 *  @return      ::PCA9959_Reset() returns the status.
 */
int32_t PCA9959_Reset(void *pResetPin);

/*! @brief       Enable OE pin.
 *  @details     Set OE pin as low.
 *  @param[in]   pOePin  	   Pointer to gpioHandleKSDK_t.
 *  @constraints This can be called any number of times only after PCA9959_OE_Pin_Init().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reentrant   No
 *  @return      ::PCA9959_Output_Enable() returns the status.
 */
int32_t PCA9959_Output_Enable(void *pOePin);

/*! @brief       Disable OE pin.
 *  @details     Set OE pin as High.
 *  @param[in]   pOePin  	   Pointer to gpioHandleKSDK_t.
 *  @constraints This can be called any number of times only after PCA9959_OE_Pin_Init().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reentrant   No
 *  @return      ::PCA9959_Output_Disable() returns the status.
 */
int32_t PCA9959_Output_Disable(void *pOePin);

/*! @brief       Set maximum current to 30 MA.
 *  @details     Set SwEn pin as High.
 *  @param[in]   pOePin  	   Pointer to gpioHandleKSDK_t.
 *  @constraints This can be called any number of times only after PCA9957_SW_EN_Pin_Init().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reentrant   No
 *  @return      ::PCA9957_Set_Imax_30MA() returns the status.
 */
int32_t PCA9959_Set_Imax_30MA(void *pImaxPin);

/*! @brief       Set maximum current to 20 MA.
 *  @details     Set SwEn pin as Low.
 *  @param[in]   pOePin  	   Pointer to gpioHandleKSDK_t.
 *  @constraints This can be called any number of times only after PCA9957_SW_EN_Pin_Init().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reentrant   No
 *  @return      ::PCA9957_Set_Imax_20MA() returns the status.
 */
int32_t PCA9959_Set_Imax_20MA(void *pImaxPin);

/*! @brief       Enable Auto switch off.
 *  @details     Enable Auto switch off.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Enable_Auto_SwitchOff() returns the status.
 */
int32_t PCA9959_SPI_Enable_Auto_SwitchOff(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       Disable Auto switch off.
 *  @details     Disable Auto switch off.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Disable_Auto_SwitchOff() returns the status.
 */
int32_t PCA9959_SPI_Disable_Auto_SwitchOff(pca9959_spi_sensorhandle_t *pSensorHandle);


/*! @brief       Disable Sleep.
 *  @details     Disable Sleep.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Disable_Sleep() returns the status.
 */
int32_t PCA9959_SPI_Disable_Sleep(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       Enable Sleep.
 *  @details     Enable Sleep.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Enable_Sleep() returns the status.
 */
int32_t PCA9959_SPI_Enable_Sleep(pca9959_spi_sensorhandle_t *pSensorHandle);


/*! @brief       check Over Temperature.
 *  @details     clear Over Temperature for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Check_OvTemp() returns the status.
 */
int32_t PCA9959_SPI_Check_OvTemp(pca9959_spi_sensorhandle_t *pSensorHandle, TempCondition *tempcondition);

/*! @brief       Enable Ceralock resonator.
 *  @details     Enable Ceralock resonator for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Enable_Ceralock_ExtClk_For_Grad_Ctl() returns the status.
 */
int32_t PCA9959_SPI_Use_Ceralock_For_Grad_Ctl(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       Disable Ceralock resonator.
 *  @details     Disable Ceralock resonator for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Disable_Ceralock_ExtClk_For_Grad_Ctl() returns the status.
 */
int32_t PCA9959_SPI_Use_ExtClk_For_Grad_Ctl(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       Enable 50ns Turn on Delay between LED outputs.
 *  @details     Enable 50ns Turn on Delay between LED outputs for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Enable_Turn_On_Delay() returns the status.
 */
int32_t PCA9959_SPI_Enable_Turn_On_Delay(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       Disable 50ns Turn on Delay between LED outputs.
 *  @details     Disable 50ns Turn on Delay between LED outputs for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Disable_Turn_On_Delay() returns the status.
 */
int32_t PCA9959_SPI_Disable_Turn_On_Delay(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       Clear Error.
 *  @details     clear error for LED channel.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Clear_Error() returns the status.
 */
int32_t PCA9959_SPI_Clear_Error(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       check Error.
 *  @details     clear error (open or short) for any LED channel.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Check_Error() returns the status.
 */
int32_t PCA9959_SPI_Check_Error(pca9959_spi_sensorhandle_t *pSensorHandle, ErrorState *errorstate);

/*! @brief       Get error type.
 *  @details     Get error type for LED channel.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @param[in]   lednum                LED channel.
 *  @param[out]  lederrortype          LED error type.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_LED_Get_Error_Type() returns the status.
 */
int32_t PCA9959_SPI_LED_Get_Error_Type(pca9959_spi_sensorhandle_t *pSensorHandle, LedNum lednum, LedErrorType *lederrortype);

/*! @brief       Check External Clock Presence.
 *  @details     Check External Clock Presence for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @param[in]   lednum                LED channel.
 *  @param[out]  lederrortype          LED error type.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Check_Valid_Ext_Clk_Presence() returns the status.
 */
int32_t PCA9959_SPI_Check_Valid_Ext_Clk_Presence(pca9959_spi_sensorhandle_t *pSensorHandle, ExClkPrs *exclkprs);


/*! @brief       set Time Step for duration control.
 *  @details     set Time Step for duration control for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_TStep_Gradation_Control() returns the status.
 */
int32_t PCA9959_SPI_TStep_Duration_Control(pca9959_spi_sensorhandle_t *pSensorHandle,TStepSelect tstepselect);


/*! @brief       set counter for duration control.
 *  @details     set counter for duration control for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_DurCnt_Duration_Control() returns the status.
 */
int32_t PCA9959_SPI_DurCnt_Duration_Control(pca9959_spi_sensorhandle_t *pSensorHandle,durCount durcnt);

/*! @brief       start gradation control.
 *  @details     start gradation control control for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Start_Gradation() returns the status.
 */
int32_t PCA9959_SPI_Start_Gradation(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       stop gradation control.
 *  @details     stop gradation control control for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Stop_Gradation() returns the status.
 */
int32_t PCA9959_SPI_Stop_Gradation(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       set Gradation Mode.
 *  @details     set gradation Mode for PCA9959.
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Gradation_Mode() returns the status.
 */
int32_t PCA9959_SPI_Gradation_Mode(pca9959_spi_sensorhandle_t *pSensorHandle, GradOperation gradOperation);

/*! @brief       side configuration.
 *  @details     side configuration for PCA9959 (0 for One-Short Mode, 1 for Recurrence Mode).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Side_Configuration() returns the status.
 */
int32_t PCA9959_SPI_Side_Configuration(pca9959_spi_sensorhandle_t *pSensorHandle, SideConfiguration sideConfiguration);

/*! @brief       side execution.
 *  @details     side execution for PCA9959 (0 for executing side0, 1 for executing side1).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Side_Execute() returns the status.
 */
int32_t PCA9959_SPI_Side_Execute(pca9959_spi_sensorhandle_t *pSensorHandle, SideExecute sideExecute);


/*! @brief       page selection.
 *  @details     page selection for PCA9959 (0 for selecting page0, 1 for selecting page1).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Page_Select() returns the status.
 */
int32_t PCA9959_SPI_Page_Select(pca9959_spi_sensorhandle_t *pSensorHandle, PageSelect pageSelect);

/*! @brief       Individual Grid Group Configuration.
 *  @details     Individual Grid Group Configuration for PCA9959 (grids 0-63 groups 0-3).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Grid_Group_Configuration() returns the status.
 */
int32_t PCA9959_SPI_Grid_Group_Configuration(pca9959_spi_sensorhandle_t *pSensorHandle, GroupNumber groupnumber, GridGroupConf gridgroupconf,endGrid end);

/*! @brief       All Grid Group Configuration.
 *  @details     All Grid Group Configuration for PCA9959 (grids 0-63 groups 0-3).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_All_Grid_Group_Configuration() returns the status.
 */
int32_t PCA9959_SPI_All_Grid_Group_Configuration(pca9959_spi_sensorhandle_t *pSensorHandle, GroupNumber groupnumber,GridGroupConf gridgroupconf,endGrid end);

/*! @brief       Range Grid Group Configuration.
 *  @details     Range Grid Group Configuration for PCA9959 (grids 0-63 groups 0-3).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Range_Grid_Group_Configuration() returns the status.
 */
int32_t PCA9959_SPI_Range_Grid_Group_Configuration(pca9959_spi_sensorhandle_t *pSensorHandle, GroupNumber groupnumber,GridGroupConf gridgroupconf, endGrid end);

/*! @brief       Individual LED channel enable.
 *  @details     Individual LED channel enable for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Individual_LED_Channel_Enable() returns the status.
 */
int32_t PCA9959_SPI_Individual_LED_Channel_Enable(pca9959_spi_sensorhandle_t *pSensorHandle, LedNum lednum);

/*! @brief       Individual LED channel disable.
 *  @details     Individual LED channel disable for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Individual_LED_Channel_Disable() returns the status.
 */
int32_t PCA9959_SPI_Individual_LED_Channel_Disable(pca9959_spi_sensorhandle_t *pSensorHandle, LedNum lednum);

/*! @brief       All LED channel enable.
 *  @details     All LED channel enable for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_All_LED_Channel_Enable() returns the status.
 */
int32_t PCA9959_SPI_All_LED_Channel_Enable(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       All LED channel disable.
 *  @details     All LED channel disable for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_All_LED_Channel_Disable() returns the status.
 */
int32_t PCA9959_SPI_All_LED_Channel_Disable(pca9959_spi_sensorhandle_t *pSensorHandle);

/*! @brief       Range LED channel enable.
 *  @details     Range LED channel enable for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Range_LED_Channel_Enable() returns the status.
 */
int32_t PCA9959_SPI_Range_LED_Channel_Enable(pca9959_spi_sensorhandle_t *pSensorHandle,startLed start, endLed end);

/*! @brief       Range LED channel disable.
 *  @details     Range LED channel disable for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Range_LED_Channel_Disable() returns the status.
 */
int32_t PCA9959_SPI_Range_LED_Channel_Disable(pca9959_spi_sensorhandle_t *pSensorHandle,startLed start, endLed end);

/*! @brief       Assign Indiviual LEDs to a group.
 *  @details     Assign Indiviual LEDs to a group for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_LED_ChannelX_Group_Assignment() returns the status.
 */
int32_t PCA9959_SPI_LED_ChannelX_Group_Assignment(pca9959_spi_sensorhandle_t *pSensorHandle, CHxgroupAssign chxgroupassign,LedNum lednum);

/*! @brief       All LEDs to a group.
 *  @details     All LEDs to a group for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_All_LED_ChannelX_Group_Assignment() returns the status.
 */
int32_t PCA9959_SPI_All_LED_ChannelX_Group_Assignment(pca9959_spi_sensorhandle_t *pSensorHandle, CHxgroupAssign chxgroupassign);

/*! @brief       LEDs in a range to a group.
 *  @details     LEDs in a range to a group for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Range_LED_ChannelX_Group_Assignment() returns the status.
 */
int32_t PCA9959_SPI_Range_LED_ChannelX_Group_Assignment(pca9959_spi_sensorhandle_t *pSensorHandle, CHxgroupAssign chxgroupassign,startLed start, endLed end);

/*! @brief       Set Preset Current for individual LED channels.
 *  @details     Set Preset Current for individual LED channels for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_All_LED_ChannelX_Group_Assignment() returns the status.
 */
int32_t PCA9959_SPI_LED_Channel_PresetCurrent(pca9959_spi_sensorhandle_t *pSensorHandle, LedNum lednum,LedBrightness brightness,PresetCurrent presetcurrent);

/*! @brief       Set Preset Current for all LED channels.
 *  @details     Set Preset Current for all LED channels for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_All_LED_Channel_PresetCurrent() returns the status.
 */
int32_t PCA9959_SPI_All_LED_Channel_PresetCurrent(pca9959_spi_sensorhandle_t *pSensorHandle, LedBrightness brightness,PresetCurrent presetcurrent);

/*! @brief       Set Preset Current for LED channels in range.
 *  @details     Set Preset Current for LED channels in range for PCA9959 (LED 0-23).
 *  @param[in]   pSensorHandle  	   Pointer to sensor handle structure.
 *  @constraints This can be called any number of times only after PCA9959_SPI_Initialize().
 *				 Application has to ensure that previous instances of these APIs have exited before invocation
 *  @reentrant   No
 *  @return      ::PCA9959_SPI_Range_LED_Channel_PresetCurrent() returns the status.
 */
int32_t PCA9959_SPI_Range_LED_Channel_PresetCurrent(pca9959_spi_sensorhandle_t *pSensorHandle, LedBrightness brightness,PresetCurrent presetcurrent,startLed start, endLed end);

#endif /* PCA9959_DRV_H_ */
