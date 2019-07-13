/*
 * File:   p6_intext.c
 * Author: Koppernikus
 *Se realiza un programa para usar interrupciones externas (INT0), para cambiar 
 * el estado de un led, se hace mediante la llamada de una ISR de alta prioridad
 * Created on 21 de agosto de 2017, 07:52 PM
 */


#include <xc.h>
//////////////////////////Bits de configuracion////////////////////////////////
#define _XTAL_FREQ 48000000                                             //Se utiliza una frecuencia de reloj de 48MHz
#pragma config PLLDIV = 5                                               //Divisor de frecuencia con el postscaler
#pragma config CPUDIV = OSC1_PLL2                                       //Division de frecuencia con el prescaller
#pragma config FOSC = HSPLL_HS                                          //Modo de oscilacion externo con PLL de alta velocidad
#pragma config IESO = OFF                                               //Switchover
#pragma config MCLRE = OFF


void ConfigInit(){
    //Funcion de configuracion general del sistema
    
    //Configuracion de los puertos I/0
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 0;
    LATBbits.LB1 = 0;
    //Enmascaramiento en ADCON1 para usarn AN12(PB0) como pin digital  
    ADCON1 |= 0x0F;     
    
    //************************
    //Configurando INT0
    //***********************
         
    //Habilita Interrupciones globales
    INTCONbits.GIE = 1;
    //Habilita las interrupciones perifericas
    INTCONbits.PEIE = 1;
    //Habilita la interrupcion INT0
    INTCONbits.INT0IE = 1;
    //Seteando la bandera de INT0
    INTCONbits.INT0IF = 0;
    //Especifica la deteccion de la interrupcion con flanco de bajada
    INTCON2bits.INTEDG0 = 1;
    
}
void interrupt ISR_INT0(){
    if(INT0IF){

        LATBbits.LB1 =! LATBbits.LB1;
        __delay_ms(250);
        INTCONbits.INT0IF = 0;
       
    }
}

void main(void) {
    ConfigInit();
    while(1){
        
    }
    return;
}



