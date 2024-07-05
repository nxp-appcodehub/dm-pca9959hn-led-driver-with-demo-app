/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  pca9959_led_demoapp.c
 *  @brief The pca9959_led_demoapp.c file implements the ISSDK PCA9959 SPI LED driver
 *         example demonstration for SPI with Interrupt and EDMA Mode.
 */

//-----------------------------------------------------------------------
// SDK Includes
//-----------------------------------------------------------------------
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "pca9959_drv.h"
#include "systick_utils.h"
#include "Driver_GPIO.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if (RTE_SPI1_DMA_EN)
#define EXAMPLE_DMA_BASEADDR (DMA0)
#define EXAMPLE_DMA_CLOCK    kCLOCK_Dma0
#endif


/*******************************************************************************
 * Macros
 ******************************************************************************/

#define ERROR_NONE       0
#define ERROR            1


/*******************************************************************************
 * Global Variables
 ******************************************************************************/
uint8_t sideNo;
uint8_t presetCur;
uint8_t glednum;
uint8_t groupNumber;
uint8_t gridNo;
uint8_t gbrightness;
uint8_t tstepval;
uint8_t gridgrpconf;
uint8_t gdurcnt;
uint8_t endgrid;
uint8_t startled;
uint8_t endled;


/*!@brief        Get Side Number.
 *  @details     Get Side Number from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      Side Number.
 */


uint8_t getSideNumber()
{

	PRINTF("\r\n Press 1 for side 0 \r\n");
	PRINTF("\r\n Press 2 for side 1 \r\n");

	PRINTF("\r\n Enter Side Number [1 or 2] :- ");

	do {
		SCANF("%d",&sideNo);
		PRINTF("%d\r\n",sideNo);
		if(sideNo < 1 || sideNo > 2){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter Side Number [1 or 2] :- ");
		}
		else
			return sideNo ;
	}
	while(sideNo < 1 || sideNo > 2);
}

/*!@brief        Get Preset Current.
 *  @details     Get Preset Current from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      Preset Current.
 */


uint8_t getPresetCurrent()
{

	PRINTF("\r\n Enter Preset Current [1 to 3] :- ");
	do {
		SCANF("%d",&presetCur);
		PRINTF("%d\r\n",presetCur);
		if(presetCur < 1 || presetCur > 3){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter Preset Current [1 to 3] :- ");
		}
		else
			return presetCur ;
	}
	while(presetCur < 1 || presetCur > 3);
}

/*!@brief        Get LED Number.
 *  @details     Get LED Number from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      LED Number.
 */


uint8_t getLednum()
{
	PRINTF("\r\n Enter LED Number [1 to 24] :- ");
	do {
		SCANF("%d",&glednum);
		PRINTF("%d\r\n",glednum);
		if(glednum < 1 || glednum > 24){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter LED Number [1 to 24] :- ");
		}
		else
			return glednum ;
	}
	while(glednum < 1 || glednum > 24);
}


/*!@brief        Get Group Number.
 *  @details     Get Group Number from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      Group Number.
 */


uint8_t getGroupNumber()
{

	PRINTF("\r\n Enter Group Number [1 to 4] :- ");
	do {
		SCANF("%d",&groupNumber);
		PRINTF("%d\r\n",groupNumber);
		if(groupNumber < 1 || groupNumber > 4){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter Group Number [1 to 4] :- ");
		}
		else
			return groupNumber ;
	}
	while(groupNumber < 1 || groupNumber > 4);
}

/*!@brief        Get Grid Number.
 *  @details     Get Grid Number from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      Group Number.
 */


uint8_t getGridNumber()
{

	PRINTF("\r\n Enter Grid Number [1 to 64] :- ");
	do {
		SCANF("%d",&gridNo);
		PRINTF("%d\r\n",gridNo);
		if(gridNo < 1 || gridNo > 64){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter Grid Number [1 to 64] :- ");
		}
		else
			return gridNo ;
	}
	while(gridNo < 1 || gridNo > 64);
}

/*!@brief        Get LED Brightness.
 *  @details     Get LED Brightness from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      LED Brightness.
 */


uint8_t getBrightness()
{
	PRINTF("\r\n Enter Brightness [1 to 64] :- ");
	do {
		SCANF("%d",&gbrightness);
		PRINTF("%d\r\n",gbrightness);
		if(gbrightness < 1 || gbrightness > 64){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter Brightness [1 to 64] :- ");
		}
		else
			return gbrightness ;
	}
	while(gbrightness < 1 || gbrightness > 64);
}

/*!@brief        Get TStep Value.
 *  @details     Get TStep Value from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      TStep Value.
 */


uint8_t setTStepValue()
{
	PRINTF("\r\n 1. TStep: 2.5 microseconds \r\n");
	PRINTF("\r\n 2. TStep: 5 microseconds \r\n");
	PRINTF("\r\n 3. TStep: 10 microseconds \r\n");
	PRINTF("\r\n 4. TStep: 20 microseconds \r\n");

	PRINTF("\r\n Enter TStep Value [1 to 4] :- ");
	do {
		SCANF("%d",&tstepval);
		PRINTF("%d\r\n",tstepval);
		if(tstepval < 1 || tstepval > 4){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter TStep Value [1 to 4] :- ");
		}
		else
			return tstepval ;
	}
	while(tstepval < 1 || tstepval > 4);
}

/*!@brief        Get Grid_Group Configuration Setting.
 *  @details     Get Grid_Group Configuration Setting from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      Grid_Group Configuration.
 */


uint8_t getGridGroupConf()
{

	PRINTF("\r\n ******** Choose one of the below options for preset current configurations ********\r\n");
	PRINTF("\r\n 1. Selected LEDs are in off state\r\n");
	PRINTF("\r\n 2. Selected LEDs will get preset current 1 \r\n");
	PRINTF("\r\n 3. Selected LEDs will get preset current 2\r\n");
	PRINTF("\r\n 4. Selected LEDs will get preset current 3\r\n");

	PRINTF("\r\n Enter Grid preset current configuration [1 to 4] :- ");
	do {
		SCANF("%d",&gridgrpconf);
		PRINTF("%d\r\n",gridgrpconf);
		if(gridgrpconf < 1 || gridgrpconf > 4){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter Grid preset current configuration [1 to 4] :- ");
		}
		else
			return gridgrpconf ;
	}
	while(gridgrpconf < 1 || gridgrpconf > 4);
}

