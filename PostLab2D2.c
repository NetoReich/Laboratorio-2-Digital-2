// File:   PostLab2D2.c
// Author: Johann Haeussler 21223
// 27.07.23

#pragma config  FOSC    = INTRC_NOCLKOUT
#pragma config  WDTE    = OFF
#pragma config  PWRTE   = OFF
#pragma config  MCLRE   = OFF
#pragma config  CP      = OFF
#pragma config  CPD     = OFF
#pragma config  BOREN   = OFF
#pragma config  IESO    = OFF
#pragma config  FCMEN   = OFF
#pragma config  LVP     = OFF

#pragma config  BOR4V   = BOR40V
#pragma config  WRT     = OFF

#include <stdint.h>
#include <xc.h>
#include "LCD.h"
#include "ADC.h"
#include "USART.h"

#define _XTAL_FREQ  8000000

//Variables utilizadas
char old_pot;
uint8_t POT;
char cont;
uint8_t unidad, decena,centena;


void setup(void);

void main(void) {

    setup();
    while(1){
        old_pot = POT;
        
        //POT = ADC_READ();
        if (ADCON0bits.GO == 0){    //leemos el chanal 5 y guardamos
            POT= ADC_READ();        //los datos en la variable
            ADCON0bits.GO = 1;
        }
        
        centena = CENTENA(POT);     //Aqui separamos el valor para poder
        decena = DECENA(POT);       //imprimirlos despues
        unidad = UNIDAD(POT);
        
        centena += 48;              //por ser idioma ASCII 48 significa 0
        decena += 48;               //de esta forma obtenemos numeros y no palabras
        unidad += 48;
        
        cont = USART_READ();        //leemos si recivimos algun caracter de la compu

        if(cont == '+'){            //dependiendo de si es + o -
            PORTA++;                //incrementamos o decrementamos el puerto
        }else if(cont == '-'){
            PORTA--;                //reiniciamos variables para que no este 
        }                           //continuamente incrementando o aumentado
        cont = 0;                   
        
        if(old_pot != POT){         //utilizamos esta subrutina para evitar que la 
            __delay_ms(100);        //terminal este imprimiendo todo el tiempo
            USART_WRITE("\n\r+ Aumentar contador\n\r");
            USART_WRITE("- Disminuir contador\n\r");
            USART_WRITE("Voltaje de POT: ");
            USART_CHAR(centena);
            USART_WRITE(".");
            USART_CHAR(decena);
            USART_CHAR(unidad);
            USART_WRITE("V");
            USART_WRITE("\n\r\n\r");
            __delay_ms(100);
        }
        
        
        LCD_CLEAR8();               
        LCD_XY8(1,1);
        LCD_STRING8("POT");
        LCD_XY8(2,1);
        LCD_CHAR8(centena);
        LCD_STRING8(".");
        LCD_CHAR8(decena);
        LCD_CHAR8(unidad);
        LCD_STRING8("V");
        
        centena = CENTENA(PORTA);   
        decena = DECENA(PORTA);
        unidad = UNIDAD(PORTA);
        
        centena += 48;
        decena += 48;
        unidad += 48;
        
        LCD_XY8(1,10);
        LCD_STRING8("CPU:");
        LCD_XY8(2,10);
        LCD_CHAR8(centena);
        LCD_STRING8(".");
        LCD_CHAR8(decena);
        LCD_CHAR8(unidad);
        LCD_STRING8("V");
        
    }
    return;
}

void setup(void){
    
    ANSEL =  0b00100000;    
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISD = 0x00;
    TRISC = 0b10000000;     
    PORTA = 0x00;
    PORTD = 0x00;
    PORTC = 0X00;
    //oscilador a 8M Hz
    OSCILLATOR(1);
    
    //Config. ADC
    ADC_INIT(5);          
    
    ADCON1bits.VCFG0 = 0;   
    ADCON1bits.VCFG1 = 0;   
    
    ADCON0bits.ADCS0 = 0;   
    ADCON0bits.ADCS1 = 1;

    ADCON1bits.ADFM =0;     
    
    ADCON0bits.ADON = 1;  
    __delay_us(50);
    ADCON0bits.GO_nDONE = 1;
    
    POT = 0;                
    cont = 0;
    unidad = 0; 
    decena = 0;
    centena = 0;
    old_pot = 0;

    LCD_INIT8();
    USART_INIT(9600);
    return;
}
