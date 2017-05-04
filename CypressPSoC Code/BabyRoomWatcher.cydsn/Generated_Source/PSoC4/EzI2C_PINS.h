/***************************************************************************//**
* \file EzI2C_PINS.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_EzI2C_H)
#define CY_SCB_PINS_EzI2C_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define EzI2C_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define EzI2C_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define EzI2C_REMOVE_TX_SDA_MISO_PIN      (1u)
#define EzI2C_REMOVE_CTS_SCLK_PIN      (1u)
#define EzI2C_REMOVE_RTS_SS0_PIN      (1u)
#define EzI2C_REMOVE_SS1_PIN                 (1u)
#define EzI2C_REMOVE_SS2_PIN                 (1u)
#define EzI2C_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define EzI2C_REMOVE_I2C_PINS                (0u)
#define EzI2C_REMOVE_SPI_MASTER_PINS         (1u)
#define EzI2C_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define EzI2C_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define EzI2C_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define EzI2C_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define EzI2C_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define EzI2C_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define EzI2C_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define EzI2C_REMOVE_SPI_SLAVE_PINS          (1u)
#define EzI2C_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define EzI2C_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define EzI2C_REMOVE_UART_TX_PIN             (1u)
#define EzI2C_REMOVE_UART_RX_TX_PIN          (1u)
#define EzI2C_REMOVE_UART_RX_PIN             (1u)
#define EzI2C_REMOVE_UART_RX_WAKE_PIN        (1u)
#define EzI2C_REMOVE_UART_RTS_PIN            (1u)
#define EzI2C_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define EzI2C_RX_WAKE_SCL_MOSI_PIN (0u == EzI2C_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define EzI2C_RX_SCL_MOSI_PIN     (0u == EzI2C_REMOVE_RX_SCL_MOSI_PIN)
#define EzI2C_TX_SDA_MISO_PIN     (0u == EzI2C_REMOVE_TX_SDA_MISO_PIN)
#define EzI2C_CTS_SCLK_PIN     (0u == EzI2C_REMOVE_CTS_SCLK_PIN)
#define EzI2C_RTS_SS0_PIN     (0u == EzI2C_REMOVE_RTS_SS0_PIN)
#define EzI2C_SS1_PIN                (0u == EzI2C_REMOVE_SS1_PIN)
#define EzI2C_SS2_PIN                (0u == EzI2C_REMOVE_SS2_PIN)
#define EzI2C_SS3_PIN                (0u == EzI2C_REMOVE_SS3_PIN)

/* Mode defined pins */
#define EzI2C_I2C_PINS               (0u == EzI2C_REMOVE_I2C_PINS)
#define EzI2C_SPI_MASTER_PINS        (0u == EzI2C_REMOVE_SPI_MASTER_PINS)
#define EzI2C_SPI_MASTER_SCLK_PIN    (0u == EzI2C_REMOVE_SPI_MASTER_SCLK_PIN)
#define EzI2C_SPI_MASTER_MOSI_PIN    (0u == EzI2C_REMOVE_SPI_MASTER_MOSI_PIN)
#define EzI2C_SPI_MASTER_MISO_PIN    (0u == EzI2C_REMOVE_SPI_MASTER_MISO_PIN)
#define EzI2C_SPI_MASTER_SS0_PIN     (0u == EzI2C_REMOVE_SPI_MASTER_SS0_PIN)
#define EzI2C_SPI_MASTER_SS1_PIN     (0u == EzI2C_REMOVE_SPI_MASTER_SS1_PIN)
#define EzI2C_SPI_MASTER_SS2_PIN     (0u == EzI2C_REMOVE_SPI_MASTER_SS2_PIN)
#define EzI2C_SPI_MASTER_SS3_PIN     (0u == EzI2C_REMOVE_SPI_MASTER_SS3_PIN)
#define EzI2C_SPI_SLAVE_PINS         (0u == EzI2C_REMOVE_SPI_SLAVE_PINS)
#define EzI2C_SPI_SLAVE_MOSI_PIN     (0u == EzI2C_REMOVE_SPI_SLAVE_MOSI_PIN)
#define EzI2C_SPI_SLAVE_MISO_PIN     (0u == EzI2C_REMOVE_SPI_SLAVE_MISO_PIN)
#define EzI2C_UART_TX_PIN            (0u == EzI2C_REMOVE_UART_TX_PIN)
#define EzI2C_UART_RX_TX_PIN         (0u == EzI2C_REMOVE_UART_RX_TX_PIN)
#define EzI2C_UART_RX_PIN            (0u == EzI2C_REMOVE_UART_RX_PIN)
#define EzI2C_UART_RX_WAKE_PIN       (0u == EzI2C_REMOVE_UART_RX_WAKE_PIN)
#define EzI2C_UART_RTS_PIN           (0u == EzI2C_REMOVE_UART_RTS_PIN)
#define EzI2C_UART_CTS_PIN           (0u == EzI2C_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (EzI2C_RX_WAKE_SCL_MOSI_PIN)
    #include "EzI2C_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (EzI2C_RX_SCL_MOSI) */

#if (EzI2C_RX_SCL_MOSI_PIN)
    #include "EzI2C_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (EzI2C_RX_SCL_MOSI) */

#if (EzI2C_TX_SDA_MISO_PIN)
    #include "EzI2C_uart_tx_i2c_sda_spi_miso.h"
#endif /* (EzI2C_TX_SDA_MISO) */

#if (EzI2C_CTS_SCLK_PIN)
    #include "EzI2C_uart_cts_spi_sclk.h"
#endif /* (EzI2C_CTS_SCLK) */

#if (EzI2C_RTS_SS0_PIN)
    #include "EzI2C_uart_rts_spi_ss0.h"
#endif /* (EzI2C_RTS_SS0_PIN) */

#if (EzI2C_SS1_PIN)
    #include "EzI2C_spi_ss1.h"
