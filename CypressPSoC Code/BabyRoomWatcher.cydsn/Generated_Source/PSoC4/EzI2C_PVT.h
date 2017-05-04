/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_EzI2C_H)
#define CY_SCB_PVT_EzI2C_H

#include "EzI2C.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define EzI2C_SetI2CExtClkInterruptMode(interruptMask) EzI2C_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define EzI2C_ClearI2CExtClkInterruptSource(interruptMask) EzI2C_CLEAR_INTR_I2C_EC(interruptMask)
#define EzI2C_GetI2CExtClkInterruptSource()                (EzI2C_INTR_I2C_EC_REG)
#define EzI2C_GetI2CExtClkInterruptMode()                  (EzI2C_INTR_I2C_EC_MASK_REG)
#define EzI2C_GetI2CExtClkInterruptSourceMasked()          (EzI2C_INTR_I2C_EC_MASKED_REG)

#if (!EzI2C_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define EzI2C_SetSpiExtClkInterruptMode(interruptMask) \
                                                                EzI2C_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define EzI2C_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                EzI2C_CLEAR_INTR_SPI_EC(interruptMask)
    #define EzI2C_GetExtSpiClkInterruptSource()                 (EzI2C_INTR_SPI_EC_REG)
    #define EzI2C_GetExtSpiClkInterruptMode()                   (EzI2C_INTR_SPI_EC_MASK_REG)
    #define EzI2C_GetExtSpiClkInterruptSourceMasked()           (EzI2C_INTR_SPI_EC_MASKED_REG)
#endif /* (!EzI2C_CY_SCBIP_V1) */

#if(EzI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void EzI2C_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (EzI2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (EzI2C_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_EzI2C_CUSTOM_INTR_HANDLER)
    extern cyisraddress EzI2C_customIntrHandler;
#endif /* !defined (CY_REMOVE_EzI2C_CUSTOM_INTR_HANDLER) */
#endif /* (EzI2C_SCB_IRQ_INTERNAL) */

extern EzI2C_BACKUP_STRUCT EzI2C_backup;

#if(EzI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 EzI2C_scbMode;
    extern uint8 EzI2C_scbEnableWake;
    extern uint8 EzI2C_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 EzI2C_mode;
    extern uint8 EzI2C_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * EzI2C_rxBuffer;
    extern uint8   EzI2C_rxDataBits;
    extern uint32  EzI2C_rxBufferSize;

    extern volatile uint8 * EzI2C_txBuffer;
    extern uint8   EzI2C_txDataBits;
    extern uint32  EzI2C_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 EzI2C_numberOfAddr;
    extern uint8 EzI2C_subAddrSize;
#endif /* (EzI2C_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (EzI2C_SCB_MODE_I2C_CONST_CFG || \
        EzI2C_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 EzI2C_IntrTxMask;
#endif /* (! (EzI2C_SCB_MODE_I2C_CONST_CFG || \
              EzI2C_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(EzI2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define EzI2C_SCB_MODE_I2C_RUNTM_CFG     (EzI2C_SCB_MODE_I2C      == EzI2C_scbMode)
    #define EzI2C_SCB_MODE_SPI_RUNTM_CFG     (EzI2C_SCB_MODE_SPI      == EzI2C_scbMode)
    #define EzI2C_SCB_MODE_UART_RUNTM_CFG    (EzI2C_SCB_MODE_UART     == EzI2C_scbMode)
    #define EzI2C_SCB_MODE_EZI2C_RUNTM_CFG   (EzI2C_SCB_MODE_EZI2C    == EzI2C_scbMode)
    #define EzI2C_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (EzI2C_SCB_MODE_UNCONFIG == EzI2C_scbMode)

    /* Defines wakeup enable */
    #define EzI2C_SCB_WAKE_ENABLE_CHECK       (0u != EzI2C_scbEnableWake)
#endif /* (EzI2C_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!EzI2C_CY_SCBIP_V1)
    #define EzI2C_SCB_PINS_NUMBER    (7u)
#else
    #define EzI2C_SCB_PINS_NUMBER    (2u)
#endif /* (!EzI2C_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_EzI2C_H) */


/* [] END OF FILE */
