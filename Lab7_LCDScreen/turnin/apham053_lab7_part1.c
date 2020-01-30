/*	Author: apham053
 *  Partner(s) Name: Steven Rodriguez
 *	Lab Section:
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
   
volatile unsigned char TimerFlag = 0; 

unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0; 

void TimerOn() {
  TCCR1B = 0x0B;
  OCR1A = 125;
  TIMSK1 = 0x02;
  TCNT1 = 0;
  _avr_timer_cntcurr = _avr_timer_M;
  SREG |= 0x80;
}

void TimerOff() {
  TCCR1B = 0x00;
}

void TimerISR() {        
  TimerFlag = 1;
}  

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--; 
	if (_avr_timer_cntcurr == 0) { 
		TimerISR(); 
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
 
unsigned char C = 0x07;        
#define A0 (~PINA & 0x01)  
#define A1 (~PINA & 0x02)  

enum States { Start, Wait, Add, Sub, Reset, Release} State;

void tick() {
    switch(State) {
        case Start:
	    C = 0x07;       
	    State = Wait; 	
	    break;
	case Wait: 
		if (A0 && !A1) {
			State = Add;
		}
		else if (!A0 && A1) {
			State = Sub;
		}
		else if (A0 && A1) {
			State = Reset;
		}
		else {
			State = Wait;
		}
	    break;
	case Add:   
		State = Release;
	    break;
	case Sub:
		State = Release;
            break;
	case Reset:
		State = Release;
	    break;
	case Release:
		if (!A0 && !A1) {
			State = Wait;
		}
		else if (A0 && A1) {
			State = Reset;
		}
		else if (A0 && !A1) {
			State = Add;
		}
		else if (!A0 && A1) {
                        State = Sub;
                }
		else { 
			State = Release;
		}
	        break;
    	defau/*	Author: apham053
 *  Partner(s) Name: Steven Rodriguez
 *	Lab Section:
 *	Assignment: Lab #7  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
   
volatile unsigned char TimerFlag = 0;  //

unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0; 

void TimerOn() {
  TCCR1B = 0x0B;
  OCR1A = 125;
  TIMSK1 = 0x02;
  TCNT1 = 0;
  _avr_timer_cntcurr = _avr_timer_M;
  SREG |= 0x80;
}

void TimerOff() {
  TCCR1B = 0x00;
}

void TimerISR() {        //
  TimerFlag = 1;
}  

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--; 
	if (_avr_timer_cntcurr == 0) { 
		TimerISR(); 
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
 

    enum States { Start, blink1, blink2, blink3, wait } State;
    unsigned char C = 0x00; 
    unsigned char score = 0x05;
    #define A0 (PINA & 0x01)
    
    void tick() {
	switch(State) {
	    case Start:
		C = 0x00;
		State = blink1;
		break;
	    case blink1:
		C = 0x01; 
		State = A0 ? wait : blink2;
		break;
	    case blink2:
		C = 0x02;
		State = A0 ? wait : blink3;
		break;
	    case blink3: 
		C = 0x04;
		State = A0 ? wait : blink1;
		break;
	    case wait:
	    score = score + 1;
	    if (score == 9) {
			LCD_DisplayString(1, "Victory!");
		}
		else {
	    LCD_WriteData(score + '0');
	    } 	
		State = A0 ? blink1 : wait; 
		break;
	    default: 
		State = Start;
		break;
   	}

	switch(State) {
	    case Start:
		break;
	    case blink1:
                break;
	    case blink2:
                break;
	    case blink3:
                break;
	    case wait:
		break;
	    default:
		break;
	}
	
	PORTB = C;
    }

int main (void) {
    DDRA = 0x00;
    DDRB = 0xFF;
    DDRD = 0xFF;
    PORTA = 0xFF;
    PORTB = 0x00;
    PORTD = 0x00;
    C = 0x00; 
    State = Start;
    TimerSet(300); 
    TimerOn();	
    LCD_init();
    LCD_Cursor(1);    
    
    while(1) {
	tick();
	while(!TimerFlag) {}
	    TimerFlag = 0;	
    }	   
    return 1;
}
lt:
		State = Start;
		break;
    }
    
    switch(State) {
	case Start:
	    break;
	case Wait:
	    break;
	case Add:
	    if (C < 0x09) {
                C = C + 1;
            }
	    else {
                C = 0x09;
            }
            break;
	case Sub:
	    if (C > 0x00) {
		C = C - 1;
	    }
	    else {
		C = 0x00;
	    }
            break;
	case Reset:
	    C = 0x00;
            break;
        case Release:
		break;
	default:
	    break;	    
    }    
}   

int main (void) {
    DDRA = 0x00;
    DDRC = 0xFF;
    DDRD = 0xFF;
    PORTA = 0xFF;
    PORTC = 0x00;
    PORTD = 0x00;
    C = 0x07; 
    State = Start;
    TimerSet(1000); 
    TimerOn();	    
    LCD_init();
    LCD_Cursor(1);
    
    while(1) {
	tick();
	while(!TimerFlag) {}
	    TimerFlag = 0;
	    //LCD_ClearScreen();
	    PORTC = C;
	    LCD_WriteData(C + '0');	
    }	   
    return 1;
}
