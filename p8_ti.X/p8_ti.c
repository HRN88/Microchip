/*
 * File:   p8_ti.c
 * Author: Koppernikus
 * 
 *Se muestra como hacer parpadear dos leds usando el TMR0 y TMR1, se realiza
 * mediante la llamada de una funcion ISR. En el primer ejemplo se hace sin 
 * prioridad, por lo que solo existe una sola funcion ISR de alta prioridad,
 * que se ejecuta primero. El segundo ejemplo permite la prioridad en las
 * interrupciones, por lo que existen 2 funciones ISR (HighISR y LowISR)
 * de alta prioridad y de baja prioridad.
 * 
 * Created on 24 de agosto de 2017, 06:17 PM
 */


#include <xc.h>
#define _XTAL_FREQ 48000000

// PIC18F4550 Configuration Bit Settings
// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HSPLL_HS // Oscillator Selection bits (Internal oscillator, XT used by USB (INTXT))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
int contador = 0;
int contador2 = 0;
void ConfigInit(){
    //Funcion para la configuracion del sistema
    
    //***I/O ports***
    TRISB = 0;
    LATB = 0;
    
   //***TMR0***
    T0CON = 0b11000101;
    TMR0 = 68;
    //Habilita las interrupciones por desbordamieto
    INTCONbits.TMR0IE = 1;
    //Borra la bandera por el desbordamiento
    INTCONbits.TMR0IF = 0;
    
    //***TMR1***    
    T1CON = 0b10111001;
    TMR1H = 0xFA;
    TMR1L = 0x24;
    //Habilita las interrupciones por desbordamiento
    PIE1bits.TMR1IE = 1;
    //Borra la bandera por desbordamiento
    PIR1bits.TMR1IF = 0;
    
    //Habilita las prioridades en las interripciones
    RCONbits.IPEN = 1;
    //Activa las interrupciones generales de alta prioridad
    INTCONbits.GIEH = 1;
    //Activa las interrupciones generales de baja prioridad
    INTCONbits.GIEL = 1;
    //Activa las interrupciones perifericas
    INTCONbits.PEIE = 1;
    //Indica que la interrupcion del TMR0 es de alta prioridad
    INTCON2bits.TMR0IP = 1;
    //Indica que la interrupcion del TMR1 es de baja prioridad
    IPR1bits.TMR1IP = 0;
    
    
    
}
void led1(){
    TMR0IF = 0;
    contador++;
    TMR0 = 68;
    if(contador >= 100){
        LATBbits.LATB0 =! LATBbits.LATB0;
        contador = 0;
    }
}
void led2(){
    TMR1IF = 0;
    contador2++;
    TMR1H = 0xFA;
    TMR1L = 0x24;
    if(contador2 >= 10){
        LATBbits.LATB1 =! LATBbits.LATB1;
        __delay_ms(1000);
        contador2 = 0;
    }
}
void interrupt HighISR(){
    if(TMR0IF) led1();
    
}

void interrupt low_priority LowISR(){
    if(TMR1IF) led2();
    
}

void main(void) {
    ConfigInit();
    while(1){
        
    }
    return;
}