#endif /* (EzI2C_SS1_PIN) */

#if (EzI2C_SS2_PIN)
    #include "EzI2C_spi_ss2.h"
#endif /* (EzI2C_SS2_PIN) */

#if (EzI2C_SS3_PIN)
    #include "EzI2C_spi_ss3.h"
#endif /* (EzI2C_SS3_PIN) */

#if (EzI2C_I2C_PINS)
    #include "EzI2C_scl.h"
    #include "EzI2C_sda.h"
#endif /* (EzI2C_I2C_PINS) */

#if (EzI2C_SPI_MASTER_PINS)
#if (EzI2C_SPI_MASTER_SCLK_PIN)
    #include "EzI2C_sclk_m.h"
#endif /* (EzI2C_SPI_MASTER_SCLK_PIN) */

#if (EzI2C_SPI_MASTER_MOSI_PIN)
    #include "EzI2C_mosi_m.h"
#endif /* (EzI2C_SPI_MASTER_MOSI_PIN) */

#if (EzI2C_SPI_MASTER_MISO_PIN)
    #include "EzI2C_miso_m.h"
#endif /*(EzI2C_SPI_MASTER_MISO_PIN) */
#endif /* (EzI2C_SPI_MASTER_PINS) */

#if (EzI2C_SPI_SLAVE_PINS)
    #include "EzI2C_sclk_s.h"
    #include "EzI2C_ss_s.h"

#if (EzI2C_SPI_SLAVE_MOSI_PIN)
    #include "EzI2C_mosi_s.h"
#endif /* (EzI2C_SPI_SLAVE_MOSI_PIN) */

#if (EzI2C_SPI_SLAVE_MISO_PIN)
    #include "EzI2C_miso_s.h"
#endif /*(EzI2C_SPI_SLAVE_MISO_PIN) */
#endif /* (EzI2C_SPI_SLAVE_PINS) */

#if (EzI2C_SPI_MASTER_SS0_PIN)
    #include "EzI2C_ss0_m.h"
#endif /* (EzI2C_SPI_MASTER_SS0_PIN) */

#if (EzI2C_SPI_MASTER_SS1_PIN)
    #include "EzI2C_ss1_m.h"
#endif /* (EzI2C_SPI_MASTER_SS1_PIN) */

#if (EzI2C_SPI_MASTER_SS2_PIN)
    #include "EzI2C_ss2_m.h"
#endif /* (EzI2C_SPI_MASTER_SS2_PIN) */

#if (EzI2C_SPI_MASTER_SS3_PIN)
    #include "EzI2C_ss3_m.h"
#endif /* (EzI2C_SPI_MASTER_SS3_PIN) */

#if (EzI2C_UART_TX_PIN)
    #include "EzI2C_tx.h"
#endif /* (EzI2C_UART_TX_PIN) */

#if (EzI2C_UART_RX_TX_PIN)
    #include "EzI2C_rx_tx.h"
#endif /* (EzI2C_UART_RX_TX_PIN) */

#if (EzI2C_UART_RX_PIN)
    #include "EzI2C_rx.h"
#endif /* (EzI2C_UART_RX_PIN) */

#if (EzI2C_UART_RX_WAKE_PIN)
    #include "EzI2C_rx_wake.h"
#endif /* (EzI2C_UART_RX_WAKE_PIN) */

#if (EzI2C_UART_RTS_PIN)
    #include "EzI2C_rts.h"
#endif /* (EzI2C_UART_RTS_PIN) */

#if (EzI2C_UART_CTS_PIN)
    #include "EzI2C_cts.h"
#endif /* (EzI2C_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (EzI2C_RX_SCL_MOSI_PIN)
    #define EzI2C_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) EzI2C_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define EzI2C_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) EzI2C_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define EzI2C_RX_SCL_MOSI_HSIOM_MASK      (EzI2C_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define EzI2C_RX_SCL_MOSI_HSIOM_POS       (EzI2C_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define EzI2C_RX_SCL_MOSI_HSIOM_SEL_GPIO  (EzI2C_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define EzI2C_RX_SCL_MOSI_HSIOM_SEL_I2C   (EzI2C_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define EzI2C_RX_SCL_MOSI_HSIOM_SEL_SPI   (EzI2C_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define EzI2C_RX_SCL_MOSI_HSIOM_SEL_UART  (EzI2C_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (EzI2C_RX_WAKE_SCL_MOSI_PIN)
    #define EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define EzI2C_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define EzI2C_RX_WAKE_SCL_MOSI_HSIOM_MASK      (EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define EzI2C_RX_WAKE_SCL_MOSI_HSIOM_POS       (EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define EzI2C_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define EzI2C_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define EzI2C_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define EzI2C_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define EzI2C_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define EzI2C_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) EzI2C_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define EzI2C_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (EzI2C_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define EzI2C_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) EzI2C_INTCFG_TYPE_MASK << \
                                                                           EzI2C_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins EzI2C_RX_SCL_MOSI_PIN or EzI2C_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (EzI2C_RX_SCL_MOSI_PIN) */

#if (EzI2C_TX_SDA_MISO_PIN)
    #define EzI2C_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) EzI2C_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define EzI2C_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) EzI2C_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define EzI2C_TX_SDA_MISO_HSIOM_MASK      (EzI2C_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define EzI2C_TX_SDA_MISO_HSIOM_POS       (EzI2C_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define EzI2C_TX_SDA_MISO_HSIOM_SEL_GPIO  (EzI2C_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define EzI2C_TX_SDA_MISO_HSIOM_SEL_I2C   (EzI2C_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define EzI2C_TX_SDA_MISO_HSIOM_SEL_SPI   (EzI2C_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define EzI2C_TX_SDA_MISO_HSIOM_SEL_UART  (EzI2C_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (EzI2C_TX_SDA_MISO_PIN) */

