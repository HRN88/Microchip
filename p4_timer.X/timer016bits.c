/*
 * File:   ejmplo1.c
 * Author: Koppernikus
 *
 * Created on 05 de Agosto de 2017, 12:51 PM
 * 
 * ////////////////////////////////README//////////////////////////////////
 * 
 * //Consideraciones:
 * 
 * Se utiliza un cristal de 20 MHZ
 * CPUCLK = 48MHz
 */
#include <xc.h>
//////////////////////////Bits de configuracion////////////////////////////////
#define _XTAL_FREQ 48000000                                             //Se utiliza una frecuencia de reloj de 48MHz
#pragma config PLLDIV = 5                                               //Divisor de frecuencia con el postscaler
#pragma config CPUDIV = OSC1_PLL2                                       //Division de frecuencia con el prescaller
#pragma config FOSC = HSPLL_HS                                          //Modo de oscilacion externo con PLL de alta velocidad
#pragma config IESO = OFF                                               //Switchover
#pragma config MCLRE = OFF												//Master clear, ¿Que hace este bit de configuracion?


void timer0_conf();

void main(void) {
    TRISB = 0;
    PORTB = 0;
    timer0_conf();
    int contador = 0;
    LATBbits.LATB0 = 0;
    while(1){
        if(INTCONbits.TMR0IF){                                          //Se pone en 1 cuando hay desbordamiento
            TMR0L = 0x44;                          
            TMR0H = 0x48;                                                  //Se vuelve a poner en el valor deseado
            contador++;
            INTCONbits.TMR0IF = 0;                                      //Poner a cero para que vuelva a cambiar al detectar desbordamiento
            if(contador >= 2 ){
                LATBbits.LATB0 = !LATBbits.LATB0;
                contador = 0;
            }
            
        }      
        
        
    };
    
}

void timer0_conf(){
    //Funcion para configurar el timer0 a 16bits
    T0CON = 0b10000111;                 //Registro de configuracion TIMER0
    TMR0L = 0x44;                          
    TMR0H = 0x48;
   
    
}