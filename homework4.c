#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework4.h"
#include "string.h"

int main(void)
{
    char rChar;
    char *response = "\n\n\r2534 is the best course in the curriculum!\r\n\n";

    // TODO: Declare the variables that main uses to interact with your state machine.
    //finished = false;
    state = STATEX;

    // Stops the Watchdog timer.
    initBoard();
    // TODO: Declare a UART config struct as defined in uart.h.
    //       To begin, configure the UART for 9600 baud, 8-bit payload (LSB first), no parity, 1 stop bit.
    eUSCI_UART_ConfigV1 uartConfig =
    {
         EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source = 3000000 = 3MHz: N = freq / baud rate = 312.5
         19,                                            // UCBR = INT(N/16) = 19.53 = 19
         8,                                             // UCxBRF = INT([N/16 - INT(N/16)] x 16) = 8.5 = 8
         0x55,                                          // UCxBRS
         EUSCI_A_UART_NO_PARITY,                        // No Parity
         EUSCI_A_UART_LSB_FIRST,                        // LSB First
         EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
         EUSCI_A_UART_MODE,                             // UART mode
         EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
         EUSCI_A_UART_8_BIT_LEN,

    };

    // TODO: Make sure Tx AND Rx pins of EUSCI_A0 work for UART and not as regular GPIO pins.
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    // TODO: Initialize EUSCI_A0
    UART_initModule(EUSCI_A0_BASE, &uartConfig);


    // TODO: Enable EUSCI_A0
    UART_enableModule(EUSCI_A0_BASE);

    while(1)
    {
        // TODO: Check the receive interrupt flag to see if a received character is available.
        //       Return 0xFF if no character is available.
        if(UARTHasChar(EUSCI_A0_BASE))
            rChar = UARTGetChar(EUSCI_A0_BASE);
        else
            rChar = 0x55;


        // TODO: If an actual character was received, echo the character to the terminal AND use it to update the FSM.
        //       Check the transmit interrupt flag prior to transmitting the character.


        if (UARTCanSend(EUSCI_A0_BASE) && rChar != 0x55)
        {
            UARTPutChar(EUSCI_A0_BASE, rChar);

            if(charFSM(rChar))
            {
                char *strCopy = response;
                int i = 0;
                while(*(strCopy+i) != '\0')
                {
                    rChar = *(strCopy+i);
                    if (UARTCanSend(EUSCI_A0_BASE))
                    {
                        UARTPutChar(EUSCI_A0_BASE, rChar);
                        i++;
                    }
                }
            }
        }

        //}
        // TODO: If the FSM indicates a successful string entry, transmit the response string.
        //       Check the transmit interrupt flag prior to transmitting each character and moving on to the next one.
        //       Make sure to reset the success variable after transmission.


    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}


// TODO: FSM for detecting character sequence.
bool charFSM(char rChar)
{

    bool finished = false;
    switch (state)
    {
        case STATEX:
            if (rChar == '2')
                state = STATEONE;
            else
                state = STATEX;
            break;

        case STATEONE:
            if (rChar == '5')
                state = STATETWO;
            else
                state = STATEX;
            break;

        case STATETWO:
            if (rChar == '3')
                state = STATETHREE;
            else
                state = STATEX;
            break;

        case STATETHREE:
            if (rChar == '4')
                finished = true;

            state = STATEX;
            break;
        }



    return finished;
}



bool UARTHasChar(uint32_t moduleInstance)
{
    return (UART_getInterruptStatus (moduleInstance, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
                        == EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
}
uint8_t UARTGetChar(uint32_t moduleInstance)
{
    return UART_receiveData(moduleInstance);
}

bool UARTCanSend(uint32_t moduleInstance)
{
    return (UART_getInterruptStatus (moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
                            == EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG);
}

void UARTPutChar(uint32_t moduleInstance, uint8_t tChar)
{
    UART_transmitData(moduleInstance, tChar);
}
















