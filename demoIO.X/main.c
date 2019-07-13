/* 
 * File:   main.c
 * Author: Koppernikus
 *
 * Created on 29 de junio de 2018, 08:31 PM
 */


// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC3_PLL4// System Clock Postscaler Selection bits ([Primary Oscillator Src: /3][96 MHz PLL Src: /4])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (XT oscillator, PLL enabled (XTPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

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

#define _XTAL_FREQ 24000000
#include<xc.h>

/*
 * 
 */
#include "Serial.h"
#define INPUT 1
#define OUTPUT 0

#define A0 1
#define A1 2
#define A2 4
#define A3 8
#define A4 16
#define A5 32

#define B0 1
#define B1 2
#define B2 4
#define B3 8
#define B4 16
#define B5 32

#define PA 0
#define PB 1
#define PC 2
#define PD 3
#define PE 4

#define ALL 0xFF

#define HIGH 1
#define LOW 0

void initialSetings(){
   
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
            
}

void pinMode(int port, int selectPin, int mode){
    switch(port){
        case 0:  //For port A
            if(mode){
                TRISA = TRISA | selectPin;
            }
         else{
                TRISA = TRISA & (~selectPin);
                
        }
            break;
            
        case 1: //For port B -----------------------------------
            if(mode){
                TRISB = TRISB | selectPin;
            }
         else{
                TRISB = TRISB & (~selectPin);
         }
            break;
        
        case 2: //For port C --------------------------------------
            if(mode){
                TRISC = TRISC | selectPin;
            }
         else{
                TRISC = TRISC & (~selectPin);
         }
            break;
            
        case 3: //For port D --------------------------------------
            if(mode){
                TRISD = TRISD | selectPin;
            }
         else{
                TRISD = TRISD & (~selectPin);
         }
            break;
            
        case 4: //For port E -------------------------------------
            if(mode){
                TRISE = TRISE | selectPin;
            }
         else{
                TRISE = TRISE & (~selectPin);
         }
            break; 
    }
}
void pinWrite(int port, int selectPin, int value){
    switch(port){
        case 0:  //For port A
            if(value){
                LATA = LATA | selectPin;
            }
         else{
                LATA = LATA & (~selectPin);
                
        }
            break;
            
        case 1: //For port B -----------------------------------
            if(value){
                LATB = LATB | selectPin;
            }
         else{
                LATB = LATB & (~selectPin);
         }
            break;
        
        case 2: //For port C --------------------------------------
            if(value){
                LATC = LATC | selectPin;
            }
         else{
                LATC = LATC & (~selectPin);
         }
            break;
            
        case 3: //For port D --------------------------------------
            if(value){
                LATD = LATD | selectPin;
            }
         else{
                LATD = LATD & (~selectPin);
         }
            break;
            
        case 4: //For port E -------------------------------------
            if(value){
                LATE = LATE | selectPin;
            }
         else{
                LATE = LATE & (~selectPin);
         }
            break; 
    }
}
int pinRead(int port){
    switch(port){
        case 0:
            return LATA;
            break;
    }
      
    
    
}
   
    
    

    
void main(void) {
    initialSetings();
    pinMode(PA, ALL, OUTPUT);
    pinWrite(PA, 0x01, HIGH);

    while(1){
        __delay_ms(500);
        LATA = LATA << 1;
        __delay_ms(500);
        if(pinRead(PA) == 0x08){
            pinWrite(PA, 0x01, HIGH);
        }
        
        
    }

}

