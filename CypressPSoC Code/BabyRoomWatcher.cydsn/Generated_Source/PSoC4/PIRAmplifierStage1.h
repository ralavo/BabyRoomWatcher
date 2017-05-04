/*******************************************************************************
* File Name: PIRAmplifierStage1.h
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


#if !defined(CY_OPAMP_PIRAmplifierStage1_H)
#define CY_OPAMP_PIRAmplifierStage1_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} PIRAmplifierStage1_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void PIRAmplifierStage1_Init(void);
void PIRAmplifierStage1_Enable(void);
void PIRAmplifierStage1_Start(void);
void PIRAmplifierStage1_Stop(void);
void PIRAmplifierStage1_SetPower(uint32 power);
void PIRAmplifierStage1_PumpControl(uint32 onOff);
void PIRAmplifierStage1_Sleep(void);
void PIRAmplifierStage1_Wakeup(void);
void PIRAmplifierStage1_SaveConfig(void);
void PIRAmplifierStage1_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define PIRAmplifierStage1_LOW_POWER      (1u)
#define PIRAmplifierStage1_MED_POWER      (2u)
#define PIRAmplifierStage1_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define PIRAmplifierStage1_PUMP_ON        (1u)
#define PIRAmplifierStage1_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define PIRAmplifierStage1_OUTPUT_CURRENT         (1u)
#define PIRAmplifierStage1_POWER                  (3u)
#define PIRAmplifierStage1_MODE                   (0u)
#define PIRAmplifierStage1_OA_COMP_TRIM_VALUE     (3u)
#define PIRAmplifierStage1_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  PIRAmplifierStage1_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define PIRAmplifierStage1_CTB_CTRL_REG       (*(reg32 *) PIRAmplifierStage1_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define PIRAmplifierStage1_CTB_CTRL_PTR       ( (reg32 *) PIRAmplifierStage1_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define PIRAmplifierStage1_CTB_CTRL_REG       (*(reg32 *) PIRAmplifierStage1_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define PIRAmplifierStage1_CTB_CTRL_PTR       ( (reg32 *) PIRAmplifierStage1_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define PIRAmplifierStage1_OA_RES_CTRL_REG    (*(reg32 *) PIRAmplifierStage1_cy_psoc4_abuf__OA_RES_CTRL)
#define PIRAmplifierStage1_OA_RES_CTRL_PTR    ( (reg32 *) PIRAmplifierStage1_cy_psoc4_abuf__OA_RES_CTRL)
#define PIRAmplifierStage1_OA_COMP_TRIM_REG   (*(reg32 *) PIRAmplifierStage1_cy_psoc4_abuf__OA_COMP_TRIM)
#define PIRAmplifierStage1_OA_COMP_TRIM_PTR   ( (reg32 *) PIRAmplifierStage1_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* PIRAmplifierStage1_CTB_CTRL_REG */
#define PIRAmplifierStage1_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define PIRAmplifierStage1_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define PIRAmplifierStage1_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << PIRAmplifierStage1_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define PIRAmplifierStage1_CTB_CTRL_ENABLED               ((uint32) 0x01u << PIRAmplifierStage1_CTB_CTRL_ENABLED_SHIFT)


/* PIRAmplifierStage1_OA_RES_CTRL_REG */
#define PIRAmplifierStage1_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define PIRAmplifierStage1_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define PIRAmplifierStage1_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define PIRAmplifierStage1_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define PIRAmplifierStage1_OA_PWR_MODE                ((uint32) 0x02u << PIRAmplifierStage1_OA_PWR_MODE_SHIFT)
#define PIRAmplifierStage1_OA_PWR_MODE_MASK           ((uint32) 0x03u << PIRAmplifierStage1_OA_PWR_MODE_SHIFT)
#define PIRAmplifierStage1_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << PIRAmplifierStage1_OA_DRIVE_STR_SEL_SHIFT)
#define PIRAmplifierStage1_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << PIRAmplifierStage1_OA_DRIVE_STR_SEL_SHIFT)
#define PIRAmplifierStage1_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << PIRAmplifierStage1_OA_DRIVE_STR_SEL_SHIFT)
#define PIRAmplifierStage1_OA_COMP_EN                 ((uint32) 0x00u << PIRAmplifierStage1_OA_COMP_EN_SHIFT)
#define PIRAmplifierStage1_OA_PUMP_EN                 ((uint32) 0x01u << PIRAmplifierStage1_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define PIRAmplifierStage1_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (PIRAmplifierStage1_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define PIRAmplifierStage1_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (PIRAmplifierStage1_OA_DRIVE_STR_SEL_10X) : \
                                                                             (PIRAmplifierStage1_OA_DRIVE_STR_SEL_1X))
#define PIRAmplifierStage1_GET_OA_PWR_MODE(mode)          ((mode) & PIRAmplifierStage1_OA_PWR_MODE_MASK)
#define PIRAmplifierStage1_CHECK_PWR_MODE_OFF             (0u != (PIRAmplifierStage1_OA_RES_CTRL_REG & \
                                                                PIRAmplifierStage1_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define PIRAmplifierStage1_CHECK_DEEPSLEEP_SUPPORT        (0u != PIRAmplifierStage1_DEEPSLEEP_SUPPORT) 

#define PIRAmplifierStage1_DEFAULT_CTB_CTRL (PIRAmplifierStage1_GET_DEEPSLEEP_ON(PIRAmplifierStage1_DEEPSLEEP_SUPPORT) | \
                                           PIRAmplifierStage1_CTB_CTRL_ENABLED)

#define PIRAmplifierStage1_DEFAULT_OA_RES_CTRL (PIRAmplifierStage1_OA_COMP_EN | \
                                              PIRAmplifierStage1_GET_OA_DRIVE_STR(PIRAmplifierStage1_OUTPUT_CURRENT))

#define PIRAmplifierStage1_DEFAULT_OA_COMP_TRIM_REG (PIRAmplifierStage1_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define PIRAmplifierStage1_LOWPOWER                   (PIRAmplifierStage1_LOW_POWER)
#define PIRAmplifierStage1_MEDPOWER                   (PIRAmplifierStage1_MED_POWER)
#define PIRAmplifierStage1_HIGHPOWER                  (PIRAmplifierStage1_HIGH_POWER)

/* PUMP ON/OFF defines */
#define PIRAmplifierStage1_PUMPON                     (PIRAmplifierStage1_PUMP_ON)
#define PIRAmplifierStage1_PUMPOFF                    (PIRAmplifierStage1_PUMP_OFF)

#define PIRAmplifierStage1_OA_CTRL                    (PIRAmplifierStage1_CTB_CTRL_REG)
#define PIRAmplifierStage1_OA_RES_CTRL                (PIRAmplifierStage1_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define PIRAmplifierStage1_OA_CTB_EN_SHIFT            (PIRAmplifierStage1_CTB_CTRL_ENABLED_SHIFT)
#define PIRAmplifierStage1_OA_PUMP_CTRL_SHIFT         (PIRAmplifierStage1_OA_PUMP_EN_SHIFT)
#define PIRAmplifierStage1_OA_PUMP_EN_MASK            (0x800u)
#define PIRAmplifierStage1_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_PIRAmplifierStage1_H */


/* [] END OF FILE */
