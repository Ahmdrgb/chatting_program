/*
 * button.h
 *
 *  Created on: Sep 3, 2023
 *      Author: EUI-Support
 */

#ifndef BUTTON_H_
#define BUTTON_H_

volatile extern uint8_t curr;


void buttons_Init(uint8_t n);
void button_INT(uint8_t n);
void SetCallBackFunction(void (*temp)(void));
void GPIOF_Handler();





#endif /* BUTTON_H_ */
