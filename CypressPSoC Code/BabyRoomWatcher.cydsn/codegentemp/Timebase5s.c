/*******************************************************************************
* File Name: Timebase5s.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the Timebase5s
*  component
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

#include "Timebase5s.h"

uint8 Timebase5s_initVar = 0u;


/*******************************************************************************
* Function Name: Timebase5s_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Timebase5s configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Timebase5s__QUAD == Timebase5s_CONFIG)
        Timebase5s_CONTROL_REG = Timebase5s_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Timebase5s_TRIG_CONTROL1_REG  = Timebase5s_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Timebase5s_SetInterruptMode(Timebase5s_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Timebase5s_SetCounterMode(Timebase5s_COUNT_DOWN);
        Timebase5s_WritePeriod(Timebase5s_QUAD_PERIOD_INIT_VALUE);
        Timebase5s_WriteCounter(Timebase5s_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Timebase5s__QUAD == Timebase5s_CONFIG) */

    #if (Timebase5s__TIMER == Timebase5s_CONFIG)
        Timebase5s_CONTROL_REG = Timebase5s_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Timebase5s_TRIG_CONTROL1_REG  = Timebase5s_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Timebase5s_SetInterruptMode(Timebase5s_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Timebase5s_WritePeriod(Timebase5s_TC_PERIOD_VALUE );

        #if (Timebase5s__COMPARE == Timebase5s_TC_COMP_CAP_MODE)
            Timebase5s_WriteCompare(Timebase5s_TC_COMPARE_VALUE);

            #if (1u == Timebase5s_TC_COMPARE_SWAP)
                Timebase5s_SetCompareSwap(1u);
                Timebase5s_WriteCompareBuf(Timebase5s_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Timebase5s_TC_COMPARE_SWAP) */
        #endif  /* (Timebase5s__COMPARE == Timebase5s_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Timebase5s_CY_TCPWM_V2 && Timebase5s_TIMER_UPDOWN_CNT_USED && !Timebase5s_CY_TCPWM_4000)
            Timebase5s_WriteCounter(1u);
        #elif(Timebase5s__COUNT_DOWN == Timebase5s_TC_COUNTER_MODE)
            Timebase5s_WriteCounter(Timebase5s_TC_PERIOD_VALUE);
        #else
            Timebase5s_WriteCounter(0u);
        #endif /* (Timebase5s_CY_TCPWM_V2 && Timebase5s_TIMER_UPDOWN_CNT_USED && !Timebase5s_CY_TCPWM_4000) */
    #endif  /* (Timebase5s__TIMER == Timebase5s_CONFIG) */

    #if (Timebase5s__PWM_SEL == Timebase5s_CONFIG)
        Timebase5s_CONTROL_REG = Timebase5s_CTRL_PWM_BASE_CONFIG;

        #if (Timebase5s__PWM_PR == Timebase5s_PWM_MODE)
            Timebase5s_CONTROL_REG |= Timebase5s_CTRL_PWM_RUN_MODE;
            Timebase5s_WriteCounter(Timebase5s_PWM_PR_INIT_VALUE);
        #else
            Timebase5s_CONTROL_REG |= Timebase5s_CTRL_PWM_ALIGN | Timebase5s_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Timebase5s_CY_TCPWM_V2 && Timebase5s_PWM_UPDOWN_CNT_USED && !Timebase5s_CY_TCPWM_4000)
                Timebase5s_WriteCounter(1u);
            #elif (Timebase5s__RIGHT == Timebase5s_PWM_ALIGN)
                Timebase5s_WriteCounter(Timebase5s_PWM_PERIOD_VALUE);
            #else 
                Timebase5s_WriteCounter(0u);
            #endif  /* (Timebase5s_CY_TCPWM_V2 && Timebase5s_PWM_UPDOWN_CNT_USED && !Timebase5s_CY_TCPWM_4000) */
        #endif  /* (Timebase5s__PWM_PR == Timebase5s_PWM_MODE) */

        #if (Timebase5s__PWM_DT == Timebase5s_PWM_MODE)
            Timebase5s_CONTROL_REG |= Timebase5s_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Timebase5s__PWM_DT == Timebase5s_PWM_MODE) */

        #if (Timebase5s__PWM == Timebase5s_PWM_MODE)
            Timebase5s_CONTROL_REG |= Timebase5s_CTRL_PWM_PRESCALER;
        #endif  /* (Timebase5s__PWM == Timebase5s_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Timebase5s_TRIG_CONTROL1_REG  = Timebase5s_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Timebase5s_SetInterruptMode(Timebase5s_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Timebase5s__PWM_PR == Timebase5s_PWM_MODE)
            Timebase5s_TRIG_CONTROL2_REG =
                    (Timebase5s_CC_MATCH_NO_CHANGE    |
                    Timebase5s_OVERLOW_NO_CHANGE      |
                    Timebase5s_UNDERFLOW_NO_CHANGE);
        #else
            #if (Timebase5s__LEFT == Timebase5s_PWM_ALIGN)
                Timebase5s_TRIG_CONTROL2_REG = Timebase5s_PWM_MODE_LEFT;
            #endif  /* ( Timebase5s_PWM_LEFT == Timebase5s_PWM_ALIGN) */

            #if (Timebase5s__RIGHT == Timebase5s_PWM_ALIGN)
                Timebase5s_TRIG_CONTROL2_REG = Timebase5s_PWM_MODE_RIGHT;
            #endif  /* ( Timebase5s_PWM_RIGHT == Timebase5s_PWM_ALIGN) */

            #if (Timebase5s__CENTER == Timebase5s_PWM_ALIGN)
                Timebase5s_TRIG_CONTROL2_REG = Timebase5s_PWM_MODE_CENTER;
            #endif  /* ( Timebase5s_PWM_CENTER == Timebase5s_PWM_ALIGN) */

            #if (Timebase5s__ASYMMETRIC == Timebase5s_PWM_ALIGN)
                Timebase5s_TRIG_CONTROL2_REG = Timebase5s_PWM_MODE_ASYM;
            #endif  /* (Timebase5s__ASYMMETRIC == Timebase5s_PWM_ALIGN) */
        #endif  /* (Timebase5s__PWM_PR == Timebase5s_PWM_MODE) */

        /* Set other values from customizer */
        Timebase5s_WritePeriod(Timebase5s_PWM_PERIOD_VALUE );
        Timebase5s_WriteCompare(Timebase5s_PWM_COMPARE_VALUE);

        #if (1u == Timebase5s_PWM_COMPARE_SWAP)
            Timebase5s_SetCompareSwap(1u);
            Timebase5s_WriteCompareBuf(Timebase5s_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Timebase5s_PWM_COMPARE_SWAP) */

        #if (1u == Timebase5s_PWM_PERIOD_SWAP)
            Timebase5s_SetPeriodSwap(1u);
            Timebase5s_WritePeriodBuf(Timebase5s_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Timebase5s_PWM_PERIOD_SWAP) */
    #endif  /* (Timebase5s__PWM_SEL == Timebase5s_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Timebase5s_Enable
