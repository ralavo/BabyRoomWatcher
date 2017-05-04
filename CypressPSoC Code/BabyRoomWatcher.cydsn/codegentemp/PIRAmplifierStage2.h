/***************************************************************************//**
* \file     PIRAmplifierStage2.h
* \version  1.0
*
* \brief
*  This file contains the public API function prototypes and constants used in
*  the PGA_P4 Component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_P4_PIRAmplifierStage2_H) 
#define CY_PGA_P4_PIRAmplifierStage2_H 

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define PIRAmplifierStage2_VREF_MODE              (1u)
#define PIRAmplifierStage2_OUTPUT_MODE            (0u)
#define PIRAmplifierStage2_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/
extern uint8 PIRAmplifierStage2_initVar;
/** @} globals */


/***************************************
*        Function Prototypes 
***************************************/

/**
* \addtogroup group_general
* @{
*/
void PIRAmplifierStage2_Init(void);
void PIRAmplifierStage2_Enable(void);
void PIRAmplifierStage2_Start(void);
void PIRAmplifierStage2_Stop(void);
void PIRAmplifierStage2_SetPower(uint32 powerLevel);
void PIRAmplifierStage2_SetGain(uint32 gainLevel);
void PIRAmplifierStage2_PumpControl(uint32 onOff);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PIRAmplifierStage2_Sleep(void);
void PIRAmplifierStage2_Wakeup(void);
void PIRAmplifierStage2_SaveConfig(void);
void PIRAmplifierStage2_RestoreConfig(void);
/** @} power */


/**************************************
*           API Constants
**************************************/

/* Gain setting constants */
#define PIRAmplifierStage2__GAIN_1 0
#define PIRAmplifierStage2__GAIN_1_4 1
#define PIRAmplifierStage2__GAIN_2 2
#define PIRAmplifierStage2__GAIN_2_8 3
#define PIRAmplifierStage2__GAIN_4 4
#define PIRAmplifierStage2__GAIN_5_8 5
#define PIRAmplifierStage2__GAIN_10_7 7
#define PIRAmplifierStage2__GAIN_8 6
#define PIRAmplifierStage2__GAIN_21_3 9
#define PIRAmplifierStage2__GAIN_32 10
#define PIRAmplifierStage2__GAIN_16 8


/* Power setting constants */
#define PIRAmplifierStage2__LOW 1
#define PIRAmplifierStage2__MED 2
#define PIRAmplifierStage2__HIGH 3


