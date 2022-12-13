

/*============================================================================
 * uart1.h
 *	Module for 
 * Author: 
 *==========================================================================*/

#ifndef UART1_H
#define	UART1_H
#include <inttypes.h>

extern void uart1_init(uint32_t baudrate);

extern uint8_t uart1_txrdy();

extern void uart1_txwrite(char c);

extern void uart1_txwrite_str(char *cp);

extern uint8_t uart1_rxrdy();

extern uint8_t uart1_rxread();

#endif