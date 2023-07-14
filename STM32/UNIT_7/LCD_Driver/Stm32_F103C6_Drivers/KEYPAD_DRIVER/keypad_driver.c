/*
 * keypad_driver.c
 *
 *  Created on: Jul 13, 2023
 *      Author: ahmed osama
 */



#include "keypad_driver.h"

GPIO_PConfig_t PinCfg;

int Keypad_Row[] = {R0, R1, R2, R3}; //rows of the keypad
int Keypad_Col[] = {C0, C1, C2, C3}; //columns of the keypad

void Keypad_Init(){


}


char Keypad_GetKey();

