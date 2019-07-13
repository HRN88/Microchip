/*
 * File:   p5_semaforo.c
 * Author: Koppernikus
 *
 * Se realiza un semaforo de tres estados (verde, amarillo, rojo):
 * Verde    3 tiempos
 * Amarillo 2 tiempos
 * Rojo     3 tiempos
 * 
 * Utilizar el TMR0 e interrupciones para la llamada a la rutina ISR
 * 
 * Created on 20 de agosto de 2017, 08:13 PM
 */

#include <xc.h>
//////////////////////////Bits de configuracion////////////////////////////////
#define _XTAL_FREQ 48000000                                             //Se utiliza una frecuencia de reloj de 48MHz
#pragma config PLLDIV = 5                                               //Divisor de frecuencia con el postscaler
#pragma config CPUDIV = OSC1_PLL2                                       //Division de frecuencia con el prescaller
#pragma config FOSC = HSPLL_HS                                          //Modo de oscilacion externo con PLL de alta velocidad
#pragma config IESO = OFF                                               //Switchover
#pragma config MCLRE = OFF	

char estado = '0';
int contador;

void ConfigInit(){
    //Funcion para la configuracion inicial de todo el sistema
    
    //Entradas y salidas
    TRISB = 0;              //PORTB como salidas
    LATB = 0;               //Limpiando el LATCH del PORTB
    
    
    //Configuracion del TMR0 ********************************************
    
    //Registro de configuracion para el TMR0 T0CON
    T0CON = 0b11000101;     
    //Precarga para 1ms
    TMR0 = 68;         
    //Bandera del desbordamiento del timer
    INTCONbits.T0IF = 0;
  
    //Configuracion de interrupciones ********************************
    
    //Registro de configuracion para interrupciones INTCON
    //Interrupciones globales habilitadas
    INTCONbits.GIE = 1;
    //Interrupcion por el TMR0 habilitada
    INTCONbits.TMR0IE = 1;
    
    
}
void interrupt RutinaISR(){
    //Rutina de interrupcion de alta prioridad
    contador ++;
    TMR0 = 68;
    INTCONbits.TMR0IF = 0;
    
    if(contador == 500) estado = '1';
    if(contador == 3500) estado = '2';
    if(contador == 4500) estado = '3';
    if(contador == 7500){
        contador = 0;
        estado = '0';
    }
}


void main(void) {
    ConfigInit();
    while(1){
        
        switch(estado){
            case '0':
                PORTB = 0x00;
                break;
            case '1':
                PORTB = 0x01;
                break;
            case '2':
                PORTB = 0x02;
                break;
            case '3':
                PORTB = 0x04;
                break;
        }
        
    }
    return;
}





