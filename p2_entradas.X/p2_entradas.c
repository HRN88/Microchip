/*
 * File:   p2_entradas.c
 * Author: Koppernikus
 *
 * Created on 13 de agosto de 2017, 06:27 PM
 * 
 * ////////////////////////////////README//////////////////////////////////
 *Programa para contar del 0-8 con 4 bits mediante 4 leds conectados al PORTB,
 * la suma se realiza pulsando un push-button, el cual se conecta al PIN RA0
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

void configuracion();

void main(void) {
    configuracion();
    char contador = 0;
    while(1){
        if(PORTAbits.RA0 == 0){
            __delay_ms(200);
            contador++;
            LATB = contador;
            if(contador == 8){
                contador = 0;
            }
            
        }        
    
    };
    
}

void configuracion(){
    //Configuracion del sistema
    TRISAbits.RA0 = 1;                  //Define el pin RA0 como entrada
    ADCON1 = 0x0F;                      //Indica que todo el puerto "A" será para entradas digitales
    
    TRISB = 0;                          //Se indica que el PORTB como salida
    LATB = 0;                           //Se inicializa el LATCH en cero
    
}
