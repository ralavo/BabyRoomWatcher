/***************************************************************************//**
* \file     PIRAmplifierStage2_PVT.h
* \version  1.0
*
* \brief
*  This file contains the private constants and macros used in
*  the PGA_P4 Component code.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_P4_PIRAmplifierStage2_PVT_H) 
#define CY_PGA_P4_PIRAmplifierStage2_PVT_H

#include "PIRAmplifierStage2.h"


/***************************************
*         Internal Constants
***************************************/
    
#define PIRAmplifierStage2_POWER                  ((uint32)3u)
#define PIRAmplifierStage2_GAIN                   ((uint32)0u)
    
#define PIRAmplifierStage2_POWER_MAX              (PIRAmplifierStage2_HIGH)
#define PIRAmplifierStage2_GAIN_MAX               (PIRAmplifierStage2_GAIN_32)

/* ((Gain steps / 2) + 1) */
#define PIRAmplifierStage2_COMP_TAB_HEIGHT        ((PIRAmplifierStage2_GAIN_MAX >> 1u) + 1u)
#define PIRAmplifierStage2_COMP_TAB_WIDTH         (PIRAmplifierStage2_POWER_MAX)
#define PIRAmplifierStage2_GET_COMP_TAB_GAIN_MASK (0x00000007u)

#define PIRAmplifierStage2_VREF_INTERNAL          (0u)
#define PIRAmplifierStage2_OUTPUT_MODE_10x        (1u)

#define PIRAmplifierStage2_DEFAULT_POWER          ((uint32)PIRAmplifierStage2_POWER << PIRAmplifierStage2_OA_PWR_MODE_SHIFT)
#define PIRAmplifierStage2_DEFAULT_GAIN           ((uint32)PIRAmplifierStage2_GAIN << PIRAmplifierStage2_RES_TAP_SHIFT)
#define PIRAmplifierStage2_DEFAULT_GAIN_POWER     (PIRAmplifierStage2_DEFAULT_GAIN | PIRAmplifierStage2_DEFAULT_POWER)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint32 PIRAmplifierStage2_internalGainPower;
extern const uint32 PIRAmplifierStage2_compTab[PIRAmplifierStage2_COMP_TAB_HEIGHT][PIRAmplifierStage2_COMP_TAB_WIDTH];


/***************************************
*       Macro Definitions
***************************************/

/* Returns true if component available in Deep Sleep power mode */
#define PIRAmplifierStage2_CHECK_DEEPSLEEP_SUPPORT (PIRAmplifierStage2_DEEPSLEEP_SUPPORT != 0u)
/* Returns true if component uses 10x (Class AB) output buffer mode*/
#define PIRAmplifierStage2_CHECK_OUTPUT_MODE      (PIRAmplifierStage2_OUTPUT_MODE == PIRAmplifierStage2_OUTPUT_MODE_10x)
#define PIRAmplifierStage2_GET_DEEPSLEEP_ON       ((PIRAmplifierStage2_CHECK_DEEPSLEEP_SUPPORT) ? \
                                                    (PIRAmplifierStage2_DEEPSLEEP_ON) : (0u))
#define PIRAmplifierStage2_GET_OA_DRIVE_STR       ((PIRAmplifierStage2_CHECK_OUTPUT_MODE) ? \
                                                    (PIRAmplifierStage2_OA_DRIVE_STR_SEL_10X) : \
                                                        (PIRAmplifierStage2_OA_DRIVE_STR_SEL_1X))
#define PIRAmplifierStage2_GET_POWER              (PIRAmplifierStage2_internalGainPower & \
                                                    PIRAmplifierStage2_OA_PWR_MODE_MASK)
#define PIRAmplifierStage2_DEFAULT_CTB_CTRL       (PIRAmplifierStage2_GET_DEEPSLEEP_ON | PIRAmplifierStage2_ENABLED)
#define PIRAmplifierStage2_DEFAULT_OA_RES_CTRL    (PIRAmplifierStage2_GET_OA_DRIVE_STR | PIRAmplifierStage2_OA_PUMP_EN)
#define PIRAmplifierStage2_DEFAULT_OA_RES_CTRL_MASK (PIRAmplifierStage2_OA_DRIVE_STR_SEL_MASK | PIRAmplifierStage2_OA_PUMP_EN)
#define PIRAmplifierStage2_GET_COMP_TAB_GAIN      ((PIRAmplifierStage2_internalGainPower >> \
                                                    (PIRAmplifierStage2_RES_TAP_SHIFT + 1u)) & \
                                                        PIRAmplifierStage2_GET_COMP_TAB_GAIN_MASK)
#define PIRAmplifierStage2_GET_COMP_TAB           (PIRAmplifierStage2_compTab[PIRAmplifierStage2_GET_COMP_TAB_GAIN] \
                                                                         [PIRAmplifierStage2_GET_POWER - 1u])
#define PIRAmplifierStage2_GET_C_FB               (PIRAmplifierStage2_GET_COMP_TAB & PIRAmplifierStage2_C_FB_MASK)
#define PIRAmplifierStage2_GET_OA_COMP_TRIM       (PIRAmplifierStage2_GET_COMP_TAB & PIRAmplifierStage2_OA_COMP_TRIM_MASK)


#endif /* CY_PGA_P4_PIRAmplifierStage2_PVT_H */

/* [] END OF FILE */
