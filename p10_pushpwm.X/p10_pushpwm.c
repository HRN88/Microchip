/*
 * File:   p10_pushpwm.c
 * Author: Koppernikus
 *
 * Se realiza el control de brillo de un LED, se utiliza el PWM del modulo CCP2
 * se utiliza una frecuencia de 3.0KHz, y se varia el DC por medio de un boton 
 * conectado en la interrupcion INT0 utilizando la llamada a una ISR de alta
 * prioridad.
 * La salida del PWM es en el pin RB3 por lo que se debe cambiar el FUSE CCP2MX
 * al valor OFF
 * Created on 30 de agosto de 2017, 08:03 PM
 */


#define _XTAL_FREQ 48000000
#include <xc.h>
#include <math.h>


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
#pragma config CCP2MX = OFF      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
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

void dectobin(int numero);
int incremento = 0;
int modulo[10];
int msb;
int lsb;
void ConfigInit(){
    //Configuracion inicail del sistema
    
    //****************Configuracion del CCP2
    
    //Valor para una frecuencia de 3.0KHz equivalente a 333.33us de periodo
    PR2 = 0xF9;
    
    /* NOTA: El valor del Duty Cycle se modifica en la interrupcion, en este
     * en este apartado se incluira un valor por defecto del 50%, que equivale a
     * 166.66us
     */
    //Valor precargado para un Duty Cycle de 50%
    CCPR2L = 0;
    CCP2CON = 0b00001100;
    
    //************Configuracion para el Timer 2
    //Se configura el prescaler a 16 y se inicia el Timer2
    T2CON = 0b00000111;
    
    /* Los pines de salida para el PWM por el CCP2 son: 36:RB3 y 16:RC1
     * ambos estan multiplexados, y es necesario que esten configurados como 
     * salida
     */
    TRISBbits.RB3 = 0;
    LATBbits.LB3 = 0;
    
    TRISBbits.RB1 = 0;
    LATBbits.LB1 = 0;
    
    TRISBbits.RB0 = 1;
    LATBbits.LB0 = 0;
    
    
    /*El pin de interrupcion INT0(RB0) debe estar como digital*/
    
    ADCON1 |= 0x0F;    
    
    
    //****************Configuracion de interrupciones****************
    
    //Se habilita la Interrupcion INT0
    INT0IE = 1;
    //Se limpia el flag de interrupcion
    INT0IF = 0;
    //Se habilitan las interrupciones globales
    GIE = 1;
    //Se habilitan las interrupciones de perifericos
    PEIE = 1;
    //Se configura interrupcion Rising edge
    INTCON2bits.INTEDG0 = 1;    
    
}

void boton(){
    //Al dispararse la interrupcion, la variable contador se incrementa, mientras
    //sea menor al valor maximo de un Duty Cycle de 100%, manda a llamar a dectobin
    
    if(incremento <= 1000){
        incremento +=10;
        dectobin(incremento);
        
        CCPR2L = incremento;
        //CCP2CON = CCP2CON | lsb;
    }
    else{
        incremento = 0;
    }
    
    LATBbits.LB1 =! LATBbits.LB1;
    __delay_ms(250);
    INT0IF = 0;
}

void interrupt high_isr(){
    if(INT0IF) boton();
}
void main(void) {
    ConfigInit();
    while(1){
        
    }
    return;
}


void dectobin(int numero){
    //Funcion que recive un numero entero como argumento, y lo convierte a binario,
    //para despues separar en 1 byte la parte MSB, y en otros dos bits la parte LSB
       
    
    for(int i = 0; i <= 9; i++){
	    modulo[i] = numero % 2;
	    numero = numero / 2;
	    if(i <= 2){
	        lsb += pow(2,i) * modulo[i];
	    }
	    else{
	         msb += pow(2,i) * modulo[i];
	    }
	}
    
    
}