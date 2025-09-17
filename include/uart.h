/* 
Author: Gabriel Rodgers <gabrielrodgers4i@gmail.com>
Date: 8/31/2025
*/

#include <stdint.h>

#ifndef _UART_H
#define _UART_H

#include "misc.h"

status_t uart_init(uint32_t rate);
status_t uart_tx(char buf);
status_t write(char* buf);
//void uart_rx(uint8_t* buf);

#endif /* _UART_H */
