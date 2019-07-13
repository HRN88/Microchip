
//Define 8 or 16 bits
#define T0_8BIT 1
#define T0_6BIT 0

//Define prescaler from 2 to 256
#define PRE2    0b000
#define PRE4    0b001   
#define PRE8    0b010
#define PRE16   0b011
#define PRE32   0b100
#define PRE64   0b101
#define PRE128  0b110
#define PRE256  0b111



void configTIMER0(int mode, int prescaler, int count){
	//Set the timer0
    if(mode){
        T0CONbits.T08BIT = 1;   //Using 8 bit timer
        TMR0 = count;
    }
    else{
        T0CONbits.T08BIT = 0;  //Using 16 bit timer
        TMR0H = 0xFF00 & count;
        TMR0L = 0x00FF & count;
        
    }
    
    T0CONbits.T0CS = 0;         //Using CLKO for clock
    T0CONbits.T0PS = prescaler; //define prescaler
    T0CONbits.PSA = 0;
        
}
void startTIMER0(){
	//Start the timer0
    T0CONbits.TMR0ON = 1; //Enable TIMER0
    
}

void stopTIMER0(){
	//Stop the timer0
    T0CONbits.TMR0ON = 0; //Disable TIMER0
}
void reloadTIMER0(int count){
	//Reload the timer0
    INTCONbits.TMR0IF = 0;
    
    if(T0CONbits.T08BIT){
        T0CONbits.T08BIT = 1;   //Using 8 bit timer
        TMR0 = count;
    }
    else{
        T0CONbits.T08BIT = 0;  //Using 16 bit timer
        TMR0H = 0xFF00 & count;
        TMR0L = 0x00FF & count;
        
    }
    
}