/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * Processor:       PIC18F2550
 * Compiler:        XC8 1.35+
 * Author:          Jeroen Van Aken
 * Updated:         17/02/2016
 ********************************************************************/

/** I N C L U D E S *************************************************/
#include "config.h"

/** D E F I N E S ***************************************************/
#define PUSHED 0
#define _XTAL_FREQ 20000000

/** P U B L I C   V A R I A B L E S *********************************/
// in order for the variable to be used in other file, it also has to
// be declared as 'extern' in the config.h file
unsigned char led1_output;

/** P R I V A T E   V A R I A B L E S *******************************/

/** P R I V A T E   P R O T O T Y P E S *****************************/
static void init(void);
static void OpenTimer0(unsigned char intEnable);
static unsigned char timed_to_1ms(void);

/********************************************************************/
/** P U B L I C   D E C L A R A T I O N S ***************************/
/********************************************************************
 * Function:        void main(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        Main program entry point
 ********************************************************************/
void main(void) {
	init();						//initialize the system
    int x;
    //int timer;
    int a;
	 while(timed_to_1ms()) {
         //timer++;
        //**** put here a reference to one or more FSM's
        fsm_io();
        if (PRG_BUTTON == PUSHED){
            x++;
            
            for(int i=0; i<x; i++){
                LED2_OUT = TRUE;
                __delay_ms(100); 
                LED2_OUT = FALSE;
                __delay_ms(100); 
            }
        }
        
        
        
	}
}

/********************************************************************/
/** P R I V A T E   D E C L A R A T I O N S *************************/
/********************************************************************
 * Function:        void init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        Init is a centralize initialization routine.              
 *                  It will initialze all IO and variables, also the
 *                  hardware_init() for the hardware functions should
 *                  be called here.              
 ********************************************************************/
static void init(void) {
    // Reset all IO
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    ADCON1 = 0x0F;      //set all AD to digital
    OpenTimer0(FALSE);
    
	// Configure I/O as input (1) or output (0)
    TRISAbits.TRISA0 = 0;       // RA0 first analog input or digital IO
    TRISAbits.TRISA1 = 0;       // RA1 second analog input or digital IO
    TRISAbits.TRISA2 = 0;       // RA2 third analog input or digital IO
    TRISAbits.TRISA3 = 0;       // RA3 fourth analog input or digital IO
    TRISAbits.TRISA4 = 0;       // RA4 fifth analog input or digital IO
    TRISAbits.TRISA5 = 0;       // RA5 digital output only
    
    TRISBbits.TRISB0 = 0;       // IO expander CS
    TRISBbits.TRISB1 = 0;       // IO expander clock
    TRISBbits.TRISB2 = 0;       // ...
    TRISBbits.TRISB3 = 0;       // ...
    TRISBbits.TRISB4 = 0;       // ...
    TRISBbits.TRISB5 = 0;       // ...
    TRISBbits.TRISB6 = 0;       // ...
    TRISBbits.TRISB7 = 0;       // ...
    
    TRISCbits.TRISC0 = 1;       // Pushbutton on the µC PCB
    TRISCbits.TRISC1 = 0;       // LED2 on the µC PCB
    TRISCbits.TRISC2 = 0;       // LED1 on the µC PCB
    TRISCbits.TRISC6 = 0;       // ...
    TRISCbits.TRISC7 = 0;       // IO expander data out
    
    led1_output = 0;
    //PWM_duty[0] = 0;

    fsm_io_init();
    fsm_game_init();
       
#if ENABLE_SERVO == TRUE
    SERVO_init();
#endif
#if ENABLE_ADC  == TRUE
    ADC_init();
#endif
#if ENABLE_IOEXP  == TRUE
    IOEXP_init();
#endif
#if ENABLE_AUDIO	== TRUE
    AUDIO_init();
#endif  
}

/********************************************************************
 * Function:        void OpenTimer0(unsigned char intEnable)
 * PreCondition:    None
 * Input:           intEnable: enable Timer0 interrupt
 * Output:          None
 * Overview:        Will initialize Timer0 given the parameters
 ********************************************************************/
static void OpenTimer0(unsigned char intEnable) {
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b101;
    TMR0H = 0;                // Reset Timer0 to 0x0000
    TMR0L = 69;
    
    INTCONbits.TMR0IE = intEnable & 0x01;
    INTCONbits.GIE = (intEnable & 0x01) | INTCONbits.GIE;
    INTCONbits.TMR0IF = 0;      // Clear Timer0 overflow flag
}

/********************************************************************
 * Function:        void timed_to_1ms(void)
 * PreCondition:    OpenTimer0(FALSE)
 * Input:           None
 * Output:          None
 * Overview:        Stays in a while loop, doing NOP until Timer0 
 *                  generates an overflow
 ********************************************************************/
static unsigned char timed_to_1ms(void) {
	while(!INTCONbits.TMR0IF){Nop();};
    TMR0L = 69;     // tuned to 1ms
	INTCONbits.TMR0IF = 0;
    return 1;
}

/********************************************************************
 * Function:        void interrupt_handler(void)
 * PreCondition:    GIE need to be set
 * Input:           None
 * Output:          None
 * Overview:        This routine is called whenever an interrupt 
 *                  condition is  reached
 ********************************************************************/	
void interrupt interrupt_handler(void) {
#if ENABLE_AUDIO == TRUE
    AUDIO_ISR();
#endif
#if ENABLE_SERVO == TRUE
    SERVO_ISR();
#endif
#if ENABLE_ADC == TRUE
    ADC_ISR();
#endif
}
//EOF-------------------------------------------------------------------------