/*!@brief        Get Duration Count.
 *  @details     Get Duration Count from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      Duration Count.
 */


uint8_t getDurCount()
{
	PRINTF("\r\n Enter Duration count [1 to 64] :- ");
	do {
		SCANF("%d",&gdurcnt);
		PRINTF("%d\r\n",gdurcnt);
		if(gdurcnt < 1 || gdurcnt > 64){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter Duration count [1 to 64] :- ");
		}
		else
			return gdurcnt ;
	}
	while(gdurcnt < 1 || gdurcnt > 64);
}

/*!@brief        Get End Grid.
 *  @details     Get End Grid from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      End Grid Value.
 */

uint8_t getEndGrid()
{
	PRINTF("\r\n Enter Grid End Value [1 to 64] :- ");
	do {
		SCANF("%d",&endgrid);
		PRINTF("%d\r\n",endgrid);
		if(endgrid < 1 || endgrid > 64){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter Grid End Value [1 to 64] :- ");
		}
		else
			return endgrid;
	}
	while(endgrid < 1 || endgrid > 64);
}

/*!@brief        Get Start LED.
 *  @details     Get Start LED from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      Start LED.
 */


uint8_t getStartLed()
{
	PRINTF("\r\n Enter Start Value [1 to 24] :- ");
	do {
		SCANF("%d",&startled);
		PRINTF("%d\r\n",startled);
		if(startled < 1 || startled > 24){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter Start Value [1 to 24] :- ");
		}
		else
			return startled;
	}
	while(startled < 1 || startled > 64);
}

/*!@brief        Get End LED.
 *  @details     Get End LED from user.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      End LED.
 */


uint8_t getEndLed(startLed startled)
{
	PRINTF("\r\n Enter End Value [1 to 24] :- ");
	do {
		SCANF("%d",&endled);
		PRINTF("%d\r\n",endled);
		if((endled < 1 || endled > 24) || (startled > endled)){
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
			PRINTF("\r\n Enter End Value [1 to 24] :- ");
		}
		else
			return endled;
	}
	while((endled < 1 || endled > 24) || (startled > endled));
}

