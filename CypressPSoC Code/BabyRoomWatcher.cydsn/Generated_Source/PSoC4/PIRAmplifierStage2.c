/***************************************************************************//**
* \file     PIRAmplifierStage2.c
* \version  1.0
*
* \brief
*  This file provides the source code to the API for the PGA_P4 Component
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PIRAmplifierStage2_PVT.h"


uint8 PIRAmplifierStage2_initVar = 0u; /**< Describes the init state of the component */

uint32 PIRAmplifierStage2_internalGainPower = 0u; /**< Stores component Gain, Power and Enable values */

/***************************************************************************//**
* Compensation table 
*
* There is a feedback compensation capacitor recomended setting (for certain 
* gain and power setting) under the mask 0x0F000000u
* or (PIRAmplifierStage2_C_FB_MASK)
*
* Also there is an OpAmp compensation recomended setting (for certain 
* gain and power setting) under the mask 0x00000003u
* or (PIRAmplifierStage2_GET_OA_COMP_TRIM)
*
* There is only 6 values for whole gain range because the recommended 
* values are for each pair of adjacent gain values, e.g.:
* the first (index = 0) value is for gain = 1 and 1.4,
* the second (index = 1) value is for gain = 2 and 2.8,and so on,
* and the sixth (index = 5) value is for gain = 32 only.
*******************************************************************************/
const uint32 PIRAmplifierStage2_compTab[PIRAmplifierStage2_COMP_TAB_HEIGHT][PIRAmplifierStage2_COMP_TAB_WIDTH] =
{
#if (PIRAmplifierStage2_CHECK_OUTPUT_MODE) /* Class AB */
    {0x0F000002u, 0x0F000002u, 0x0F000002u},
    {0x07000002u, 0x09000002u, 0x09000002u},
    {0x04000002u, 0x04000002u, 0x04000002u},
    {0x03000001u, 0x02000002u, 0x03000002u},
    {0x01000001u, 0x00000002u, 0x00000002u},
    {0x01000001u, 0x01000001u, 0x02000001u}
#else /* Class A */
    {0x0F000002u, 0x0F000002u, 0x0F000002u},
    {0x08000002u, 0x09000002u, 0x09000002u},
    {0x03000001u, 0x05000002u, 0x04000002u},
    {0x00000001u, 0x02000002u, 0x03000002u},
    {0x00000001u, 0x00000002u, 0x01000002u},
    {0x00000001u, 0x00000001u, 0x00000001u}
#endif /* PIRAmplifierStage2_OUTPUT_MODE */
};


/*******************************************************************************   
* Function Name: PIRAmplifierStage2_Init
****************************************************************************//**
*
*  Initializes component's parameters to the values set by user in the 
*  customizer of the component placed onto schematic. Usually it is called in 
*  PIRAmplifierStage2_Start().
*
*******************************************************************************/
void PIRAmplifierStage2_Init(void)
{
    /* Set default internal variable value */
    PIRAmplifierStage2_internalGainPower = PIRAmplifierStage2_DEFAULT_GAIN_POWER;
    
    /* Set default register values */
    PIRAmplifierStage2_CTB_CTRL_REG |= PIRAmplifierStage2_DEFAULT_CTB_CTRL;
    PIRAmplifierStage2_OA_RES_CTRL_REG &= (uint32) ~PIRAmplifierStage2_DEFAULT_OA_RES_CTRL_MASK;
    PIRAmplifierStage2_OA_RES_CTRL_REG |= PIRAmplifierStage2_DEFAULT_OA_RES_CTRL;
    
    #if (PIRAmplifierStage2_VREF_MODE == PIRAmplifierStage2_VREF_INTERNAL)
        /* Configure resistor matrix bottom to the internal Vss */
        PIRAmplifierStage2_OA_SW_REG |= PIRAmplifierStage2_RBOT_TO_VSSA;
    #endif /* Vref Internal */
    
    /* Check if component has been enabled */
    if((PIRAmplifierStage2_OA_RES_CTRL_REG & PIRAmplifierStage2_OA_PWR_MODE_MASK) != 0u)
    {
        /* Set the default power level */
        PIRAmplifierStage2_Enable();
    }
    
    /* Set default gain and correspondent Cfb and OA_trim values */
    PIRAmplifierStage2_SetGain(PIRAmplifierStage2_GAIN);
}


/*******************************************************************************   
* Function Name: PIRAmplifierStage2_Enable
****************************************************************************//**
*
*  Powers up amplifier (to default power level or restored after 
*  previous PIRAmplifierStage2_Stop() call).
*  Usually it is called in PIRAmplifierStage2_Start().
*  
*******************************************************************************/
void PIRAmplifierStage2_Enable(void)
{
    PIRAmplifierStage2_OA_RES_CTRL_REG |= PIRAmplifierStage2_GET_POWER;
}


/*******************************************************************************
* Function Name: PIRAmplifierStage2_Start
****************************************************************************//**
*
*  Enables the amplifier operation (calls PIRAmplifierStage2_Enable).
*  Also on the first call (after the system reset) initializes all the component
*  related registers with default values (calls PIRAmplifierStage2_Init).
*
*  \globalvars
*   The PIRAmplifierStage2_initVar variable is used to indicate initial
*   configuration of this component. The variable is initialized to zero (0u)
*   and set to one (1u) at the first time PIRAmplifierStage2_Start() is called.
*   This allows to enable the component without re-initialization in all
*   subsequent calls of the PIRAmplifierStage2_Start() routine.
*
*******************************************************************************/
void PIRAmplifierStage2_Start(void)
{
    if(PIRAmplifierStage2_initVar == 0u)
    {
        PIRAmplifierStage2_Init();
        PIRAmplifierStage2_initVar = 1u;
    }

    PIRAmplifierStage2_Enable();
}


