/******************************************************************************
*
* Module: Card
*
* File Name: card.h
*
* Description: Header file for Card Module
*
* Author: Omar Khedr
******************************************************************************/
#ifndef _CARD_H_ 
#define _CARD_H_

/*Include of Standard types header file */
#include "Std_Types.h"
/*Include for standard library to use printf & scanf functions*/
#include "stdio.h"

/*******************************************************************************
*                              Module Data Types                              *
*******************************************************************************/

/*A structure that contains card holder's data*/
typedef struct
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
} ST_cardData_t;

/*An enumeration for card errors*/
typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

/*******************************************************************************
 *                      Module Used Macros                                    *
 *******************************************************************************/

#define	ZERO		(0U)
#define ONE			(1U)
#define MAXIMUM_NAME (24U)
#define MINIMUM_NAME (20U)
#define EXACT_EXPIRY (5U)
#define MAXIMUM_MONTH (12U)
#define FIRST		(0U) 
#define SECOND		(1U)
#define THIRD		(2U)
#define ZERO_ASCII (48U)
#define NINE_ASCII (57U)
#define MAXIMUM_PAN (19U)
#define MINIMUM_PAN (16U)


#endif