#if (EzI2C_CTS_SCLK_PIN)
    #define EzI2C_CTS_SCLK_HSIOM_REG   (*(reg32 *) EzI2C_uart_cts_spi_sclk__0__HSIOM)
    #define EzI2C_CTS_SCLK_HSIOM_PTR   ( (reg32 *) EzI2C_uart_cts_spi_sclk__0__HSIOM)
    
    #define EzI2C_CTS_SCLK_HSIOM_MASK      (EzI2C_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define EzI2C_CTS_SCLK_HSIOM_POS       (EzI2C_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define EzI2C_CTS_SCLK_HSIOM_SEL_GPIO  (EzI2C_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define EzI2C_CTS_SCLK_HSIOM_SEL_I2C   (EzI2C_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define EzI2C_CTS_SCLK_HSIOM_SEL_SPI   (EzI2C_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define EzI2C_CTS_SCLK_HSIOM_SEL_UART  (EzI2C_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (EzI2C_CTS_SCLK_PIN) */

#if (EzI2C_RTS_SS0_PIN)
    #define EzI2C_RTS_SS0_HSIOM_REG   (*(reg32 *) EzI2C_uart_rts_spi_ss0__0__HSIOM)
    #define EzI2C_RTS_SS0_HSIOM_PTR   ( (reg32 *) EzI2C_uart_rts_spi_ss0__0__HSIOM)
    
    #define EzI2C_RTS_SS0_HSIOM_MASK      (EzI2C_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define EzI2C_RTS_SS0_HSIOM_POS       (EzI2C_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define EzI2C_RTS_SS0_HSIOM_SEL_GPIO  (EzI2C_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define EzI2C_RTS_SS0_HSIOM_SEL_I2C   (EzI2C_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define EzI2C_RTS_SS0_HSIOM_SEL_SPI   (EzI2C_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(EzI2C_CY_SCBIP_V0 || EzI2C_CY_SCBIP_V1)
    #define EzI2C_RTS_SS0_HSIOM_SEL_UART  (EzI2C_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(EzI2C_CY_SCBIP_V0 || EzI2C_CY_SCBIP_V1) */
#endif /* (EzI2C_RTS_SS0_PIN) */

#if (EzI2C_SS1_PIN)
    #define EzI2C_SS1_HSIOM_REG  (*(reg32 *) EzI2C_spi_ss1__0__HSIOM)
    #define EzI2C_SS1_HSIOM_PTR  ( (reg32 *) EzI2C_spi_ss1__0__HSIOM)
    
    #define EzI2C_SS1_HSIOM_MASK     (EzI2C_spi_ss1__0__HSIOM_MASK)
    #define EzI2C_SS1_HSIOM_POS      (EzI2C_spi_ss1__0__HSIOM_SHIFT)
    #define EzI2C_SS1_HSIOM_SEL_GPIO (EzI2C_spi_ss1__0__HSIOM_GPIO)
    #define EzI2C_SS1_HSIOM_SEL_I2C  (EzI2C_spi_ss1__0__HSIOM_I2C)
    #define EzI2C_SS1_HSIOM_SEL_SPI  (EzI2C_spi_ss1__0__HSIOM_SPI)
#endif /* (EzI2C_SS1_PIN) */

#if (EzI2C_SS2_PIN)
    #define EzI2C_SS2_HSIOM_REG     (*(reg32 *) EzI2C_spi_ss2__0__HSIOM)
    #define EzI2C_SS2_HSIOM_PTR     ( (reg32 *) EzI2C_spi_ss2__0__HSIOM)
    
    #define EzI2C_SS2_HSIOM_MASK     (EzI2C_spi_ss2__0__HSIOM_MASK)
    #define EzI2C_SS2_HSIOM_POS      (EzI2C_spi_ss2__0__HSIOM_SHIFT)
    #define EzI2C_SS2_HSIOM_SEL_GPIO (EzI2C_spi_ss2__0__HSIOM_GPIO)
    #define EzI2C_SS2_HSIOM_SEL_I2C  (EzI2C_spi_ss2__0__HSIOM_I2C)
    #define EzI2C_SS2_HSIOM_SEL_SPI  (EzI2C_spi_ss2__0__HSIOM_SPI)
#endif /* (EzI2C_SS2_PIN) */

#if (EzI2C_SS3_PIN)
    #define EzI2C_SS3_HSIOM_REG     (*(reg32 *) EzI2C_spi_ss3__0__HSIOM)
    #define EzI2C_SS3_HSIOM_PTR     ( (reg32 *) EzI2C_spi_ss3__0__HSIOM)
    
    #define EzI2C_SS3_HSIOM_MASK     (EzI2C_spi_ss3__0__HSIOM_MASK)
    #define EzI2C_SS3_HSIOM_POS      (EzI2C_spi_ss3__0__HSIOM_SHIFT)
    #define EzI2C_SS3_HSIOM_SEL_GPIO (EzI2C_spi_ss3__0__HSIOM_GPIO)
    #define EzI2C_SS3_HSIOM_SEL_I2C  (EzI2C_spi_ss3__0__HSIOM_I2C)
    #define EzI2C_SS3_HSIOM_SEL_SPI  (EzI2C_spi_ss3__0__HSIOM_SPI)
#endif /* (EzI2C_SS3_PIN) */

