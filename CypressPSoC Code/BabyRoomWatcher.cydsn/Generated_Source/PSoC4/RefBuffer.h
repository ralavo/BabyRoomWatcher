/*******************************************************************************
* File Name: RefBuffer.h
* Version 1.20
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Opamp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_RefBuffer_H)
#define CY_OPAMP_RefBuffer_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} RefBuffer_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void RefBuffer_Init(void);
void RefBuffer_Enable(void);
void RefBuffer_Start(void);
void RefBuffer_Stop(void);
void RefBuffer_SetPower(uint32 power);
void RefBuffer_PumpControl(uint32 onOff);
void RefBuffer_Sleep(void);
void RefBuffer_Wakeup(void);
void RefBuffer_SaveConfig(void);
void RefBuffer_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define RefBuffer_LOW_POWER      (1u)
#define RefBuffer_MED_POWER      (2u)
#define RefBuffer_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define RefBuffer_PUMP_ON        (1u)
#define RefBuffer_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define RefBuffer_OUTPUT_CURRENT         (1u)
#define RefBuffer_POWER                  (3u)
#define RefBuffer_MODE                   (1u)
#define RefBuffer_OA_COMP_TRIM_VALUE     (3u)
#define RefBuffer_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  RefBuffer_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define RefBuffer_CTB_CTRL_REG       (*(reg32 *) RefBuffer_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define RefBuffer_CTB_CTRL_PTR       ( (reg32 *) RefBuffer_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define RefBuffer_CTB_CTRL_REG       (*(reg32 *) RefBuffer_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define RefBuffer_CTB_CTRL_PTR       ( (reg32 *) RefBuffer_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define RefBuffer_OA_RES_CTRL_REG    (*(reg32 *) RefBuffer_cy_psoc4_abuf__OA_RES_CTRL)
#define RefBuffer_OA_RES_CTRL_PTR    ( (reg32 *) RefBuffer_cy_psoc4_abuf__OA_RES_CTRL)
#define RefBuffer_OA_COMP_TRIM_REG   (*(reg32 *) RefBuffer_cy_psoc4_abuf__OA_COMP_TRIM)
#define RefBuffer_OA_COMP_TRIM_PTR   ( (reg32 *) RefBuffer_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* RefBuffer_CTB_CTRL_REG */
#define RefBuffer_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define RefBuffer_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define RefBuffer_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << RefBuffer_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define RefBuffer_CTB_CTRL_ENABLED               ((uint32) 0x01u << RefBuffer_CTB_CTRL_ENABLED_SHIFT)


/* RefBuffer_OA_RES_CTRL_REG */
#define RefBuffer_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define RefBuffer_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define RefBuffer_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define RefBuffer_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define RefBuffer_OA_PWR_MODE                ((uint32) 0x02u << RefBuffer_OA_PWR_MODE_SHIFT)
#define RefBuffer_OA_PWR_MODE_MASK           ((uint32) 0x03u << RefBuffer_OA_PWR_MODE_SHIFT)
#define RefBuffer_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << RefBuffer_OA_DRIVE_STR_SEL_SHIFT)
#define RefBuffer_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << RefBuffer_OA_DRIVE_STR_SEL_SHIFT)
#define RefBuffer_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << RefBuffer_OA_DRIVE_STR_SEL_SHIFT)
#define RefBuffer_OA_COMP_EN                 ((uint32) 0x00u << RefBuffer_OA_COMP_EN_SHIFT)
#define RefBuffer_OA_PUMP_EN                 ((uint32) 0x01u << RefBuffer_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define RefBuffer_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (RefBuffer_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define RefBuffer_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (RefBuffer_OA_DRIVE_STR_SEL_10X) : \
                                                                             (RefBuffer_OA_DRIVE_STR_SEL_1X))
#define RefBuffer_GET_OA_PWR_MODE(mode)          ((mode) & RefBuffer_OA_PWR_MODE_MASK)
#define RefBuffer_CHECK_PWR_MODE_OFF             (0u != (RefBuffer_OA_RES_CTRL_REG & \
                                                                RefBuffer_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define RefBuffer_CHECK_DEEPSLEEP_SUPPORT        (0u != RefBuffer_DEEPSLEEP_SUPPORT) 

#define RefBuffer_DEFAULT_CTB_CTRL (RefBuffer_GET_DEEPSLEEP_ON(RefBuffer_DEEPSLEEP_SUPPORT) | \
                                           RefBuffer_CTB_CTRL_ENABLED)

#define RefBuffer_DEFAULT_OA_RES_CTRL (RefBuffer_OA_COMP_EN | \
                                              RefBuffer_GET_OA_DRIVE_STR(RefBuffer_OUTPUT_CURRENT))

#define RefBuffer_DEFAULT_OA_COMP_TRIM_REG (RefBuffer_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define RefBuffer_LOWPOWER                   (RefBuffer_LOW_POWER)
#define RefBuffer_MEDPOWER                   (RefBuffer_MED_POWER)
#define RefBuffer_HIGHPOWER                  (RefBuffer_HIGH_POWER)

/* PUMP ON/OFF defines */
#define RefBuffer_PUMPON                     (RefBuffer_PUMP_ON)
#define RefBuffer_PUMPOFF                    (RefBuffer_PUMP_OFF)

#define RefBuffer_OA_CTRL                    (RefBuffer_CTB_CTRL_REG)
#define RefBuffer_OA_RES_CTRL                (RefBuffer_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define RefBuffer_OA_CTB_EN_SHIFT            (RefBuffer_CTB_CTRL_ENABLED_SHIFT)
#define RefBuffer_OA_PUMP_CTRL_SHIFT         (RefBuffer_OA_PUMP_EN_SHIFT)
#define RefBuffer_OA_PUMP_EN_MASK            (0x800u)
#define RefBuffer_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_RefBuffer_H */


/* [] END OF FILE */
