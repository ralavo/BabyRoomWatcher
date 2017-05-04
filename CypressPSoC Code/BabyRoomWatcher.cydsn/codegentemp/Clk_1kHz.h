/*******************************************************************************
* File Name: Clk_1kHz.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clk_1kHz_H)
#define CY_CLOCK_Clk_1kHz_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Clk_1kHz_StartEx(uint32 alignClkDiv);
#define Clk_1kHz_Start() \
    Clk_1kHz_StartEx(Clk_1kHz__PA_DIV_ID)

#else

void Clk_1kHz_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Clk_1kHz_Stop(void);

void Clk_1kHz_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clk_1kHz_GetDividerRegister(void);
uint8  Clk_1kHz_GetFractionalDividerRegister(void);

#define Clk_1kHz_Enable()                         Clk_1kHz_Start()
#define Clk_1kHz_Disable()                        Clk_1kHz_Stop()
#define Clk_1kHz_SetDividerRegister(clkDivider, reset)  \
    Clk_1kHz_SetFractionalDividerRegister((clkDivider), 0u)
#define Clk_1kHz_SetDivider(clkDivider)           Clk_1kHz_SetDividerRegister((clkDivider), 1u)
#define Clk_1kHz_SetDividerValue(clkDivider)      Clk_1kHz_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Clk_1kHz_DIV_ID     Clk_1kHz__DIV_ID

#define Clk_1kHz_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Clk_1kHz_CTRL_REG   (*(reg32 *)Clk_1kHz__CTRL_REGISTER)
#define Clk_1kHz_DIV_REG    (*(reg32 *)Clk_1kHz__DIV_REGISTER)

#define Clk_1kHz_CMD_DIV_SHIFT          (0u)
#define Clk_1kHz_CMD_PA_DIV_SHIFT       (8u)
#define Clk_1kHz_CMD_DISABLE_SHIFT      (30u)
#define Clk_1kHz_CMD_ENABLE_SHIFT       (31u)

#define Clk_1kHz_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Clk_1kHz_CMD_DISABLE_SHIFT))
#define Clk_1kHz_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Clk_1kHz_CMD_ENABLE_SHIFT))

#define Clk_1kHz_DIV_FRAC_MASK  (0x000000F8u)
#define Clk_1kHz_DIV_FRAC_SHIFT (3u)
#define Clk_1kHz_DIV_INT_MASK   (0xFFFFFF00u)
#define Clk_1kHz_DIV_INT_SHIFT  (8u)

#else 

#define Clk_1kHz_DIV_REG        (*(reg32 *)Clk_1kHz__REGISTER)
#define Clk_1kHz_ENABLE_REG     Clk_1kHz_DIV_REG
#define Clk_1kHz_DIV_FRAC_MASK  Clk_1kHz__FRAC_MASK
#define Clk_1kHz_DIV_FRAC_SHIFT (16u)
#define Clk_1kHz_DIV_INT_MASK   Clk_1kHz__DIVIDER_MASK
#define Clk_1kHz_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Clk_1kHz_H) */

/* [] END OF FILE */
