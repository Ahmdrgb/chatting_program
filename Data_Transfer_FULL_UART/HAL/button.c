/*
 * button.c
 *
 *  Created on: Sep 3, 2023
 *      Author: EUI-Support
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "button.h"
#include "LEDs.h"

#include "inc/hw_gpio.h"

void (*ISR)(void) = 0;

void buttons_Init(uint8_t n)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);


    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    if(n == 1)
    {
        GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_0);
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    }
    else
    {
        GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_4);
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);

    }
}

void button_INT(uint8_t n)
{
    if(n == 1)
    {

        GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
        GPIOIntRegister(GPIO_PORTF_BASE, &GPIOF_Handler);

        IntEnable(INT_GPIOF);
        GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
        IntMasterEnable();

    }
    else
    {
        GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
        GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);


        GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
        GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);

        GPIOIntRegister(GPIO_PORTF_BASE, &GPIOF_Handler);
        IntEnable(INT_GPIOF);
        IntMasterEnable();
    }
}

void SetCallBackFunction(void (*temp)(void))
{
	ISR = temp;
}

void GPIOF_Handler()
{
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
	if (ISR != 0)
	{
		ISR();
	}
	
	/*
    switch(curr)
    {
    case 0:
        curr=1;
        break;
    case 1:
        curr=2;
        break;
    case 2:
        curr=0;
        break;
    default:
        break;
    }
	*/

}

