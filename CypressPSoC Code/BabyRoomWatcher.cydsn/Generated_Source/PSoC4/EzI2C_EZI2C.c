/***************************************************************************//**
* \file EzI2C_EZI2C.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  EZI2C mode.
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
#include "EzI2C_EZI2C_PVT.h"


/***************************************
*      EZI2C Private Vars
***************************************/

volatile uint8 EzI2C_curStatus; /* Status byte */
uint8 EzI2C_fsmState;           /* FSM state   */

/* Variables intended to be used with Buffer 1: Primary slave address */
volatile uint8 * EzI2C_dataBuffer1; /* Pointer to data buffer 1 */
uint16 EzI2C_bufSizeBuf1;           /* Size of buffer 1 in bytes      */
uint16 EzI2C_protectBuf1;           /* Start index of write protected area buffer 1 */
uint8 EzI2C_offsetBuf1; /* Current offset within buffer 1 */
uint16 EzI2C_indexBuf1;             /* Current index within buffer 1  */

#if(EzI2C_SECONDARY_ADDRESS_ENABLE_CONST)
    uint8 EzI2C_addrBuf1; /* Primary slave address. Used for software comparison   */
    uint8 EzI2C_addrBuf2; /* Secondary slave address. Used for software comparison */

    /* Variables intended to be used with Buffer 2: Primary slave address */
    volatile uint8 * EzI2C_dataBuffer2; /* Pointer to data buffer 2 */
    uint16 EzI2C_bufSizeBuf2;           /* Size of buffer 2 in bytes */
    uint16 EzI2C_protectBuf2;           /* Start index of write protected area buffer 2 */
    uint8 EzI2C_offsetBuf2; /* Current offset within buffer 2 */
    uint16 EzI2C_indexBuf2;             /* Current index within buffer 2 */
#endif /* (EzI2C_SECONDARY_ADDRESS_ENABLE_CONST) */


/***************************************
*      EZI2C Private Functions
***************************************/

#if(EzI2C_SECONDARY_ADDRESS_ENABLE_CONST)
    static uint32 EzI2C_EzI2CUpdateRxMatchReg(uint32 addr1, uint32 addr2);
#endif /* (EzI2C_SECONDARY_ADDRESS_ENABLE_CONST) */

