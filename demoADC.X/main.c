	// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC3_PLL4// System Clock Postscaler Selection bits ([Primary Oscillator Src: /3][96 MHz PLL Src: /4])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
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
#include<stdio.h>
#include"Serial.h"


#define AN0 0b0000
#define AN1 0b0001
#define AN2 0b0010

/*----------------------------Estas son mis funciones para leer ADC Normal
void configADC( ){
    ADCON0 = 0x01; 
    ADCON1 = 0x00;
    ADCON2 = 0b10010010; 
    TRISA = 0xFF;;
    
}
int readADC(int channel){
    ADCON0 = 0x01;
    ADCON0 |= (channel << 2);
    ADCON0bits.GODONE = 1;
    while(ADCON0bits.GODONE);
    return ((ADRESH << 8) + ADRESL);
    
}*/

//-*------------------------------------Estas son mis funciones par ADC con interrupcion sencillo
/*
void configADC(){
    //ADCON0 = 0x01; 
    ADCON1 = 0x00;       //Niveles de referencia y todos los pines como analogicos.   
    ADCON2 = 0b10010010; //Select TADQ = 4
    TRISA = 0xFF;;
    PIE1bits.ADIE = 1;   //Enablilng ADC interrupts
    PIR1bits.ADIF = 0;   //Flag for ADC
    INTCONbits.GIE = 1;  //Enabling global interrupts
    INTCONbits.PEIE = 1; //Enabling pheripheral interrupts
       
}

void readADC(int channel){
    ADCON0 = 0x00;
    ADCON0 |= (channel << 2);
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
   
    
}

void auxRead(){
     printf(" %d", ((ADRESH << 8) + ADRESL));
}


void interrupt ISR(void){
    if(PIR1bits.ADIF == 1){
        auxRead();
        PIR1bits.ADIF = 0;
    }
        
    
}*/
//*************************************Funciones ADC con trigger

void configADC(){
    ADCON1 = 0x00;       //Niveles de referencia y todos los pines como analogicos.   
    ADCON2 = 0b10010010; //Select TADQ = 4
    TRISA = 0xFF;;
    CCP1CON = 0b00001011; //CCP1 is trigger special event
    T1CON = 0b10111001;
    TMR1 = 1;
    
    
}
void main(void){
    startSerial(9600, _XTAL_FREQ, ASYNC_, BRG_8);
   
    printSerialnl("Loading system...");
     
    configADC();
   
    printSerialnl("ADC module started...");
    printSerialnl("Esta es una prueba %d este es otro valor", ADCON2);
     //__delay_ms(200);
    //ADCON0bits.ADON = 1;
    //ADCON0bits.GO = 1;
    //int res = 0;
    readADC(AN0);
    while(1){
        
        //__delay_ms(500);
        
    }
}
