// File:   USART.h
// Author: Johann Haeussler 21223
// 27.07.23

 
#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <proc/pic16f887.h>

void USART_INIT(uint16_t BAUD);
void USART_CHAR(char d);
void USART_WRITE(char *c);
char USART_READ();

#endif	/* XC_HEADER_TEMPLATE_H */

