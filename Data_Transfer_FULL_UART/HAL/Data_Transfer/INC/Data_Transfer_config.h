/*
 * Data_Transfer_config.h
 *
 *  Created on: Sep 3, 2023
 *      Author: mtear
 */

#ifndef HAL_DATA_TRANSFER_INC_DATA_TRANSFER_CONFIG_H_
#define HAL_DATA_TRANSFER_INC_DATA_TRANSFER_CONFIG_H_

#define data_prephiral_clk   SYSCTL_PERIPH_UART0
#define data_prephiral_base   UART0_BASE
#define uart_baud_rate             9600
#define uart_data_length          UART_CONFIG_WLEN_8
#define Max_Length    15

#define UART

#define Tiva_1_Address 20
#define Tiva_2_Address 10



#endif /* HAL_DATA_TRANSFER_INC_DATA_TRANSFER_CONFIG_H_ */
