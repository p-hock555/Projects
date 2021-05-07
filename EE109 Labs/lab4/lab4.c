/********************************************
*
*  Name: Penelope Hocking
*  Email:hocking@usc.edu
*  Section: Friday 2pm
*  Assignment: Lab 4 - Up/Down counter on LCD display
*
********************************************/

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

int main(void) {

        // Setup DDR and PORT bits for the 2 input buttons
        // as necessary
        DDRC |= 0x00; //initally all inputs nit necessary
        PORTC |= (1 << PC2) | (1 << PC4); //initialize PC2 and PC4 to be pull-up resistors 

        // Initialize the LCD
        lcd_init();
        lcd_writecommand(1);

        // Use a state machine approach to organize your code
        //   - Declare and initialize a variable to 
        //     track what state you are in
        int a, b;
        char cnt = 0;
        char i = 0;
        char currst = 0; // 0 for up; 1 for down
        
            while (1) {               // Loop forever
                i++;
                if(i == 25)
                {
                    if(currst == 0){
                        //up state
                        if(cnt == 9){
                            cnt = 0;
                        }
                        else{
                            cnt++;
                        }
                    }
                    else{
                        //down state
                        if(cnt == 0){
                            cnt = 9;
                        }
                        else{
                            cnt--;
                        }
                    }
                    lcd_moveto(0, 0);
                    lcd_writedata(cnt + '0');
                    i = 0;
                }

                // Use an outer if statement to select what state you are in
                // Then inside each 'if' or 'else' block, perform the desired
                // output operations and then sample the inputs to update
                // the state for the next iteration
                
                a = PINC & (1 << PC2);
                b = PINC & (1 << PC4);
                if(a == 0){
                    //up button pressed
                    currst = 0;
                }
                else if(b == 0){
                    //down button pressed
                    currst = 1;
                }
                
                // Delay before we go to the next iteration of the loop
                _delay_ms(20);
    }

    return 0;   /* never reached */
}

