#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "encoder.h"
#include "thermostat.h"

//ISR Global variables
volatile unsigned char changed;  // Flag for state change
volatile unsigned char count; //keep the low count threshold in an int
volatile unsigned char new_state, old_state;
volatile unsigned char a, b;

/*
    initialize_ISR - Initialize the ISR global variables and interrupt
*/
void initialize_ISR(void)
{
	// Initialize DDR and PORT registers and LCD
    PORTB |= (1 << PB3) | (1 << PB4); //pull up resistors for the rotary encoder

	//initialization code for the ISR
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT3) | (1 << PCINT4); 
    sei(); //enable global interrupts
}

ISR(PCINT0_vect)
{
	// Read the input bits and determine A and B
    a = PINB & (1 << PB3);
    b = PINB & (1 << PB4);

	// For each state, examine the two input bits to see if state
	// has changed, and if so set "new_state" to the new state,
	// and adjust the count value.
	if (old_state == 0) {
		//00
	    // Handle A and B inputs for state 0
	    if(a)
	    {
	    	//clockwise
	    	new_state = 1;
	    	count++;
	    }
	    if(b)
	    {
	    	//counter clockwise
	    	new_state = 2;
	    	count--;
	    }

	}
	else if (old_state == 1) {
		//01

	    // Handle A and B inputs for state 1
	    if(!a)
	    {
	    	//counter clockwise
	    	new_state = 0;
	    	count--;
	    }
	    if(b)
	    {
	    	//clockwise
	    	new_state = 3;
	    	count++;
	    }
	}
	else if (old_state == 2) {
		//10

	    // Handle A and B inputs for state 2
	    if(a)
	    {
	    	//counter clockwise
	    	new_state = 3;
	    	count--;
	    }
	    if(!b)
	    {
	    	//clockwise
	    	new_state = 0;
	    	count++;
	    }

	}
	else {   // old_state = 3
		//11

	    // Handle A and B inputs for state 3
	    if(!b)
	    {
	    	//counter clockwise
	    	new_state = 1;
	    	count--;
	    }
	    if(!a)
	    {
	    	//clockwise
	    	new_state = 2;
	    	count++;
	    }

	}

	// If state changed, update the value of old_state,
	// and set a flag that the state has changed.
	if (new_state != old_state) {
	    changed = 1;
	    old_state = new_state;
	}
}