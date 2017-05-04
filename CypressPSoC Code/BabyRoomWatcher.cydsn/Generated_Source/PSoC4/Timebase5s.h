/*******************************************************************************
* File Name: Timebase5s.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the Timebase5s
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_Timebase5s_H)
#define CY_TCPWM_Timebase5s_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Timebase5s_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Timebase5s_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Timebase5s_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Timebase5s_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Timebase5s_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define Timebase5s_QUAD_ENCODING_MODES            (0lu)
#define Timebase5s_QUAD_AUTO_START                (0lu)

/* Signal modes */
#define Timebase5s_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Timebase5s_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Timebase5s_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Timebase5s_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Timebase5s_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Timebase5s_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Timebase5s_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Timebase5s_TC_RUN_MODE                    (0lu)
#define Timebase5s_TC_COUNTER_MODE                (1lu)
#define Timebase5s_TC_COMP_CAP_MODE               (0lu)
#define Timebase5s_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Timebase5s_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Timebase5s_TC_COUNT_SIGNAL_MODE           (3lu)
#define Timebase5s_TC_START_SIGNAL_MODE           (0lu)
#define Timebase5s_TC_STOP_SIGNAL_MODE            (0lu)
#define Timebase5s_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Timebase5s_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Timebase5s_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Timebase5s_TC_START_SIGNAL_PRESENT        (0lu)
#define Timebase5s_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Timebase5s_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Timebase5s_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define Timebase5s_PWM_KILL_EVENT                 (0lu)
#define Timebase5s_PWM_STOP_EVENT                 (0lu)
#define Timebase5s_PWM_MODE                       (4lu)
#define Timebase5s_PWM_OUT_N_INVERT               (0lu)
#define Timebase5s_PWM_OUT_INVERT                 (0lu)
#define Timebase5s_PWM_ALIGN                      (0lu)
#define Timebase5s_PWM_RUN_MODE                   (0lu)
#define Timebase5s_PWM_DEAD_TIME_CYCLE            (0lu)
#define Timebase5s_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Timebase5s_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Timebase5s_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Timebase5s_PWM_START_SIGNAL_MODE          (0lu)
#define Timebase5s_PWM_STOP_SIGNAL_MODE           (0lu)
#define Timebase5s_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Timebase5s_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Timebase5s_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Timebase5s_PWM_START_SIGNAL_PRESENT       (0lu)
#define Timebase5s_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Timebase5s_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Timebase5s_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Timebase5s_TC_PERIOD_VALUE                (4999lu)
#define Timebase5s_TC_COMPARE_VALUE               (2500lu)
#define Timebase5s_TC_COMPARE_BUF_VALUE           (65535lu)
#define Timebase5s_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Timebase5s_PWM_PERIOD_VALUE               (65535lu)
#define Timebase5s_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Timebase5s_PWM_PERIOD_SWAP                (0lu)
#define Timebase5s_PWM_COMPARE_VALUE              (65535lu)
#define Timebase5s_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Timebase5s_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Timebase5s__LEFT 0
#define Timebase5s__RIGHT 1
#define Timebase5s__CENTER 2
#define Timebase5s__ASYMMETRIC 3

#define Timebase5s__X1 0
#define Timebase5s__X2 1
#define Timebase5s__X4 2

#define Timebase5s__PWM 4
#define Timebase5s__PWM_DT 5
#define Timebase5s__PWM_PR 6

#define Timebase5s__INVERSE 1
#define Timebase5s__DIRECT 0

#define Timebase5s__CAPTURE 2
#define Timebase5s__COMPARE 0

#define Timebase5s__TRIG_LEVEL 3
#define Timebase5s__TRIG_RISING 0
#define Timebase5s__TRIG_FALLING 1
#define Timebase5s__TRIG_BOTH 2

#define Timebase5s__INTR_MASK_TC 1
#define Timebase5s__INTR_MASK_CC_MATCH 2
#define Timebase5s__INTR_MASK_NONE 0
#define Timebase5s__INTR_MASK_TC_CC 3

#define Timebase5s__UNCONFIG 8
#define Timebase5s__TIMER 1
#define Timebase5s__QUAD 3
#define Timebase5s__PWM_SEL 7

#define Timebase5s__COUNT_UP 0
#define Timebase5s__COUNT_DOWN 1
#define Timebase5s__COUNT_UPDOWN0 2
#define Timebase5s__COUNT_UPDOWN1 3


