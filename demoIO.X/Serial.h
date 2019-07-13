/*This library is for USART control*/

#define SYNC_ 1
#define ASYNC_ 0
#define BRG_16 1
#define BRG_8 0

void startSerial(int baudrate, long FOSC, int mode, int brg_16){
    int n;
    if(!mode){
        TXSTAbits.SYNC = 0;     //For synchronous mode
    }
    else{
        TXSTAbits.SYNC = 1;     //For asynchronous mode
    }  
    
   //Define RC6 like output TX and RC7 like input
    RCSTAbits.SPEN = 1;     //Serial port enable bit
    TRISCbits.RC6 = 0;      //Output Tx
    TRISCbits.RC7 = 1;      //Input Rx
    
    RCSTAbits.CREN = 1;     //Enabling reciver
    TXSTAbits.TXEN = 1;     //enabling transmission
    
    
    //These bits configure Rx with interruption
    PIE1bits.RCIE = 1;      //Enable Rx interrupt
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;    //Enable peripheral interrupt
    TXSTAbits.BRGH = 1;     //For high speed
  
     
    if(brg_16){
        //No funciona correctamente
        BAUDCONbits.BRG16 = 1;
        n = (int)((FOSC / baudrate) / 4) - 1;
        SPBRG = (int)(n & 0x00FF);
        SPBRGH = (int)(n & 0xFF00);
    }
    else{
        //Si funciona correctamente
        BAUDCONbits.BRG16 = 0;
        n = (int)((FOSC / baudrate) / 16) - 1;
        SPBRG = (int)(n & 0x00FF);
    }
   
    
    
}

void sendDataSerial(char c){
    /*Send a character*/
    TXREG = c;
    while(!TXSTAbits.TRMT);    
}

void printSerial(char String[]){
    /*Print a string*/
    char *p;
    p = String;
    while(*p != '\0'){
        sendDataSerial(*p);
        p++;
    }    
}

void printSerialnl(char String[]){
    /*Print a string in a new line*/
    char *p;
    p = String;
    while(*p != '\0'){
        sendDataSerial(*p);
        p++;
    }   
    sendDataSerial('\n');
    sendDataSerial('\r');
}

void closeSerial(){
    /*Close serial port*/
    RCSTAbits.SPEN = 0; 
    RCSTAbits.CREN = 0;
    TXSTAbits.TXEN = 0;
    PIE1bits.RCIE = 1; 
    
}

char readSerial(){
    //Read Serial with polling
    while(!PIR1bits.RCIF);
    return RCREG;
}