#if(EzI2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of EZI2C */
    const EzI2C_EZI2C_INIT_STRUCT EzI2C_configEzI2C =
    {
        EzI2C_EZI2C_CLOCK_STRETCHING,
        EzI2C_EZI2C_MEDIAN_FILTER_ENABLE,
        EzI2C_EZI2C_NUMBER_OF_ADDRESSES,
        EzI2C_EZI2C_PRIMARY_SLAVE_ADDRESS,
        EzI2C_EZI2C_SECONDARY_SLAVE_ADDRESS,
        EzI2C_EZI2C_SUB_ADDRESS_SIZE,
        EzI2C_EZI2C_WAKE_ENABLE,
        EzI2C_EZI2C_BYTE_MODE_ENABLE
    };

    /*******************************************************************************
    * Function Name: EzI2C_EzI2CInit
    ****************************************************************************//**
    *
    *  Configures the EzI2C for EZI2C operation.
    *
    *  This function is intended specifically to be used when the EzI2C 
    *  configuration is set to “Unconfigured EzI2C” in the customizer. 
    *  After initializing the EzI2C in EZI2C mode using this function, 
    *  the component can be enabled using the EzI2C_Start() or 
    * EzI2C_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    * \param config: pointer to a structure that contains the following list of 
    *  fields. These fields match the selections available in the customizer. 
    *  Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void EzI2C_EzI2CInit(const EzI2C_EZI2C_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            EzI2C_SetPins(EzI2C_SCB_MODE_EZI2C, EzI2C_DUMMY_PARAM,
                                                                      EzI2C_DUMMY_PARAM);

            /* Store internal configuration */
            EzI2C_scbMode       = (uint8) EzI2C_SCB_MODE_EZI2C;
            EzI2C_scbEnableWake = (uint8) config->enableWake;
            EzI2C_scbEnableIntr = (uint8) EzI2C_SCB_IRQ_INTERNAL;

            EzI2C_numberOfAddr  = (uint8) config->numberOfAddresses;
            EzI2C_subAddrSize   = (uint8) config->subAddrSize;

        #if (EzI2C_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            EzI2C_SET_I2C_CFG_SDA_FILT_TRIM(EzI2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (EzI2C_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings, AF = 1, DF = 0. Ticket ID#176179 */
            EzI2C_I2C_CFG_ANALOG_FITER_ENABLE;

            /* Configure I2C interface */
            EzI2C_CTRL_REG     = EzI2C_GET_CTRL_BYTE_MODE  (config->enableByteMode)    |
                                            EzI2C_GET_CTRL_ADDR_ACCEPT(config->numberOfAddresses) |
                                            EzI2C_GET_CTRL_EC_AM_MODE (config->enableWake);

            EzI2C_I2C_CTRL_REG = EzI2C_EZI2C_CTRL;

            /* Configure RX direction */
            EzI2C_RX_CTRL_REG = EzI2C_EZI2C_RX_CTRL |
                                        EzI2C_GET_RX_CTRL_MEDIAN(EzI2C_DIGITAL_FILTER_DISABLE);
                                                ;
            EzI2C_RX_FIFO_CTRL_REG = EzI2C_CLEAR_REG;

            /* Set default address and mask */
            if(EzI2C_EZI2C_PRIMARY_ADDRESS == config->numberOfAddresses)
            {
                EzI2C_RX_MATCH_REG = EzI2C_EzI2CUpdateRxMatchReg(config->primarySlaveAddr,
                                                                                       config->primarySlaveAddr);
            }
            else
            {
                EzI2C_RX_MATCH_REG = EzI2C_EzI2CUpdateRxMatchReg(config->primarySlaveAddr,
                                                                                       config->secondarySlaveAddr);
            }

            /* Configure TX direction */
            EzI2C_TX_CTRL_REG      = EzI2C_EZI2C_TX_CTRL;
            EzI2C_TX_FIFO_CTRL_REG = ((0u != (config->enableClockStretch)) ?
                                                 EzI2C_CLEAR_REG : EzI2C_EZI2C_TX_FIFO_CTRL);

            /* Configure interrupt sources */
        #if (!EzI2C_CY_SCBIP_V1)
           EzI2C_INTR_SPI_EC_MASK_REG = EzI2C_NO_INTR_SOURCES;
        #endif /* (!EzI2C_CY_SCBIP_V1) */

            EzI2C_INTR_I2C_EC_MASK_REG = EzI2C_NO_INTR_SOURCES;
            EzI2C_INTR_MASTER_MASK_REG = EzI2C_NO_INTR_SOURCES;
            EzI2C_INTR_SLAVE_MASK_REG  = EzI2C_EZI2C_INTR_SLAVE_MASK;
            EzI2C_INTR_TX_MASK_REG     = EzI2C_NO_INTR_SOURCES;

            /* Configure interrupt with EZI2C handler but do not enable it */
            CyIntDisable    (EzI2C_ISR_NUMBER);
            CyIntSetPriority(EzI2C_ISR_NUMBER, EzI2C_ISR_PRIORITY);
            (void) CyIntSetVector(EzI2C_ISR_NUMBER, (0u != (config->enableClockStretch)) ?
                                                                      (&EzI2C_EZI2C_STRETCH_ISR) :
                                                                      (&EzI2C_EZI2C_NO_STRETCH_ISR));

            if(0u != (config->enableClockStretch))
            {
                /* Configure interrupt sources */
                EzI2C_INTR_SLAVE_MASK_REG |= EzI2C_INTR_SLAVE_I2C_ADDR_MATCH;
                EzI2C_INTR_RX_MASK_REG     = EzI2C_NO_INTR_SOURCES;
            }
            else
            {
                /* Enable Auto ACK/NACK features */
                EzI2C_I2C_CTRL_REG |= EzI2C_EZI2C_CTRL_AUTO;

                /* Configure RX interrupt source */
                EzI2C_INTR_SLAVE_MASK_REG |= EzI2C_INTR_SLAVE_I2C_START;
                EzI2C_INTR_RX_MASK_REG     = EzI2C_INTR_RX_NOT_EMPTY;
            }

            /* Configure global variables */
            EzI2C_fsmState = EzI2C_EZI2C_FSM_IDLE;

            EzI2C_curStatus  = 0u;
            EzI2C_indexBuf1  = 0u;
            EzI2C_offsetBuf1 = 0u;
            EzI2C_indexBuf2  = 0u;
            EzI2C_offsetBuf2 = 0u;

            EzI2C_addrBuf1 = (uint8) config->primarySlaveAddr;
            EzI2C_addrBuf2 = (uint8) config->secondarySlaveAddr;
        }
    }