/* Prescaler */
#define Timebase5s_PRESCALE_DIVBY1                ((uint32)(0u << Timebase5s_PRESCALER_SHIFT))
#define Timebase5s_PRESCALE_DIVBY2                ((uint32)(1u << Timebase5s_PRESCALER_SHIFT))
#define Timebase5s_PRESCALE_DIVBY4                ((uint32)(2u << Timebase5s_PRESCALER_SHIFT))
#define Timebase5s_PRESCALE_DIVBY8                ((uint32)(3u << Timebase5s_PRESCALER_SHIFT))
#define Timebase5s_PRESCALE_DIVBY16               ((uint32)(4u << Timebase5s_PRESCALER_SHIFT))
#define Timebase5s_PRESCALE_DIVBY32               ((uint32)(5u << Timebase5s_PRESCALER_SHIFT))
#define Timebase5s_PRESCALE_DIVBY64               ((uint32)(6u << Timebase5s_PRESCALER_SHIFT))
#define Timebase5s_PRESCALE_DIVBY128              ((uint32)(7u << Timebase5s_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Timebase5s_MODE_TIMER_COMPARE             ((uint32)(Timebase5s__COMPARE         <<  \
                                                                  Timebase5s_MODE_SHIFT))
#define Timebase5s_MODE_TIMER_CAPTURE             ((uint32)(Timebase5s__CAPTURE         <<  \
                                                                  Timebase5s_MODE_SHIFT))
#define Timebase5s_MODE_QUAD                      ((uint32)(Timebase5s__QUAD            <<  \
                                                                  Timebase5s_MODE_SHIFT))
#define Timebase5s_MODE_PWM                       ((uint32)(Timebase5s__PWM             <<  \
                                                                  Timebase5s_MODE_SHIFT))
#define Timebase5s_MODE_PWM_DT                    ((uint32)(Timebase5s__PWM_DT          <<  \
                                                                  Timebase5s_MODE_SHIFT))
#define Timebase5s_MODE_PWM_PR                    ((uint32)(Timebase5s__PWM_PR          <<  \
                                                                  Timebase5s_MODE_SHIFT))

/* Quad Modes */
#define Timebase5s_MODE_X1                        ((uint32)(Timebase5s__X1              <<  \
                                                                  Timebase5s_QUAD_MODE_SHIFT))
#define Timebase5s_MODE_X2                        ((uint32)(Timebase5s__X2              <<  \
                                                                  Timebase5s_QUAD_MODE_SHIFT))
#define Timebase5s_MODE_X4                        ((uint32)(Timebase5s__X4              <<  \
                                                                  Timebase5s_QUAD_MODE_SHIFT))

/* Counter modes */
#define Timebase5s_COUNT_UP                       ((uint32)(Timebase5s__COUNT_UP        <<  \
                                                                  Timebase5s_UPDOWN_SHIFT))
#define Timebase5s_COUNT_DOWN                     ((uint32)(Timebase5s__COUNT_DOWN      <<  \
                                                                  Timebase5s_UPDOWN_SHIFT))
#define Timebase5s_COUNT_UPDOWN0                  ((uint32)(Timebase5s__COUNT_UPDOWN0   <<  \
                                                                  Timebase5s_UPDOWN_SHIFT))
#define Timebase5s_COUNT_UPDOWN1                  ((uint32)(Timebase5s__COUNT_UPDOWN1   <<  \
                                                                  Timebase5s_UPDOWN_SHIFT))

/* PWM output invert */
#define Timebase5s_INVERT_LINE                    ((uint32)(Timebase5s__INVERSE         <<  \
                                                                  Timebase5s_INV_OUT_SHIFT))
#define Timebase5s_INVERT_LINE_N                  ((uint32)(Timebase5s__INVERSE         <<  \
                                                                  Timebase5s_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Timebase5s_TRIG_RISING                    ((uint32)Timebase5s__TRIG_RISING)
#define Timebase5s_TRIG_FALLING                   ((uint32)Timebase5s__TRIG_FALLING)
#define Timebase5s_TRIG_BOTH                      ((uint32)Timebase5s__TRIG_BOTH)
#define Timebase5s_TRIG_LEVEL                     ((uint32)Timebase5s__TRIG_LEVEL)

