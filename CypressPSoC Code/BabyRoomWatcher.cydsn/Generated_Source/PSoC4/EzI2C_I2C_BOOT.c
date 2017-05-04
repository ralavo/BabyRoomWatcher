/***************************************************************************//**
* \file EzI2C_I2C_BOOT.c
* \version 3.20
*
* \brief
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component I2C mode.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "EzI2C_BOOT.h"
#include "EzI2C_I2C_PVT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_I2C_BTLDR_COMM_ENABLED)

/***************************************
*    Private I/O Component Vars
***************************************/

/* Writes to this buffer */
static uint8 EzI2C_slReadBuf[EzI2C_I2C_BTLDR_SIZEOF_READ_BUFFER];

/* Reads from this buffer */
static uint8 EzI2C_slWriteBuf[EzI2C_I2C_BTLDR_SIZEOF_WRITE_BUFFER];

/* Flag to release buffer to be read */
static uint32 EzI2C_applyBuffer;


/***************************************
*    Private Function Prototypes
***************************************/

static void EzI2C_I2CResposeInsert(void);


/*******************************************************************************
* Function Name: EzI2C_I2CCyBtldrCommStart
****************************************************************************//**
*
*  Starts the I2C component and enables its interrupt.
*  Every incoming I2C write transaction is treated as a command for the
*  bootloader.
*  Every incoming I2C read transaction returns 0xFF until the bootloader
*  provides a response to the executed command.
*
* \globalvars
*  EzI2C_applyBuffer - the flag to release the buffer with a response
*  to be read by the host.
*
*******************************************************************************/
void EzI2C_I2CCyBtldrCommStart(void)
{
    EzI2C_I2CSlaveInitWriteBuf(EzI2C_slWriteBuf, EzI2C_I2C_BTLDR_SIZEOF_WRITE_BUFFER);
    EzI2C_I2CSlaveInitReadBuf (EzI2C_slReadBuf, 0u);

    EzI2C_SetCustomInterruptHandler(&EzI2C_I2CResposeInsert);
    EzI2C_applyBuffer = 0u;

    EzI2C_Start();
}


/*******************************************************************************
* Function Name: EzI2C_I2CCyBtldrCommStop
****************************************************************************//**
*
*  Disables the I2C component.
*
*******************************************************************************/
void EzI2C_I2CCyBtldrCommStop(void)
{
    EzI2C_Stop();
}


/*******************************************************************************
* Function Name: EzI2C_I2CCyBtldrCommReset
****************************************************************************//**
*
*  Resets read and write I2C buffers to the initial state and resets the slave
*  status.
*
* \globalvars
*  EzI2C_slRdBufSize - used to store slave read buffer size.
*  EzI2C_slRdBufIndex - used to store the current index within the
*  slave read buffer.
*  EzI2C_slWrBufIndex - used to store current index within slave
*  write buffer.
*  EzI2C_slStatus  - used to store current status of I2C slave.
*
*******************************************************************************/
void EzI2C_I2CCyBtldrCommReset(void)
{
    /* Make read buffer full */
    EzI2C_slRdBufSize = 0u;

    /* Reset write buffer and Read buffer */
    EzI2C_slRdBufIndex = 0u;
    EzI2C_slWrBufIndex = 0u;

    /* Clear read and write status */
    EzI2C_slStatus = 0u;
}


