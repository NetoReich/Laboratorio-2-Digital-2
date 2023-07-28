// File:   LCD.h
// Author: Johann Haeussler 21223
// 27.07.23

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <proc/pic16f887.h>
//#define _XTAL_FREQ  8000000


void LCD_PORT8(char a);
void LCD_COM8(char a);
void LCD_CLEAR8(void);
void LCD_XY8(char x, char y);
void LCD_INIT8(void);
void LCD_CHAR8(char a);
void LCD_STRING8(char *a);
void LCD_RIGHT8(void);
void LCD_LEFT8(void);

#define LCD_PORT PORTD
#define RS_PIN RC0
#define E_PIN RC1

#endif	/* LCD_H */