#if (EzI2C_I2C_PINS)
    #define EzI2C_SCL_HSIOM_REG  (*(reg32 *) EzI2C_scl__0__HSIOM)
    #define EzI2C_SCL_HSIOM_PTR  ( (reg32 *) EzI2C_scl__0__HSIOM)
    
    #define EzI2C_SCL_HSIOM_MASK     (EzI2C_scl__0__HSIOM_MASK)
    #define EzI2C_SCL_HSIOM_POS      (EzI2C_scl__0__HSIOM_SHIFT)
    #define EzI2C_SCL_HSIOM_SEL_GPIO (EzI2C_sda__0__HSIOM_GPIO)
    #define EzI2C_SCL_HSIOM_SEL_I2C  (EzI2C_sda__0__HSIOM_I2C)
    
    #define EzI2C_SDA_HSIOM_REG  (*(reg32 *) EzI2C_sda__0__HSIOM)
    #define EzI2C_SDA_HSIOM_PTR  ( (reg32 *) EzI2C_sda__0__HSIOM)
    
    #define EzI2C_SDA_HSIOM_MASK     (EzI2C_sda__0__HSIOM_MASK)
    #define EzI2C_SDA_HSIOM_POS      (EzI2C_sda__0__HSIOM_SHIFT)
    #define EzI2C_SDA_HSIOM_SEL_GPIO (EzI2C_sda__0__HSIOM_GPIO)
    #define EzI2C_SDA_HSIOM_SEL_I2C  (EzI2C_sda__0__HSIOM_I2C)
#endif /* (EzI2C_I2C_PINS) */

#if (EzI2C_SPI_SLAVE_PINS)
    #define EzI2C_SCLK_S_HSIOM_REG   (*(reg32 *) EzI2C_sclk_s__0__HSIOM)
    #define EzI2C_SCLK_S_HSIOM_PTR   ( (reg32 *) EzI2C_sclk_s__0__HSIOM)
    
    #define EzI2C_SCLK_S_HSIOM_MASK      (EzI2C_sclk_s__0__HSIOM_MASK)
    #define EzI2C_SCLK_S_HSIOM_POS       (EzI2C_sclk_s__0__HSIOM_SHIFT)
    #define EzI2C_SCLK_S_HSIOM_SEL_GPIO  (EzI2C_sclk_s__0__HSIOM_GPIO)
    #define EzI2C_SCLK_S_HSIOM_SEL_SPI   (EzI2C_sclk_s__0__HSIOM_SPI)
    
    #define EzI2C_SS0_S_HSIOM_REG    (*(reg32 *) EzI2C_ss0_s__0__HSIOM)
    #define EzI2C_SS0_S_HSIOM_PTR    ( (reg32 *) EzI2C_ss0_s__0__HSIOM)
    
    #define EzI2C_SS0_S_HSIOM_MASK       (EzI2C_ss0_s__0__HSIOM_MASK)
    #define EzI2C_SS0_S_HSIOM_POS        (EzI2C_ss0_s__0__HSIOM_SHIFT)
    #define EzI2C_SS0_S_HSIOM_SEL_GPIO   (EzI2C_ss0_s__0__HSIOM_GPIO)  
    #define EzI2C_SS0_S_HSIOM_SEL_SPI    (EzI2C_ss0_s__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_SLAVE_PINS) */

#if (EzI2C_SPI_SLAVE_MOSI_PIN)
    #define EzI2C_MOSI_S_HSIOM_REG   (*(reg32 *) EzI2C_mosi_s__0__HSIOM)
    #define EzI2C_MOSI_S_HSIOM_PTR   ( (reg32 *) EzI2C_mosi_s__0__HSIOM)
    
    #define EzI2C_MOSI_S_HSIOM_MASK      (EzI2C_mosi_s__0__HSIOM_MASK)
    #define EzI2C_MOSI_S_HSIOM_POS       (EzI2C_mosi_s__0__HSIOM_SHIFT)
    #define EzI2C_MOSI_S_HSIOM_SEL_GPIO  (EzI2C_mosi_s__0__HSIOM_GPIO)
    #define EzI2C_MOSI_S_HSIOM_SEL_SPI   (EzI2C_mosi_s__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_SLAVE_MOSI_PIN) */

#if (EzI2C_SPI_SLAVE_MISO_PIN)
    #define EzI2C_MISO_S_HSIOM_REG   (*(reg32 *) EzI2C_miso_s__0__HSIOM)
    #define EzI2C_MISO_S_HSIOM_PTR   ( (reg32 *) EzI2C_miso_s__0__HSIOM)
    
    #define EzI2C_MISO_S_HSIOM_MASK      (EzI2C_miso_s__0__HSIOM_MASK)
    #define EzI2C_MISO_S_HSIOM_POS       (EzI2C_miso_s__0__HSIOM_SHIFT)
    #define EzI2C_MISO_S_HSIOM_SEL_GPIO  (EzI2C_miso_s__0__HSIOM_GPIO)
    #define EzI2C_MISO_S_HSIOM_SEL_SPI   (EzI2C_miso_s__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_SLAVE_MISO_PIN) */

#if (EzI2C_SPI_MASTER_MISO_PIN)
    #define EzI2C_MISO_M_HSIOM_REG   (*(reg32 *) EzI2C_miso_m__0__HSIOM)
    #define EzI2C_MISO_M_HSIOM_PTR   ( (reg32 *) EzI2C_miso_m__0__HSIOM)
    
    #define EzI2C_MISO_M_HSIOM_MASK      (EzI2C_miso_m__0__HSIOM_MASK)
    #define EzI2C_MISO_M_HSIOM_POS       (EzI2C_miso_m__0__HSIOM_SHIFT)
    #define EzI2C_MISO_M_HSIOM_SEL_GPIO  (EzI2C_miso_m__0__HSIOM_GPIO)
    #define EzI2C_MISO_M_HSIOM_SEL_SPI   (EzI2C_miso_m__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_MASTER_MISO_PIN) */

#if (EzI2C_SPI_MASTER_MOSI_PIN)
    #define EzI2C_MOSI_M_HSIOM_REG   (*(reg32 *) EzI2C_mosi_m__0__HSIOM)
    #define EzI2C_MOSI_M_HSIOM_PTR   ( (reg32 *) EzI2C_mosi_m__0__HSIOM)
    
    #define EzI2C_MOSI_M_HSIOM_MASK      (EzI2C_mosi_m__0__HSIOM_MASK)
    #define EzI2C_MOSI_M_HSIOM_POS       (EzI2C_mosi_m__0__HSIOM_SHIFT)
    #define EzI2C_MOSI_M_HSIOM_SEL_GPIO  (EzI2C_mosi_m__0__HSIOM_GPIO)
    #define EzI2C_MOSI_M_HSIOM_SEL_SPI   (EzI2C_mosi_m__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_MASTER_MOSI_PIN) */