/* Interrupt mask */
#define Timebase5s_INTR_MASK_TC                   ((uint32)Timebase5s__INTR_MASK_TC)
#define Timebase5s_INTR_MASK_CC_MATCH             ((uint32)Timebase5s__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Timebase5s_CC_MATCH_SET                   (0x00u)
#define Timebase5s_CC_MATCH_CLEAR                 (0x01u)
#define Timebase5s_CC_MATCH_INVERT                (0x02u)
#define Timebase5s_CC_MATCH_NO_CHANGE             (0x03u)
#define Timebase5s_OVERLOW_SET                    (0x00u)
#define Timebase5s_OVERLOW_CLEAR                  (0x04u)
#define Timebase5s_OVERLOW_INVERT                 (0x08u)
#define Timebase5s_OVERLOW_NO_CHANGE              (0x0Cu)
#define Timebase5s_UNDERFLOW_SET                  (0x00u)
#define Timebase5s_UNDERFLOW_CLEAR                (0x10u)
#define Timebase5s_UNDERFLOW_INVERT               (0x20u)
#define Timebase5s_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Timebase5s_PWM_MODE_LEFT                  (Timebase5s_CC_MATCH_CLEAR        |   \
                                                         Timebase5s_OVERLOW_SET           |   \
                                                         Timebase5s_UNDERFLOW_NO_CHANGE)
#define Timebase5s_PWM_MODE_RIGHT                 (Timebase5s_CC_MATCH_SET          |   \
                                                         Timebase5s_OVERLOW_NO_CHANGE     |   \
                                                         Timebase5s_UNDERFLOW_CLEAR)
#define Timebase5s_PWM_MODE_ASYM                  (Timebase5s_CC_MATCH_INVERT       |   \
                                                         Timebase5s_OVERLOW_SET           |   \
                                                         Timebase5s_UNDERFLOW_CLEAR)

#if (Timebase5s_CY_TCPWM_V2)
    #if(Timebase5s_CY_TCPWM_4000)
        #define Timebase5s_PWM_MODE_CENTER                (Timebase5s_CC_MATCH_INVERT       |   \
                                                                 Timebase5s_OVERLOW_NO_CHANGE     |   \
                                                                 Timebase5s_UNDERFLOW_CLEAR)
    #else
        #define Timebase5s_PWM_MODE_CENTER                (Timebase5s_CC_MATCH_INVERT       |   \
                                                                 Timebase5s_OVERLOW_SET           |   \
                                                                 Timebase5s_UNDERFLOW_CLEAR)
    #endif /* (Timebase5s_CY_TCPWM_4000) */
#else
    #define Timebase5s_PWM_MODE_CENTER                (Timebase5s_CC_MATCH_INVERT       |   \
                                                             Timebase5s_OVERLOW_NO_CHANGE     |   \
                                                             Timebase5s_UNDERFLOW_CLEAR)
#endif /* (Timebase5s_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Timebase5s_CMD_CAPTURE                    (0u)
#define Timebase5s_CMD_RELOAD                     (8u)
#define Timebase5s_CMD_STOP                       (16u)
#define Timebase5s_CMD_START                      (24u)

/* Status */
#define Timebase5s_STATUS_DOWN                    (1u)
#define Timebase5s_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Timebase5s_Init(void);
void   Timebase5s_Enable(void);
void   Timebase5s_Start(void);
void   Timebase5s_Stop(void);

void   Timebase5s_SetMode(uint32 mode);
void   Timebase5s_SetCounterMode(uint32 counterMode);
void   Timebase5s_SetPWMMode(uint32 modeMask);
void   Timebase5s_SetQDMode(uint32 qdMode);

void   Timebase5s_SetPrescaler(uint32 prescaler);
void   Timebase5s_TriggerCommand(uint32 mask, uint32 command);
void   Timebase5s_SetOneShot(uint32 oneShotEnable);
uint32 Timebase5s_ReadStatus(void);

void   Timebase5s_SetPWMSyncKill(uint32 syncKillEnable);
void   Timebase5s_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Timebase5s_SetPWMDeadTime(uint32 deadTime);
void   Timebase5s_SetPWMInvert(uint32 mask);

void   Timebase5s_SetInterruptMode(uint32 interruptMask);
uint32 Timebase5s_GetInterruptSourceMasked(void);
uint32 Timebase5s_GetInterruptSource(void);
void   Timebase5s_ClearInterrupt(uint32 interruptMask);
void   Timebase5s_SetInterrupt(uint32 interruptMask);

