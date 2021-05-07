/********************************************
 *
 *  Name: Penelope Hocking 
 *  Email: hocking@usc.edu
 *  Section: Friday 2pm
 *  Assignment: Lab 8 - Digital Stopwatch
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

#include "lcd.h"
#include "adc.h"

void init_timer1(unsigned short m);
volatile char flag = 0;
volatile int tenths = 0;
volatile int tens = 0;
volatile int ones = 0;
volatile int prescalar = 0;

int main(void)
{

    // Initialize the LCD
    lcd_init();
    lcd_writecommand(1);


    // Initialize the ADC
    adc_init();

    // Write splash screen
    lcd_moveto(0,4);
    lcd_stringout("Penelope");
    lcd_moveto(1,4);
    lcd_stringout("Lab 8");
    _delay_ms(2000);

    lcd_writecommand(1); //clear the screen 
    int state = 0; // 0=stop 1=started 2=lapped
    sei(); //enable global interrupts 
    char buf[12];
    
    snprintf(buf, 5, "%d%d.%d", tens, ones, tenths);
    lcd_moveto(0,0);
    lcd_stringout(buf);
    unsigned char sample;
    init_timer1(25000); //start the timer

    while (1) { // Loop forever
        sample = adc_sample(0);
        _delay_ms(150); //debounce

        //check to see if we can display a new time
        if(flag)
        {
            //use variables that were set by the ISR
            snprintf(buf, 5, "%d%d.%d", tens, ones, tenths);
            lcd_moveto(0,0);
            lcd_stringout(buf);
            flag = 0;
        }
        
        //check to see if up button pressed 
        if(sample >= 45 && sample <= 65)
        {
            //up button pressed
            if(state == 0)
            {
                prescalar = 1;
                state = 1; // change the state
            }
            else if(state == 1)
            {
                prescalar = 0; //stop counting
                state = 0; //set to stopped state
            }
            else if(state == 2)
            {
                prescalar = 1; //start the count again
                state = 1; //now in the start state
            }
            _delay_ms(150);
        }

        if((sample >= 90 && sample <= 110)){
            //down button was pressed
            if(state == 0)
            {
                //reset all values to 0 to restart the timer from the beginning
                tens = 0;
                ones = 0;
                tenths = 0;
                snprintf(buf, 5, "%d%d.%d", tens, ones, tenths);
                lcd_moveto(0,0);
                lcd_stringout(buf);

            }
            else if(state == 1)
            {
                prescalar = 0; //stop the time, but keep the timer running internally
                state = 2; //now in the lapped state
            }
            else if(state == 2)
            {
                prescalar = 1; //start the count again
                state = 1; //now in the start state
            }
            _delay_ms(150);
        }

    }
    return 0;   /* never reached */
}

void init_timer1(unsigned short m)
{
    TCCR1B |= (1 << WGM12);
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = m;
    TCCR1B |= (1 << CS11) | (1 << CS10);
}

ISR(TIMER1_COMPA_vect){
    if(prescalar)
    {
        flag = 1;
        tenths++;
        if(tenths > 9){
            tenths = 0;
            ones++;
        }
        if(ones > 9){
            ones = 0;
            tens++;
        }
        if(tens > 5){
            tens = 0;
            ones = 0;
            tenths = 0;
        }
    }
}