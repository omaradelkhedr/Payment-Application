/******************************************************************************
*
* Module: Card
*
* File Name: card.c
*
* Description: Source file for Card Module
*
* Author: Omar Khedr
******************************************************************************/

/*Include of the module header file*/
#include "../inc/card.h"

/************************************************************************************
* Function Name: getCardHolderName
* Parameters (in): None
* Parameters (inout): ST_cardData_t* cardData - to store the user's data
* Parameters (out): None
* Return value: EN_cardError_t - (WRONG_NAME, CARD_OK)
* Description: Function to get the card holder name from the user
************************************************************************************/

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	/*Request to get the user name*/
	printf("Please Enter the Card Holder's Name (19<Number of Characters<25)\n");
	/*Store Card Holder's name*/
	gets(cardData->cardHolderName);
	/*While loop to store the length of the character array in which the user stored his name,
	the loop will be terminated when the character is NULL*/
	uint8_t U8_LocalString_length=ZERO;
	uint8_t U8_LocalString_iterator= ZERO;
	while (cardData->cardHolderName[U8_LocalString_iterator])
	{
		U8_LocalString_length++;
		U8_LocalString_iterator++;
	}
	/*Error State Variable to return the state of the function (WRONG_NAME or CARD_OK)*/
	EN_cardError_t EN_LocalState;
	/*If condition to check if the number of characters is NULL,<20,>24*/
	if (
		(ZERO == U8_LocalString_length)
		|| (U8_LocalString_length < MINIMUM_NAME) 
		|| (U8_LocalString_length > MAXIMUM_NAME)
		)
	{
		EN_LocalState = WRONG_NAME;
	}
	else
	{
		EN_LocalState = CARD_OK;
	}
	return EN_LocalState;
}

/************************************************************************************
* Function Name: getCardExpiryDate
* Parameters (in): None
* Parameters (inout): ST_cardData_t* cardData - to store the user's data
* Parameters (out): None
* Return value: EN_cardError_t - (WRONG_EXP_DATE, CARD_OK)
* Description: Function to get the card expiry date from the user
************************************************************************************/

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	/*Request to get the expiry date of the card*/
	printf("Please Enter the Card's Expiray Date (It should be 5 characters & and in this format \"MM/YY\")\n");
	/*Store Card's expiry date*/
	gets(cardData->cardExpirationDate);
	/*While loop to store the length of the character array in which the user stored the expiry date,
	the loop will be terminated when the character is NULL*/
	uint8_t U8_LocalString_length = ZERO;
	uint8_t U8_LocalString_iterator = ZERO;
	while (cardData->cardExpirationDate[U8_LocalString_iterator])
	{
		U8_LocalString_length++;
		U8_LocalString_iterator++;
	}
	/*Variable to store the month*/
	uint8_t U8_LocalMonth = ((cardData->cardExpirationDate[FIRST] - ZERO_ASCII)*10) + (cardData->cardExpirationDate[SECOND] - ZERO_ASCII);
	/*Error State Variable to return the state of the function (WRONG_EXP_DATE or CARD_OK)*/
	EN_cardError_t EN_LocalState;
	/*If condition to check if the number of characters is equal to 5,NULL,Has the wrong format or has an invalid date*/
	if (
		(U8_LocalString_length != EXACT_EXPIRY)
		|| (cardData->cardExpirationDate[THIRD] != '/') 
		|| (U8_LocalMonth > MAXIMUM_MONTH) 
		|| (ZERO==U8_LocalMonth) 
		)
	{
		EN_LocalState = WRONG_EXP_DATE;
	}
	else
	{
		EN_LocalState = CARD_OK;
	}
	return EN_LocalState;
}

/************************************************************************************
* Function Name: getCardPAN
* Parameters (in): None
* Parameters (inout): ST_cardData_t* cardData - to store the user's data
* Parameters (out): None
* Return value: EN_cardError_t - (WRONG_PAN , CARD_OK)
* Description: Function to get the primary account number (PAN) from the user
************************************************************************************/

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	/*Request to get the PAN of the card*/
	printf("Please Enter the Card's Primary Account Number \"PAN\" (It should be numbers only & (15<Number of Characters<20))\n");
	/*Store Card's PAN*/
	gets(cardData->primaryAccountNumber);
	/*While loop to store the length of the character array in which the user stored the PAN,
	the loop will be terminated when the character is NULL*/
	uint8_t U8_LocalString_length = ZERO;
	uint8_t U8_LocalString_iterator = ZERO;
	while (cardData->primaryAccountNumber[U8_LocalString_iterator])
	{
		U8_LocalString_length++;
		U8_LocalString_iterator++;
	}
	/*Error Flag to check if all characters are numbers only*/
	uint8_t U8_LocalError_Flag = ZERO;
	U8_LocalString_iterator = ZERO;
	/*While Loop to make sure that all characters are numbers only*/
	while (cardData->primaryAccountNumber[U8_LocalString_iterator])
	{
		if (
			(cardData->primaryAccountNumber[U8_LocalString_iterator] < ZERO_ASCII)
			|| (cardData->primaryAccountNumber[U8_LocalString_iterator] > NINE_ASCII)
			)
		{
			U8_LocalError_Flag = ONE;
		}
		U8_LocalString_iterator++;
	}
	/*Error State Variable to return the state of the function (WRONG_PAN or CARD_OK)*/
	EN_cardError_t EN_LocalState;
	/*If condition to check if the number of characters length is (15<length<20),NULL,Has a character that is not a number*/
	if (
		(U8_LocalString_length < MINIMUM_PAN)
		|| (U8_LocalString_length > MAXIMUM_PAN)
		|| (ONE == U8_LocalError_Flag)
		|| (ZERO == U8_LocalString_length)
		)
	{
		EN_LocalState = WRONG_PAN;
	}
	else
	{
		EN_LocalState = CARD_OK;
	}
	return EN_LocalState;
}