void   Timebase5s_WriteCounter(uint32 count);
uint32 Timebase5s_ReadCounter(void);

uint32 Timebase5s_ReadCapture(void);
uint32 Timebase5s_ReadCaptureBuf(void);

void   Timebase5s_WritePeriod(uint32 period);
uint32 Timebase5s_ReadPeriod(void);
void   Timebase5s_WritePeriodBuf(uint32 periodBuf);
uint32 Timebase5s_ReadPeriodBuf(void);

void   Timebase5s_WriteCompare(uint32 compare);
uint32 Timebase5s_ReadCompare(void);
void   Timebase5s_WriteCompareBuf(uint32 compareBuf);
uint32 Timebase5s_ReadCompareBuf(void);

void   Timebase5s_SetPeriodSwap(uint32 swapEnable);
void   Timebase5s_SetCompareSwap(uint32 swapEnable);

void   Timebase5s_SetCaptureMode(uint32 triggerMode);
void   Timebase5s_SetReloadMode(uint32 triggerMode);
void   Timebase5s_SetStartMode(uint32 triggerMode);
void   Timebase5s_SetStopMode(uint32 triggerMode);
void   Timebase5s_SetCountMode(uint32 triggerMode);

void   Timebase5s_SaveConfig(void);
void   Timebase5s_RestoreConfig(void);
void   Timebase5s_Sleep(void);
void   Timebase5s_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Timebase5s_BLOCK_CONTROL_REG              (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Timebase5s_BLOCK_CONTROL_PTR              ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Timebase5s_COMMAND_REG                    (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Timebase5s_COMMAND_PTR                    ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Timebase5s_INTRRUPT_CAUSE_REG             (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Timebase5s_INTRRUPT_CAUSE_PTR             ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Timebase5s_CONTROL_REG                    (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__CTRL )
#define Timebase5s_CONTROL_PTR                    ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__CTRL )
#define Timebase5s_STATUS_REG                     (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__STATUS )
#define Timebase5s_STATUS_PTR                     ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__STATUS )
#define Timebase5s_COUNTER_REG                    (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__COUNTER )
#define Timebase5s_COUNTER_PTR                    ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__COUNTER )
#define Timebase5s_COMP_CAP_REG                   (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__CC )
#define Timebase5s_COMP_CAP_PTR                   ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__CC )
#define Timebase5s_COMP_CAP_BUF_REG               (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__CC_BUFF )
#define Timebase5s_COMP_CAP_BUF_PTR               ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__CC_BUFF )
#define Timebase5s_PERIOD_REG                     (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__PERIOD )
#define Timebase5s_PERIOD_PTR                     ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__PERIOD )
#define Timebase5s_PERIOD_BUF_REG                 (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Timebase5s_PERIOD_BUF_PTR                 ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Timebase5s_TRIG_CONTROL0_REG              (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Timebase5s_TRIG_CONTROL0_PTR              ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Timebase5s_TRIG_CONTROL1_REG              (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Timebase5s_TRIG_CONTROL1_PTR              ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Timebase5s_TRIG_CONTROL2_REG              (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Timebase5s_TRIG_CONTROL2_PTR              ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Timebase5s_INTERRUPT_REQ_REG              (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__INTR )
#define Timebase5s_INTERRUPT_REQ_PTR              ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__INTR )
#define Timebase5s_INTERRUPT_SET_REG              (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__INTR_SET )
#define Timebase5s_INTERRUPT_SET_PTR              ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__INTR_SET )
#define Timebase5s_INTERRUPT_MASK_REG             (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__INTR_MASK )
#define Timebase5s_INTERRUPT_MASK_PTR             ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__INTR_MASK )
#define Timebase5s_INTERRUPT_MASKED_REG           (*(reg32 *) Timebase5s_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Timebase5s_INTERRUPT_MASKED_PTR           ( (reg32 *) Timebase5s_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Timebase5s_MASK                           ((uint32)Timebase5s_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Timebase5s_RELOAD_CC_SHIFT                (0u)
#define Timebase5s_RELOAD_PERIOD_SHIFT            (1u)
#define Timebase5s_PWM_SYNC_KILL_SHIFT            (2u)
#define Timebase5s_PWM_STOP_KILL_SHIFT            (3u)
#define Timebase5s_PRESCALER_SHIFT                (8u)
#define Timebase5s_UPDOWN_SHIFT                   (16u)
#define Timebase5s_ONESHOT_SHIFT                  (18u)
#define Timebase5s_QUAD_MODE_SHIFT                (20u)
#define Timebase5s_INV_OUT_SHIFT                  (20u)
#define Timebase5s_INV_COMPL_OUT_SHIFT            (21u)
#define Timebase5s_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Timebase5s_RELOAD_CC_MASK                 ((uint32)(Timebase5s_1BIT_MASK        <<  \
                                                                            Timebase5s_RELOAD_CC_SHIFT))
#define Timebase5s_RELOAD_PERIOD_MASK             ((uint32)(Timebase5s_1BIT_MASK        <<  \
                                                                            Timebase5s_RELOAD_PERIOD_SHIFT))