********************************************************************************
*
* Summary:
*  Enables the Timebase5s.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Timebase5s_BLOCK_CONTROL_REG |= Timebase5s_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Timebase5s__PWM_SEL == Timebase5s_CONFIG)
        #if (0u == Timebase5s_PWM_START_SIGNAL_PRESENT)
            Timebase5s_TriggerCommand(Timebase5s_MASK, Timebase5s_CMD_START);
        #endif /* (0u == Timebase5s_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Timebase5s__PWM_SEL == Timebase5s_CONFIG) */

    #if (Timebase5s__TIMER == Timebase5s_CONFIG)
        #if (0u == Timebase5s_TC_START_SIGNAL_PRESENT)
            Timebase5s_TriggerCommand(Timebase5s_MASK, Timebase5s_CMD_START);
        #endif /* (0u == Timebase5s_TC_START_SIGNAL_PRESENT) */
    #endif /* (Timebase5s__TIMER == Timebase5s_CONFIG) */
    
    #if (Timebase5s__QUAD == Timebase5s_CONFIG)
        #if (0u != Timebase5s_QUAD_AUTO_START)
            Timebase5s_TriggerCommand(Timebase5s_MASK, Timebase5s_CMD_RELOAD);
        #endif /* (0u != Timebase5s_QUAD_AUTO_START) */
    #endif  /* (Timebase5s__QUAD == Timebase5s_CONFIG) */
}


/*******************************************************************************
* Function Name: Timebase5s_Start
********************************************************************************
*
* Summary:
*  Initializes the Timebase5s with default customizer
*  values when called the first time and enables the Timebase5s.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Timebase5s_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Timebase5s_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Timebase5s_Start() routine.
*
*******************************************************************************/
void Timebase5s_Start(void)
{
    if (0u == Timebase5s_initVar)
    {
        Timebase5s_Init();
        Timebase5s_initVar = 1u;
    }

    Timebase5s_Enable();
}


