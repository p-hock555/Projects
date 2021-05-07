/********************************************
 *
 *  Name: Penelope Hocking 
 *  Email: hocking@usc.edu
 *  Section: Friday 2pm
 *  Assignment: Lab 6 - Analog-to-digital conversion
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "lcd.h"
#include "adc.h"

void rand_init(void);

int main(void)
{

    // Initialize the LCD
    lcd_init();
    lcd_writecommand(1);


    // Initialize the ADC
    adc_init();


    // Initialize the random number function
    rand_init();


    // Write splash screen
    lcd_moveto(0,4);
    lcd_stringout("Penelope");
    lcd_moveto(1,4);
    lcd_stringout("Lab 6");
    _delay_ms(1000);

    // Find a random initial position of the 'X'
    lcd_writecommand(1); //clear the screen 
    int x = rand() % 16; //store a value between 0 and 15
    lcd_moveto(0, x); 
    lcd_stringout("X"); //print an X in this random position  
    int caret = 0; 
    lcd_moveto(1, caret);
    lcd_stringout("^");
    int time = 0;
    unsigned char pm;
    
    while (1) {                 // Loop forever
	// Check for button pressed
         // If pressed, move 'X' to new position
        if((adc_sample(0) >= 0) && (adc_sample(0) <= 5)) {
            if(15 > x) {
                _delay_ms(5); //debounce
                while(adc_sample(0) <= 5 && adc_sample(0) >= 0) {};
                _delay_ms(5);
                lcd_moveto(0, x++); // move to the next position X needs to be 
                lcd_stringout(" "); //remove the 'X' from the previous position
                lcd_moveto(0, x);
                lcd_stringout("X");
                _delay_ms(100);
            }
        } 
        else if (adc_sample(0) <= 160 && adc_sample(0) >= 150) {
            if(x > 0) {
                _delay_ms(5); //debounce
                while(adc_sample(0) <= 160 && adc_sample(0) >= 150) {};
                _delay_ms(5);
                //Erase the X
                lcd_moveto(0, x--); //move backward 
                lcd_stringout(" "); //remove the X from the position it is currrently in
                //Move the position 
                lcd_moveto(0, x);
                lcd_stringout("X"); //update X
                _delay_ms(100);
            }
        }
        pm = adc_sample(3) * 15/255.0;
        //move the caret 
        if(caret != pm) {
            lcd_moveto(1, caret);
            lcd_stringout(" ");
            lcd_moveto(1, pm);
            lcd_stringout("^");
            caret = pm;
        }
        _delay_ms(10);
        
        //Win if the caret and x are aligned for 2 sec
        if(x == caret) {
            //update for time to know when 2 seconds have passed 
            time++;
            if(time == 200) {
                lcd_writecommand(1);
                lcd_moveto(0, 0);
                lcd_stringout("You win!"); //when 2 seconds go by output the win screen
                while(1) {};
            }
        }
        else time = 0;
    }

    return 0;   /* never reached */
}

void rand_init()
{
    int seed = 0;
    unsigned char i, j, x;

    // Build a 15-bit number from the LSBs of an ADC
    // conversion of the channels 1-5, 3 times each
    for (i = 0; i < 3; i++) {
	for (j = 1; j < 6; j++) {
	    x = adc_sample(j);
	    x &= 1;	// Get the LSB of the result
	    seed = (seed << 1) + x; // Build up the 15-bit result
	}
    }
    srand(seed);	// Seed the rand function
}
