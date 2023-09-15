/******************************************************************************/
/*                                                                            */
/* !Layer           : Application                                             */
/*                                                                            */
/* !Module          : chat application                                        */
/* !Description     : chat application                                        */
/*                                                                            */
/* !File            : Chat_program.c                                          */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : chat program | EME - CLASS 1                            */
/*                                                                            */
/* !Target          : TIVA-C TM4C123GH6PM                                     */
/*                                                                            */
/* !Compiler        : Code Composer Studio 8.3.1                              */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Ragab,ahmed abdellazem     !Date : sep 10, 2023   */
/* !Coded by        : Ahmed Ragab,ahmed abdellazem    !Date : sep 10, 2023    */
/*                                                                            */
/* Ver 1.0    sep 15, 2023     Initial release                                */
/******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#include "../../HAL/Data_Transfer/INC/Data_Transfer_interface.h"
#include "../../HAL/Data_Transfer/INC/Data_Transfer_config.h"
#include "../INC/Chat_interface.h"

#include "../../HAL/button.h"
#include "../../HAL/LEDs.h"

extern uint8_t Recived_Byte;
extern uint8_t PC_Buffer_FULL;
extern uint8_t PC_Index;
extern uint8_t Send_Flag;
extern uint8_t State;
volatile uint8_t Button_State;

void (*arrFun[3])(void)={State_Idle,State_Listner,State_Chatting};

uint8_t RecievedBufferECU[Max_Length] ={0};
uint8_t ECU_Index=0;

void State_Idle(void)
{
    RED_LED(ON);
    BLUE_LED(OFF);
    GREEN_LED(OFF);
    Send_Flag=0;
    PC_Buffer_FULL=0;
    PC_Index=0;
    while(Button_State == 0)
    {

    }

}
void State_Listner(void)
{
    RED_LED(OFF);
    BLUE_LED(ON);
    GREEN_LED(OFF);
    Send_Flag=0;
    PC_Buffer_FULL=0;
    PC_Index=0;

    while(Button_State == 1)
    {
        if(IsDataAvailable())
        {
            send_blockPC();
        }
        else
        {

        }

    }

}
void State_Chatting(void)
{
    RED_LED(ON);
    BLUE_LED(ON);
    GREEN_LED(ON);
    Send_Flag=0;
    PC_Buffer_FULL=0;
    PC_Index=0;

    while(Button_State == 2)
    {
        if(IsDataAvailable())
        {
            send_blockPC();
        }
        else
        {

        }
        if(Send_Flag == 1)
        {
            Send_Flag=0;
            send_BlockECU();
        }
        else
        {
            /*Do Nothing*/
        }

        if(PC_Buffer_FULL == 1)
        {
            /*\033[2J\033[H*/
            send_StringPC("\n\rBuffer Is Full Press 1 To send or any To FLUSH...\n\r");
            PC_Buffer_FULL=0;
        }
        else
        {

        }
    }
}

void Chat_Run(void)
{

    data_transfer_init();

    buttons_Init(1);
    LEDs_Init();
    button_INT(1);
    SetCallBackFunction(Switch_Handler);

    while(1){


        arrFun[Button_State]();
        /*
         *-> State 0 : LED is RED IDLE State
         *-> State 1 : LED is Blue + Read Only (Listener)
         *-> State 2 : Turn ON All Leds + Read/Write
         * */
        //        if(UARTCharsAvail(UART5_BASE))
        //        {
        //            send_blockPC();
        //        }
        //        else
        //        {
        //
        //        }
        //        if(Send_Flag == 1)
        //        {
        //            Send_Flag=0;
        //            send_BlockECU();
        //        }
        //        else
        //        {
        //            /*Do Nothing*/
        //
        //        }
        //
        //        if(PC_Buffer_FULL == 1)
        //        {
        //            /*\033[2J\033[H*/
        //            send_StringPC("\n\rBuffer Is Full Press 1 To send or any To FLUSH...");
        //            PC_Buffer_FULL=0;
        //        }
        //        else
        //        {
        //
        //        }

    }
}
void Switch_Handler(void)
{
    switch(Button_State)
    {
    case 0:
        Button_State=1;
        break;
    case 1:
        Button_State=2;
        break;
    case 2:
        Button_State=0;
        break;
    default:
        break;
    }

}