#if (EzI2C_SPI_MASTER_SCLK_PIN)
    #define EzI2C_SCLK_M_HSIOM_REG   (*(reg32 *) EzI2C_sclk_m__0__HSIOM)
    #define EzI2C_SCLK_M_HSIOM_PTR   ( (reg32 *) EzI2C_sclk_m__0__HSIOM)
    
    #define EzI2C_SCLK_M_HSIOM_MASK      (EzI2C_sclk_m__0__HSIOM_MASK)
    #define EzI2C_SCLK_M_HSIOM_POS       (EzI2C_sclk_m__0__HSIOM_SHIFT)
    #define EzI2C_SCLK_M_HSIOM_SEL_GPIO  (EzI2C_sclk_m__0__HSIOM_GPIO)
    #define EzI2C_SCLK_M_HSIOM_SEL_SPI   (EzI2C_sclk_m__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_MASTER_SCLK_PIN) */

#if (EzI2C_SPI_MASTER_SS0_PIN)
    #define EzI2C_SS0_M_HSIOM_REG    (*(reg32 *) EzI2C_ss0_m__0__HSIOM)
    #define EzI2C_SS0_M_HSIOM_PTR    ( (reg32 *) EzI2C_ss0_m__0__HSIOM)
    
    #define EzI2C_SS0_M_HSIOM_MASK       (EzI2C_ss0_m__0__HSIOM_MASK)
    #define EzI2C_SS0_M_HSIOM_POS        (EzI2C_ss0_m__0__HSIOM_SHIFT)
    #define EzI2C_SS0_M_HSIOM_SEL_GPIO   (EzI2C_ss0_m__0__HSIOM_GPIO)
    #define EzI2C_SS0_M_HSIOM_SEL_SPI    (EzI2C_ss0_m__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_MASTER_SS0_PIN) */

#if (EzI2C_SPI_MASTER_SS1_PIN)
    #define EzI2C_SS1_M_HSIOM_REG    (*(reg32 *) EzI2C_ss1_m__0__HSIOM)
    #define EzI2C_SS1_M_HSIOM_PTR    ( (reg32 *) EzI2C_ss1_m__0__HSIOM)
    
    #define EzI2C_SS1_M_HSIOM_MASK       (EzI2C_ss1_m__0__HSIOM_MASK)
    #define EzI2C_SS1_M_HSIOM_POS        (EzI2C_ss1_m__0__HSIOM_SHIFT)
    #define EzI2C_SS1_M_HSIOM_SEL_GPIO   (EzI2C_ss1_m__0__HSIOM_GPIO)
    #define EzI2C_SS1_M_HSIOM_SEL_SPI    (EzI2C_ss1_m__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_MASTER_SS1_PIN) */

#if (EzI2C_SPI_MASTER_SS2_PIN)
    #define EzI2C_SS2_M_HSIOM_REG    (*(reg32 *) EzI2C_ss2_m__0__HSIOM)
    #define EzI2C_SS2_M_HSIOM_PTR    ( (reg32 *) EzI2C_ss2_m__0__HSIOM)
    
    #define EzI2C_SS2_M_HSIOM_MASK       (EzI2C_ss2_m__0__HSIOM_MASK)
    #define EzI2C_SS2_M_HSIOM_POS        (EzI2C_ss2_m__0__HSIOM_SHIFT)
    #define EzI2C_SS2_M_HSIOM_SEL_GPIO   (EzI2C_ss2_m__0__HSIOM_GPIO)
    #define EzI2C_SS2_M_HSIOM_SEL_SPI    (EzI2C_ss2_m__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_MASTER_SS2_PIN) */

#if (EzI2C_SPI_MASTER_SS3_PIN)
    #define EzI2C_SS3_M_HSIOM_REG    (*(reg32 *) EzI2C_ss3_m__0__HSIOM)
    #define EzI2C_SS3_M_HSIOM_PTR    ( (reg32 *) EzI2C_ss3_m__0__HSIOM)
    
    #define EzI2C_SS3_M_HSIOM_MASK      (EzI2C_ss3_m__0__HSIOM_MASK)
    #define EzI2C_SS3_M_HSIOM_POS       (EzI2C_ss3_m__0__HSIOM_SHIFT)
    #define EzI2C_SS3_M_HSIOM_SEL_GPIO  (EzI2C_ss3_m__0__HSIOM_GPIO)
    #define EzI2C_SS3_M_HSIOM_SEL_SPI   (EzI2C_ss3_m__0__HSIOM_SPI)
#endif /* (EzI2C_SPI_MASTER_SS3_PIN) */

#if (EzI2C_UART_RX_PIN)
    #define EzI2C_RX_HSIOM_REG   (*(reg32 *) EzI2C_rx__0__HSIOM)
    #define EzI2C_RX_HSIOM_PTR   ( (reg32 *) EzI2C_rx__0__HSIOM)
    
    #define EzI2C_RX_HSIOM_MASK      (EzI2C_rx__0__HSIOM_MASK)
    #define EzI2C_RX_HSIOM_POS       (EzI2C_rx__0__HSIOM_SHIFT)
    #define EzI2C_RX_HSIOM_SEL_GPIO  (EzI2C_rx__0__HSIOM_GPIO)
    #define EzI2C_RX_HSIOM_SEL_UART  (EzI2C_rx__0__HSIOM_UART)
#endif /* (EzI2C_UART_RX_PIN) */