#define Timebase5s_PWM_SYNC_KILL_MASK             ((uint32)(Timebase5s_1BIT_MASK        <<  \
                                                                            Timebase5s_PWM_SYNC_KILL_SHIFT))
#define Timebase5s_PWM_STOP_KILL_MASK             ((uint32)(Timebase5s_1BIT_MASK        <<  \
                                                                            Timebase5s_PWM_STOP_KILL_SHIFT))
#define Timebase5s_PRESCALER_MASK                 ((uint32)(Timebase5s_8BIT_MASK        <<  \
                                                                            Timebase5s_PRESCALER_SHIFT))
#define Timebase5s_UPDOWN_MASK                    ((uint32)(Timebase5s_2BIT_MASK        <<  \
                                                                            Timebase5s_UPDOWN_SHIFT))
#define Timebase5s_ONESHOT_MASK                   ((uint32)(Timebase5s_1BIT_MASK        <<  \
                                                                            Timebase5s_ONESHOT_SHIFT))
#define Timebase5s_QUAD_MODE_MASK                 ((uint32)(Timebase5s_3BIT_MASK        <<  \
                                                                            Timebase5s_QUAD_MODE_SHIFT))
#define Timebase5s_INV_OUT_MASK                   ((uint32)(Timebase5s_2BIT_MASK        <<  \
                                                                            Timebase5s_INV_OUT_SHIFT))
#define Timebase5s_MODE_MASK                      ((uint32)(Timebase5s_3BIT_MASK        <<  \
                                                                            Timebase5s_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Timebase5s_CAPTURE_SHIFT                  (0u)
#define Timebase5s_COUNT_SHIFT                    (2u)
#define Timebase5s_RELOAD_SHIFT                   (4u)
#define Timebase5s_STOP_SHIFT                     (6u)
#define Timebase5s_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Timebase5s_CAPTURE_MASK                   ((uint32)(Timebase5s_2BIT_MASK        <<  \
                                                                  Timebase5s_CAPTURE_SHIFT))
#define Timebase5s_COUNT_MASK                     ((uint32)(Timebase5s_2BIT_MASK        <<  \
                                                                  Timebase5s_COUNT_SHIFT))
#define Timebase5s_RELOAD_MASK                    ((uint32)(Timebase5s_2BIT_MASK        <<  \
                                                                  Timebase5s_RELOAD_SHIFT))
#define Timebase5s_STOP_MASK                      ((uint32)(Timebase5s_2BIT_MASK        <<  \
                                                                  Timebase5s_STOP_SHIFT))
#define Timebase5s_START_MASK                     ((uint32)(Timebase5s_2BIT_MASK        <<  \
                                                                  Timebase5s_START_SHIFT))

/* MASK */
#define Timebase5s_1BIT_MASK                      ((uint32)0x01u)
#define Timebase5s_2BIT_MASK                      ((uint32)0x03u)
#define Timebase5s_3BIT_MASK                      ((uint32)0x07u)
#define Timebase5s_6BIT_MASK                      ((uint32)0x3Fu)
#define Timebase5s_8BIT_MASK                      ((uint32)0xFFu)
#define Timebase5s_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Timebase5s_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Timebase5s_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Timebase5s_QUAD_ENCODING_MODES     << Timebase5s_QUAD_MODE_SHIFT))       |\
         ((uint32)(Timebase5s_CONFIG                  << Timebase5s_MODE_SHIFT)))

