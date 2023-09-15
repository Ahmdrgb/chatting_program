/******************************************************************************/
/*                                                                            */
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Module          : chat program                                            */
/* !Description     : chat program                                            */
/*                                                                            */
/* !File            : Data_Transfer_program.c                                 */
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
#include"../INC/Data_Transfer_interface.h"
#include"../INC/Data_Transfer_config.h"

volatile uint8_t Recived_Byte=0;
volatile uint8_t PC_Buffer_FULL=0;
volatile uint8_t RecievedBufferPC[Max_Length] ={0};
volatile uint8_t PC_Index=0;
volatile uint8_t State=0;
volatile uint8_t Send_Flag=0;


void data_transfer_init()
{

    /*****************************************************UART PC********************************************************/

    SysCtlPeripheralEnable(data_prephiral_clk);
    // Wait for the UART0 module to be ready.
    while(!SysCtlPeripheralReady(data_prephiral_clk)){}
    // Initialize the UART
    UARTConfigSetExpClk(data_prephiral_base, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    /*ENABLE PORTE */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    UARTFIFODisable(UART0_BASE);

    UARTIntRegister(UART0_BASE, Data_Transfer_Handler);
    UARTIntEnable(UART0_BASE, UART_INT_RX);

    /********************************************************************************************************************/

#ifdef UART

    /*****************************************************UART PC********************************************************/
    // Enable the UART5 module.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
    // Wait for the UART5 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART5)){}
    // Initialize the UART

    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    /*ENABLE PORTE */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4|GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);
    /********************************************************************************************************************/

#else
#ifdef I2C

    //
    // The I2C0 peripheral must be enabled before use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

    //
    // For this example I2C0 is used with PortB[3:2].  The actual port and
    // pins used may be different on your part, consult the data sheet for
    // more information.  GPIO port B needs to be enabled so these pins can
    // be used.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //
    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    //
    // Select the I2C function for these pins.  This function will also
    // configure the GPIO pins pins for I2C operation, setting them to
    // open-drain operation with weak pull-ups.  Consult the data sheet
    // to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);


    //
    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.  For this example we will use a data rate of 100kbps.
    //
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    //I2CLoopbackEnable(I2C0_BASE);

    //
    // Enable the I2C0 slave module. This module is enabled only for testing
    // purposes.  It does not need to be enabled for proper operation of the
    // I2Cx master module.
    //
    I2CSlaveEnable(I2C0_BASE);

    //
    // Set the slave address to SLAVE_ADDRESS.  In loopback mode, it's an
    // arbitrary 7-bit number (set in a macro above) that is sent to the
    // I2CMasterSlaveAddrSet function.
    //
    I2CSlaveInit(I2C0_BASE, Tiva_1_Address);


    /*
     *  D0(Master/Slave)                 D1(Master/Slave)
     *
     *  0                                1
     *
     *
     * */

#endif
#endif

}


uint8_t recieve_bytePC()
{
    return UARTCharGet(UART0_BASE);
}

void send_byteECU(uint8_t character)
{
#ifdef UART

    UARTCharPut(UART5_BASE, character);
#else
#ifdef I2C

    I2CMasterDataPut(I2C0_BASE, character);
    //
    // Initiate send of data from the master.  Since the loopback
    // mode is enabled, the master and slave units are connected
    // allowing us to receive the same data that we sent out.
    //
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
    //
    // Wait until the slave has received and acknowledged the data.
    //
       while(!(I2CSlaveStatus(I2C0_BASE) & I2C_SLAVE_ACT_RREQ))
        {
        }

#endif
#endif
}

void send_BlockECU()
{
    uint16_t i=0;
    uint16_t Arr_Size;
    //
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.  Set the address to SLAVE_ADDRESS
    // (as set in the slave module).  The receive parameter is set to false
    // which indicates the I2C Master is initiating a writes to the slave.  If
    // true, that would indicate that the I2C Master is initiating reads from
    // the slave.
    //

#ifdef UART

    Arr_Size = PC_Index;
#else
#ifdef I2C
    I2CMasterSlaveAddrSet(I2C0_BASE, Tiva_2_Address, false);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    while(!(I2CSlaveStatus(I2C0_BASE) & I2C_SLAVE_ACT_RREQ))
     {
     }

    Arr_Size = PC_Index -1;

#endif
#endif

    for(i=0;i<Arr_Size;i++)
    {
        send_byteECU(RecievedBufferPC[i]);
    }

#ifdef I2C

    I2CMasterDataPut(I2C0_BASE, RecievedBufferPC[i]);
    I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);

    while(!(I2CSlaveStatus(I2C0_BASE) & I2C_SLAVE_ACT_RREQ))
     {
     }

#endif

    //
    // Wait until the slave has received and acknowledged the data.
    //
    //    while(!(I2CSlaveStatus(I2C0_BASE) & I2C_SLAVE_ACT_RREQ))
    //    {
    //    }
    PC_Index = 0;

}
uint8_t recieve_byteECU()
{
    return UARTCharGetNonBlocking(UART5_BASE);
}

bool IsDataAvailable()
{
    bool state;

#ifdef UART
    state= UARTCharsAvail(UART5_BASE);
#else
#ifdef I2C
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    state = ((I2CSlaveStatus(I2C0_BASE) & I2C_SLAVE_ACT_RREQ));// == I2C_SLAVE_ACT_RREQ));
#endif
#endif

    return state;

}

void send_blockPC()
{
    uint8_t temp,i=0;
    send_StringPC("\n\rMSG> ");

    //    temp= I2CSlaveDataGet(I2C0_BASE);
    //    UARTCharPut(data_prephiral_base, temp);
#ifdef UART
    while(IsDataAvailable())
    {
        temp=UARTCharGet(UART5_BASE);
        UARTCharPut(data_prephiral_base, temp);
    }
#else
#ifdef I2C
    while(IsDataAvailable())
    {
        temp= I2CSlaveDataGet(I2C0_BASE);
        UARTCharPut(data_prephiral_base, temp);
    }
#endif
#endif


    send_StringPC("\n\r");
    for(i=0;i<PC_Index;i++)
    {
        send_bytePC(RecievedBufferPC[i]);
    }

}

void send_bytePC(uint8_t character){


    UARTCharPut(data_prephiral_base, character);

}
void send_StringPC(uint8_t *str)
{
    uint16_t i=0;
    for(i=0;str[i];i++)
    {
        send_bytePC(str[i]);
    }
}



void Data_Transfer_Handler(void)
{
    UARTIntClear(UART0_BASE, UART_INT_RX);

    if(PC_Index<Max_Length)
    {
        RecievedBufferPC[PC_Index]=UARTCharGet(UART0_BASE);
        UARTCharPut(UART0_BASE, RecievedBufferPC[PC_Index]);

        if(RecievedBufferPC[PC_Index] == 13)
        {
            Send_Flag=1;
            send_StringPC("\n\r");
        }
        else if(RecievedBufferPC[PC_Index] == 127)
        {
            if(PC_Index>=1)
            {
            PC_Index--;
            }
        }
        else
        {

            PC_Index++;
            if(PC_Index == Max_Length)
            {
                PC_Buffer_FULL=1;
            }
            else
            {

            }
        }

    }else
    {
        State=UARTCharGet(UART0_BASE);

        if(State == '1')
        {
            Send_Flag=1;
            send_StringPC("\n\r");

        }
        else
        {
            PC_Index=0;
        }
    }
}
