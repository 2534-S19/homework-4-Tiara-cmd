/*
 * homework4.h
 *
 *  Created on:
 *      Author:
 */

#ifndef HOMEWORK4_H_
#define HOMEWORK4_H_

// This function initializes the board by turning off the Watchdog Timer.
void initBoard();
bool charFSM(char rChar);

bool UARTHasChar(uint32_t moduleInstance);
uint8_t UARTGetChar(uint32_t moduleInstance);
bool UARTCanSend(uint32_t moduleInstance);
void UARTPutChar(uint32_t moduleInstance, uint8_t tChar);

enum stateMachine {STATEX,STATEONE,STATETWO,STATETHREE} state;


// TODO: Define any constants that are local to homework.c using #define


#endif /* HOMEWORK4_H_ */
