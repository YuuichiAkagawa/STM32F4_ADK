/*
 * uart_debug.h
 *
 *  Created on: Jan 28, 2012
 *      Author: akagawa
 */
#include "xprintf.h"

void uart_debug_init(void);
void uart_debug_putc( unsigned char c);
void LogicAnalyzerTirggerConfig(void);
void LogicAnalyzerTirgger(uint8_t t);
