// Fast_PWM_Mode.c

// LED on PD5 (pin 11), on all the time
// LED on PD6/OC0A (pin 12), PWMed

#ifndef F_CPU					// if F_CPU was not defined in Project -> Properties
#define F_CPU 1000000UL			// define it now as 1 GHz unsigned long
#endif

#include <avr/io.h>				// this is always included in AVR programs

///////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {
	
	DDRD |= (1 << PD6) | (1 << PD5);			// set PD6/OC0A (pin 12) and PD5 (pin 11) for output
	
	/*
	TCCR0A - Timer/Counter 0 Control Register A
	
	bit           7         6         5         4        3       2        1        0
	name        COM0A1    COM0A0    COM0B1    COM0B0     -       -      WGM01    WGM00
	set to        1         0         0         0        0       0        1        1
	
	COM0A1 = 1    when Timer/Counter 0 (TCNT0) rolls over, set pin OC0A to high
	COM0A0 = 0    when Timer/Counter 0 (TCNT0) equals OCR0A, set pin OC0A to low
	
	COM0B1 = 0    normal port operation, OC0B disconnected
	COM0B0 = 0
	
	bit 3 = 0
	bit 2 = 0
	
	WGM01 = 1     Fast PWM mode, also see TCCR0B
	WGM00 = 1
	*/
	TCCR0A = 0b10000011;
	
	/*
	TCCR0B - Timer/Counter 0 Control Register B
	
	bit           7          6        5       4         3         2         1        0
	name        FOC0A      FOC0B      -       -       WGM02      CS02      CS01     CS00
	set to        0          0        0       0         0         0         0        1
	
	FOC0A = 0     not used in PWM mode
	FOC0B = 0
	
	bit 5 = 0
	bit 4 = 0
	
	WGM02 = 0     Fast PWM mode, also see TCCR0A
	
	CS02 = 0
	CS01 = 0      no prescaling
	CS00 = 1
	*/
	TCCR0B = 0b00000001;
	
	PORTD |= (1 << PD5);		// turn on PD5 (pin 11) full bright
	
	OCR0A = 0b10000000;			// PWM PD6/OC0A (pin 12) LED on at 1/2 brightness
	
	while (1) {	}
	
	return(0);					// should never get here, this is to prevent a compiler warning
}