/*******************************************************************************
* Function Name: Timebase5s_Stop
********************************************************************************
*
* Summary:
*  Disables the Timebase5s.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_BLOCK_CONTROL_REG &= (uint32)~Timebase5s_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Timebase5s. This function is used when
*  configured as a generic Timebase5s and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Timebase5s to operate in
*   Values:
*   - Timebase5s_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Timebase5s_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Timebase5s_MODE_QUAD - Quadrature decoder
*         - Timebase5s_MODE_PWM - PWM
*         - Timebase5s_MODE_PWM_DT - PWM with dead time
*         - Timebase5s_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_MODE_MASK;
    Timebase5s_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Timebase5s_MODE_X1 - Counts on phi 1 rising
*         - Timebase5s_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Timebase5s_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_QUAD_MODE_MASK;
    Timebase5s_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Timebase5s_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Timebase5s_PRESCALE_DIVBY2    - Divide by 2
*         - Timebase5s_PRESCALE_DIVBY4    - Divide by 4
*         - Timebase5s_PRESCALE_DIVBY8    - Divide by 8
*         - Timebase5s_PRESCALE_DIVBY16   - Divide by 16
*         - Timebase5s_PRESCALE_DIVBY32   - Divide by 32
*         - Timebase5s_PRESCALE_DIVBY64   - Divide by 64
*         - Timebase5s_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_PRESCALER_MASK;
    Timebase5s_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Timebase5s runs
*  continuously or stops when terminal count is reached.  By default the
*  Timebase5s operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_ONESHOT_MASK;
    Timebase5s_CONTROL_REG |= ((uint32)((oneShotEnable & Timebase5s_1BIT_MASK) <<
                                                               Timebase5s_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetPWMMode(uint32 modeMask)
{
    Timebase5s_TRIG_CONTROL2_REG = (modeMask & Timebase5s_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Timebase5s_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_PWM_SYNC_KILL_MASK;
    Timebase5s_CONTROL_REG |= ((uint32)((syncKillEnable & Timebase5s_1BIT_MASK)  <<
                                               Timebase5s_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_PWM_STOP_KILL_MASK;
    Timebase5s_CONTROL_REG |= ((uint32)((stopOnKillEnable & Timebase5s_1BIT_MASK)  <<
                                                         Timebase5s_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_PRESCALER_MASK;
    Timebase5s_CONTROL_REG |= ((uint32)((deadTime & Timebase5s_8BIT_MASK) <<
                                                          Timebase5s_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - Timebase5s_INVERT_LINE   - Inverts the line output
*         - Timebase5s_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_INV_OUT_MASK;
    Timebase5s_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Timebase5s_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_WriteCounter(uint32 count)
{
    Timebase5s_COUNTER_REG = (count & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 Timebase5s_ReadCounter(void)
{
    return (Timebase5s_COUNTER_REG & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Timebase5s_COUNT_UP       - Counts up
*     - Timebase5s_COUNT_DOWN     - Counts down
*     - Timebase5s_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Timebase5s_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_UPDOWN_MASK;
    Timebase5s_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_WritePeriod(uint32 period)
{
    Timebase5s_PERIOD_REG = (period & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Timebase5s_ReadPeriod(void)
{
    return (Timebase5s_PERIOD_REG & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_RELOAD_CC_MASK;
    Timebase5s_CONTROL_REG |= (swapEnable & Timebase5s_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_WritePeriodBuf(uint32 periodBuf)
{
    Timebase5s_PERIOD_BUF_REG = (periodBuf & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Timebase5s_ReadPeriodBuf(void)
{
    return (Timebase5s_PERIOD_BUF_REG & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_CONTROL_REG &= (uint32)~Timebase5s_RELOAD_PERIOD_MASK;
    Timebase5s_CONTROL_REG |= ((uint32)((swapEnable & Timebase5s_1BIT_MASK) <<
                                                            Timebase5s_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Timebase5s_WriteCompare(uint32 compare)
{
    #if (Timebase5s_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Timebase5s_CY_TCPWM_4000) */

    #if (Timebase5s_CY_TCPWM_4000)
        currentMode = ((Timebase5s_CONTROL_REG & Timebase5s_UPDOWN_MASK) >> Timebase5s_UPDOWN_SHIFT);

        if (((uint32)Timebase5s__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Timebase5s__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Timebase5s_CY_TCPWM_4000) */
    
    Timebase5s_COMP_CAP_REG = (compare & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Timebase5s_ReadCompare(void)
{
    #if (Timebase5s_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Timebase5s_CY_TCPWM_4000) */

    #if (Timebase5s_CY_TCPWM_4000)
        currentMode = ((Timebase5s_CONTROL_REG & Timebase5s_UPDOWN_MASK) >> Timebase5s_UPDOWN_SHIFT);
        
        regVal = Timebase5s_COMP_CAP_REG;
        
        if (((uint32)Timebase5s__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Timebase5s__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Timebase5s_16BIT_MASK);
    #else
        return (Timebase5s_COMP_CAP_REG & Timebase5s_16BIT_MASK);
    #endif /* (Timebase5s_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Timebase5s_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Timebase5s_WriteCompareBuf(uint32 compareBuf)
{
    #if (Timebase5s_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Timebase5s_CY_TCPWM_4000) */

    #if (Timebase5s_CY_TCPWM_4000)
        currentMode = ((Timebase5s_CONTROL_REG & Timebase5s_UPDOWN_MASK) >> Timebase5s_UPDOWN_SHIFT);

        if (((uint32)Timebase5s__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Timebase5s__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Timebase5s_CY_TCPWM_4000) */
    
    Timebase5s_COMP_CAP_BUF_REG = (compareBuf & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Timebase5s_ReadCompareBuf(void)
{
    #if (Timebase5s_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Timebase5s_CY_TCPWM_4000) */

    #if (Timebase5s_CY_TCPWM_4000)
        currentMode = ((Timebase5s_CONTROL_REG & Timebase5s_UPDOWN_MASK) >> Timebase5s_UPDOWN_SHIFT);

        regVal = Timebase5s_COMP_CAP_BUF_REG;
        
        if (((uint32)Timebase5s__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Timebase5s__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Timebase5s_16BIT_MASK);
    #else
        return (Timebase5s_COMP_CAP_BUF_REG & Timebase5s_16BIT_MASK);
    #endif /* (Timebase5s_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Timebase5s_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 Timebase5s_ReadCapture(void)
{
    return (Timebase5s_COMP_CAP_REG & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 Timebase5s_ReadCaptureBuf(void)
{
    return (Timebase5s_COMP_CAP_BUF_REG & Timebase5s_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timebase5s_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timebase5s_TRIG_LEVEL     - Level
*     - Timebase5s_TRIG_RISING    - Rising edge
*     - Timebase5s_TRIG_FALLING   - Falling edge
*     - Timebase5s_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_TRIG_CONTROL1_REG &= (uint32)~Timebase5s_CAPTURE_MASK;
    Timebase5s_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timebase5s_TRIG_LEVEL     - Level
*     - Timebase5s_TRIG_RISING    - Rising edge
*     - Timebase5s_TRIG_FALLING   - Falling edge
*     - Timebase5s_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_TRIG_CONTROL1_REG &= (uint32)~Timebase5s_RELOAD_MASK;
    Timebase5s_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timebase5s_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timebase5s_TRIG_LEVEL     - Level
*     - Timebase5s_TRIG_RISING    - Rising edge
*     - Timebase5s_TRIG_FALLING   - Falling edge
*     - Timebase5s_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_TRIG_CONTROL1_REG &= (uint32)~Timebase5s_START_MASK;
    Timebase5s_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timebase5s_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timebase5s_TRIG_LEVEL     - Level
*     - Timebase5s_TRIG_RISING    - Rising edge
*     - Timebase5s_TRIG_FALLING   - Falling edge
*     - Timebase5s_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_TRIG_CONTROL1_REG &= (uint32)~Timebase5s_STOP_MASK;
    Timebase5s_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timebase5s_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timebase5s_TRIG_LEVEL     - Level
*     - Timebase5s_TRIG_RISING    - Rising edge
*     - Timebase5s_TRIG_FALLING   - Falling edge
*     - Timebase5s_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_TRIG_CONTROL1_REG &= (uint32)~Timebase5s_COUNT_MASK;
    Timebase5s_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timebase5s_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - Timebase5s_CMD_CAPTURE    - Trigger Capture/Switch command
*     - Timebase5s_CMD_RELOAD     - Trigger Reload/Index command
*     - Timebase5s_CMD_STOP       - Trigger Stop/Kill command
*     - Timebase5s_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timebase5s_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timebase5s_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Timebase5s.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Timebase5s_STATUS_DOWN    - Set if counting down
*     - Timebase5s_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Timebase5s_ReadStatus(void)
{
    return ((Timebase5s_STATUS_REG >> Timebase5s_RUNNING_STATUS_SHIFT) |
            (Timebase5s_STATUS_REG & Timebase5s_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Timebase5s_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Timebase5s_INTR_MASK_TC       - Terminal count mask
*     - Timebase5s_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetInterruptMode(uint32 interruptMask)
{
    Timebase5s_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Timebase5s_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - Timebase5s_INTR_MASK_TC       - Terminal count mask
*     - Timebase5s_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Timebase5s_GetInterruptSourceMasked(void)
{
    return (Timebase5s_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Timebase5s_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - Timebase5s_INTR_MASK_TC       - Terminal count mask
*     - Timebase5s_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Timebase5s_GetInterruptSource(void)
{
    return (Timebase5s_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Timebase5s_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Timebase5s_INTR_MASK_TC       - Terminal count mask
*     - Timebase5s_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_ClearInterrupt(uint32 interruptMask)
{
    Timebase5s_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Timebase5s_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Timebase5s_INTR_MASK_TC       - Terminal count mask
*     - Timebase5s_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Timebase5s_SetInterrupt(uint32 interruptMask)
{
    Timebase5s_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
