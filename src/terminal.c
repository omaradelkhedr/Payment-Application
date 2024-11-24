/******************************************************************************
*
* Module: Terminal
*
* File Name: terminal.c
*
* Description: Source file for Terminal Module
*
* Author: Omar Khedr
******************************************************************************/

/*Include of the module header file*/
#include "../inc/terminal.h"

/************************************************************************************
* Function Name: getTransactionDate
* Parameters (in): None
* Parameters (inout): ST_terminalData_t* termData - to store the terminal's data
* Parameters (out): None
* Return value: EN_terminalError_t - (WRONG_DATE , TERMINAL_OK)
* Description: Function to get the transaction date from the user
************************************************************************************/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{

	/*Request to get the date*/
	printf("Please enter the Transaction Date (It should be 10 characters & stored in this format \"DD/MM/YYYY\")\n");
	/*Store date*/
	gets(termData->transactionDate);
	/*While loop to store the length of the character array in which the user stored the transaction date,
	the loop will be terminated when the character is NULL*/
	uint8_t U8_LocalString_length = ZERO;
	uint8_t U8_LocalString_iterator = ZERO;
	while (termData->transactionDate[U8_LocalString_iterator])
	{
		U8_LocalString_length++;
		U8_LocalString_iterator++;
	}
	/*Error State Variable to return the state of the function (WRONG_DATE or TERMINAL_OK)*/
	EN_terminalError_t EN_LocalState;
	/*Variable to store the day*/
	uint8_t U8_LocalDay = ((termData->transactionDate[FIRST] - ZERO_ASCII) * 10) + (termData->transactionDate[SECOND] - ZERO_ASCII);
	/*Variable to store the month*/
	uint8_t U8_LocalMonth = ((termData->transactionDate[FOURTH] - ZERO_ASCII) * 10) + (termData->transactionDate[FIFTH] - ZERO_ASCII);
	/*If condition to check if the number of characters is equal to 10,NULL,Has the wrong format or has an invalid date*/
	if (
		(U8_LocalString_length != EXACT_TRANSACTION)
		|| (termData->transactionDate[THIRD] != '/')
		|| (termData->transactionDate[SIXTH] != '/')
		|| (U8_LocalMonth > MAXIMUM_MONTH)
		|| (U8_LocalDay > MAXIMUM_DAY)
		|| (ZERO == U8_LocalMonth)
		|| (ZERO == U8_LocalDay)
		)
	{
		EN_LocalState = WRONG_DATE;
	}
	else
	{
		EN_LocalState = TERMINAL_OK;
	}
	return EN_LocalState;
}

/************************************************************************************
* Function Name: isCardExpired
* Parameters (in): ST_cardData_t cardData - to get the expiry date of the card
*                  ST_terminalData_t termData - to get the transaction date
* Parameters (inout): None
* Parameters (out): None
* Return value: EN_terminalError_t - (EXPIRED_CARD , TERMINAL_OK)
* Description: Function to check if the current date is before the expiry date
************************************************************************************/

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	/*Error State Variable to return the state of the function (WRONG_DATE or TERMINAL_OK)*/
	EN_terminalError_t EN_LocalState;
	/***************************Card Data*********************************/
	/*Variable to store the Month on the Card*/
	uint8_t U8_LocalExpiray_Month = ((cardData.cardExpirationDate[FIRST] - ZERO_ASCII) * 10) + (cardData.cardExpirationDate[SECOND] - ZERO_ASCII);
	/*Variable to store the Year on the Card*/
	uint8_t U8_LocalExpiray_Year = ((cardData.cardExpirationDate[FOURTH] - ZERO_ASCII) * 10) + (cardData.cardExpirationDate[FIFTH] - ZERO_ASCII) ;
	/***************************Terminal Data*********************************/
	/*Variable to store the Current Month*/
	uint8_t U8_LocalCurrent_Month = ((termData.transactionDate[FOURTH] - ZERO_ASCII) * 10) + (termData.transactionDate[FIFTH] - ZERO_ASCII);
	/*Variable to store the Current Year*/
	uint8_t U8_LocalCurrent_Year = ((termData.transactionDate[NINTH] - ZERO_ASCII) * 10) + (termData.transactionDate[TENTH] - ZERO_ASCII);
	/*If condition to check if the expiry date is before the transaction date*/
	if (U8_LocalCurrent_Year <= U8_LocalExpiray_Year)
	{
		if (U8_LocalCurrent_Month <= U8_LocalExpiray_Month)
		{
			EN_LocalState = TERMINAL_OK;
		}
		else
		{
			EN_LocalState = EXPIRED_CARD;
		}
	}
	else
	{
		EN_LocalState = EXPIRED_CARD;
	}
	return EN_LocalState;
}

