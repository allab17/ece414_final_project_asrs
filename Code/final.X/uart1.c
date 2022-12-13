
#include <inttypes.h>
#include <xc.h>
#include <plib.h>
#include <stdio.h>
#include "uart1.h"

const int CLOCK_FREQ = 40000000;

void uart1_init(uint32_t baudrate) {
//    ANSELA = 0;
//    TRISBbits.TRISB3 = 1;
//    TRISAbits.TRISA2 = 1;
    
    __XC_UART=1;
    
    PPSOutput(1, RPB3, U1TX);    
    PPSInput(3, U1RX, RPA2);
    
    U1BRG = (CLOCK_FREQ / (16*baudrate)) - 1;
    U1MODEbits.BRGH = 0;
    
    //enable transmission and receiving
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;
    
    //enable UART
    U1MODEbits.ON = 1;
    
}

uint8_t uart1_txrdy() {
    return  !U1STAbits.UTXBF; //if the buffer is full we are not ready
}

void uart1_txwrite(char c) {
    if (!uart1_txrdy()) return NULL;  
    U1TXREG = c;
}

void uart1_txwrite_str(char *cp) {
    while (*cp) { 
        uart1_txwrite(*cp++);  //serially writes the characters to implement the string 
    }
}

uint8_t uart1_rxrdy() {
    return U1STAbits.URXDA; //the rx buffer contains data 
}

 uint8_t uart1_rxread() {
    if (!uart1_rxrdy) return 0;
    else return U1RXREG;
}