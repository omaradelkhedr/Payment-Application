/******************************************************************************
*
* Module: Terminal
*
* File Name: terminal.h
*
* Description: Header file for Terminal Module
*
* Author: Omar Khedr
******************************************************************************/

#ifndef _TERMINAL_H_ 
#define _TERMINAL_H_

/*Include of Card header file*/
#include "card.h"

/*******************************************************************************
*                              Module Data Types                              *
*******************************************************************************/

/*A structure for terminal data*/
typedef struct
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

/*Enumeration for terminal errors*/
typedef enum
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

/*******************************************************************************
 *                      Module Used Macros                                    *
 *******************************************************************************/

#define FOURTH (3U)
#define FIFTH (4U)
#define EXACT_TRANSACTION (10U)
#define SIXTH (5U)
#define MAXIMUM_DAY (31U)
#define NINTH (8U)
#define TENTH (9U)

#endif