/*!@brief        set Led Output Delay .
 *  @details     Set Led Output Delay (50ns delay) between LED Channel.
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void setLedOpDelay(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	uint32_t status;

	status = PCA9959_SPI_Enable_Turn_On_Delay(pca9959Driver);
	if (SENSOR_ERROR_NONE != status)
	{
		PRINTF("\r\n LED Delay Set Failed\r\n");
	}
	else
		PRINTF("\r\n LED Delay Set Done \r\n");

}

/*!@brief        Set Sleep Control.
 *  @details     Enable/DIsable Sleep.
 *
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void setSleepControl(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t ipSleep;

	PRINTF("\r\n 1. Enable Sleep \r\n");
	PRINTF("\r\n 2. Disable Sleep \r\n");

	PRINTF("\r\n Enter your choice :- ");
	do {
		ipSleep = GETCHAR();
		ipSleep -= 48;
		PRINTF("%d\r\n",ipSleep);

		if(ipSleep < 1 || ipSleep > 2)
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
	}
	while(ipSleep < 1 || ipSleep > 2);
	GETCHAR();

	if(ipSleep == 1)
	{
		status = PCA9959_SPI_Enable_Sleep(pca9959Driver);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n Enable Sleep Failed \r\n");
		}
		else
			PRINTF("\r\n Enabled Sleep \r\n");
	}
	else
	{
		status = PCA9959_SPI_Disable_Sleep(pca9959Driver);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n Disable Sleep Failed \r\n");
		}
		else
			PRINTF("\r\n Disable Sleep\r\n");

	}
}

/*!@brief        Auto Switch off Control.
 *  @details     Enable/Disable auto Switch off LED channel on error.
 *
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void autoSwitchoffControl(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t ipswitch;

	PRINTF("\r\n 1. Auto Switch Off Enable \r\n");
	PRINTF("\r\n 2. Auto Switch Off Disable \r\n");

	PRINTF("\r\n Enter your choice :- ");
	do {
		ipswitch = GETCHAR();
		ipswitch -= 48;
		PRINTF("%d\r\n",ipswitch);

		if(ipswitch < 1 || ipswitch > 2)
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
	}
	while(ipswitch < 1 || ipswitch > 2);
	GETCHAR();

	if(ipswitch == 1)
	{
		status = PCA9959_SPI_Enable_Auto_SwitchOff(pca9959Driver);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n Auto Switch Off Enable Failed \r\n");
		}
		else
			PRINTF("\r\n Auto Switch Off Enable \r\n");
	}
	else
	{
		status = PCA9959_SPI_Disable_Auto_SwitchOff(pca9959Driver);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n Auto Switch Off Disable Failed \r\n");
		}
		else
			PRINTF("\r\n Auto Switch Off Disable \r\n");

	}
}

/*!@brief        Set maximum current.
 *  @details     set Imax to 30MA or 20 MA.
 *
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void setMAxCurrent()
{
	int32_t status;
	uint8_t ipImax;

	PRINTF("\r\n 1. Set Max Current 30 MA \r\n");
	PRINTF("\r\n 2. Set Max Current 20 MA \r\n");

	PRINTF("\r\n Enter your choice :- ");
	do {
		ipImax = GETCHAR();
		ipImax -= 48;
		PRINTF("%d\r\n",ipImax);

		if(ipImax < 1 || ipImax > 2)
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
	}
	while(ipImax < 1 || ipImax > 2);
	GETCHAR();

	if(ipImax == 1)
	{
		status = PCA9959_Set_Imax_30MA(&PCA9959_SW_EN);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n 30 MA maximum Current Set Failed \r\n");
		}
		else
			PRINTF("\r\n 30 MA maximum Current Set \r\n");
	}
	else
	{
		status = PCA9959_Set_Imax_20MA(&PCA9959_SW_EN);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n 20 MA maximum Current Set Failed \r\n");
		}
		else
			PRINTF("\r\n 20 MA maximum Current Set \r\n");

	}
}

/*!@brief        Use Internal/External (Cerlock Resonator/External) clock for gradation control.
 *  @details     Use Internal/External (Cerlock Resonator/External) 20MHz clock for gradation control.
 *
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void setCeraLockResonator(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t ceraLock;

	PRINTF("\r\n User have to use external clock generator to generate 20MHz clock on OSCIN pin if user chooses option 2 i.e. external clock\r\n");
	PRINTF("\r\n Before using external clock for gradation control, user have to provide 20MHz external clock on OSCIN pin\r\n");

	PRINTF("\r\n 1. Use ceralock resonator b/w OSCIN & OSCIN for gradation control \r\n");
	PRINTF("\r\n 2. Use external clock on OSCOUT for gradation control\r\n");

	PRINTF("\r\n Enter your choice :- ");
	do {
		ceraLock = GETCHAR();
		ceraLock -= 48;
		PRINTF("%d\r\n",ceraLock);

		if(ceraLock < 1 || ceraLock > 2)
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
	}
	while(ceraLock < 1 || ceraLock > 2);
	GETCHAR();

	if(ceraLock == 1)
	{
		status = PCA9959_SPI_Use_Ceralock_For_Grad_Ctl(pca9959Driver);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n Ceralock Resonator for Gradation Control Enable Failed \r\n");
		}
		else
			PRINTF("\r\n Ceralock Resonator for Gradation Control Enable Done \r\n");
	}
	else
	{
		status = PCA9959_SPI_Use_ExtClk_For_Grad_Ctl(pca9959Driver);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n External Clock for Gradation Control Enable Failed \r\n");
		}
		else
			PRINTF("\r\n External Clock for Gradation Control Enable Done \r\n");

	}
}

/*!@brief        LED channel error.
 *  @details     check LED channel error.
 *
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void errorControl(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t ipError, ledn, i;
	ErrorState errorstate;
	LedErrorType lederror;

	PRINTF("\r\n 1. Check Error \r\n");
	PRINTF("\r\n 2. Clear Error \r\n");
	PRINTF("\r\n 3. Check Individual LED Error \r\n");

	PRINTF("\r\n Enter your choice :- ");
	do {
		ipError = GETCHAR();
		ipError -= 48;
		PRINTF("%d\r\n",ipError);

		if(ipError < 1 || ipError > 3)
			PRINTF("\r\n Invalid Value, Please enter correct value\r\n");
	}
	while(ipError < 1 || ipError > 3);
	GETCHAR();

	switch(ipError)
	{
	case 1:
		status = PCA9959_SPI_Check_Error(pca9959Driver, &errorstate);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n Check Error Failed \r\n");
		}
		else
		{
			if(errorstate == errorDetected)
			{
				for( i =0; i <= PCA9959_MAX_LED_PORT; i++)
				{
					status = PCA9959_SPI_LED_Get_Error_Type(pca9959Driver, i, &lederror);
					if (SENSOR_ERROR_NONE != status)
					{
						PRINTF("\r\n Check Error Failed for Led :- %d\r\n", (i+1));
					}
					else
					{
						if(lederror == shortCircuit)
							PRINTF("\r\n\033[31m Short Circuit Occurred for Led :- %d \033[37m \r\n", (i+1));
						else if(lederror == openCircuit)
							PRINTF("\r\n\033[31m Open Circuit Occurred for Led :- %d \033[37m \r\n", (i +1));
					}
				}
			}
			else
				PRINTF("\r\n Error Not Occurred \r\n");
		}
		break;
	case 2:
		status = PCA9959_SPI_Clear_Error(pca9959Driver);
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n Clear Error Failed \r\n");
		}
		else
			PRINTF("\r\n Error Cleared \r\n");
		break;
	case 3:
		ledn = getLednum();
		if(ledn)
		{
			status = PCA9959_SPI_LED_Get_Error_Type(pca9959Driver, (ledn -1), &lederror);
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Check Led :- %d Error Failed \r\n", ledn);
			}
			else
			{
				if(lederror == noError)
					PRINTF("\r\n No Error Occurred \r\n");
				else if(lederror == shortCircuit)
					PRINTF("\r\n\033[31m Short Circuit Occurred \033[37m\r\n");
				else if(lederror == openCircuit)
					PRINTF("\r\n\033[31m Open Circuit Occurred \033[37m\r\n");
				else
					PRINTF("\r\n Check Led :- %d Error Failed \r\n", ledn);
			}
		}
		break;
	}
}

/*!@brief        check over/under temperature.
 *  @details     check over/under temperature.
 *
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void overTempCheck(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	TempCondition tempCondsn;

	status = PCA9959_SPI_Check_OvTemp(pca9959Driver, &tempCondsn);
	if (SENSOR_ERROR_NONE != status)
	{
		PRINTF("\r\n Check Over Temperature Failed \r\n");
	}
	else
	{
		if(tempCondsn == underTemp)
			PRINTF("\r\n Operating in Under Temperature \r\n");
		else
			PRINTF("\r\n Operating in Normal Temperature \r\n");
	}
}

/*!@brief        check presence of external clock.
 *  @details     check presence of external clock.
 *
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void checkExtClock(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	ExClkPrs extclk;

	PRINTF("\r\n If user enables 20 MHz external clock for gradation control, user have to provide external clock by using clock generator\r\n");
	PRINTF("\r\n Otherwise use only ceralock resonator to get 20MHz clock for gradation control\r\n");

	status = PCA9959_SPI_Check_Valid_Ext_Clk_Presence(pca9959Driver, &extclk);
	if (SENSOR_ERROR_NONE != status)
	{
		PRINTF("\r\n Check External Clock Failed\r\n");
	}
	else
	{
		if(extclk == extClockAbsent)
			PRINTF("\r\n Clock detected is in invalid range\r\n");
		else
			PRINTF("\r\n Clock detected in correct range \r\n");
	}
}

/*!@brief        Side Control.
 *  @details     Side Control Settings (Configure/Execute).
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void sideControl(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t sidectl, sideConfig,sideExec, lsidectl = 1;

	PRINTF("\r\n By default side 0 gets configured and executed\r\n");
	PRINTF("\r\n Configure side 0/1 and perform LED control configurations for that particular side\r\n");
	PRINTF("\r\n User can switch between side 0 and side 1 using side execute only when gradation is enabled\r\n");

	do
	{
		PRINTF("\r\n");
		PRINTF("\r\n ******** Side Control ********\r\n");
		PRINTF("\r\n 1. Side Configuration\r\n");
		PRINTF("\r\n 2. Side Execute\r\n");
		PRINTF("\r\n 3. Exit From Side Control \r\n");

		PRINTF("\r\n Enter your choice :- ");
		sidectl = GETCHAR();
		sidectl -= 48;
		PRINTF("%d\r\n",sidectl);
		GETCHAR();

		switch (sidectl)
		{

		case 1:
			sideConfig = getSideNumber();
			status = PCA9959_SPI_Side_Configuration(pca9959Driver,(sideConfig-1));
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Side configuration failed\r\n");
			}
			else
				PRINTF("\r\n Side configuration completed\r\n");
			break;
		case 2:
			sideExec = getSideNumber();
			status = PCA9959_SPI_Side_Execute(pca9959Driver,(sideExec-1));
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Side execution failed\r\n");
			}
			else
				PRINTF("\r\n Side executed\r\n");
			break;
		case 3:
			lsidectl = 0;
			break;
		default:
			break;
		}
	}
	while(lsidectl);

}

/*!@brief        Set Individual LEDs Grid Group Configuration.
 *  @details     Set Individual LEDs Grid Group Configuration (Preset Current Values).
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void setIndividualPresetCurrent(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	uint8_t ipPresetCurr,ledNum,ledBrightness,indPresetCurr = 1;
	int32_t status;

	do
	{
		PRINTF("\r\n ********* Set Preset Current for individual LEDs *********\r\n");
		PRINTF("\r\n 1. Set Preset Current 1 \r\n");
		PRINTF("\r\n 2. Set Preset Current 2 \r\n");
		PRINTF("\r\n 3. Set Preset Current 3 \r\n");
		PRINTF("\r\n 4. Exit Preset Current Setting Main Menu \r\n");

		PRINTF("\r\n Enter your choice :- ");
		ipPresetCurr = GETCHAR();
		ipPresetCurr -= 48;
		PRINTF("%d\r\n",ipPresetCurr);
		GETCHAR();

		switch(ipPresetCurr)
		{
		case 1:
			ledNum = getLednum();
			ledBrightness = getBrightness();
			if(ledNum && ledBrightness)
			{
				status = PCA9959_SPI_LED_Channel_PresetCurrent(pca9959Driver,(ledNum-1),(ledBrightness-1),presetCurrent1);
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Preset Current 1 Setting Failed\r\n");
				}
				else
					PRINTF("\r\n LED Preset Current 1 Setting Done \r\n");
			}
			break;
		case 2:
			ledNum = getLednum();
			ledBrightness = getBrightness();
			if(ledNum && ledBrightness)
			{
				status = PCA9959_SPI_LED_Channel_PresetCurrent(pca9959Driver,(ledNum-1),(ledBrightness-1),presetCurrent2);
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Preset Current 2 Setting Failed\r\n");
				}
				else
					PRINTF("\r\n LED Preset Current 2 Setting Done \r\n");
			}
			break;
		case 3:
			ledNum = getLednum();
			ledBrightness = getBrightness();
			if(ledNum && ledBrightness)
			{
				status = PCA9959_SPI_LED_Channel_PresetCurrent(pca9959Driver,(ledNum-1),(ledBrightness-1),presetCurrent3);
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Preset Current 3 Setting Failed\r\n");
				}
				else
					PRINTF("\r\n LED Preset Current 3 Setting Done \r\n");
			}
			break;
		case 4:
			indPresetCurr = 0;
			break;
		default:
			break;
		}
	}while(indPresetCurr);
}

/*!@brief        Individual LED Channel Configuration.
 *  @details     Individual LED Channel (0-23) Configuration.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void individualChannelConfiguration(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	uint8_t chnlConf, ledNum,groupNum,ledBrightness,presetCurrent,lchnlconf = 1;
	int32_t status;

	do
	{
		PRINTF("\r\n ********* Individual Channel Configuration Main Menu *********\r\n");
		PRINTF("\r\n 1. LED Channel Enable \r\n");
		PRINTF("\r\n 2. LED Channel Disable \r\n");
		PRINTF("\r\n 3. LED Channel Group Assignment \r\n");
		PRINTF("\r\n 4. Set Preset Current for LED Channel \r\n");
		PRINTF("\r\n 5. Exit Gradation Main Menu \r\n");

		PRINTF("\r\n Enter your choice :- ");
		chnlConf = GETCHAR();
		chnlConf -= 48;
		PRINTF("%d\r\n",chnlConf);
		GETCHAR();

		switch(chnlConf)
		{
		case 1:
			ledNum = getLednum();
			if(ledNum)
			{
				status = PCA9959_SPI_Individual_LED_Channel_Enable(pca9959Driver, (ledNum - 1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Channel Enable Failed\r\n");
				}
				else
					PRINTF("\r\n LED Channel Enable Done \r\n");
			}
			break;
		case 2:
			ledNum = getLednum();
			if(ledNum )
			{
				status = PCA9959_SPI_Individual_LED_Channel_Disable(pca9959Driver, (ledNum - 1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Channel Disable Failed\r\n");
				}
				else
					PRINTF("\r\n LED Channel Disable Done \r\n");
			}
			break;
		case 3:
			ledNum = getLednum();
			groupNum = getGroupNumber();
			if(ledNum && groupNum)
			{
				status = PCA9959_SPI_LED_ChannelX_Group_Assignment(pca9959Driver,(groupNum-1),(ledNum - 1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Assignment Failed\r\n");
				}
				else
					PRINTF("\r\n LED Assignment Done \r\n");
			}
			break;
		case 4:
			setIndividualPresetCurrent(pca9959Driver);
			break;
		case 5:
			lchnlconf = 0;
			break;
		default:
			break;
		}
	}while(lchnlconf);
}

/*!@brief        Individual LED Control.
 *  @details     Individual LED Control (Grid_Group Settings and Channel Configuration).
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void ledControl(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t individualLedControl, lled = 1;
	uint8_t sideConfig,sideExec, groupNum, gridGroupConf,endgrid,tStepVal,durCounter;


	do
	{
		PRINTF("\r\n");
		PRINTF("\r\n ******** Individual LED Control ********\r\n");

		PRINTF("\r\n 1. Individual Grid Group Configuration \r\n");
		PRINTF("\r\n 2. Individual LED Channel Configuration \r\n");
		PRINTF("\r\n 3. Exit From Individual LED Control \r\n");

		PRINTF("\r\n Enter your choice :- ");
		individualLedControl = GETCHAR();
		individualLedControl -= 48;
		PRINTF("%d\r\n",individualLedControl);
		GETCHAR();

		switch (individualLedControl)
		{

		case 1:
			groupNum = getGroupNumber();
			gridGroupConf = getGridGroupConf();
			PRINTF("\r\n Please Select Ending Grid Number as Grid Configuration Starts from Grid 0\r\n");
			endgrid = getEndGrid();
			if(groupNum && gridGroupConf && endgrid)
			{
				status = PCA9959_SPI_Page_Select(pca9959Driver,page0);
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n Page Select Failed for gradation configuration\r\n");
				}
				else
					PRINTF("\r\n Page Select done for gradation configuration \r\n");

				status = PCA9959_SPI_Grid_Group_Configuration(pca9959Driver,(groupNum-1),(gridGroupConf-1),(endgrid-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n Grid Group Configuration Failed\r\n");
				}
				else
					PRINTF("\r\n Grid Group Configuration Done \r\n");
			}
			break;
		case 2:
			status = PCA9959_SPI_Page_Select(pca9959Driver,page1);
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Page Select Failed for channel configuration\r\n");
			}
			else
				PRINTF("\r\n Page Select done for channel configuration \r\n");
			individualChannelConfiguration(pca9959Driver);
			break;
		case 3:
			lled = 0;
			break;
		default:
			break;
		}
	}
	while(lled);
}

/*!@brief        Set All LEDs Grid Group Configuration.
 *  @details     Set All LEDs Grid Group Configuration (Preset Current Values).
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void setAllLEDPresetCurrent(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	uint8_t ipPresetCurr,ledBrightness,allPresetCurr = 1;
	int32_t status;

	do
	{
		PRINTF("\r\n ********* Set Preset Current for all LEDs *********\r\n");
		PRINTF("\r\n 1. Set Preset Current 1 \r\n");
		PRINTF("\r\n 2. Set Preset Current 2 \r\n");
		PRINTF("\r\n 3. Set Preset Current 3 \r\n");
		PRINTF("\r\n 4. Exit Preset Current Setting Main Menu \r\n");

		PRINTF("\r\n Enter your choice :- ");
		ipPresetCurr = GETCHAR();
		ipPresetCurr -= 48;
		PRINTF("%d\r\n",ipPresetCurr);
		GETCHAR();

		switch(ipPresetCurr)
		{
		case 1:
			ledBrightness = getBrightness();
			if(ledBrightness)
			{
				status = PCA9959_SPI_All_LED_Channel_PresetCurrent(pca9959Driver,(ledBrightness-1),pc1);
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Preset Current 1 Setting Failed\r\n");
				}
				else
					PRINTF("\r\n LED Preset Current 1 Setting Done \r\n");
			}
			break;
		case 2:
			ledBrightness = getBrightness();
			if(ledBrightness)
			{
				status = PCA9959_SPI_All_LED_Channel_PresetCurrent(pca9959Driver,(ledBrightness-1),pc2);
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Preset Current 2 Setting Failed\r\n");
				}
				else
					PRINTF("\r\n LED Preset Current 2 Setting Done \r\n");
			}
			break;
		case 3:
			ledBrightness = getBrightness();
			if(ledBrightness)
			{
				status = PCA9959_SPI_All_LED_Channel_PresetCurrent(pca9959Driver,(ledBrightness-1),pc3);
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Preset Current 3 Setting Failed\r\n");
				}
				else
					PRINTF("\r\n LED Preset Current 3 Setting Done \r\n");
			}
			break;
		case 4:
			allPresetCurr = 0;
			break;
		default:
			break;
		}
	}while(allPresetCurr);
}

/*!@brief        All LED Channel Configuration.
 *  @details     All LED Channel (0-23) Configuration.
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void allChannelConfiguration(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	uint8_t chnlConf, ledNum,groupnum,ledBrightness,presetCurrent,lgain = 1;
	int32_t status;

	do
	{
		PRINTF("\r\n ********* All Channel Configuration Main Menu *********\r\n");
		PRINTF("\r\n 1. LED Channel Enable \r\n");
		PRINTF("\r\n 2. LED Channel Disable \r\n");
		PRINTF("\r\n 3. All LED Channel Group Assignment \r\n");
		PRINTF("\r\n 4. Set Preset Current for All LED Channel \r\n");
		PRINTF("\r\n 5. Exit LED channel Main Menu \r\n");

		PRINTF("\r\n Enter your choice :- ");
		chnlConf = GETCHAR();
		chnlConf -= 48;
		PRINTF("%d\r\n",chnlConf);
		GETCHAR();

		switch(chnlConf)
		{
		case 1:
			status = PCA9959_SPI_All_LED_Channel_Enable(pca9959Driver);
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n All LED Channel Enable Failed\r\n");
			}
			else
				PRINTF("\r\n All LED Channel Enable Done \r\n");
			break;
		case 2:
			status = PCA9959_SPI_All_LED_Channel_Disable(pca9959Driver);
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n All LED Channel Disable Failed\r\n");
			}
			else
				PRINTF("\r\n All LED Channel Disable Done \r\n");
			break;
		case 3:
			groupnum = getGroupNumber();
			if(groupnum)
			{
				status = PCA9959_SPI_All_LED_ChannelX_Group_Assignment(pca9959Driver,(groupnum-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n All LED Assignment Failed\r\n");
				}
				else
					PRINTF("\r\n All LED Assignment Done \r\n");
			}
			break;
		case 4:
			setAllLEDPresetCurrent(pca9959Driver);
			break;
		case 5:
			lgain = 0;
			break;
		default:
			break;
		}
	}while(lgain);
}

/*!@brief        All LED Control.
 *  @details     All LED Control (Grid_Group Settings and Channel Configuration).
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void allLedControl(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t allLedControl, lallled = 1;
	uint8_t sideConfig,sideExec, groupnum, gridGroupConf,tStepVal,durCounter;


	do
	{
		PRINTF("\r\n");
		PRINTF("\r\n ******** ALL LED Control ********\r\n");

		PRINTF("\r\n 1. All Grid Group Configuration \r\n");
		PRINTF("\r\n 2. All LED Channels Configuration \r\n");
		PRINTF("\r\n 3. Exit From ALL LED Control \r\n");

		PRINTF("\r\n Enter your choice :- ");
		allLedControl = GETCHAR();
		allLedControl -= 48;
		PRINTF("%d\r\n",allLedControl);
		GETCHAR();

		switch (allLedControl)
		{

		case 1:
			groupnum = getGroupNumber();
			gridGroupConf = getGridGroupConf();
			PRINTF("\r\n Please Select Ending Grid Number as Grid Configuration Starts from Grid 0\r\n");
			endgrid = getEndGrid();
			if(groupnum && gridGroupConf && endgrid)
			{

				status = PCA9959_SPI_Page_Select(pca9959Driver,page0);
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n Page Select Failed for gradation configuration\r\n");
				}
				else
					PRINTF("\r\n Page Select done for gradation configuration \r\n");

				status = PCA9959_SPI_All_Grid_Group_Configuration(pca9959Driver,(groupnum-1),(gridGroupConf-1),(endgrid-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n All Grid Group Configuration Failed\r\n");
				}
				else
					PRINTF("\r\n All Grid Group Configuration Done \r\n");
			}
			break;
		case 2:
			status = PCA9959_SPI_Page_Select(pca9959Driver,page1);
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Page Select Failed for channel configuration\r\n");
			}
			else
				PRINTF("\r\n Page Select done for channel configuration \r\n");
			allChannelConfiguration(pca9959Driver);
			break;
		case 3:
			lallled = 0;
			break;
		default:
			break;
		}
	}
	while(lallled);
}

/*!@brief        Set Grid Group Configuration of LEDs in [x-y] range.
 *  @details     Set Grid Group Configuration of LEDs in [x-y] range (Preset Current Values).
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void setRangeLEDPresetCurrent(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	uint8_t ipPresetCurr,startled,endled,ledBrightness,rangePresetCurr = 1;
	int32_t status;

	do
	{
		PRINTF("\r\n ********* Set Individual Preset Current for LEDs in Range *********\r\n");
		PRINTF("\r\n 1. Set Preset Current 1 \r\n");
		PRINTF("\r\n 2. Set Preset Current 2 \r\n");
		PRINTF("\r\n 3. Set Preset Current 3 \r\n");
		PRINTF("\r\n 4. Exit Preset Current Setting Main Menu \r\n");

		PRINTF("\r\n Enter your choice :- ");
		ipPresetCurr = GETCHAR();
		ipPresetCurr -= 48;
		PRINTF("%d\r\n",ipPresetCurr);
		GETCHAR();

		switch(ipPresetCurr)
		{
		case 1:
			startled = getStartLed();
			endled = getEndLed(startled);
			ledBrightness = getBrightness();
			if(ledBrightness)
			{
				status = PCA9959_SPI_Range_LED_Channel_PresetCurrent(pca9959Driver,(ledBrightness-1),pc1,(startled-1),(endled-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Preset Current 1 Setting Failed\r\n");
				}
				else
					PRINTF("\r\n LED Preset Current 1 Setting Done \r\n");
			}
			break;
		case 2:
			startled = getStartLed();
			endled = getEndLed(startled);
			ledBrightness = getBrightness();
			if(ledBrightness)
			{
				status = PCA9959_SPI_Range_LED_Channel_PresetCurrent(pca9959Driver,(ledBrightness-1),pc2,(startled-1),(endled-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Preset Current 2 Setting Failed\r\n");
				}
				else
					PRINTF("\r\n LED Preset Current 2 Setting Done \r\n");
			}
			break;
		case 3:
			startled = getStartLed();
			endled = getEndLed(startled);
			ledBrightness = getBrightness();
			if(ledBrightness)
			{
				status = PCA9959_SPI_Range_LED_Channel_PresetCurrent(pca9959Driver,(ledBrightness-1),pc3,(startled-1),(endled-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n LED Preset Current 3 Setting Failed\r\n");
				}
				else
					PRINTF("\r\n LED Preset Current 3 Setting Done \r\n");
			}
			break;
		case 4:
			rangePresetCurr = 0;
			break;
		default:
			break;
		}
	}while(rangePresetCurr);
}


/*!@brief        Configure LED Channels in range [x-y].
 *  @details     Configure LED Channels in range [x-y].
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */
void rangeChannelConfiguration(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	uint8_t chnlConf, ledNum,groupnum,ledBrightness,presetCurrent,startled,endled,lgain = 1;
	int32_t status;

	do
	{
		PRINTF("\r\n ********* Range Channel Configuration Main Menu *********\r\n");
		PRINTF("\r\n 1. Enable LED Channel in Range \r\n");
		PRINTF("\r\n 2. Disable LED Channel in Range \r\n");
		PRINTF("\r\n 3. Range LED Channel Group Assignment \r\n");
		PRINTF("\r\n 4. Set Preset Current for LED Channels in Range \r\n");
		PRINTF("\r\n 5. Exit LED channel Main Menu \r\n");

		PRINTF("\r\n Enter your choice :- ");
		chnlConf = GETCHAR();
		chnlConf -= 48;
		PRINTF("%d\r\n",chnlConf);
		GETCHAR();

		switch(chnlConf)
		{
		case 1:
			startled = getStartLed();
			endled = getEndLed(startled);
			status = PCA9959_SPI_Range_LED_Channel_Enable(pca9959Driver,(startled-1),(endled-1));
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Range LED Channel Enable Failed\r\n");
			}
			else
				PRINTF("\r\n Range LED Channel Enable Done \r\n");
			break;
		case 2:
			startled = getStartLed();
			endled = getEndLed(startled);
			status = PCA9959_SPI_Range_LED_Channel_Disable(pca9959Driver,(startled-1),(endled-1));
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Range LED Channel Disable Failed\r\n");
			}
			else
				PRINTF("\r\n Range LED Channel Disable Done \r\n");
			break;
		case 3:
			startled = getStartLed();
			endled = getEndLed(startled);
			groupnum = getGroupNumber();
			if(groupnum)
			{
				status = PCA9959_SPI_Range_LED_ChannelX_Group_Assignment(pca9959Driver,(groupnum-1),(startled-1),(endled-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n Range LED Assignment Failed\r\n");
				}
				else
					PRINTF("\r\n Range LED Assignment Done \r\n");
			}
			break;
		case 4:
			setRangeLEDPresetCurrent(pca9959Driver);
			break;
		case 5:
			lgain = 0;
			break;
		default:
			break;
		}
	}while(lgain);
}

