/********************************************
 *
 *  Name: Penelope Hocking
 *  Email: hocking@usc.edu	
 *  Section: Friday 2pm
 *  Assignment: Lab 7 - Rotary Encoder
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "lcd.h"

void variable_delay_us(int);
void play_note(unsigned short);

//ISR Global variables
volatile unsigned char changed;  // Flag for state change
volatile int count;		// Count to display
volatile unsigned char new_state, old_state;
volatile unsigned char a, b;

// Frequencies for natural notes from middle C (C4)
// up one octave to C5.
unsigned short frequency[8] =
    { 262, 294, 330, 349, 392, 440, 494, 523 };

int main(void) {
    count = 0;		// Count to display
    changed = 0;
    char buffer[12];
    unsigned short freq = frequency[0];

    // Initialize DDR and PORT registers and LCD
    // DDRB |= (1 << PB4); //output for the speaker
    PORTC |= (1 << PC1) | (1 << PC5); //pull up resistors for the rotary encoder

    //initialization code for the ISR
    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT9) | (1 << PCINT13); 
    sei(); //enable global interrupts

    // Write a spash screen to the LCD
    lcd_init(); //initialize the lcd
    lcd_writecommand(1); //clear the lcd

    //splash screen
    lcd_moveto(0,4);
    lcd_stringout("Penelope");
    lcd_moveto(1,4);
    lcd_stringout("Lab 7");
    _delay_ms(1000);
    lcd_writecommand(1);

    // Read the A and B inputs to determine the intial state
    // Warning: Do NOT read A and B separately.  You should read BOTH inputs
    // at the same time, then determine the A and B values from that value.   
    a = PINC & (1 << PC1);
    b = PINC & (1 << PC5); 

    if (!b && !a)
	old_state = 0;
    else if (!b && a)
	old_state = 1;
    else if (b && !a)
	old_state = 2;
    else
	old_state = 3;

    new_state = old_state;

    while (1) {                 // Loop forever

        if (changed) { // Did state change?
	   		changed = 0;        // Reset changed flag

		    // Output count to LCD
		    lcd_writecommand(1);
		    lcd_moveto(0,0);
		    snprintf(buffer, 6, "%d", count);
		    lcd_stringout(buffer);

		    // Do we play a note?
		    if ((count % 8) == 0) {
			// Determine which note (0-7) to play	
			// Find the frequency of the note
		   	int c = abs(count);
		    if(c % 64 == 0)
		    {//0
		    	freq = frequency[0];
		    }
		    if(c % 64 == 8)
		    {//1
		    	freq = frequency[1];
		    }
		    if(c % 64 == 16)
		    {//2
		    	freq = frequency[2];
		    }
		    if(c % 64 == 24)
		    {//3
		    	freq = frequency[3];
		    }
		    if(c % 64 == 32)
		    {//4
		    	freq = frequency[4];
		    }
		    if(c % 64 == 40)
		    {//5
		    	freq = frequency[5];
		    }
		    if(c % 64 == 48)
		    {//6
		    	freq = frequency[6];
		    }
		    if(c % 64 == 56)
		    {//7
		    	freq = frequency[7];
		    }

			// Call play_note and pass it the frequency
			play_note(freq);
	    }
        }
    }
}

/*
  Play a tone at the frequency specified for one second
*/
void play_note(unsigned short freq)
{
    unsigned long period;

    period = 1000000 / freq;      // Period of note in microseconds

    while (freq--) {
	// Make PB4 high
    PORTB |= (1 << PB4);

	// Use variable_delay_us to delay for half the period
	variable_delay_us((period/2));

	// Make PB4 low
	PORTB &= ~(1<<PB4);

	// Delay for half the period again
	variable_delay_us((period/2));

    }
}

/*
    variable_delay_us - Delay a variable number of microseconds
*/
void variable_delay_us(int delay)
{
    int i = (delay + 5) / 10;

    while (i--)
        _delay_us(10);
}

ISR(PCINT1_vect)
{
	// Read the input bits and determine A and B
    a = PINC & (1 << PC1);
    b = PINC & (1 << PC5);

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