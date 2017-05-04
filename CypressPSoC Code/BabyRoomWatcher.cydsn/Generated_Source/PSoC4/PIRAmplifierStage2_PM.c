/***************************************************************************//**
* \file     PIRAmplifierStage2_PM.c  
* \version  1.0
*
* \brief
*  This file provides the power management source code to the API for PGA_P4 
*  Component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PIRAmplifierStage2_PVT.h"


/*******************************************************************************
* Function Name: PIRAmplifierStage2_SaveConfig
****************************************************************************//**
*
*  Empty function. Included for consistency with other components.
*
*******************************************************************************/
void PIRAmplifierStage2_SaveConfig(void)
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: PIRAmplifierStage2_RestoreConfig
****************************************************************************//**
*
*  Empty function. Included for consistency with other components.
*
*******************************************************************************/
void PIRAmplifierStage2_RestoreConfig(void)
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: PIRAmplifierStage2_Sleep
****************************************************************************//**
*
*  When the "Deep sleep operation" is disabled then the function disables 
*  component's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  When the "Deep sleep operation" is enabled then the function does nothing
*  and the component continues to operate during Deep Sleep state.
*
*  \internal
*   The PIRAmplifierStage2_backup.enableState is modified 
*   depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void PIRAmplifierStage2_Sleep(void)
{
    #if(!PIRAmplifierStage2_CHECK_DEEPSLEEP_SUPPORT)
        if((PIRAmplifierStage2_OA_RES_CTRL_REG & PIRAmplifierStage2_OA_PWR_MODE_MASK) != 0u)
        {
            PIRAmplifierStage2_internalGainPower |= PIRAmplifierStage2_ENABLED;
            PIRAmplifierStage2_Stop();
        }
        else /* The component is disabled */
        {
            PIRAmplifierStage2_internalGainPower &= (uint32) ~PIRAmplifierStage2_ENABLED;
        }
        /* Save the configuration */
        PIRAmplifierStage2_SaveConfig();
    #endif /* (PIRAmplifierStage2_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: PIRAmplifierStage2_Wakeup
****************************************************************************//**
*
*  When the "Deep sleep operation" is disabled then the function enables
*  block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  When the "Deep sleep operation" is enabled then the function does nothing
*  and the component continues to operate during Active state.
*
*  \internal
*   The PIRAmplifierStage2_backup.enableState is used to 
*   restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void PIRAmplifierStage2_Wakeup(void)
{
    #if(!PIRAmplifierStage2_CHECK_DEEPSLEEP_SUPPORT)
        /* Restore the configurations */
        PIRAmplifierStage2_RestoreConfig();
        /* Enables the component operation */
        if((PIRAmplifierStage2_internalGainPower & PIRAmplifierStage2_ENABLED) != 0u)
        {
            PIRAmplifierStage2_Enable();
        } /* Do nothing if component was disabled before */
    #endif /* (PIRAmplifierStage2_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */
