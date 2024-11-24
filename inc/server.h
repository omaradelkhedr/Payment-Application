/******************************************************************************
*
* Module: Server
*
* File Name: server.h
*
* Description: Header file for Server Module
*
* Author: Omar Khedr
******************************************************************************/

#ifndef _SERVER_H_ 
#define _SERVER_H_

/*Include of Terminal header file*/
#include "terminal.h"

/*Include of String header file*/
#include "string.h"

/*******************************************************************************
*                              Module Data Types                              *
*******************************************************************************/

/*Enumeration for the transaction state*/
typedef enum
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

/*Enumeration for server errors*/
typedef enum
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;

/*A structure for transaction data*/
typedef struct
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

/*Structure that holds the data of the client*/
typedef struct
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);

/*******************************************************************************
 *                      Module Used Macros                                    *
 *******************************************************************************/

#define MAXIMUM_ACCOUNTS (255U)
#define RAISED_FLAG (1U)
#define MAXIMUM_TRANSACTIONS (255U)

 /*******************************************************************************
  *                      Module Externs                                         *
  *******************************************************************************/

extern ST_accountsDB_t  Accounts[MAXIMUM_ACCOUNTS];
extern uint16_t U16_GlobalAccount_Index;
extern ST_transaction_t Transactions[MAXIMUM_ACCOUNTS];
extern uint16_t U16_GlobalTransaction_Index;


#endif