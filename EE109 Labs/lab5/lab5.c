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
#include <stdio.h>

#include "lcd.h"

enum{
    STATE_0,
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
};

int main(void) {
       
    lcd_init();
    lcd_writecommand(1);
  /* Call lcd_stringout to print out your name */
    lcd_moveto(0,4);
    lcd_stringout("Penelope");
  /* Use snprintf to create a string with your birthdate */
    char date[10];
    snprintf(date, 10, "%02d/%02d/%02d", 12, 29, 99);
  /* Use lcd_moveto to start at an appropriate column 
     in the bottom row to appear centered */
    lcd_moveto(1,4);
  /* Use lcd_stringout to print the birthdate string */
    lcd_stringout(date);
  /* Delay 1 second */
    _delay_ms(1000);

    char state[30];
    char *s = "S0";
    char *l = "locked";
    char status[30];
    lcd_writecommand(1); //clear the screen
    snprintf(state, 30, "State = %s", s);
    snprintf(status, 30, "Status: %s", l);
    lcd_moveto(0,0);
    lcd_stringout(state);
    lcd_moveto(1,0);
    lcd_stringout(status);


    DDRC |= 0x00; //initally all inputs nit necessary
    PORTC |= (1 << PC2) | (1 << PC4); //initialize PC2 and PC4 to be pull-up resistors 
    int a, b; //value of buttons pressed
    int currst = STATE_0;
    int nextst = STATE_0;
    int ap = 0;
    int bp = 0;
    char *outputState = "S0";
    char *locked = "locked";

  while(1)
  {
    //read button inputs
    a = PINC & (1 << PC2);
    b = PINC & (1 << PC4);

    if(a == 0){
        while((PINC & (1 << PC2)) == 0){  }
            ap = 1;
    }
    if(b == 0){
        while((PINC & (1 << PC4)) == 0){  }
            bp = 1;
    }


    if(currst == STATE_0 && bp){
        outputState = "S1";
        nextst = STATE_1;  
    }
    if(currst == STATE_1 && ap){
        outputState = "S2";
        nextst = STATE_2;
    }
    if(currst == STATE_2 && ap){
        outputState = "S3";
        nextst = STATE_3;
    }
    if(currst == STATE_3 && bp){
        outputState = "S4";
        nextst = STATE_4;
        locked = "unlocked";
    }
    if(currst == STATE_4 && (ap || bp)){
        outputState = "S0";
        nextst = STATE_0;
        locked = "locked  ";
    }

    currst = nextst; 
    ap = 0;
    bp = 0;

    lcd_moveto(0,8);
    lcd_stringout(outputState);
    lcd_moveto(1,8);
    lcd_stringout(locked);
    _delay_ms(20);
}
}


