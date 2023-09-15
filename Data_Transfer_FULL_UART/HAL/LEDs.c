/*
 * LEDs.c
 *
 *  Created on: Sep 2, 2023
 *      Author: EUI-Support
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "LEDs.h"

void LEDs_Init()
{
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

}

void RED_LED(state s)
{

    switch(s)
    {
    case ON:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        break;
    case OFF:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
    }


}

void BLUE_LED(state s)
{

    switch(s)
    {
    case ON:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        break;
    case OFF:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
    }


}


void GREEN_LED(state s)
{

    switch(s)
    {
    case ON:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        break;
    case OFF:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
    }

}