#define Timebase5s_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Timebase5s_PWM_STOP_EVENT          << Timebase5s_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Timebase5s_PWM_OUT_INVERT          << Timebase5s_INV_OUT_SHIFT))         |\
         ((uint32)(Timebase5s_PWM_OUT_N_INVERT        << Timebase5s_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Timebase5s_PWM_MODE                << Timebase5s_MODE_SHIFT)))

#define Timebase5s_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Timebase5s_PWM_RUN_MODE         << Timebase5s_ONESHOT_SHIFT))
            
#define Timebase5s_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Timebase5s_PWM_ALIGN            << Timebase5s_UPDOWN_SHIFT))

#define Timebase5s_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Timebase5s_PWM_KILL_EVENT      << Timebase5s_PWM_SYNC_KILL_SHIFT))

#define Timebase5s_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Timebase5s_PWM_DEAD_TIME_CYCLE  << Timebase5s_PRESCALER_SHIFT))

#define Timebase5s_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Timebase5s_PWM_PRESCALER        << Timebase5s_PRESCALER_SHIFT))

#define Timebase5s_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Timebase5s_TC_PRESCALER            << Timebase5s_PRESCALER_SHIFT))       |\
         ((uint32)(Timebase5s_TC_COUNTER_MODE         << Timebase5s_UPDOWN_SHIFT))          |\
         ((uint32)(Timebase5s_TC_RUN_MODE             << Timebase5s_ONESHOT_SHIFT))         |\
         ((uint32)(Timebase5s_TC_COMP_CAP_MODE        << Timebase5s_MODE_SHIFT)))
        
#define Timebase5s_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Timebase5s_QUAD_PHIA_SIGNAL_MODE   << Timebase5s_COUNT_SHIFT))           |\
         ((uint32)(Timebase5s_QUAD_INDEX_SIGNAL_MODE  << Timebase5s_RELOAD_SHIFT))          |\
         ((uint32)(Timebase5s_QUAD_STOP_SIGNAL_MODE   << Timebase5s_STOP_SHIFT))            |\
         ((uint32)(Timebase5s_QUAD_PHIB_SIGNAL_MODE   << Timebase5s_START_SHIFT)))

#define Timebase5s_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Timebase5s_PWM_SWITCH_SIGNAL_MODE  << Timebase5s_CAPTURE_SHIFT))         |\
         ((uint32)(Timebase5s_PWM_COUNT_SIGNAL_MODE   << Timebase5s_COUNT_SHIFT))           |\
         ((uint32)(Timebase5s_PWM_RELOAD_SIGNAL_MODE  << Timebase5s_RELOAD_SHIFT))          |\
         ((uint32)(Timebase5s_PWM_STOP_SIGNAL_MODE    << Timebase5s_STOP_SHIFT))            |\
         ((uint32)(Timebase5s_PWM_START_SIGNAL_MODE   << Timebase5s_START_SHIFT)))

#define Timebase5s_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Timebase5s_TC_CAPTURE_SIGNAL_MODE  << Timebase5s_CAPTURE_SHIFT))         |\
         ((uint32)(Timebase5s_TC_COUNT_SIGNAL_MODE    << Timebase5s_COUNT_SHIFT))           |\
         ((uint32)(Timebase5s_TC_RELOAD_SIGNAL_MODE   << Timebase5s_RELOAD_SHIFT))          |\
         ((uint32)(Timebase5s_TC_STOP_SIGNAL_MODE     << Timebase5s_STOP_SHIFT))            |\
         ((uint32)(Timebase5s_TC_START_SIGNAL_MODE    << Timebase5s_START_SHIFT)))
        
#define Timebase5s_TIMER_UPDOWN_CNT_USED                                                          \
                ((Timebase5s__COUNT_UPDOWN0 == Timebase5s_TC_COUNTER_MODE)                  ||\
                 (Timebase5s__COUNT_UPDOWN1 == Timebase5s_TC_COUNTER_MODE))

#define Timebase5s_PWM_UPDOWN_CNT_USED                                                            \
                ((Timebase5s__CENTER == Timebase5s_PWM_ALIGN)                               ||\
                 (Timebase5s__ASYMMETRIC == Timebase5s_PWM_ALIGN))               
        
#define Timebase5s_PWM_PR_INIT_VALUE              (1u)
#define Timebase5s_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Timebase5s_H */

/* [] END OF FILE */