#if (EzI2C_UART_RX_WAKE_PIN)
    #define EzI2C_RX_WAKE_HSIOM_REG   (*(reg32 *) EzI2C_rx_wake__0__HSIOM)
    #define EzI2C_RX_WAKE_HSIOM_PTR   ( (reg32 *) EzI2C_rx_wake__0__HSIOM)
    
    #define EzI2C_RX_WAKE_HSIOM_MASK      (EzI2C_rx_wake__0__HSIOM_MASK)
    #define EzI2C_RX_WAKE_HSIOM_POS       (EzI2C_rx_wake__0__HSIOM_SHIFT)
    #define EzI2C_RX_WAKE_HSIOM_SEL_GPIO  (EzI2C_rx_wake__0__HSIOM_GPIO)
    #define EzI2C_RX_WAKE_HSIOM_SEL_UART  (EzI2C_rx_wake__0__HSIOM_UART)
#endif /* (EzI2C_UART_WAKE_RX_PIN) */

#if (EzI2C_UART_CTS_PIN)
    #define EzI2C_CTS_HSIOM_REG   (*(reg32 *) EzI2C_cts__0__HSIOM)
    #define EzI2C_CTS_HSIOM_PTR   ( (reg32 *) EzI2C_cts__0__HSIOM)
    
    #define EzI2C_CTS_HSIOM_MASK      (EzI2C_cts__0__HSIOM_MASK)
    #define EzI2C_CTS_HSIOM_POS       (EzI2C_cts__0__HSIOM_SHIFT)
    #define EzI2C_CTS_HSIOM_SEL_GPIO  (EzI2C_cts__0__HSIOM_GPIO)
    #define EzI2C_CTS_HSIOM_SEL_UART  (EzI2C_cts__0__HSIOM_UART)
#endif /* (EzI2C_UART_CTS_PIN) */

#if (EzI2C_UART_TX_PIN)
    #define EzI2C_TX_HSIOM_REG   (*(reg32 *) EzI2C_tx__0__HSIOM)
    #define EzI2C_TX_HSIOM_PTR   ( (reg32 *) EzI2C_tx__0__HSIOM)
    
    #define EzI2C_TX_HSIOM_MASK      (EzI2C_tx__0__HSIOM_MASK)
    #define EzI2C_TX_HSIOM_POS       (EzI2C_tx__0__HSIOM_SHIFT)
    #define EzI2C_TX_HSIOM_SEL_GPIO  (EzI2C_tx__0__HSIOM_GPIO)
    #define EzI2C_TX_HSIOM_SEL_UART  (EzI2C_tx__0__HSIOM_UART)
#endif /* (EzI2C_UART_TX_PIN) */

#if (EzI2C_UART_RX_TX_PIN)
    #define EzI2C_RX_TX_HSIOM_REG   (*(reg32 *) EzI2C_rx_tx__0__HSIOM)
    #define EzI2C_RX_TX_HSIOM_PTR   ( (reg32 *) EzI2C_rx_tx__0__HSIOM)
    
    #define EzI2C_RX_TX_HSIOM_MASK      (EzI2C_rx_tx__0__HSIOM_MASK)
    #define EzI2C_RX_TX_HSIOM_POS       (EzI2C_rx_tx__0__HSIOM_SHIFT)
    #define EzI2C_RX_TX_HSIOM_SEL_GPIO  (EzI2C_rx_tx__0__HSIOM_GPIO)
    #define EzI2C_RX_TX_HSIOM_SEL_UART  (EzI2C_rx_tx__0__HSIOM_UART)
#endif /* (EzI2C_UART_RX_TX_PIN) */

#if (EzI2C_UART_RTS_PIN)
    #define EzI2C_RTS_HSIOM_REG      (*(reg32 *) EzI2C_rts__0__HSIOM)
    #define EzI2C_RTS_HSIOM_PTR      ( (reg32 *) EzI2C_rts__0__HSIOM)
    
    #define EzI2C_RTS_HSIOM_MASK     (EzI2C_rts__0__HSIOM_MASK)
    #define EzI2C_RTS_HSIOM_POS      (EzI2C_rts__0__HSIOM_SHIFT)    
    #define EzI2C_RTS_HSIOM_SEL_GPIO (EzI2C_rts__0__HSIOM_GPIO)
    #define EzI2C_RTS_HSIOM_SEL_UART (EzI2C_rts__0__HSIOM_UART)    
#endif /* (EzI2C_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define EzI2C_HSIOM_DEF_SEL      (0x00u)
#define EzI2C_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for EzI2C_CY_SCBIP_V0 
* and EzI2C_CY_SCBIP_V1. It is not recommended to use them for 
* EzI2C_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define EzI2C_HSIOM_UART_SEL     (0x09u)
#define EzI2C_HSIOM_I2C_SEL      (0x0Eu)
#define EzI2C_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define EzI2C_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define EzI2C_RX_SCL_MOSI_PIN_INDEX       (0u)
#define EzI2C_TX_SDA_MISO_PIN_INDEX       (1u)
#define EzI2C_CTS_SCLK_PIN_INDEX       (2u)
#define EzI2C_RTS_SS0_PIN_INDEX       (3u)
#define EzI2C_SS1_PIN_INDEX                  (4u)
#define EzI2C_SS2_PIN_INDEX                  (5u)
#define EzI2C_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define EzI2C_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << EzI2C_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define EzI2C_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << EzI2C_RX_SCL_MOSI_PIN_INDEX)
#define EzI2C_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << EzI2C_TX_SDA_MISO_PIN_INDEX)
#define EzI2C_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << EzI2C_CTS_SCLK_PIN_INDEX)
#define EzI2C_RTS_SS0_PIN_MASK     ((uint32) 0x01u << EzI2C_RTS_SS0_PIN_INDEX)
#define EzI2C_SS1_PIN_MASK                ((uint32) 0x01u << EzI2C_SS1_PIN_INDEX)
#define EzI2C_SS2_PIN_MASK                ((uint32) 0x01u << EzI2C_SS2_PIN_INDEX)
#define EzI2C_SS3_PIN_MASK                ((uint32) 0x01u << EzI2C_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define EzI2C_INTCFG_TYPE_MASK           (0x03u)
#define EzI2C_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define EzI2C_PIN_DM_ALG_HIZ  (0u)
#define EzI2C_PIN_DM_DIG_HIZ  (1u)
#define EzI2C_PIN_DM_OD_LO    (4u)
#define EzI2C_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define EzI2C_DM_MASK    (0x7u)
#define EzI2C_DM_SIZE    (3u)
#define EzI2C_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) EzI2C_DM_MASK << (EzI2C_DM_SIZE * (pos)))) >> \
                                                              (EzI2C_DM_SIZE * (pos)) )

