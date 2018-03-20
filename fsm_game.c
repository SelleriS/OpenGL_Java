/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * Processor:       PIC18F2550
 * Compiler:        XC8 1.35+
 * Author:          Jeroen Van Aken
 * Updated:         24/02/2017
 ********************************************************************/
/** I N C L U D E S *************************************************/
#include "config.h"
#include <stdlib.h>

/** D E F I N E S ***************************************************/
#define PUSHED 0

/** P R I V A T E   V A R I A B L E S *******************************/
static unsigned char audio_on_counter;
static unsigned char audio_off_counter;
static unsigned int random_counter;
static unsigned int led_on_counter;
static unsigned int led_off_counter;
static unsigned int led_turn_on;
static unsigned int led_time;
static unsigned int set_time;
static unsigned int button_push;;
static enum {FSM_IDLE, 
            FSM_COUNTDOWN, 
            FSM_GAMEMODE_1, 
            FSM_GAMEMODE_2, 
            FSM_RIGHT,
            FSM_WON,
            FSM_WRONG,
            FSM_OFF
            } current_state;
/*static enum {FSM_IDLE, 
            FSM_IDLE_SOUND, 
            FSM_WAIT_RANDOM, 
            FSM_LED_ON, 
            FSM_BTN_START_EDGE,
            FSM_BTN_GAME_EDGE
            } current_state;
         */   
/********************************************************************
 * Function:        void fsm_game_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        This init sets the start state for this FSM and
 *                  may initialize some counters          
 ********************************************************************/
void fsm_game_init(void) {
	//current_state = FSM_IDLE;
	//audio_on_counter = 0;
	//audio_off_counter = 0;   
    
    current_state = FSM_IDLE;
	led_on_counter = 0;
	led_off_counter = 0;   
}

/********************************************************************
 * Function:        void fsm_game(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        An implementation for a simple reaction game
 ********************************************************************/
void fsm_game(void) {
    
    
   /* switch (current_state) { 
        case FSM_IDLE :
        // *** outputs ***

            led_on_counter = 0;
            led_off_counter=0;
            led_time=0;
            set_time=0;
            LED2_OUT=0;
        // *** transitions ***
            if (PRG_BUTTON==1) current_state = FSM_PLUSTIME;
           
            break;

        case FSM_PLUSTIME
        :
        // *** outputs ***
            
        // *** transitions ***
            if (PRG_BUTTON==0) {set_time++;current_state = FSM_TURNON;}
           
            break;

        case FSM_TURNON :
        // *** outputs ***
            led_on_counter++;
            led_off_counter=0;
            LED2_OUT=1;
        // *** transitions ***
            if (led_on_counter>300) current_state = FSM_TURNOFF;
            break;

        case FSM_TURNOFF : 
        // *** outputs ***
            led_on_counter=0;
            led_off_counter++;
            LED2_OUT=0;
        // *** transitions ***
            if (led_off_counter>300) current_state = FSM_MINUS;
            break;

        case FSM_MINUS : 
        // *** outputs ***
            led_time++;
        // *** transitions ***
            if (led_time<set_time) current_state = FSM_TURNON;
            if (led_time==set_time) current_state = FSM_SILENCE;
            break;
            
        case FSM_SILENCE : 
        // *** outputs ***
            led_time=0;
        // *** transitions ***
           // if (PRG_BUTTON != PUSHED) current_state = FSM_IDLE_SOUND;
            if (PRG_BUTTON==1) current_state = FSM_PLUSTIME;
            break;

        default:
            current_state = FSM_IDLE;
            break;
    }
    
    */
    
  /*  switch (current_state) { 
        case FSM_IDLE :
        // *** outputs ***
            AUDIO_stop();
            led_output = 0;
            ioexp_output = 0xAA;
            audio_on_counter = 0;
            audio_off_counter++;
            random_counter++;
            servo_setpoint[0] = 5;
        // *** transitions ***
            if (audio_off_counter >= 250) current_state = FSM_IDLE_SOUND;
            if (PRG_BUTTON == PUSHED) current_state = FSM_BTN_START_EDGE;
            break;

        case FSM_IDLE_SOUND :
        // *** outputs ***
            AUDIO_play(D1);
            led_output = 0;
            ioexp_output =0x55;
            audio_off_counter = 0;
            audio_on_counter++;
            random_counter++;
            servo_setpoint[0] = 5;
        // *** transitions ***
            if (audio_on_counter >= 250) current_state = FSM_IDLE;
            if (PRG_BUTTON == PUSHED) current_state = FSM_BTN_START_EDGE;
            break;

        case FSM_WAIT_RANDOM :
        // *** outputs ***
            AUDIO_stop();
            led_output = 0;
            random_counter = random_counter - 8;
        // *** transitions ***
            if (random_counter < 10) current_state = FSM_LED_ON;
            break;

        case FSM_LED_ON : 
        // *** outputs ***
            AUDIO_play(F1);
            led_output = 1;
            servo_setpoint[0] = 30;
        // *** transitions ***
            if (PRG_BUTTON == PUSHED) current_state = FSM_BTN_GAME_EDGE;
            break;

        case FSM_BTN_START_EDGE : 
        // *** outputs ***
            srand(random_counter);
            ioexp_output = 0x00;
            random_counter = rand();
        // *** transitions ***
            if (PRG_BUTTON != PUSHED) current_state = FSM_WAIT_RANDOM;
            break;
            
        case FSM_BTN_GAME_EDGE : 
        // *** outputs ***
        // *** transitions ***
            if (PRG_BUTTON != PUSHED) current_state = FSM_IDLE_SOUND;
            break;

        default:
            current_state = FSM_IDLE;
            break;
    }
    */
}