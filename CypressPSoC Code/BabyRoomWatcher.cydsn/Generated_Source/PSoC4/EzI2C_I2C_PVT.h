/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
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

#if !defined(CY_SCB_I2C_PVT_EzI2C_H)
#define CY_SCB_I2C_PVT_EzI2C_H

#include "EzI2C_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 EzI2C_state; /* Current state of I2C FSM */

#if(EzI2C_I2C_SLAVE_CONST)
    extern volatile uint8 EzI2C_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * EzI2C_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  EzI2C_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  EzI2C_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * EzI2C_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  EzI2C_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  EzI2C_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  EzI2C_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   EzI2C_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (EzI2C_I2C_SLAVE_CONST) */

#if(EzI2C_I2C_MASTER_CONST)
    extern volatile uint16 EzI2C_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  EzI2C_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * EzI2C_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  EzI2C_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  EzI2C_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * EzI2C_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  EzI2C_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  EzI2C_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  EzI2C_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (EzI2C_I2C_MASTER_CONST) */

#if (EzI2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*EzI2C_customAddressHandler) (void);
#endif /* (EzI2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(EzI2C_SCB_MODE_I2C_CONST_CFG)
    void EzI2C_I2CInit(void);
#endif /* (EzI2C_SCB_MODE_I2C_CONST_CFG) */

void EzI2C_I2CStop(void);
void EzI2C_I2CSaveConfig(void);
void EzI2C_I2CRestoreConfig(void);

#if(EzI2C_I2C_MASTER_CONST)
    void EzI2C_I2CReStartGeneration(void);
#endif /* (EzI2C_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_EzI2C_H) */


/* [] END OF FILE */