/************************************************************************************
* Function Name: getTransactionAmount
* Parameters (in): None
* Parameters (inout): ST_terminalData_t* termData - to store the terminal's data
* Parameters (out): None
* Return value: EN_terminalError_t - (INVALID_AMOUNT , TERMINAL_OK)
* Description: Function to get the transaction amount from the user
************************************************************************************/

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{

	/*Request to get the transaction amount*/
	printf("Please enter the Transaction Amount \n");
	/*Store transaction amount*/
	scanf("%f", &termData->transAmount);
	fflush(stdin);
	/*Error State Variable to return the state of the function (INVALID_AMOUNT or TERMINAL_OK)*/
	EN_terminalError_t EN_LocalState;
	/*If condition to check if the amount is less than or equal to zero*/
	if (termData->transAmount <= ZERO)
	{
		EN_LocalState = INVALID_AMOUNT;
	}
	else
	{
		EN_LocalState = TERMINAL_OK;
	}
	return EN_LocalState;
}

/************************************************************************************
* Function Name: setMaxAmount
* Parameters (in): None
* Parameters (inout): ST_terminalData_t* termData - to store the terminal's data
* Parameters (out): None
* Return value: EN_terminalError_t - (INVALID_MAX_AMOUNT  , TERMINAL_OK)
* Description: Function to set the maximum amount of transaction
************************************************************************************/

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	/*Request to get the maximum amount*/
	printf("Please enter the Maximum Allowed Amount \n");
	/*Store the maximum amount*/
	scanf("%f", &termData->maxTransAmount);
	fflush(stdin);
	/*Error State Variable to return the state of the function (INVALID_MAX_AMOUNT  or TERMINAL_OK)*/
	EN_terminalError_t EN_LocalState;
	/*If condition to check if the amount is less than or equal to zero*/
	if (termData->maxTransAmount <= ZERO)
	{
		EN_LocalState = INVALID_MAX_AMOUNT;
	}
	else
	{
		EN_LocalState = TERMINAL_OK;
	}
	return EN_LocalState;
}

/************************************************************************************
* Function Name: isBelowMaxAmount
* Parameters (in): None
* Parameters (inout): ST_terminalData_t* termData - to store the terminal's data
* Parameters (out): None
* Return value: EN_terminalError_t - (EXCEED_MAX_AMOUNT , TERMINAL_OK)
* Description: Function to check if the transaction amount is above max allowed amount
************************************************************************************/

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	/*Error State Variable to return the state of the function (EXCEED_MAX_AMOUNT or TERMINAL_OK)*/
	EN_terminalError_t EN_LocalState;
	/*Variable to store the maximum allowed transaction*/
	float32_t FLOAT32_LocalMax = termData->maxTransAmount;
	/*Variable to store the transaction amount*/
	float32_t FLOAT32_LocalAmount = termData->transAmount;
	/*If condition to check if maximum allowed transaction is below transaction amount*/
	if (FLOAT32_LocalAmount <= FLOAT32_LocalMax)
	{
		EN_LocalState = TERMINAL_OK;
	}
	else
	{
		EN_LocalState = EXCEED_MAX_AMOUNT;
	}
	return EN_LocalState;
}