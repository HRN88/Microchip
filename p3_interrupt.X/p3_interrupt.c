/*
 * File:   p3_interrupt.c
 * Author: Koppernikus
 *
 * Realizar un contador del 0 al 8 mediante el PORTB y 4 leds, realizar el incremento
 * mediante el TIMER0 cada 1s, usar la llamada a una ISR de alta prioridad mediante el 
 * desbordamiento.
 * 
 * A la vez realizar la el cambio de estado de un led extra en funcion de un push-button
 * 
 * 
 * Created on 14 de agosto de 2017, 10:17 PM
 */


#include <xc.h>

//////////////////////////Bits de configuracion////////////////////////////////
#define _XTAL_FREQ 48000000                                             //Se utiliza una frecuencia de reloj de 48MHz
#pragma config PLLDIV = 5                                               //Divisor de frecuencia con el postscaler
#pragma config CPUDIV = OSC1_PLL2                                       //Division de frecuencia con el prescaller
#pragma config FOSC = HSPLL_HS                                          //Modo de oscilacion externo con PLL de alta velocidad
#pragma config IESO = OFF                                               //Switchover
#pragma config MCLRE = OFF												//Master clear, ¿Que hace este bit de configuracion?

int contador = 0;
int contador1 = 0;
void interrupt interrupcion();
void Timer0Config();
void IOportsConfig();
void InterruptConfig();

void main(void) {
    IOportsConfig();
    Timer0Config();
    InterruptConfig();
    while(1){
            
            PORTBbits.RB4 =! PORTBbits.RB4;
            __delay_ms(250);
            
            
            
        
       
    };
    
              
        
        
    
    
}

void InterruptConfig(){
    //Habilita las prioridades para interrupciones
    RCONbits.IPEN = 1;
    //Habilita la interrupcion por el Timer0
    INTCONbits.TMR0IE = 1;
    //Flag par el Timer0 por desbordamiento
    INTCONbits.TMR0IF = 0;
    
    INTCONbits.GIE = 1;
}

void Timer0Config(){
    //Timer0 (7)Habilitado, (6)8-bits Mode, (0-2)64-Prescaler 
    T0CON = 0b11000101;     
    //Precarga para desbordamiento que da 1 ms
    TMR0 = 68;                          
   
    
}
void IOportsConfig(){
    //PORTB como salidas
    TRISB = 0x00;  
    //LATB en ceros
    LATB = 0x00;
    //PORTA como entradas
    TRISA = 0x0F;
    //PORTA como entradas digitales
    ADCON1 = 0x0F;
}

void interrupt Interrupcion(){
    contador ++;
    TMR0IF = 0;
    TMR0 = 68;
    if(contador >= 1000){
        contador = 0;
        LATB += 1;
        if(LATBbits.LATB3)
            LATB = 0;
        
    }
    
}