/*!@brief       Control LEDs in range [x-y].
 *  @details    Control LEDs in range (Grid_Group Settings and Channel Configuration).
 *  @param[in]   NO
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void rangeLedControl(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t rangeLedControl, lrangeled = 1;
	uint8_t sideConfig,sideExec, groupnum, gridGroupConf,tStepVal,durCounter,startgrid,endgrid;


	do
	{
		PRINTF("\r\n");
		PRINTF("\r\n ******** Range LED Control ********\r\n");

		PRINTF("\r\n 1. Range Grid Group Configuration \r\n");
		PRINTF("\r\n 2. Range LED Channels Configuration \r\n");
		PRINTF("\r\n 3. Exit From Range LED Control \r\n");

		PRINTF("\r\n Enter your choice :- ");
		rangeLedControl = GETCHAR();
		rangeLedControl -= 48;
		PRINTF("%d\r\n",rangeLedControl);
		GETCHAR();

		switch (rangeLedControl)
		{

		case 1:
			groupnum = getGroupNumber();
			gridGroupConf = getGridGroupConf();
			PRINTF("\r\n Please Select Ending Grid Number as Grid Configuration Starts from Grid 0\r\n");
			endgrid = getEndGrid();
			if(groupnum && gridGroupConf && endgrid)
			{

				status = PCA9959_SPI_Page_Select(pca9959Driver,page0);
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n Page Select Failed for gradation configuration\r\n");
				}
				else
					PRINTF("\r\n Page Select done for gradation configuration \r\n");

				status = PCA9959_SPI_Range_Grid_Group_Configuration(pca9959Driver,(groupnum-1),(gridGroupConf-1),(endgrid-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n Range Grid Group Configuration Failed\r\n");
				}
				else
					PRINTF("\r\n Range Grid Group Configuration Done \r\n");
			}
			break;
		case 2:
			status = PCA9959_SPI_Page_Select(pca9959Driver,page1);
			rangeChannelConfiguration(pca9959Driver);
			break;
		case 3:
			lrangeled = 0;
			break;
		default:
			break;
		}
	}
	while(lrangeled);
}

/*!@brief        Get Gradation operation.
 *  @details     Get Gradation operation (singleShot/Continuous) from user.
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */


