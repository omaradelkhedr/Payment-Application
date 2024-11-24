#ifndef _APP_H_ 
#define _APP_H_

/******************************************************************************
*
* Module: Application
*
* File Name: app.h
*
* Description: Header file for Application Module
*
* Author: Omar Khedr
******************************************************************************/

/*Include of Server header file*/
#include "server.h"

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void appStart(void);

/*******************************************************************************
 *                      Module Used Macros                                         *
 *******************************************************************************/

#define TWO (2U)

/*******************************************************************************
 *                      Module Externs                                         *
 *******************************************************************************/

extern uint8_t U8_GlobalExit;

#endif