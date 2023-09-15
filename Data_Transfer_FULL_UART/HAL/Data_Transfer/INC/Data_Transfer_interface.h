/******************************************************************************/
/*                                                                            */
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Module          : chat program                                            */
/* !Description     : chat program                                            */
/*                                                                            */
/* !File            : Data_Transfer_interface.h                               */
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

#ifndef HAL_DATA_TRANSFER_INC_DATA_TRANSFER_INTERFACE_H_
#define HAL_DATA_TRANSFER_INC_DATA_TRANSFER_INTERFACE_H_
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/i2c.h"

#include "driverlib/pin_map.h"

void data_transfer_init();
void send_byteECU(uint8_t character);
uint8_t recieve_bytePC();
uint8_t recieve_byteECU();
void send_bytePC(uint8_t character);
void send_StringPC(uint8_t *str);
void send_BlockECU();
void send_blockPC();
void Data_Transfer_Handler(void);
void Switch_Handler(void);
void send_bytePC(uint8_t character);
bool IsDataAvailable();

#endif /* HAL_DATA_TRANSFER_INC_DATA_TRANSFER_INTERFACE_H_ */