void setGradOperation(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	uint8_t gradOperation;
	uint32_t status;

	PRINTF("\r\n 1. Single Shot \r\n");
	PRINTF("\r\n 2. Continuous \r\n");

	PRINTF("\r\n Enter your choice :- ");
	gradOperation = GETCHAR();
	gradOperation -= 48;
	PRINTF("%d\r\n",gradOperation);
	GETCHAR();

	if( gradOperation >= 1 && gradOperation <= 2)
	{
		status = PCA9959_SPI_Gradation_Mode(pca9959Driver, (gradOperation - 1));
		if (SENSOR_ERROR_NONE != status)
		{
			PRINTF("\r\n Gradation Mode Set Failed\r\n");
		}
		else
			PRINTF("\r\n Gradation Mode Setting Done \r\n");
	}
	else
	{
		PRINTF("\r\nInvalid Option \r\n");
	}
}

/*!@brief        Set Grid Duration.
 *  @details     Set Grid Duration (TStep & duration count).
 *  @param[in]   Pointer to spi sensor handle structure (pca9959Driver).
 *  @constraints None
 *
 *  @reentrant   No
 *  @return      No.
 */

void setGridDuration(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t gridduration, tStepVal,durCounter, lgriddur = 1;

	do
	{
		PRINTF("\r\n");
		PRINTF("\r\n ******** ALL LED Control ********\r\n");
		PRINTF("\r\n 1. Set TStep Value\r\n");
		PRINTF("\r\n 2. Set Duration Counter Value\r\n");
		PRINTF("\r\n 3. Exit From Duration Control \r\n");

		PRINTF("\r\n Enter your choice :- ");
		gridduration = GETCHAR();
		gridduration -= 48;
		PRINTF("%d\r\n",gridduration);
		GETCHAR();

		switch (gridduration)
		{

		case 1:
			tStepVal = setTStepValue();
			if(tStepVal)
			{
				status = PCA9959_SPI_TStep_Duration_Control(pca9959Driver, (tStepVal-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n TStep Value Setting Failed\r\n");
				}
				else
					PRINTF("\r\n TStep Value Setting Done \r\n");
			}
			break;
		case 2:
			durCounter = getDurCount();
			if(durCounter)
			{
				status = PCA9959_SPI_DurCnt_Duration_Control(pca9959Driver, (durCounter-1));
				if (SENSOR_ERROR_NONE != status)
				{
					PRINTF("\r\n Duration Counter Value Setting Failed\r\n");
				}
				else
					PRINTF("\r\n Duration Counter Value Setting Done \r\n");
			}
			break;
		case 3:
			lgriddur = 0;
			break;
		default:
			break;
		}
	}
	while(lgriddur);

}

void gradationConfiguration(pca9959_spi_sensorhandle_t *pca9959Driver)
{
	int32_t status;
	uint8_t gradControl, lled = 1;
	uint8_t sideConfig,sideExec, groupNum, gridGroupConf,gridNum,tStepVal,durCounter;


	do
	{
		PRINTF("\r\n");
		PRINTF("\r\n ******** Gradation Configuration Menu ********\r\n");
		PRINTF("\r\n 1. Grid Duration\r\n");
		PRINTF("\r\n 2. Gradation Mode\r\n");
		PRINTF("\r\n 3. Start Gradation \r\n");
		PRINTF("\r\n 4. Stop Gradation \r\n");
		PRINTF("\r\n 5. Exit From Gradation Control \r\n");

		PRINTF("\r\n Enter your choice :- ");
		gradControl = GETCHAR();
		gradControl -= 48;
		PRINTF("%d\r\n",gradControl);
		GETCHAR();

		switch (gradControl)
		{

		case 1:
			setGridDuration(pca9959Driver);
			break;
		case 2:
			setGradOperation(pca9959Driver);
			break;
		case 3:
			status = PCA9959_SPI_Start_Gradation(pca9959Driver);
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Gradation Start Failed\r\n");
			}
			else
				PRINTF("\r\n Gradation Started\r\n");
			break;
		case 4:
			status = PCA9959_SPI_Stop_Gradation(pca9959Driver);
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Gradation Stop Failed\r\n");
			}
			else
				PRINTF("\r\n Gradation Stop Done \r\n");
			break;
		case 5:
			lled = 0;
			break;
		default:
			break;
		}
	}
	while(lled);
}

