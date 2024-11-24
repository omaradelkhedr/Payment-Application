/******************************************************************************
 *
 * Module: Application
 *
 * File Name: app.c
 *
 * Description: Source file for Application Module
 *
 * Author: Omar Khedr
 ******************************************************************************/

/*Include of the module header file*/
#include "../inc/app.h"

/*Variable to exit the infinite loop*/
uint8_t U8_GlobalExit = ZERO;

/*Initialization of used structutre*/
static ST_transaction_t ST_LocalTransaction = {0};

/************************************************************************************
 * Function Name: appStart
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to start the application
 ************************************************************************************/

void appStart(void)
{
	/*Switch Case to return to the location*/
	static uint8_t U8_LocalEntryPoint = 0;
	switch (U8_LocalEntryPoint)
	{
	case 0:
		/*Welcome message*/
		printf("************Welcome to the Payment Appilaction*************\n");
		U8_LocalEntryPoint++;
	case 1:
		/*Card Module Flowchart*/
		if (getCardHolderName(&ST_LocalTransaction.cardHolderData) == CARD_OK)
		{
			U8_LocalEntryPoint++;
		case 2:
			if (getCardExpiryDate(&ST_LocalTransaction.cardHolderData) == CARD_OK)
			{
				U8_LocalEntryPoint++;
			case 3:
				if (getCardPAN(&ST_LocalTransaction.cardHolderData) == CARD_OK)
				{
					U8_LocalEntryPoint++;
				case 4:
					if (getTransactionDate(&ST_LocalTransaction.terminalData) == TERMINAL_OK)
					{
						U8_LocalEntryPoint++;
					case 5:
						if (isCardExpired(ST_LocalTransaction.cardHolderData, ST_LocalTransaction.terminalData) == TERMINAL_OK)
						{
							U8_LocalEntryPoint++;
						case 6:
							if (setMaxAmount(&ST_LocalTransaction.terminalData) == TERMINAL_OK)
							{
								U8_LocalEntryPoint++;
							case 7:
								if (getTransactionAmount(&ST_LocalTransaction.terminalData) == TERMINAL_OK)
								{
									U8_LocalEntryPoint++;
								case 8:
									if (isBelowMaxAmount(&ST_LocalTransaction.terminalData) == TERMINAL_OK)
									{
										U8_LocalEntryPoint++;
										EN_transState_t EN_LocalState;
									case 9:
										EN_LocalState = recieveTransactionData(&ST_LocalTransaction);
										if (EN_LocalState == APPROVED)
										{
											static uint8_t U8_LocalChoice = 0;
											printf("The new Balance is : %f\n", Accounts[U16_GlobalAccount_Index].balance);
										case 10:
											printf("Do you want to make another transaction?\nYES: [1]\nNO: [2]\n");
											scanf("%d", &U8_LocalChoice);
											fflush(stdin);
											if (U8_LocalChoice == ONE)
											{
												U8_LocalEntryPoint = 7;
											}
											else if (U8_LocalChoice == TWO)
											{
												printf("Thank You for using this Payment Application \n");
												U8_LocalEntryPoint = ZERO;
												U8_GlobalExit = ONE;
											}
											else
											{
												printf("Wrong Entry,Please Try Again: \n");
												U8_LocalEntryPoint = 10;
											}
										}
										else if (EN_LocalState == DECLINED_INSUFFECIENT_FUND)
										{
											printf("Declined Insuffecient Fund \n");
											U8_LocalEntryPoint = ZERO;
											U8_GlobalExit = ONE;
										}
										else if (EN_LocalState == DECLINED_STOLEN_CARD)
										{
											printf("Declined Stolen Card \n");
											U8_LocalEntryPoint = ZERO;
											U8_GlobalExit = ONE;
										}
										else
										{
											printf("Saving Failed \n");
											U8_LocalEntryPoint = ZERO;
											U8_GlobalExit = ONE;
										}
									}
									else
									{
										printf("Declined Amount Exceeding Limit\n");
										U8_LocalEntryPoint = ZERO;
										U8_GlobalExit = ONE;
									}
								}
								else
								{
									printf("Wrong Entry, Please Try Again: \n");
								}
							}
							else
							{
								printf("Wrong Entry,Please Try Again: \n");
							}
						}
						else
						{
							printf("Declined Expired Card\n");
							U8_LocalEntryPoint = ZERO;
							U8_GlobalExit = ONE;
						}
					}
					else
					{
						printf("Wrong Entry, Please Try Again: \n");
					}
				}
				else
				{
					printf("Wrong Entry, Please Try Again: \n");
				}
			}
			else
			{
				printf("Wrong Entry, Please Try Again: \n");
			}
		}
	default:
		break;
	}
}