// File:   USART.c
// Author: Johann Haeussler 21223
// 27.07.23


#include <stdint.h>
#include <xc.h>
#include "USART.h"
#define _XTAL_FREQ  8000000

void USART_INIT(uint16_t BAUD){
    unsigned char n;                
    n = ((_XTAL_FREQ/BAUD)/4) -1;  
    
    TXSTAbits.SYNC = 0;        
    TXSTAbits.BRGH = 1;         
    BAUDCTLbits.BRG16 = 1;      
    
    SPBRG = n;
    SPBRGH = 0;                
    
    RCSTAbits.SPEN = 1;         
    TXSTAbits.TX9 = 0;          
    RCSTAbits.RX9 = 0;
    TXSTAbits.TXEN = 1;         
    RCSTAbits.CREN = 1;         
}
void USART_CHAR(char d){
    while(TXSTAbits.TRMT == 0); 
        TXREG = d;
}
void USART_WRITE(char *c){     
    while(*c != '\0'){          
        USART_CHAR(*c);
        c++;
    }
}
char USART_READ(){
    if(PIR1bits.RCIF == 1){     //Chequeamos si recivimos un dato
        return RCREG;
    }
    __delay_ms(100);
}
