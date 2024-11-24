/******************************************************************************
*
* Module: Server
*
* File Name: server.c
*
* Description: Source file for Server Module
*
* Author: Omar Khedr
******************************************************************************/

/*Include of the module header file*/
#include "../inc/server.h"

/*******************************************************************************
 *                      Server-Side Accounts' Database array               *
 *******************************************************************************/

ST_accountsDB_t  Accounts[MAXIMUM_ACCOUNTS] =
{
    400,"1234567890123456",
    100,"12345678901234567",
    150, "123456789012345678" ,
    10000, "01234567890123456" ,
    50000, "4527281923662887",
    40, "2378993462987739",
    300, "26918263917289372",
    45, "1234567890123456789"
};

/*Global Variable to store account index if the account is valid*/
uint16_t U16_GlobalAccount_Index=256;

/*******************************************************************************
 *                    Server-Side Transactions' Database array                     *
 *******************************************************************************/

ST_transaction_t Transactions[MAXIMUM_ACCOUNTS] = {0};
/*Global Variable to store the transaction data*/
uint16_t U16_GlobalTransaction_Index = ZERO;



/************************************************************************************
* Function Name: recieveTransactionData
* Parameters (in): None
* Parameters (inout): ST_transaction_t* transData - to store transaction data
* Parameters (out): None
* Return value: EN_transState_t - (DECLINED_STOLEN_CARD , DECLINED_INSUFFECIENT_FUND , INTERNAL_SERVER_ERROR , APPROVED)
* Description: Function to get the transaction data & updates the database
************************************************************************************/

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    /*Error State Variable to return the state of the function (DECLINED_STOLEN_CARD or SERVER_OK)*/
    EN_transState_t EN_LocalState;
    /*If condition to impelement the server's flowchart*/
    if (isValidAccount(&transData->cardHolderData) == SERVER_OK)
    {
        if (isAmountAvailable(&transData->terminalData) == SERVER_OK)
        {
            if (saveTransaction(transData) == SERVER_OK)
            {
                Accounts[U16_GlobalAccount_Index].balance = Accounts[U16_GlobalAccount_Index].balance - transData->terminalData.transAmount; 
                EN_LocalState = APPROVED;
            }
            else
            {
               
                EN_LocalState = INTERNAL_SERVER_ERROR;
            }
        }
        else
        {
            EN_LocalState = DECLINED_INSUFFECIENT_FUND;
        }

    }
    else
    {
        EN_LocalState = DECLINED_STOLEN_CARD;
    }
    return EN_LocalState;
}

/************************************************************************************
* Function Name: isValidAccount
* Parameters (in): None
* Parameters (inout): ST_cardData_t* cardData - to get card data
* Parameters (out): None
* Return value: EN_serverError_t - (DECLINED_STOLEN_CARD , SERVER_OK)
* Description: Function to check if PAN number exists in the database or not
************************************************************************************/

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
    /*Error State Variable to return the state of the function (DECLINED_STOLEN_CARD or SERVER_OK)*/
    EN_serverError_t EN_LocalState;
    /*Flag to exit the for loop*/
    uint8_t U8_LocalFlag = ZERO;
    /*For loop iterates on all accounts in the global accounts database, if the PAN found then store its index & exit the loop
    if not found until the end of the loop then return DECLINED_STOLEN_CARD*/
    for (uint8_t U8_LocalIterator = ZERO; (U8_LocalIterator < MAXIMUM_ACCOUNTS) && !(U8_LocalFlag== RAISED_FLAG); U8_LocalIterator++)
    {
        if (strcmp((cardData->primaryAccountNumber) ,(Accounts[U8_LocalIterator].primaryAccountNumber)) == ZERO)
        {
            EN_LocalState = SERVER_OK;
            U8_LocalFlag = RAISED_FLAG;
            U16_GlobalAccount_Index = U8_LocalIterator;
        }
        else
        {
            /*Do Nothing*/
        }
    }
    if (U8_LocalFlag == ZERO)
    {
        EN_LocalState = DECLINED_STOLEN_CARD;
    }
    return EN_LocalState;
}

/************************************************************************************
* Function Name: isAmountAvailable
* Parameters (in): None
* Parameters (inout): ST_terminalData_t* termData - to get the transaction data
* Parameters (out): None
* Return value: EN_serverError_t - (LOW_BALANCE , SERVER_OK)
* Description: Function to check if the account has the amount of transaction
************************************************************************************/

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
    /*Error State Variable to return the state of the function (LOW_BALANCE or SERVER_OK)*/
    EN_serverError_t EN_LocalState;
    /*If condition to check if the transaction amount exceeds the balance or not*/
        if ((termData->transAmount) <= (Accounts[U16_GlobalAccount_Index].balance))
        {
            EN_LocalState = SERVER_OK;
        }
        else
        {
            EN_LocalState = LOW_BALANCE;
        }
    return EN_LocalState;
}

/************************************************************************************
* Function Name: saveTransaction
* Parameters (in): None
* Parameters (inout): ST_transaction_t* transData - to store transaction data
* Parameters (out): None
* Return value: EN_serverError_t - (SAVING_FAILED , SERVER_OK)
* Description: Function to save all the transaction data
************************************************************************************/

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    /*Error State Variable to return the state of the function (SAVING_FAILED or SERVER_OK)*/
    EN_serverError_t EN_LocalState;
    /*If condition to check if the transaction data can be saved or not*/
    
    if (U16_GlobalTransaction_Index == MAXIMUM_TRANSACTIONS)
    {
        /*for example the transactions array is full*/
        EN_LocalState = SAVING_FAILED;
    }
    else
    {
        transData->transactionSequenceNumber = U16_GlobalTransaction_Index;
        transData->transState = APPROVED;
        /*Save all the transaction data*/
        Transactions[U16_GlobalTransaction_Index].cardHolderData = transData->cardHolderData;
        Transactions[U16_GlobalTransaction_Index].terminalData = transData->terminalData;
        Transactions[U16_GlobalTransaction_Index].transState = transData->transState;
        Transactions[U16_GlobalTransaction_Index++].transactionSequenceNumber = transData->transactionSequenceNumber;
        EN_LocalState = SERVER_OK;
    }
   return EN_LocalState;
}