/*******************************************************************************
* Function Name: PIRAmplifierStage2_Stop
****************************************************************************//**
*
*  Powers down the amplifier.
*
*******************************************************************************/
void PIRAmplifierStage2_Stop(void)
{ 
    PIRAmplifierStage2_OA_RES_CTRL_REG &= (uint32)~PIRAmplifierStage2_OA_PWR_MODE_MASK;
}


/*******************************************************************************
* Function Name: PIRAmplifierStage2_SetPower
****************************************************************************//**
*
*  Sets the power level of amplifier.
*
* \param powerLevel
*  The power level setting of amplifier. Possible values:
*   * PIRAmplifierStage2_LOW - The lowest power consumption.
*   * PIRAmplifierStage2_MED - The middle setting.
*   * PIRAmplifierStage2_HIGH - The highest amplifier bandwidth.
*
*  \internal
*   The PIRAmplifierStage2_internalGainPower variable is used to store the
*   current gain and power level to set appropriate compensation settings.
*
*******************************************************************************/
void PIRAmplifierStage2_SetPower(uint32 powerLevel)
{
    uint32 locTmp;
    
    /* Save the powerLevel */
    PIRAmplifierStage2_internalGainPower &= (uint32) ~PIRAmplifierStage2_OA_PWR_MODE_MASK;
    PIRAmplifierStage2_internalGainPower |= powerLevel & PIRAmplifierStage2_OA_PWR_MODE_MASK;
    
    /* Save the rest of register bitfields */
    locTmp = PIRAmplifierStage2_OA_RES_CTRL_REG &
        (uint32)~(PIRAmplifierStage2_OA_PWR_MODE_MASK | PIRAmplifierStage2_C_FB_MASK);
           
    /* Set the power and the feedback capacitor values into the control register */
    PIRAmplifierStage2_OA_RES_CTRL_REG  = locTmp | PIRAmplifierStage2_GET_POWER | PIRAmplifierStage2_GET_C_FB;
    
    /* Set the OA compensation capacitor value */
    PIRAmplifierStage2_OA_COMP_TRIM_REG = PIRAmplifierStage2_GET_OA_COMP_TRIM;
}


/*******************************************************************************
* Function Name: PIRAmplifierStage2_SetGain
****************************************************************************//**
*
*  Sets values of the input and feedback resistors to set a 
*  specific gain of the amplifier.
*
* \param gainLevel
*  The gain setting of amplifier. Possible values:
*   * PIRAmplifierStage2_GAIN_1    - gain 1.0.
*   * PIRAmplifierStage2_GAIN_1_4  - gain 1.4.
*   * PIRAmplifierStage2_GAIN_2    - gain 2.0.
*   * PIRAmplifierStage2_GAIN_2_8  - gain 2.8.
*   * PIRAmplifierStage2_GAIN_4    - gain 4.0.
*   * PIRAmplifierStage2_GAIN_5_8  - gain 5.8.
*   * PIRAmplifierStage2_GAIN_8    - gain 8.0.
*   * PIRAmplifierStage2_GAIN_10_7 - gain 10.7.
*   * PIRAmplifierStage2_GAIN_16   - gain 16.0
*   * PIRAmplifierStage2_GAIN_21_3 - gain 21.3.
*   * PIRAmplifierStage2_GAIN_32   - gain 32.0.
*
*  \internal
*   The PIRAmplifierStage2_internalGainPower variable is used to store the
*   current gain and power level to set appropriate compensation settings.
*
*******************************************************************************/
void PIRAmplifierStage2_SetGain(uint32 gainLevel)
{
    uint32 locTmp;
    
    /* Save the gainLevel */
    PIRAmplifierStage2_internalGainPower &= (uint32) ~PIRAmplifierStage2_RES_TAP_MASK;
    PIRAmplifierStage2_internalGainPower |= ((uint32)(gainLevel << PIRAmplifierStage2_RES_TAP_SHIFT)) &
                                                                 PIRAmplifierStage2_RES_TAP_MASK;
    /* Save the rest of register bitfields */
    locTmp = PIRAmplifierStage2_OA_RES_CTRL_REG &
        (uint32)~(PIRAmplifierStage2_RES_TAP_MASK | PIRAmplifierStage2_C_FB_MASK);
    
    /* Set the gain and the feedback capacitor values into the control register */
    PIRAmplifierStage2_OA_RES_CTRL_REG = locTmp | (PIRAmplifierStage2_internalGainPower &
        PIRAmplifierStage2_RES_TAP_MASK) | PIRAmplifierStage2_GET_C_FB;
    
    /* Set the OA compensation capacitor value */
    PIRAmplifierStage2_OA_COMP_TRIM_REG = PIRAmplifierStage2_GET_OA_COMP_TRIM;
}


/*******************************************************************************
* Function Name: PIRAmplifierStage2_PumpControl
****************************************************************************//**
*
*  Allows the user to turn the amplifier's boost pump on or off.
*  By Default the PIRAmplifierStage2_Init() function turns the pump on.
*  
* \param onOff
*  The boost pump setting. Possible values:
*   * PIRAmplifierStage2_BOOST_OFF - Turn off the pump.
*   * PIRAmplifierStage2_BOOST_ON  - Turn on the pump.
*
**********************************************************************************/
void PIRAmplifierStage2_PumpControl(uint32 onOff)
{
    if(onOff == PIRAmplifierStage2_BOOST_ON)
    {
        PIRAmplifierStage2_OA_RES_CTRL_REG |= PIRAmplifierStage2_OA_PUMP_EN;
    }
    else
    {
        PIRAmplifierStage2_OA_RES_CTRL_REG &= (uint32)~PIRAmplifierStage2_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
