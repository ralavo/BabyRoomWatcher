/*******************************************************************************
* File Name: TIA_OUT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TIA_OUT_H) /* Pins TIA_OUT_H */
#define CY_PINS_TIA_OUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TIA_OUT_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} TIA_OUT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   TIA_OUT_Read(void);
void    TIA_OUT_Write(uint8 value);
uint8   TIA_OUT_ReadDataReg(void);
#if defined(TIA_OUT__PC) || (CY_PSOC4_4200L) 
    void    TIA_OUT_SetDriveMode(uint8 mode);
#endif
void    TIA_OUT_SetInterruptMode(uint16 position, uint16 mode);
uint8   TIA_OUT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void TIA_OUT_Sleep(void); 
void TIA_OUT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(TIA_OUT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define TIA_OUT_DRIVE_MODE_BITS        (3)
    #define TIA_OUT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TIA_OUT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the TIA_OUT_SetDriveMode() function.
         *  @{
         */
        #define TIA_OUT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define TIA_OUT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define TIA_OUT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define TIA_OUT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define TIA_OUT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define TIA_OUT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define TIA_OUT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define TIA_OUT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define TIA_OUT_MASK               TIA_OUT__MASK
#define TIA_OUT_SHIFT              TIA_OUT__SHIFT
#define TIA_OUT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TIA_OUT_SetInterruptMode() function.
     *  @{
     */
        #define TIA_OUT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define TIA_OUT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define TIA_OUT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define TIA_OUT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(TIA_OUT__SIO)
    #define TIA_OUT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(TIA_OUT__PC) && (CY_PSOC4_4200L)
    #define TIA_OUT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define TIA_OUT_USBIO_DISABLE              ((uint32)(~TIA_OUT_USBIO_ENABLE))
    #define TIA_OUT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define TIA_OUT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define TIA_OUT_USBIO_ENTER_SLEEP          ((uint32)((1u << TIA_OUT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << TIA_OUT_USBIO_SUSPEND_DEL_SHIFT)))
    #define TIA_OUT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << TIA_OUT_USBIO_SUSPEND_SHIFT)))
    #define TIA_OUT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << TIA_OUT_USBIO_SUSPEND_DEL_SHIFT)))
    #define TIA_OUT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(TIA_OUT__PC)
    /* Port Configuration */
    #define TIA_OUT_PC                 (* (reg32 *) TIA_OUT__PC)
#endif
/* Pin State */
#define TIA_OUT_PS                     (* (reg32 *) TIA_OUT__PS)
/* Data Register */
#define TIA_OUT_DR                     (* (reg32 *) TIA_OUT__DR)
/* Input Buffer Disable Override */
#define TIA_OUT_INP_DIS                (* (reg32 *) TIA_OUT__PC2)

/* Interrupt configuration Registers */
#define TIA_OUT_INTCFG                 (* (reg32 *) TIA_OUT__INTCFG)
#define TIA_OUT_INTSTAT                (* (reg32 *) TIA_OUT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define TIA_OUT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(TIA_OUT__SIO)
    #define TIA_OUT_SIO_REG            (* (reg32 *) TIA_OUT__SIO)
#endif /* (TIA_OUT__SIO_CFG) */

/* USBIO registers */
#if !defined(TIA_OUT__PC) && (CY_PSOC4_4200L)
    #define TIA_OUT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define TIA_OUT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define TIA_OUT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define TIA_OUT_DRIVE_MODE_SHIFT       (0x00u)
#define TIA_OUT_DRIVE_MODE_MASK        (0x07u << TIA_OUT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins TIA_OUT_H */


/* [] END OF FILE */
