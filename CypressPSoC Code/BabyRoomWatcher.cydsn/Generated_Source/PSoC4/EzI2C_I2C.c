/***************************************************************************//**
* \file EzI2C_I2C.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "EzI2C_PVT.h"
#include "EzI2C_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 EzI2C_state;  /* Current state of I2C FSM */

#if(EzI2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const EzI2C_I2C_INIT_STRUCT EzI2C_configI2C =
    {
        EzI2C_I2C_MODE,
        EzI2C_I2C_OVS_FACTOR_LOW,
        EzI2C_I2C_OVS_FACTOR_HIGH,
        EzI2C_I2C_MEDIAN_FILTER_ENABLE,
        EzI2C_I2C_SLAVE_ADDRESS,
        EzI2C_I2C_SLAVE_ADDRESS_MASK,
        EzI2C_I2C_ACCEPT_ADDRESS,
        EzI2C_I2C_WAKE_ENABLE,
        EzI2C_I2C_BYTE_MODE_ENABLE,
        EzI2C_I2C_DATA_RATE,
        EzI2C_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: EzI2C_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the EzI2C for I2C operation.
    *
    *  This function is intended specifically to be used when the EzI2C 
    *  configuration is set to “Unconfigured EzI2C” in the customizer. 
    *  After initializing the EzI2C in I2C mode using this function, 
    *  the component can be enabled using the EzI2C_Start() or 
    * EzI2C_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void EzI2C_I2CInit(const EzI2C_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            EzI2C_SetPins(EzI2C_SCB_MODE_I2C, EzI2C_DUMMY_PARAM,
                                     EzI2C_DUMMY_PARAM);

            /* Store internal configuration */
            EzI2C_scbMode       = (uint8) EzI2C_SCB_MODE_I2C;
            EzI2C_scbEnableWake = (uint8) config->enableWake;
            EzI2C_scbEnableIntr = (uint8) EzI2C_SCB_IRQ_INTERNAL;

            EzI2C_mode          = (uint8) config->mode;
            EzI2C_acceptAddr    = (uint8) config->acceptAddr;

        #if (EzI2C_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            EzI2C_SET_I2C_CFG_SDA_FILT_TRIM(EzI2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (EzI2C_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((EzI2C_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= EzI2C_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (EzI2C_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                EzI2C_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = EzI2C_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                EzI2C_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = EzI2C_DIGITAL_FILTER_ENABLE;
            }

        #if (!EzI2C_CY_SCBIP_V0)
            locEnableWake = (EzI2C_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!EzI2C_CY_SCBIP_V0) */

            /* Configure I2C interface */
            EzI2C_CTRL_REG     = EzI2C_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            EzI2C_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            EzI2C_GET_CTRL_EC_AM_MODE (locEnableWake);

            EzI2C_I2C_CTRL_REG = EzI2C_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    EzI2C_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    EzI2C_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    EzI2C_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            EzI2C_RX_CTRL_REG      = EzI2C_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                EzI2C_I2C_RX_CTRL;
            EzI2C_RX_FIFO_CTRL_REG = EzI2C_CLEAR_REG;

            /* Set default address and mask */
            EzI2C_RX_MATCH_REG    = ((EzI2C_I2C_SLAVE) ?
                                                (EzI2C_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 EzI2C_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (EzI2C_CLEAR_REG));


            /* Configure TX direction */
            EzI2C_TX_CTRL_REG      = EzI2C_I2C_TX_CTRL;
            EzI2C_TX_FIFO_CTRL_REG = EzI2C_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (EzI2C_ISR_NUMBER);
            CyIntSetPriority(EzI2C_ISR_NUMBER, EzI2C_ISR_PRIORITY);
            (void) CyIntSetVector(EzI2C_ISR_NUMBER, &EzI2C_I2C_ISR);

            /* Configure interrupt sources */
        #if(!EzI2C_CY_SCBIP_V1)
            EzI2C_INTR_SPI_EC_MASK_REG = EzI2C_NO_INTR_SOURCES;
        #endif /* (!EzI2C_CY_SCBIP_V1) */

            EzI2C_INTR_I2C_EC_MASK_REG = EzI2C_NO_INTR_SOURCES;
            EzI2C_INTR_RX_MASK_REG     = EzI2C_NO_INTR_SOURCES;
            EzI2C_INTR_TX_MASK_REG     = EzI2C_NO_INTR_SOURCES;

            EzI2C_INTR_SLAVE_MASK_REG  = ((EzI2C_I2C_SLAVE) ?
                            (EzI2C_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             EzI2C_I2C_INTR_SLAVE_MASK) : (EzI2C_CLEAR_REG));

            EzI2C_INTR_MASTER_MASK_REG = ((EzI2C_I2C_MASTER) ?
                                                     (EzI2C_I2C_INTR_MASTER_MASK) :
                                                     (EzI2C_CLEAR_REG));

            /* Configure global variables */
            EzI2C_state = EzI2C_I2C_FSM_IDLE;

            /* Internal slave variables */
            EzI2C_slStatus        = 0u;
            EzI2C_slRdBufIndex    = 0u;
            EzI2C_slWrBufIndex    = 0u;
            EzI2C_slOverFlowCount = 0u;

            /* Internal master variables */
            EzI2C_mstrStatus     = 0u;
            EzI2C_mstrRdBufIndex = 0u;
            EzI2C_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: EzI2C_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void EzI2C_I2CInit(void)
    {
    #if(EzI2C_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        EzI2C_SET_I2C_CFG_SDA_FILT_TRIM(EzI2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (EzI2C_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        EzI2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        EzI2C_CTRL_REG     = EzI2C_I2C_DEFAULT_CTRL;
        EzI2C_I2C_CTRL_REG = EzI2C_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        EzI2C_RX_CTRL_REG      = EzI2C_I2C_DEFAULT_RX_CTRL;
        EzI2C_RX_FIFO_CTRL_REG = EzI2C_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        EzI2C_RX_MATCH_REG     = EzI2C_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        EzI2C_TX_CTRL_REG      = EzI2C_I2C_DEFAULT_TX_CTRL;
        EzI2C_TX_FIFO_CTRL_REG = EzI2C_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (EzI2C_ISR_NUMBER);
        CyIntSetPriority(EzI2C_ISR_NUMBER, EzI2C_ISR_PRIORITY);
    #if(!EzI2C_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(EzI2C_ISR_NUMBER, &EzI2C_I2C_ISR);
    #endif /* (EzI2C_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!EzI2C_CY_SCBIP_V1)
        EzI2C_INTR_SPI_EC_MASK_REG = EzI2C_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!EzI2C_CY_SCBIP_V1) */

        EzI2C_INTR_I2C_EC_MASK_REG = EzI2C_I2C_DEFAULT_INTR_I2C_EC_MASK;
        EzI2C_INTR_SLAVE_MASK_REG  = EzI2C_I2C_DEFAULT_INTR_SLAVE_MASK;
        EzI2C_INTR_MASTER_MASK_REG = EzI2C_I2C_DEFAULT_INTR_MASTER_MASK;
        EzI2C_INTR_RX_MASK_REG     = EzI2C_I2C_DEFAULT_INTR_RX_MASK;
        EzI2C_INTR_TX_MASK_REG     = EzI2C_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        EzI2C_state = EzI2C_I2C_FSM_IDLE;

    #if(EzI2C_I2C_SLAVE)
        /* Internal slave variable */
        EzI2C_slStatus        = 0u;
        EzI2C_slRdBufIndex    = 0u;
        EzI2C_slWrBufIndex    = 0u;
        EzI2C_slOverFlowCount = 0u;
    #endif /* (EzI2C_I2C_SLAVE) */

    #if(EzI2C_I2C_MASTER)
    /* Internal master variable */
        EzI2C_mstrStatus     = 0u;
        EzI2C_mstrRdBufIndex = 0u;
        EzI2C_mstrWrBufIndex = 0u;
    #endif /* (EzI2C_I2C_MASTER) */
    }
#endif /* (EzI2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: EzI2C_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void EzI2C_I2CStop(void)
{
    EzI2C_state = EzI2C_I2C_FSM_IDLE;
}


#if(EzI2C_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: EzI2C_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables EzI2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void EzI2C_I2CSaveConfig(void)
    {
    #if (!EzI2C_CY_SCBIP_V0)
        #if (EzI2C_I2C_MULTI_MASTER_SLAVE_CONST && EzI2C_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (EzI2C_CTRL_REG & EzI2C_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                EzI2C_Stop();
                EzI2C_CTRL_REG |= EzI2C_CTRL_EC_AM_MODE;
                EzI2C_Enable();
            }
        #endif /* (EzI2C_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (EzI2C_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            EzI2C_SCBCLK_Stop();
        #endif /* (EzI2C_SCB_CLK_INTERNAL) */
    #endif /* (!EzI2C_CY_SCBIP_V0) */

        EzI2C_SetI2CExtClkInterruptMode(EzI2C_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: EzI2C_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables EzI2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void EzI2C_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        EzI2C_SetI2CExtClkInterruptMode(EzI2C_NO_INTR_SOURCES);

    #if (!EzI2C_CY_SCBIP_V0)
        #if (EzI2C_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            EzI2C_SCBCLK_Start();
        #endif /* (EzI2C_SCB_CLK_INTERNAL) */
    #endif /* (!EzI2C_CY_SCBIP_V0) */
    }
#endif /* (EzI2C_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
