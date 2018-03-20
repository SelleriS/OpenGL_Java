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

/** P U B L I C   V A R I A B L E S *********************************/
// in order for the variable to be used in other file, it also has to
// be declared as 'extern' in the config.h file
unsigned char ioexp_output;
unsigned char led_output;
unsigned int ldr_1;
unsigned char PWM_duty[1];

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
	 while(timed_to_1ms()) 
     {
         
        //**** put here a reference to one or more FSM's
        //fsm_io();
       fsm_game();
      
        // FSM1_game();
	}
}
/*void main(void) {
		init();				//initialize the system
	 while(timed_to_1ms()) {
         game();
        //**** put here a reference to one or more FSM's
      LED2_OUT=1;
	}
}
*/

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
    TRISAbits.TRISA0 = 0;       //Button matrix address C  output
    TRISAbits.TRISA1 = 0;       //The red led of the indicator output
    TRISAbits.TRISA2 = 0;       // The blue led of the indicator output
    TRISAbits.TRISA3 = 0;       // The green led of the indicator output
 
    
    TRISBbits.TRISB0 = 0;       // led mux address A output
    TRISBbits.TRISB1 = 0;       // buzzer output
    TRISBbits.TRISB2 = 0;       // servo output
    TRISBbits.TRISB3 = 1;       // button mux data input
    TRISBbits.TRISB4 = 0;       // first row of the led matrix  output
    TRISBbits.TRISB5 = 0;       // second row of the led matrix output
    TRISBbits.TRISB6 = 0;       // button matrix address A output
    TRISBbits.TRISB7 = 0;       // button matrix address B output
    
    
    TRISCbits.TRISC1 = 0;       // blue input of led matrix output
    TRISCbits.TRISC2 = 0;       // red input of led matrix  output
    TRISCbits.TRISC6 = 0;       // green input of led matrix  output
    TRISCbits.TRISC7 = 0;       // led mux address B output
    
    PWM_duty[0] = 0;
    ioexp_output = 0x00;
    led_output = 0;
    ldr_1 = 0;

    // FSM1_game_init();
   // fsm_io_init();
    fsm_game_init();
       
#if ENABLE_SERVO == TRUE
    SERVO_init();
#endif
#if ENABLE_ADC == TRUE
    ADC_init();
#endif
#if ENABLE_IOEXP == TRUE
    IOEXP_init();
#endif
#if ENABLE_AUDIO == TRUE
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
