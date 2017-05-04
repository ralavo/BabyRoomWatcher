/*******************************************************************************
* File Name: Timebase5s_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Timebase5s.h"

static Timebase5s_BACKUP_STRUCT Timebase5s_backup;


/*******************************************************************************
* Function Name: Timebase5s_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Timebase5s_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_Sleep(void)
{
    if(0u != (Timebase5s_BLOCK_CONTROL_REG & Timebase5s_MASK))
    {
        Timebase5s_backup.enableState = 1u;
    }
    else
    {
        Timebase5s_backup.enableState = 0u;
    }

    Timebase5s_Stop();
    Timebase5s_SaveConfig();
}


/*******************************************************************************
* Function Name: Timebase5s_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Timebase5s_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_Wakeup(void)
{
    Timebase5s_RestoreConfig();

    if(0u != Timebase5s_backup.enableState)
    {
        Timebase5s_Enable();
    }
}


/* [] END OF FILE */