/*******************************************************************************
* Function Name: EzI2C_I2CCyBtldrCommRead
****************************************************************************//**
*
*  Allows the caller to read data from the bootloader host (the host writes the
*  data). The function handles polling to allow a block of data to be completely
*  received from the host device.
*
*  \param pData: Pointer to storage for the block of data to be read from the
*   bootloader host
*  \param size: Number of bytes to be read.
*  \param count: Pointer to the variable to write the number of bytes actually
*   read.
*  \param timeOut: Number of units in 10 ms to wait before returning
*   because of a timeout.
*
*  \return
*   Returns CYRET_SUCCESS if no problem was encountered or returns the value
*   that best describes the problem. For more information refer to the
*   "Return Codes" section of the System Reference Guide.
*
* \globalvars
*  EzI2C_slStatus  - used to store current status of I2C slave.
*  EzI2C_slWriteBuf - used to store received command.
*  EzI2C_slWrBufIndex - used to store current index within slave
*  write buffer.
*
*******************************************************************************/
cystatus EzI2C_I2CCyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    uint32 timeoutMs;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint32) 10u * timeOut); /* Convert from 10mS check to 1mS checks */

        while (0u != timeoutMs)
        {
            /* Check if host complete write */
            if (0u != (EzI2C_I2C_SSTAT_WR_CMPLT & EzI2C_slStatus))
            {
                /* Copy number of written bytes */
                *count = (uint16) EzI2C_slWrBufIndex;

                /* Clear slave status and write index */
                EzI2C_slStatus = 0u;
                EzI2C_slWrBufIndex = 0u;

                /* Copy command into bootloader buffer */
                (void) memcpy((void *) pData, (const void *) EzI2C_slWriteBuf,
                                              EzI2C_BYTES_TO_COPY(*count, size));

                status = CYRET_SUCCESS;
                break;
            }

            CyDelay(EzI2C_WAIT_1_MS);
            --timeoutMs;
        }
    }

    return(status);
}


/*******************************************************************************
* Function Name: EzI2C_I2CCyBtldrCommWrite
****************************************************************************//**
*
*  Allows the caller to write data to the bootloader host (the host reads the
*  data). The function does not use timeout and returns after data has been
*  copied into the slave read buffer. This data is available to be read by the
*  bootloader host until following host data write.
*
*  \param pData: Pointer to the block of data to be written to the bootloader
*   host.
*  \param size: Number of bytes to be written.
*  \param count: Pointer to the variable to write the number of bytes actually
*   written.
*  \param timeOut: Number of units in 10 ms to wait before returning
*   because of a timeout.
*
*  \return
*   Returns CYRET_SUCCESS if no problem was encountered or returns the value
*   that best describes the problem. For more information refer to the
*   "Return Codes" section of the System Reference Guide.
*
* \globalvars
*  EzI2C_applyBuffer - the flag to release the buffer with
*  to be read by the host.
*
*******************************************************************************/
cystatus EzI2C_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        /* Copy response into read buffer */
        *count = size;
        (void) memcpy((void *) EzI2C_slReadBuf, (const void *) pData, (uint32) size);

        /* Read buffer is ready to be released to host */
        EzI2C_applyBuffer = (uint32) size;

        if (0u != timeOut)
        {
            /* Suppress compiler warning */
        }

        status = CYRET_SUCCESS;
    }

    return(status);
}


/*******************************************************************************
* Function Name: EzI2C_I2CResposeInsert
****************************************************************************//**
*
*  Releases the read buffer to be read when a response is copied to the buffer
*  and a new read transaction starts.
*  Closes the read buffer when write transaction is started.
*
* \globalvars
*  EzI2C_applyBuffer - the flag to release the buffer with a response
*  to be read by the host.
*
*******************************************************************************/
static void EzI2C_I2CResposeInsert(void)
{
    if (EzI2C_CHECK_INTR_SLAVE_MASKED(EzI2C_INTR_SLAVE_I2C_ADDR_MATCH))
    {
        if (EzI2C_CHECK_I2C_STATUS(EzI2C_I2C_STATUS_S_READ))
        {
            /* Address phase, host reads: release read buffer */
            if (0u != EzI2C_applyBuffer)
            {
                EzI2C_slRdBufSize  = EzI2C_applyBuffer;
                EzI2C_slRdBufIndex = 0u;
                EzI2C_applyBuffer  = 0u;
            }
        }
        else
        {
            /* Address phase, host writes: close read buffer */
            if (EzI2C_slRdBufIndex != EzI2C_slRdBufSize)
            {
                EzI2C_slRdBufIndex = EzI2C_slRdBufSize;
            }
        }
    }
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (EzI2C_I2C_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