#else

    /*******************************************************************************
    * Function Name: EzI2C_EzI2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the EZI2C operation.
    *
    *******************************************************************************/
    void EzI2C_EzI2CInit(void)
    {
        /* Configure I2C interface */
        EzI2C_CTRL_REG     = EzI2C_EZI2C_DEFAULT_CTRL;
        EzI2C_I2C_CTRL_REG = EzI2C_EZI2C_DEFAULT_I2C_CTRL;

    #if (EzI2C_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        EzI2C_SET_I2C_CFG_SDA_FILT_TRIM(EzI2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (EzI2C_CY_SCBIP_V0) */

        /* Configure RX direction */
        EzI2C_RX_CTRL_REG      = EzI2C_EZI2C_DEFAULT_RX_CTRL;
        EzI2C_RX_FIFO_CTRL_REG = EzI2C_EZI2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        EzI2C_RX_MATCH_REG     = EzI2C_EZI2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        EzI2C_TX_CTRL_REG      = EzI2C_EZI2C_DEFAULT_TX_CTRL;
        EzI2C_TX_FIFO_CTRL_REG = EzI2C_EZI2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with EZI2C handler but do not enable it */
    #if !defined (CY_EXTERNAL_INTERRUPT_CONFIG)
        CyIntDisable    (EzI2C_ISR_NUMBER);
        CyIntSetPriority(EzI2C_ISR_NUMBER, EzI2C_ISR_PRIORITY);

    #if (EzI2C_EZI2C_SCL_STRETCH_ENABLE_CONST)
        (void) CyIntSetVector(EzI2C_ISR_NUMBER, &EzI2C_EZI2C_STRETCH_ISR);
    #else
        (void) CyIntSetVector(EzI2C_ISR_NUMBER, &EzI2C_EZI2C_NO_STRETCH_ISR);
    #endif /* (EzI2C_EZI2C_SCL_STRETCH_ENABLE_CONST) */

    #endif /* !defined (CY_EXTERNAL_INTERRUPT_CONFIG) */

        /* Configure interrupt sources */
    #if (!EzI2C_CY_SCBIP_V1)
        EzI2C_INTR_SPI_EC_MASK_REG = EzI2C_EZI2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!EzI2C_CY_SCBIP_V1) */

        EzI2C_INTR_I2C_EC_MASK_REG = EzI2C_EZI2C_DEFAULT_INTR_I2C_EC_MASK;
        EzI2C_INTR_SLAVE_MASK_REG  = EzI2C_EZI2C_DEFAULT_INTR_SLAVE_MASK;
        EzI2C_INTR_MASTER_MASK_REG = EzI2C_EZI2C_DEFAULT_INTR_MASTER_MASK;
        EzI2C_INTR_RX_MASK_REG     = EzI2C_EZI2C_DEFAULT_INTR_RX_MASK;
        EzI2C_INTR_TX_MASK_REG     = EzI2C_EZI2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        EzI2C_fsmState = EzI2C_EZI2C_FSM_IDLE;

        EzI2C_curStatus  = 0u;
        EzI2C_indexBuf1  = 0u;
        EzI2C_offsetBuf1 = 0u;

    #if(EzI2C_SECONDARY_ADDRESS_ENABLE_CONST)
        EzI2C_indexBuf2  = 0u;
        EzI2C_offsetBuf2 = 0u;

        EzI2C_addrBuf1 = EzI2C_EZI2C_PRIMARY_SLAVE_ADDRESS;
        EzI2C_addrBuf2 = EzI2C_EZI2C_SECONDARY_SLAVE_ADDRESS;
    #endif /* (EzI2C_SECONDARY_ADDRESS_ENABLE_CONST) */
    }
