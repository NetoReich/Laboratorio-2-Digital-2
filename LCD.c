// File:   LCD.c
// Author: Johann Haeussler 21223
// 27.07.23

#include <stdint.h>
#include <xc.h>
#include "LCD.h"
#define _XTAL_FREQ  8000000

void LCD_PORT8(char a){
    LCD_PORT = a;
}
void LCD_COM8(char a){
    RS_PIN = 0;
    LCD_PORT8(a);
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
}
void LCD_CLEAR8(void){
    LCD_PORT8(0);
    LCD_PORT8(1); 
}
void LCD_XY8(char x, char y){
    if(x == 1)
	  LCD_COM8(0x80 + y);
	else if(x == 2)
		LCD_COM8(0xC0 + y);
}
void LCD_INIT8(void){
    LCD_PORT8(0x00);
	RS_PIN = 0;
	__delay_ms(25);
	
    LCD_COM8(0x30);
  __delay_ms(5);
    LCD_COM8(0x30);
      __delay_ms(15);
    LCD_COM8(0x30);
   
    LCD_COM8(0x38);    
    LCD_COM8(0x0C);    
    LCD_COM8(0x01);    
    LCD_COM8(0x06);    
}
void LCD_CHAR8(char a){
    RS_PIN = 1;             
    LCD_PORT8(a);   
    E_PIN  = 1;             
   __delay_ms(4);
    E_PIN  = 0;
}
void LCD_STRING8(char *a){
    int i;
	for(i=0;a[i]!='\0';i++)
	 LCD_CHAR8(a[i]);
}
void LCD_RIGHT8(void){
    LCD_COM8(0x1C);
}
void LCD_LEFT8(void){
    LCD_COM8(0x18);
}