/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup group_powerLevel
     * \brief Definitions for PIRAmplifierStage2_SetPower() function.
     *  @{
     */
    #define PIRAmplifierStage2_LOW                ((uint32)PIRAmplifierStage2__LOW)
    #define PIRAmplifierStage2_MED                ((uint32)PIRAmplifierStage2__MED)
    #define PIRAmplifierStage2_HIGH               ((uint32)PIRAmplifierStage2__HIGH)
    /** @} powerLevel */

    /** \addtogroup group_boostPump
     * \brief Definitions for PIRAmplifierStage2_PumpControl() function.
     *  @{
     */
    #define PIRAmplifierStage2_BOOST_ON           ((uint32)1u)
    #define PIRAmplifierStage2_BOOST_OFF          ((uint32)0u)
    /** @} boostPump */

    /** \addtogroup group_gain
     * \brief Definitions for PIRAmplifierStage2_SetGain() function.
     *  @{
     */
    #define PIRAmplifierStage2_GAIN_1             ((uint32)PIRAmplifierStage2__GAIN_1)
    #define PIRAmplifierStage2_GAIN_1_4           ((uint32)PIRAmplifierStage2__GAIN_1_4)
    #define PIRAmplifierStage2_GAIN_2             ((uint32)PIRAmplifierStage2__GAIN_2)
    #define PIRAmplifierStage2_GAIN_2_8           ((uint32)PIRAmplifierStage2__GAIN_2_8)
    #define PIRAmplifierStage2_GAIN_4             ((uint32)PIRAmplifierStage2__GAIN_4)
    #define PIRAmplifierStage2_GAIN_5_8           ((uint32)PIRAmplifierStage2__GAIN_5_8)
    #define PIRAmplifierStage2_GAIN_8             ((uint32)PIRAmplifierStage2__GAIN_8)
    #define PIRAmplifierStage2_GAIN_10_7          ((uint32)PIRAmplifierStage2__GAIN_10_7)
    #define PIRAmplifierStage2_GAIN_16            ((uint32)PIRAmplifierStage2__GAIN_16)
    #define PIRAmplifierStage2_GAIN_21_3          ((uint32)PIRAmplifierStage2__GAIN_21_3)
    #define PIRAmplifierStage2_GAIN_32            ((uint32)PIRAmplifierStage2__GAIN_32)
    /** @} gain */
/** @} group_constants */


/***************************************
* Registers
***************************************/

#define PIRAmplifierStage2_CTB_CTRL_REG           (*(reg32 *) PIRAmplifierStage2_cy_psoc4_abuf__CTB_CTB_CTRL)
#define PIRAmplifierStage2_CTB_CTRL_PTR           ( (reg32 *) PIRAmplifierStage2_cy_psoc4_abuf__CTB_CTB_CTRL)
#define PIRAmplifierStage2_OA_RES_CTRL_REG        (*(reg32 *) PIRAmplifierStage2_cy_psoc4_abuf__OA_RES_CTRL)
#define PIRAmplifierStage2_OA_RES_CTRL_PTR        ( (reg32 *) PIRAmplifierStage2_cy_psoc4_abuf__OA_RES_CTRL)
#define PIRAmplifierStage2_OA_SW_REG              (*(reg32 *) PIRAmplifierStage2_cy_psoc4_abuf__OA_SW)
#define PIRAmplifierStage2_OA_SW_PTR              ( (reg32 *) PIRAmplifierStage2_cy_psoc4_abuf__OA_SW)
#define PIRAmplifierStage2_OA_COMP_TRIM_REG       (*(reg32 *) PIRAmplifierStage2_cy_psoc4_abuf__OA_COMP_TRIM)
#define PIRAmplifierStage2_OA_COMP_TRIM_PTR       ( (reg32 *) PIRAmplifierStage2_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
* Register Constants
***************************************/

/* PIRAmplifierStage2_CTB_CTRL_REG */
#define PIRAmplifierStage2_DEEPSLEEP_ON_SHIFT     (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define PIRAmplifierStage2_ENABLED_SHIFT          (31u)   /* [31] Enable of the CTB IP */

#define PIRAmplifierStage2_DEEPSLEEP_ON           ((uint32)0x01u << PIRAmplifierStage2_DEEPSLEEP_ON_SHIFT)
#define PIRAmplifierStage2_ENABLED                ((uint32)0x01u << PIRAmplifierStage2_ENABLED_SHIFT)

/* PIRAmplifierStage2_OA_RES_CTRL_REG */
#define PIRAmplifierStage2_OA_PWR_MODE_SHIFT      (0u)    /* [1:0]    Power level */
#define PIRAmplifierStage2_OA_DRIVE_STR_SEL_SHIFT (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define PIRAmplifierStage2_OA_PUMP_EN_SHIFT       (11u)   /* [11]     Pump enable */
#define PIRAmplifierStage2_RES_TAP_SHIFT          (16u)   /* [19:16]  PGA gain (resistor tap point) */
#define PIRAmplifierStage2_C_FB_SHIFT             (24u)   /* [27:24]  Feedback Capacitor */

#define PIRAmplifierStage2_OA_PWR_MODE_MASK       ((uint32)0x03u << PIRAmplifierStage2_OA_PWR_MODE_SHIFT)
#define PIRAmplifierStage2_OA_DRIVE_STR_SEL_1X    ((uint32)0x00u << PIRAmplifierStage2_OA_DRIVE_STR_SEL_SHIFT)
#define PIRAmplifierStage2_OA_DRIVE_STR_SEL_10X   ((uint32)0x01u << PIRAmplifierStage2_OA_DRIVE_STR_SEL_SHIFT)
#define PIRAmplifierStage2_OA_DRIVE_STR_SEL_MASK  ((uint32)0x01u << PIRAmplifierStage2_OA_DRIVE_STR_SEL_SHIFT)
#define PIRAmplifierStage2_OA_PUMP_EN             ((uint32)0x01u << PIRAmplifierStage2_OA_PUMP_EN_SHIFT)
#define PIRAmplifierStage2_RES_TAP_MASK           ((uint32)0x0Fu << PIRAmplifierStage2_RES_TAP_SHIFT)
#define PIRAmplifierStage2_C_FB_MASK              ((uint32)0x0Fu << PIRAmplifierStage2_C_FB_SHIFT)

/** PIRAmplifierStage2_OA_COMP_TRIM_REG */
#define PIRAmplifierStage2_OA_COMP_TRIM_SHIFT     (0u)    /* [1:0]    Opamp Compensation Capacitor Trim */
#define PIRAmplifierStage2_OA_COMP_TRIM_MASK      ((uint32)0x03u << PIRAmplifierStage2_OA_COMP_TRIM_SHIFT)

/** PIRAmplifierStage2_OA_SW_REG */
#define PIRAmplifierStage2_RBOT_TO_VSSA_SHIFT     (28u)   /* Resistor bottom  to VSSA */
#define PIRAmplifierStage2_RBOT_TO_VSSA           ((uint32)0x01u << PIRAmplifierStage2_RBOT_TO_VSSA_SHIFT)


#endif /* CY_PGA_P4_PIRAmplifierStage2_H */


/* [] END OF FILE */