#endif /* (EzI2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: EzI2C_EzI2CStop
****************************************************************************//**
*
*  Resets the EZI2C FSM into the default state.
*
*******************************************************************************/
void EzI2C_EzI2CStop(void)
{
    EzI2C_fsmState = EzI2C_EZI2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: EzI2C_EzI2CGetActivity
****************************************************************************//**
*
*  Returns the EZI2C slave status.
*  The read, write and error status flags reset to zero after this function
*  call. The busy status flag is cleared when the transaction intended for
*  the EZI2C slave completes.
*
* \return
*  Returns the status of the EZI2C Slave activity.
*  - EzI2C_EZI2C_STATUS_READ1 - Read transfer complete. The transfer 
*    used the primary slave address. The error condition status bit must be 
*    checked to ensure that read transfer was completed successfully.
*  - EzI2C_EZI2C_STATUS_WRITE1 - Write transfer complete. The buffer 
*    content was modified. The transfer used the primary slave address. 
*    The error condition status bit must be checked to ensure that write 
*    transfer was completed successfully.
*  - EzI2C_EZI2C_STATUS_READ2 - Read transfer complete. The transfer
*    used the secondary slave address. The error condition status bit must be 
*    checked to ensure that read transfer was completed successfully.
*  - EzI2C_EZI2C_STATUS_WRITE2 - Write transfer complete. The buffer
*    content was modified. The transfer used the secondary slave address. 
*    The error condition status bit must be checked to ensure that write 
*    transfer was completed successfully.
*  - EzI2C_EZI2C_STATUS_BUSY - A transfer intended for the primary 
*    or secondary address is in progress. The status bit is set after an 
*    address match and cleared on a Stop or ReStart condition.
*  - EzI2C_EZI2C_STATUS_ERR - An error occurred during a transfer 
*    intended for the primary or secondary slave address. The sources of error
*    are: misplaced Start or Stop condition or lost arbitration while slave 
*    drives SDA.
*    The write buffer may contain invalid byte or part of the transaction when 
*    EzI2C_EZI2C_STATUS_ERR and EzI2C_EZI2C_STATUS_WRITE1/2 
*    is set. It is recommended to discard buffer content in this case.
*
* \globalvars
*  EzI2C_curStatus - used to store the current status of the EZI2C 
*  slave.
*
*******************************************************************************/
uint32 EzI2C_EzI2CGetActivity(void)
{
    uint32 status;

    EzI2C_DisableInt();  /* Lock from interruption */

    status = EzI2C_curStatus;

    /* Relay on address match event from HW as bus busy status */
    #if(EzI2C_EZI2C_SCL_STRETCH_DISABLE)
    {
        /* For EzI2C_CY_SCBIP_V0 the wake is prohibited by customizer */
        #if(EzI2C_EZI2C_EC_AM_ENABLE)
        {
            status |= EzI2C_CHECK_INTR_I2C_EC(EzI2C_INTR_I2C_EC_WAKE_UP) ?
                        EzI2C_EZI2C_STATUS_BUSY : 0u;
        }
        #else
        {
            status |= EzI2C_CHECK_INTR_SLAVE(EzI2C_INTR_SLAVE_I2C_ADDR_MATCH) ?
                        EzI2C_EZI2C_STATUS_BUSY : 0u;
        }
        #endif
    }
    #endif

    EzI2C_curStatus &= ((uint8) ~EzI2C_EZI2C_CLEAR_STATUS);

    EzI2C_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: EzI2C_EzI2CSetAddress1
****************************************************************************//**
*
*  Sets the primary EZI2C slave address.
*
* \param address: I2C slave address for the secondary device.
*  This address is the 7-bit right-justified slave address and does not 
*   include the R/W bit.
*
*  The address value is not checked to see if it violates the I2C spec. 
*  The preferred addresses are in the range between 8 and 120 (0x08 to 0x78).
*
* \globalvars
*  EzI2C_addrBuf1 - used to store the primary 7-bit slave address 
*  value.
*
*******************************************************************************/
void EzI2C_EzI2CSetAddress1(uint32 address)
{
    #if(EzI2C_SECONDARY_ADDRESS_ENABLE)
    {
        EzI2C_addrBuf1 = (uint8) address;

        EzI2C_RX_MATCH_REG = 
                        EzI2C_EzI2CUpdateRxMatchReg(address, (uint32) EzI2C_addrBuf2);
    }
    #else
    {
        uint32 matchReg;

        matchReg = EzI2C_RX_MATCH_REG;

        /* Set address. */
        matchReg &= (uint32) ~EzI2C_RX_MATCH_ADDR_MASK;
        matchReg |= (uint32)  EzI2C_GET_I2C_8BIT_ADDRESS(address);

        EzI2C_RX_MATCH_REG = matchReg;
    }
    #endif
}


/*******************************************************************************
* Function Name: EzI2C_EzI2CGetAddress1
****************************************************************************//**
*
*  Returns primary the EZ I2C slave address.
*  This address is the 7-bit right-justified slave address and does not include 
*  the R/W bit.
*
* \return
*  Primary EZI2C slave address.
*
* \globalvars
*  EzI2C_addrBuf1 - used to store the primary 7-bit slave address 
*  value.
*
*******************************************************************************/
uint32 EzI2C_EzI2CGetAddress1(void)
{
    uint32 address;

    #if(EzI2C_SECONDARY_ADDRESS_ENABLE)
    {
        address = (uint32) EzI2C_addrBuf1;
    }
    #else
    {
        address = (EzI2C_GET_RX_MATCH_ADDR(EzI2C_RX_MATCH_REG) >>
                   EzI2C_I2C_SLAVE_ADDR_POS);
    }
    #endif

    return(address);
}


/*******************************************************************************
* Function Name: EzI2C_EzI2CSetBuffer1
****************************************************************************//**
*
*  Sets up the data buffer to be exposed to the I2C master on a primary slave
*  address request.
*
* \param bufSize: Size of the buffer in bytes.
* \param rwBoundary: Number of data bytes starting from the beginning of the 
*  buffer with read and write access. Data bytes located at offset rwBoundary 
*  or greater are read only.
*  This value must be less than or equal to the buffer size.
* \param buffer: Pointer to the data buffer.
*
* \sideeffect
*  Calling this function in the middle of a transaction intended for the 
*  primary slave address leads to unexpected behavior.
*
* \globalvars
*  EzI2C_dataBuffer1 – the pointer to the buffer to be exposed to the
*  master on a primary address.
*  EzI2C_bufSizeBuf1 - the size of the buffer to be exposed to the 
*  master on a primary address.
*  EzI2C_protectBuf1 - the start index of the read-only region in the
*  buffer to be exposed to the master on a primary address. The read-only region
*  continues up to the end the buffer.
*
*******************************************************************************/
void EzI2C_EzI2CSetBuffer1(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer)
{
    if (NULL != buffer)
    {
        EzI2C_DisableInt();  /* Lock from interruption */

        EzI2C_dataBuffer1 =  buffer;
        EzI2C_bufSizeBuf1 = (uint16) bufSize;
        EzI2C_protectBuf1 = (uint16) rwBoundary;

        EzI2C_EnableInt();   /* Release lock */
    }
}


/*******************************************************************************
* Function Name: EzI2C_EzI2CSetReadBoundaryBuffer1
****************************************************************************//**
*
*  Sets the read only boundary in the data buffer to be exposed to the I2C
*  master on a primary slave address request.
*
* \param rwBoundry: Number of data bytes starting from the beginning of the 
*  buffer with read and write access. Data bytes located at offset rwBoundary 
*  or greater are read only.
*  This value must be less than or equal to the buffer size.
*
* \sideeffect
*  Calling this function in the middle of a transaction intended for the 
*  primary slave address leads to unexpected behavior.
*
* \globalvars
*  EzI2C_protectBuf1 - the start index of the read-only region in the
*  buffer to be exposed to the master on a primary address. The read-only region
*  continues up to the end the buffer.
*
*******************************************************************************/
void EzI2C_EzI2CSetReadBoundaryBuffer1(uint32 rwBoundary)
{
    EzI2C_protectBuf1 = (uint16) rwBoundary;
}


#if(EzI2C_SECONDARY_ADDRESS_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: EzI2C_EzI2CUpdateRxMatchReg
    ****************************************************************************//**
    *
    *  Returns the value of the RX MATCH register for addr1 and addr2. The addr1 is
    *  accepted as the primary address and it is written to RX_MATCH.ADDRESS
    *  (addr1 << 0x01).
    *  The RX_MATCH.MASK is set as follow: addr1 and addr2 equal bits set to 1
    *  otherwise 0.
    *
    * \param addr1: I2C slave address for the primary device.
    * \param addr2: I2C slave address for the secondary device.
    *  This address is the 7-bit right-justified slave address and does
    *  not include the R/W bit.
    *
    * \return
    *  Value of RX MATCH register.
    *
    *******************************************************************************/
    static uint32 EzI2C_EzI2CUpdateRxMatchReg(uint32 addr1, uint32 addr2)
    {
        uint32 matchReg;

        matchReg  = ~(addr1 ^ addr2); /* If (addr1 and addr2) bit matches - mask bit equals 1, in other case 0 */

        matchReg  = (uint32) (EzI2C_GET_I2C_8BIT_ADDRESS(matchReg) << EzI2C_RX_MATCH_MASK_POS);
        matchReg |= EzI2C_GET_I2C_8BIT_ADDRESS(addr1);

        return(matchReg);
    }

    /*******************************************************************************
    * Function Name: EzI2C_EzI2CSetAddress2
    ****************************************************************************//**
    *
    *  Sets the secondary EZI2C slave address.
    *
    * \param address: secondary I2C slave address.
    *  This address is the 7-bit right-justified slave address and does not 
    *  include the R/W bit.
    *  The address value is not checked to see if it violates the I2C spec. 
    *  The preferred addresses are in the range between 8 and 120 (0x08 to 0x78).
    *
    * \globalvars
    *  EzI2C_addrBuf2 - used to store the secondary 7-bit slave address 
    *  value.
    *
    *******************************************************************************/
    void EzI2C_EzI2CSetAddress2(uint32 address)
    {
        EzI2C_addrBuf2 = (uint8) address;

        EzI2C_RX_MATCH_REG = 
                        EzI2C_EzI2CUpdateRxMatchReg((uint32) EzI2C_addrBuf1, address);
    }


    /*******************************************************************************
    * Function Name: EzI2C_EzI2CGetAddress2
    ****************************************************************************//**
    *
    *  Returns the secondary EZ I2C slave address.
    *  This address is the 7-bit right-justified slave address and does not include 
    *  the R/W bit.
    *
    * \return
    *  Secondary I2C slave address.
    *
    * \globalvars
    *  EzI2C_addrBuf2 - used to store the secondary 7-bit slave address 
    *  value.
    *
    *******************************************************************************/
    uint32 EzI2C_EzI2CGetAddress2(void)
    {
        return((uint32) EzI2C_addrBuf2);
    }


    /*******************************************************************************
    * Function Name: EzI2C_EzI2CSetBuffer2
    ****************************************************************************//**
    *
    *  Sets up the data buffer to be exposed to the I2C master on a secondary slave
    *  address request.
    *
    * \param bufSize: Size of the buffer in bytes.
    * \param rwBoundary: Number of data bytes starting from the beginning of the 
    *  buffer with read and write access. Data bytes located at offset rwBoundary 
    *  or greater are read only.
    *  This value must be less than or equal to the buffer size.
    * \param buffer: Pointer to the data buffer.
    *
    * \sideeffects
    *  Calling this function in the middle of a transaction intended for the 
    *  secondary slave address leads to unexpected behavior.
    *
    * \globalvars
    *  EzI2C_dataBuffer2 – the pointer to the buffer to be exposed to the
    *  master on a secondary address.
    *  EzI2C_bufSizeBuf2 - the size of the buffer to be exposed to the 
    *  master on a secondary address.
    *  EzI2C_protectBuf2 - the start index of the read-only region in the
    *  buffer to be exposed to the master on a secondary address. The read-only 
    *  region continues up to the end the buffer.
    *
    *******************************************************************************/
    void EzI2C_EzI2CSetBuffer2(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer)
    {
        if (NULL != buffer)
        {
            EzI2C_DisableInt();  /* Lock from interruption */

            EzI2C_dataBuffer2 =  buffer;
            EzI2C_bufSizeBuf2 = (uint16) bufSize;
            EzI2C_protectBuf2 = (uint16) rwBoundary;

            EzI2C_EnableInt();   /* Release lock */
        }
    }


    /*******************************************************************************
    * Function Name: EzI2C_EzI2CSetReadBoundaryBuffer2
    ****************************************************************************//**
    *
    *  Sets the read only boundary in the data buffer to be exposed to the I2C
    *  master on a secondary address request.
    *
    *  \param rwBoundary: Number of data bytes starting from the beginning of the
    *   buffer with read and write access. Data bytes located at offset rwBoundary 
    *   or greater are read only.
    *   This value must be less than or equal to the buffer size.
    *
    *  \sideeffect
    *   Calling this function in the middle of a transaction intended for the 
    *   secondary slave address leads to unexpected behavior.
    *
    * \globalvars
    *  EzI2C_protectBuf2 - the start index of the read-only region in the
    *  buffer to be exposed to the master on a secondary address. The read-only 
    *  region continues up to the end the buffe
    *
    *******************************************************************************/
    void EzI2C_EzI2CSetReadBoundaryBuffer2(uint32 rwBoundary)
    {
        EzI2C_protectBuf2 = (uint16) rwBoundary;
    }

#endif /* (EzI2C_SECONDARY_ADDRESS_ENABLE_CONST) */


#if(EzI2C_EZI2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: EzI2C_EzI2CSaveConfig
    ****************************************************************************//**
    *
    *  Clock stretching is  enabled: Enables INTR_I2C_EC.WAKE_UP interrupt source.
    *  It triggers on the slave address match.
    *  Clock stretching is disabled: Waits until the I2C slave becomes free and
    *  disables the block to perform reconfiguration from the active mode operation
    *  to deep sleep with wake up on the address match: enables INTR_I2C_EC.WAKE_UP
    *  interrupt source and disables the INTR_S and INTR_TX interrupt sources.
    *  The block is disabled before reconfiguration and enabled when
    *  it is completed.
    *
    *******************************************************************************/
    void EzI2C_EzI2CSaveConfig(void)
    {
    #if(EzI2C_CY_SCBIP_V0)

        #if(EzI2C_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Enable wakeup interrupt source on address match */
            EzI2C_SetI2CExtClkInterruptMode(EzI2C_INTR_I2C_EC_WAKE_UP);
        }
        #endif

    #else
        uint8 enableInt;

        enableInt = (uint8) EzI2C_INTR_I2C_EC_WAKE_UP;

        #if(EzI2C_EZI2C_SCL_STRETCH_ENABLE)
        {
        #if (EzI2C_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID #187931 */
            EzI2C_SCBCLK_Stop();
        #endif /* (EzI2C_SCB_CLK_INTERNAL) */

            /* Enable interrupt source to wakeup device */
            EzI2C_SetI2CExtClkInterruptMode(enableInt);
        }
        #else
        {
            for(;;) /* Wait for end of transaction intended to slave */
            {
                if(0u == (EzI2C_GetI2CExtClkInterruptSource() & EzI2C_INTR_I2C_EC_WAKE_UP))
                {
                    enableInt = CyEnterCriticalSection();

                    if(0u == (EzI2C_GetI2CExtClkInterruptSource() & EzI2C_INTR_I2C_EC_WAKE_UP))
                    {
                        /* Attempts to set NACK command before disable block */
                        EzI2C_I2C_SLAVE_GENERATE_NACK;

                        if(0u == (EzI2C_GetI2CExtClkInterruptSource() & EzI2C_INTR_I2C_EC_WAKE_UP))
                        {
                            /* NACK command was set before. It is safe to disable block */
                            EzI2C_CTRL_REG &= (uint32) ~EzI2C_CTRL_ENABLED;
                            EzI2C_DisableInt();

                            CyExitCriticalSection(enableInt);
                            break;
                        }
                        else
                        {
                            /* Clear NACK command to prevent data NACK */
                            EzI2C_I2C_SLAVE_CLEAR_NACK;
                        }
                    }

                    CyExitCriticalSection(enableInt);
                }
            }

            /* Disable all active mode interrupt sources */
            EzI2C_SetTxInterruptMode(EzI2C_NO_INTR_SOURCES);
            EzI2C_SetSlaveInterruptMode(EzI2C_NO_INTR_SOURCES);
            EzI2C_ClearPendingInt();
            EzI2C_EnableInt();

            /* Enable wakeup interrupt on address match */
            EzI2C_SetI2CExtClkInterruptMode(EzI2C_INTR_I2C_EC_WAKE_UP);

            enableInt = CyEnterCriticalSection();

            EzI2C_CTRL_REG |= (uint32) EzI2C_CTRL_ENABLED;
            EzI2C_I2C_SLAVE_GENERATE_NACK;

            CyExitCriticalSection(enableInt);
        }
        #endif
    #endif /* (EzI2C_CY_SCBIP_V0) */
    }


    /*******************************************************************************
    * Function Name: EzI2C_EzI2CRestoreConfig
    ****************************************************************************//**
    *
    *  Clock stretching is  enabled: Disables the INTR_I2C_EC.WAKE_UP interrupt
    *  source.
    *  Clock stretching is disabled: Reconfigures the EZI2C component from
    *  Deep Sleep (wake up on the address match) to active operation: disables
    *  the INTR_I2C_EC.WAKE_UP interrupt source and restores the INTR_S
    *  interrupt sources to operate in the active mode.
    *  The block is disabled before reconfiguration and enabled when
    *  it is completed.
    *
    *******************************************************************************/
    void EzI2C_EzI2CRestoreConfig(void)
    {
    #if(EzI2C_CY_SCBIP_V0)

        #if(EzI2C_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Disable wakeup interrupt on address match */
            EzI2C_SetI2CExtClkInterruptMode(EzI2C_NO_INTR_SOURCES);
        }
        #endif

    #else

        #if(EzI2C_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Disable wakeup interrupt source on address match */
            EzI2C_SetI2CExtClkInterruptMode(EzI2C_NO_INTR_SOURCES);

        #if (EzI2C_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID #187931 */
            EzI2C_SCBCLK_Start();
        #endif /* (EzI2C_SCB_CLK_INTERNAL) */
        }
        #else
        {
            /* NACK will be driven on the bus by wakeup or NACK command.
            * It is safe to disable block to restore active mode configuration.
            */
            EzI2C_CTRL_REG &= (uint32) ~EzI2C_CTRL_ENABLED;

            /* Restore active mode interrupt sources */
            EzI2C_SetI2CExtClkInterruptMode(EzI2C_NO_INTR_SOURCES);
            EzI2C_SetSlaveInterruptMode(EzI2C_EZI2C_INTR_SLAVE_MASK |
                                                   EzI2C_INTR_SLAVE_I2C_START);
            EzI2C_ClearPendingInt();

            EzI2C_CTRL_REG |= (uint32) EzI2C_CTRL_ENABLED;
        }
        #endif

    #endif /* (EzI2C_CY_SCBIP_V0) */
    }
#endif /* (EzI2C_EZI2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
