/*******************************************************************************
* File Name: EzI2C_scl.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_EzI2C_scl_ALIASES_H) /* Pins EzI2C_scl_ALIASES_H */
#define CY_PINS_EzI2C_scl_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define EzI2C_scl_0			(EzI2C_scl__0__PC)
#define EzI2C_scl_0_PS		(EzI2C_scl__0__PS)
#define EzI2C_scl_0_PC		(EzI2C_scl__0__PC)
#define EzI2C_scl_0_DR		(EzI2C_scl__0__DR)
#define EzI2C_scl_0_SHIFT	(EzI2C_scl__0__SHIFT)
#define EzI2C_scl_0_INTR	((uint16)((uint16)0x0003u << (EzI2C_scl__0__SHIFT*2u)))

#define EzI2C_scl_INTR_ALL	 ((uint16)(EzI2C_scl_0_INTR))


#endif /* End Pins EzI2C_scl_ALIASES_H */


/* [] END OF FILE */