#if (EzI2C_TX_SDA_MISO_PIN)
    #define EzI2C_CHECK_TX_SDA_MISO_PIN_USED \
                (EzI2C_PIN_DM_ALG_HIZ != \
                    EzI2C_GET_P4_PIN_DM(EzI2C_uart_tx_i2c_sda_spi_miso_PC, \
                                                   EzI2C_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (EzI2C_TX_SDA_MISO_PIN) */

#if (EzI2C_RTS_SS0_PIN)
    #define EzI2C_CHECK_RTS_SS0_PIN_USED \
                (EzI2C_PIN_DM_ALG_HIZ != \
                    EzI2C_GET_P4_PIN_DM(EzI2C_uart_rts_spi_ss0_PC, \
                                                   EzI2C_uart_rts_spi_ss0_SHIFT))
#endif /* (EzI2C_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define EzI2C_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define EzI2C_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define EzI2C_SET_HSIOM_SEL(reg, mask, pos, sel) EzI2C_SET_REGISTER_BITS(reg, mask, pos, sel)
#define EzI2C_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        EzI2C_SET_REGISTER_BITS(reg, mask, pos, intType)
#define EzI2C_SET_INP_DIS(reg, mask, val) EzI2C_SET_REGISTER_BIT(reg, mask, val)

/* EzI2C_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  EzI2C_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (EzI2C_CY_SCBIP_V0)
#if (EzI2C_I2C_PINS)
    #define EzI2C_SET_I2C_SCL_DR(val) EzI2C_scl_Write(val)

    #define EzI2C_SET_I2C_SCL_HSIOM_SEL(sel) \
                          EzI2C_SET_HSIOM_SEL(EzI2C_SCL_HSIOM_REG,  \
                                                         EzI2C_SCL_HSIOM_MASK, \
                                                         EzI2C_SCL_HSIOM_POS,  \
                                                         (sel))
    #define EzI2C_WAIT_SCL_SET_HIGH  (0u == EzI2C_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (EzI2C_RX_WAKE_SCL_MOSI_PIN)
    #define EzI2C_SET_I2C_SCL_DR(val) \
                            EzI2C_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define EzI2C_SET_I2C_SCL_HSIOM_SEL(sel) \
                    EzI2C_SET_HSIOM_SEL(EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   EzI2C_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   EzI2C_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define EzI2C_WAIT_SCL_SET_HIGH  (0u == EzI2C_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (EzI2C_RX_SCL_MOSI_PIN)
    #define EzI2C_SET_I2C_SCL_DR(val) \
                            EzI2C_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define EzI2C_SET_I2C_SCL_HSIOM_SEL(sel) \
                            EzI2C_SET_HSIOM_SEL(EzI2C_RX_SCL_MOSI_HSIOM_REG,  \
                                                           EzI2C_RX_SCL_MOSI_HSIOM_MASK, \
                                                           EzI2C_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define EzI2C_WAIT_SCL_SET_HIGH  (0u == EzI2C_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define EzI2C_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define EzI2C_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define EzI2C_WAIT_SCL_SET_HIGH  (0u)
#endif /* (EzI2C_I2C_PINS) */

/* SCB I2C: sda signal */
#if (EzI2C_I2C_PINS)
    #define EzI2C_WAIT_SDA_SET_HIGH  (0u == EzI2C_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (EzI2C_TX_SDA_MISO_PIN)
    #define EzI2C_WAIT_SDA_SET_HIGH  (0u == EzI2C_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define EzI2C_WAIT_SDA_SET_HIGH  (0u)
#endif /* (EzI2C_MOSI_SCL_RX_PIN) */
#endif /* (EzI2C_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (EzI2C_RX_SCL_MOSI_PIN)
    #define EzI2C_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (EzI2C_RX_WAKE_SCL_MOSI_PIN)
    #define EzI2C_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) EzI2C_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(EzI2C_UART_RX_WAKE_PIN)
    #define EzI2C_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) EzI2C_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (EzI2C_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define EzI2C_REMOVE_MOSI_SCL_RX_WAKE_PIN    EzI2C_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define EzI2C_REMOVE_MOSI_SCL_RX_PIN         EzI2C_REMOVE_RX_SCL_MOSI_PIN
#define EzI2C_REMOVE_MISO_SDA_TX_PIN         EzI2C_REMOVE_TX_SDA_MISO_PIN
#ifndef EzI2C_REMOVE_SCLK_PIN
#define EzI2C_REMOVE_SCLK_PIN                EzI2C_REMOVE_CTS_SCLK_PIN
#endif /* EzI2C_REMOVE_SCLK_PIN */
#ifndef EzI2C_REMOVE_SS0_PIN
#define EzI2C_REMOVE_SS0_PIN                 EzI2C_REMOVE_RTS_SS0_PIN
#endif /* EzI2C_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define EzI2C_MOSI_SCL_RX_WAKE_PIN   EzI2C_RX_WAKE_SCL_MOSI_PIN
#define EzI2C_MOSI_SCL_RX_PIN        EzI2C_RX_SCL_MOSI_PIN
#define EzI2C_MISO_SDA_TX_PIN        EzI2C_TX_SDA_MISO_PIN
#ifndef EzI2C_SCLK_PIN
#define EzI2C_SCLK_PIN               EzI2C_CTS_SCLK_PIN
#endif /* EzI2C_SCLK_PIN */
#ifndef EzI2C_SS0_PIN
#define EzI2C_SS0_PIN                EzI2C_RTS_SS0_PIN
#endif /* EzI2C_SS0_PIN */

#if (EzI2C_MOSI_SCL_RX_WAKE_PIN)
    #define EzI2C_MOSI_SCL_RX_WAKE_HSIOM_REG     EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define EzI2C_MOSI_SCL_RX_WAKE_HSIOM_PTR     EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define EzI2C_MOSI_SCL_RX_WAKE_HSIOM_MASK    EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define EzI2C_MOSI_SCL_RX_WAKE_HSIOM_POS     EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define EzI2C_MOSI_SCL_RX_WAKE_INTCFG_REG    EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define EzI2C_MOSI_SCL_RX_WAKE_INTCFG_PTR    EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define EzI2C_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define EzI2C_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  EzI2C_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (EzI2C_RX_WAKE_SCL_MOSI_PIN) */

#if (EzI2C_MOSI_SCL_RX_PIN)
    #define EzI2C_MOSI_SCL_RX_HSIOM_REG      EzI2C_RX_SCL_MOSI_HSIOM_REG
    #define EzI2C_MOSI_SCL_RX_HSIOM_PTR      EzI2C_RX_SCL_MOSI_HSIOM_PTR
    #define EzI2C_MOSI_SCL_RX_HSIOM_MASK     EzI2C_RX_SCL_MOSI_HSIOM_MASK
    #define EzI2C_MOSI_SCL_RX_HSIOM_POS      EzI2C_RX_SCL_MOSI_HSIOM_POS
#endif /* (EzI2C_MOSI_SCL_RX_PIN) */

#if (EzI2C_MISO_SDA_TX_PIN)
    #define EzI2C_MISO_SDA_TX_HSIOM_REG      EzI2C_TX_SDA_MISO_HSIOM_REG
    #define EzI2C_MISO_SDA_TX_HSIOM_PTR      EzI2C_TX_SDA_MISO_HSIOM_REG
    #define EzI2C_MISO_SDA_TX_HSIOM_MASK     EzI2C_TX_SDA_MISO_HSIOM_REG
    #define EzI2C_MISO_SDA_TX_HSIOM_POS      EzI2C_TX_SDA_MISO_HSIOM_REG
#endif /* (EzI2C_MISO_SDA_TX_PIN_PIN) */

#if (EzI2C_SCLK_PIN)
    #ifndef EzI2C_SCLK_HSIOM_REG
    #define EzI2C_SCLK_HSIOM_REG     EzI2C_CTS_SCLK_HSIOM_REG
    #define EzI2C_SCLK_HSIOM_PTR     EzI2C_CTS_SCLK_HSIOM_PTR
    #define EzI2C_SCLK_HSIOM_MASK    EzI2C_CTS_SCLK_HSIOM_MASK
    #define EzI2C_SCLK_HSIOM_POS     EzI2C_CTS_SCLK_HSIOM_POS
    #endif /* EzI2C_SCLK_HSIOM_REG */
#endif /* (EzI2C_SCLK_PIN) */

#if (EzI2C_SS0_PIN)
    #ifndef EzI2C_SS0_HSIOM_REG
    #define EzI2C_SS0_HSIOM_REG      EzI2C_RTS_SS0_HSIOM_REG
    #define EzI2C_SS0_HSIOM_PTR      EzI2C_RTS_SS0_HSIOM_PTR
    #define EzI2C_SS0_HSIOM_MASK     EzI2C_RTS_SS0_HSIOM_MASK
    #define EzI2C_SS0_HSIOM_POS      EzI2C_RTS_SS0_HSIOM_POS
    #endif /* EzI2C_SS0_HSIOM_REG */
#endif /* (EzI2C_SS0_PIN) */

#define EzI2C_MOSI_SCL_RX_WAKE_PIN_INDEX EzI2C_RX_WAKE_SCL_MOSI_PIN_INDEX
#define EzI2C_MOSI_SCL_RX_PIN_INDEX      EzI2C_RX_SCL_MOSI_PIN_INDEX
#define EzI2C_MISO_SDA_TX_PIN_INDEX      EzI2C_TX_SDA_MISO_PIN_INDEX
#ifndef EzI2C_SCLK_PIN_INDEX
#define EzI2C_SCLK_PIN_INDEX             EzI2C_CTS_SCLK_PIN_INDEX
#endif /* EzI2C_SCLK_PIN_INDEX */
#ifndef EzI2C_SS0_PIN_INDEX
#define EzI2C_SS0_PIN_INDEX              EzI2C_RTS_SS0_PIN_INDEX
#endif /* EzI2C_SS0_PIN_INDEX */

#define EzI2C_MOSI_SCL_RX_WAKE_PIN_MASK EzI2C_RX_WAKE_SCL_MOSI_PIN_MASK
#define EzI2C_MOSI_SCL_RX_PIN_MASK      EzI2C_RX_SCL_MOSI_PIN_MASK
#define EzI2C_MISO_SDA_TX_PIN_MASK      EzI2C_TX_SDA_MISO_PIN_MASK
#ifndef EzI2C_SCLK_PIN_MASK
#define EzI2C_SCLK_PIN_MASK             EzI2C_CTS_SCLK_PIN_MASK
#endif /* EzI2C_SCLK_PIN_MASK */
#ifndef EzI2C_SS0_PIN_MASK
#define EzI2C_SS0_PIN_MASK              EzI2C_RTS_SS0_PIN_MASK
#endif /* EzI2C_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_EzI2C_H) */


/* [] END OF FILE */
