/*******************************************************************************
* File Name: PIRAmplifierStage1.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the Opamp (Analog Buffer)
*  Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PIRAmplifierStage1.h"

uint8 PIRAmplifierStage1_initVar = 0u; /* Defines if component was initialized */
static uint32 PIRAmplifierStage1_internalPower = 0u; /* Defines component Power value */


/*******************************************************************************
* Function Name: PIRAmplifierStage1_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PIRAmplifierStage1_Init(void)
{
    PIRAmplifierStage1_internalPower = PIRAmplifierStage1_POWER;
    PIRAmplifierStage1_CTB_CTRL_REG = PIRAmplifierStage1_DEFAULT_CTB_CTRL;
    PIRAmplifierStage1_OA_RES_CTRL_REG = PIRAmplifierStage1_DEFAULT_OA_RES_CTRL;
    PIRAmplifierStage1_OA_COMP_TRIM_REG = PIRAmplifierStage1_DEFAULT_OA_COMP_TRIM_REG;
}


/*******************************************************************************
* Function Name: PIRAmplifierStage1_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PIRAmplifierStage1_Enable(void)
{
    PIRAmplifierStage1_OA_RES_CTRL_REG |= PIRAmplifierStage1_internalPower | \
                                        PIRAmplifierStage1_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: PIRAmplifierStage1_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables power 
*  to the block. The first time the routine is executed, the Power level, Mode, 
*  and Output mode are set. When called to restart the Opamp following a Stop() call, 
*  the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PIRAmplifierStage1_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void PIRAmplifierStage1_Start(void)
{
    if( 0u == PIRAmplifierStage1_initVar)
    {
        PIRAmplifierStage1_Init();
        PIRAmplifierStage1_initVar = 1u;
    }
    PIRAmplifierStage1_Enable();
}


/*******************************************************************************
* Function Name: PIRAmplifierStage1_Stop
********************************************************************************
*
* Summary:
*  Turn off the Opamp block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PIRAmplifierStage1_Stop(void)
{
    PIRAmplifierStage1_OA_RES_CTRL_REG &= ((uint32)~(PIRAmplifierStage1_OA_PWR_MODE_MASK | \
                                                   PIRAmplifierStage1_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: PIRAmplifierStage1_SetPower
********************************************************************************
*
* Summary:
*  Sets the Opamp to one of the three power levels.
*
* Parameters:
*  power: power levels.
*   PIRAmplifierStage1_LOW_POWER - Lowest active power
*   PIRAmplifierStage1_MED_POWER - Medium power
*   PIRAmplifierStage1_HIGH_POWER - Highest active power
*
* Return:
*  None
*
**********************************************************************************/
void PIRAmplifierStage1_SetPower(uint32 power)
{
    uint32 tmp;
    
    PIRAmplifierStage1_internalPower = PIRAmplifierStage1_GET_OA_PWR_MODE(power);
    tmp = PIRAmplifierStage1_OA_RES_CTRL_REG & \
           (uint32)~PIRAmplifierStage1_OA_PWR_MODE_MASK;
    PIRAmplifierStage1_OA_RES_CTRL_REG = tmp | PIRAmplifierStage1_internalPower;
}


/*******************************************************************************
* Function Name: PIRAmplifierStage1_PumpControl
********************************************************************************
*
* Summary:
*  Allows the user to turn the Opamp's boost pump on or off. By Default the Start() 
*  function turns on the pump. Use this API to turn it off. The boost must be 
*  turned on when the supply is less than 2.7 volts and off if the supply is more 
*  than 4 volts.
*
* Parameters:
*  onOff: Control the pump.
*   PIRAmplifierStage1_PUMP_OFF - Turn off the pump
*   PIRAmplifierStage1_PUMP_ON - Turn on the pump
*
* Return:
*  None
*
**********************************************************************************/
void PIRAmplifierStage1_PumpControl(uint32 onOff)
{
    
    if(0u != onOff)
    {
        PIRAmplifierStage1_OA_RES_CTRL |= PIRAmplifierStage1_OA_PUMP_EN;    
    }
    else
    {
        PIRAmplifierStage1_OA_RES_CTRL &= (uint32)~PIRAmplifierStage1_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
