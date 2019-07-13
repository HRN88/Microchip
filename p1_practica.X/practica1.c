/*
 * File:   ejmplo1.c
 * Author: Koppernikus
 *
 * Created on 09 de agosto de 2017, 07:25 PM
 * 
 * ////////////////////////////////README//////////////////////////////////
 * 
 * 
 * //Consideraciones:
 * 
 * Se utiliza un cristal de 20 MHZ
 * CPUCLK = 48MHz
 */

#define tiempo 80
#include <xc.h>
//////////////////////////Bits de configuracion////////////////////////////////
#define _XTAL_FREQ 48000000                                             //Se utiliza una frecuencia de reloj de 48MHz
#pragma config PLLDIV = 5                                               //Divisor de frecuencia con el postscaler
#pragma config CPUDIV = OSC1_PLL2                                       //Division de frecuencia con el prescaller
#pragma config FOSC = HSPLL_HS                                          //Modo de oscilacion externo con PLL de alta velocidad
#pragma config IESO = OFF                                               //Switchover
#pragma config MCLRE = OFF												//Master clear, ¿Que hace este bit de configuracion?

void configuracion();

void main(void) {
    configuracion();
    while(1){
        
        
        LATB = 0x01;
        __delay_ms(tiempo);
        for(char a = 0; a <= 2; a++ ){
            LATB <<= 1;
            __delay_ms(tiempo);
        }
        
        for(char a = 2; a >= 1; a--){
            LATB >>= 1;
            __delay_ms(tiempo);
            
        }
        
        
        
        
        
    };
    
}

void configuracion(){
    //Configuracion del sistema
    
    TRISB = 0x80;
    LATB = 0x80;
        
    
}