int main(void)
{
	int32_t status, i;
	uint8_t character;
	ErrorState errorstate;
	ExClkPrs exclkprs;

	ARM_DRIVER_SPI *pSPIdriver = &SPI_S_DRIVER;
	GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

	pca9959_spi_sensorhandle_t  pca9959Driver;

	/* Enable EDMA for SPI */
#if (RTE_SPI1_DMA_EN)
	/* Enable DMA clock. */
	CLOCK_EnableClock(EXAMPLE_DMA_CLOCK);
	edma_config_t edmaConfig = {0};
	EDMA_GetDefaultConfig(&edmaConfig);
	EDMA_Init(EXAMPLE_DMA_BASEADDR, &edmaConfig);
#endif

	/* enable clock for GPIO*/
	CLOCK_EnableClock(kCLOCK_Gpio0);

	/* Define the init structure for the output LED pin*/
	gpio_pin_config_t led_config = {
			kGPIO_DigitalOutput,
			0,
	};

	/*! Initialize the MCU hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_SystickEnable();
	BOARD_InitDebugConsole();

	/* Initialize OE Pin and set its default state to high */
	PCA9959_OE_Pin_Init(&PCA9959_OE);

	/* By default enable output */
	PCA9959_Output_Enable(&PCA9959_OE);

	/* Initialize Reset Pin and set its default state to high */
	PCA9959_Reset_Pin_Init(&PCA9959_RESET);

	/* Initialize SW Enable Pin and set its default state to low */
	PCA9959_SW_EN_Pin_Init(&PCA9959_SW_EN);

	PRINTF("\r\n ISSDK PCA9959 LED driver example demonstration for SPI with interrupt mode.\r\n");

	/*! Initialize the SPI driver. */
	status = pSPIdriver->Initialize(SPI_S_SIGNAL_EVENT);
	if (ARM_DRIVER_OK != status)
	{
		PRINTF("\r\n SPI Initialization Failed\r\n");
		return -1;
	}

	/*! Set the SPI Power mode. */
	status = pSPIdriver->PowerControl(ARM_POWER_FULL);
	if (ARM_DRIVER_OK != status)
	{
		PRINTF("\r\n SPI Power Mode setting Failed\r\n");
		return -1;
	}

	/*! Set the SPI Slave speed. */
	status = pSPIdriver->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL0_CPHA0, SPI_S_BAUDRATE);
	if (ARM_DRIVER_OK != status)
	{
		PRINTF("\r\n SPI Control Mode setting Failed\r\n");
		return -1;
	}

	/* Initialize the PCA9959 driver. */
	status = PCA9959_SPI_Initialize(&pca9959Driver, &SPI_S_DRIVER, SPI_S_DEVICE_INDEX, &PCA9959_CS);
	if (SENSOR_ERROR_NONE != status)
	{
		PRINTF("\r\n PCA9959 Sensor Initialization Failed\r\n");
		return -1;
	}


	PRINTF("\r\n Successfully Applied PCA9959 Configuration\r\n");

	PRINTF("\r\n \033[32m It is recommended to use external supply (3V - 3.3V) on J1 \033[37m \r\n");
	PRINTF("\r\n \033[32m To use external supply Please connect pin number 2 and 3 of J2 \033[37m \r\n");

	do
	{
		PRINTF("\r\n *********** Main Menu ***************\r\n");

		PRINTF("\r\n 1.  Side Control \r\n");
		PRINTF("\r\n 2.  Individual LED Control \r\n");
		PRINTF("\r\n 3.  All LED Control \r\n");
		PRINTF("\r\n 4.  Control LEDs in Range \r\n");
		PRINTF("\r\n 5.  Gradation Configuration \r\n");
		PRINTF("\r\n 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1) \r\n");
		PRINTF("\r\n 7.  Software Reset  \r\n");
		PRINTF("\r\n 8.  Use 20MHz Internal/External clock for gradation control \r\n");
		PRINTF("\r\n 9.  Sleep Control \r\n");
		PRINTF("\r\n 10. Auto Switch Off Control \r\n");
		PRINTF("\r\n 11. Set Max Current \r\n");
		PRINTF("\r\n 12. Error Control \r\n");
		PRINTF("\r\n 13. Over Temperature Check \r\n");
		PRINTF("\r\n 14. Check presence of valid external clock \r\n");

		PRINTF("\r\n Enter your choice :- ");

		SCANF("%d",&character);
		PRINTF("%d\r\n",character);

		switch (character)
		{

		case 1: /* Side Control */
			sideControl(&pca9959Driver);
			break;
		case 2: /* All LED control */
			PCA9959_Output_Disable(&PCA9959_OE);
			ledControl(&pca9959Driver);
			PCA9959_Output_Enable(&PCA9959_OE);
			break;
		case 3: /* Individual LED control */
			PCA9959_Output_Disable(&PCA9959_OE);
			allLedControl(&pca9959Driver);
			PCA9959_Output_Enable(&PCA9959_OE);
			break;
		case 4:  /* Control LEDs in range */
			PCA9959_Output_Disable(&PCA9959_OE);
			rangeLedControl(&pca9959Driver);
			PCA9959_Output_Enable(&PCA9959_OE);
			break;
		case 5:  /* Gradation Control */
			gradationConfiguration(&pca9959Driver);
			break;
		case 6: /* LED Op Delay */
			setLedOpDelay(&pca9959Driver);
			break;
		case 7: /* Reset PCA9959 device */
			status = PCA9959_Reset(&PCA9959_RESET);
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Reset Failed \r\n");
			}
			else
				PRINTF("\r\n Reset Done \r\n");
			break;
		case 8: /* Set ceralock resonator  */
			setCeraLockResonator(&pca9959Driver);
			break;
		case 9: /* Sleep Control */
			setSleepControl(&pca9959Driver);
			break;
		case 10: /* Auto switch off control */
			autoSwitchoffControl(&pca9959Driver);
			break;
		case 11: /* Set maximum current */
			setMAxCurrent();
			break;
		case 12: /* error control */
			errorControl(&pca9959Driver);
			break;
		case 13:  /* check over temperature */
			overTempCheck(&pca9959Driver);
			break;
		case 14:  /* Check Valid 20MHz Clock */
			checkExtClock(&pca9959Driver);
			break;
		default:
			PRINTF("\r\n Invalid option...chose correct one from Main Menu\r\n");
			break;
		}

		if(character != 12)
		{
			status = PCA9959_SPI_Check_Error(&pca9959Driver, &errorstate);
			if (SENSOR_ERROR_NONE != status)
			{
				PRINTF("\r\n Check Error Failed \r\n");
			}
			else
			{
				if(errorstate == errorDetected)
				{
					PRINTF("\r\n \033[31m Error Occurred on one or more LEDs...For more details goto \"LED Error \" option in main menu \033[37m \r\n");
					PRINTF("\r\n Press Enter for main menu \r\n");
					GETCHAR();
				}
			}
		}

	}
	while(1);

	return 0;
}
