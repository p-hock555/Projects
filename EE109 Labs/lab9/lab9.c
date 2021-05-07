/********************************************
 *
 *  Name: Penelope Hocking
 *  Email: hocking@usc.edu 
 *  Section: Friday 2pm
 *  Assignment: Lab 9 - Serial Communications
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h> 

#include "lcd.h"
#include "adc.h"
#include "check9.h"

// Serial communications functions and variables
void serial_init(unsigned short);
void serial_stringout(char *);
void serial_txchar(char);

#define FOSC 16000000           // Clock frequency
#define BAUD 9600               // Baud rate used
#define MYUBRR (FOSC/16/BAUD-1) // Value for UBRR0 register

// ADC functions and variables
volatile int flag = 0;
volatile char str[17];
volatile int i = 0;

#define ADC_CHAN 0              // Buttons use ADC channel 0

char *messages[] = {
    "Hello           ",
    "How are you?    ",
    // Add more messgages
    "what's up?      ",
    "See you soon.   ",
    "Talk to you soon",
    "Where are you?  ",
    "On my way!      ",
    "Good morning!   ",
    "Have a good day ",
    "See you in class",
    "Are you coming? ",

};

int main(void) {

    // Initialize the LCD, ADC and serial modules
    lcd_init(); //initialize the LCD
    lcd_writecommand(1); //clear the screen
    adc_init(); //initialize the ADC
    serial_init(MYUBRR); //initialize serial module
    
    // Initialize the baud rate checker
    check9_init();
    
    // Enable interrupts
    UCSR0B |= (1 << RXCIE0);    // Enable receiver interrupts

    sei();                      // Enable interrupts


    // Show the splash screen
    lcd_moveto(0,4);
    lcd_stringout("Penelope");
    lcd_moveto(1,4);
    lcd_stringout("Lab 8");
    _delay_ms(2000);
    lcd_writecommand(1); //clear the screen

    int i = 0; //to see where we are in the messages array
    while (1) {                 // Loop forever

	// Get an ADC sample to read buttons
        unsigned char sample = adc_sample(ADC_CHAN);
        _delay_ms(150); //debounce

        // Up button pressed?
        if(sample >= 45 && sample <= 65)
        {
            i--;
            if(i < 0)
            {
                i = 10;
            }
            lcd_moveto(0,0);
            lcd_stringout(messages[i]);  //display the appropriate message on the screen, dont transmit 
            _delay_ms(150); //debouunce
        }


        // Down button pressed?
        else if(sample >= 95 && sample <= 110)
        {
            i++;
            if(i > 10)
            {
                i = 0;
            }
            lcd_moveto(0,0);
            lcd_stringout(messages[i]); //display the appropriate message on the screen, dont transmit
            _delay_ms(150); //debounce
        }


        // Select button pressed?
        else if(sample >= 200 && sample <= 215)
        {
            serial_stringout(messages[i]); //transmit data 
            _delay_ms(150); //debounce
        }
        

        // Message received from remote device?
        if(flag)
        {   
            lcd_moveto(1,0);
            lcd_stringout(str); //print the string that was transmitted, and set by the ISR
            flag = 0;
        }

    }
}

/* ----------------------------------------------------------------------- */

void serial_init(unsigned short ubrr_value)
{

    // Set up USART0 registers
    UBRR0 = ubrr_value;             // Set baud rate
    UCSR0B |= (1 << TXEN0 | 1 << RXEN0);  // Enable RX and TX
    UCSR0C = (3 << UCSZ00);               // Async., no parity,
                                          // 1 stop bit, 8 data bits
    
    // Enable tri-state buffer
    DDRD |= (1<<PD3);
    PORTD &= ~(1<<PD3);
}

void serial_txchar(char ch)
{
    // Wait for transmitter data register empty
    while ((UCSR0A & (1<<UDRE0)) == 0);
    UDR0 = ch;
}

void serial_stringout(char *s)
{
    // Call serial_txchar in loop to send a string
    int i = 0;
    while (s[i] != '\0') {    // Loop until next charater is NULL byte
        serial_txchar(s[i]);  // Send the character
        i++;
    }
}

ISR(USART_RX_vect)
    {
        char ch;

        ch = UDR0;                  // Get the received charater

        // Store in buffer
        str[i] = ch;
        i++;

        if(i == 16)
        {
            i = 0;
            // If message complete, set flag
            flag = 1;
        }
        
    }
