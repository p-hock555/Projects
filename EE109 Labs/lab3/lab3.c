/********************************************
*
*  Name: Penelope Hocking
*  Email: hocking@usc.edu
*  Lab section: Friday 2:00-3:20
*  Assignment: Lab 3
*
********************************************/

#include <avr/io.h>
#include <util/delay.h>

#define DOT_LENGTH  250         /* Define the length of a "dot" time in msec */

void dot(void);
void dash(void);
void makeOutput(char);
char checkInput(char);

int main(void)
{

    // Initialize appropriate DDR registers
    
    DDRD |= 0x04; //set PortD, bit 2 to be an output and the rest inputs
    DDRB |= 0x00; //set all of the pins to be inputs on group B, default all inputs so doesn't change anything

    // Initialize the LED output to 0

    // Enable the pull-up resistors for the 
    // 3 button inputs 

    PORTB |= 0x38; //enable pull up resistors on groub B pins 3-5
	

    // Loop forever
    while (1) {                 
	//  Use if statements and the checkInput()
	//  function to determine if a button
	//  is being pressed and then output
	//  the correct dot/dash sequence by
	//  calling the dot(), dash(), and 
	//  using appropriate delay functions
      char x = checkInput(3);
      char y = checkInput(4);
      char z = checkInput(5);

      //U
      if(x == 0){
        dot();
        dot();
        dash();
        _delay_ms(DOT_LENGTH);
      }
      //S
      else if(y == 0)
      {
        dot();
        dot();
        dot();
        _delay_ms(DOT_LENGTH);
      }
      //C
      else if(z == 0){
        dash();
        dot();
        dash();
        dot();
        _delay_ms(DOT_LENGTH);
      }
    }

    return 0;   /* never reached */
}


/*
  dot() - Makes the output LED blink a "dot".

  Write code to generate a dot by using the makeOutput function
  to turn the output ON and OFF with appropriate delays.
  Be sure you don't forget to also delay an
  appropriate time after you turn the output off
*/
void dot()
{
  makeOutput(0);
  _delay_ms(DOT_LENGTH);
  makeOutput(1);
  _delay_ms(DOT_LENGTH);  
}

/*
  dash() - Makes the output LED blink a "dash".

  Write code to generate a dash by using the makeOutput function
  to turn the output ON and OFF with appropriate delays.
  Be sure you don't forget to also delay
  appropriate time after you turn the output off
*/
void dash()
{
  makeOutput(0);
  _delay_ms(DOT_LENGTH * 3);
  makeOutput(1);
  _delay_ms(DOT_LENGTH);
}

/*
  makeOutput() - Changes the output bit to either a zero 
  or one, based on the input argument "value".
  
  If the argument is zero, turn the output OFF,
  otherwise turn the output ON. 
  
  Do not use any delays here.  Just use bit-wise operations
  to make the appropriate PORT bit turn on or off.
*/
void makeOutput(char value)
{
  if(value == 0){

    PORTD |= 0x04; //output ON

  }
  else{
    PORTD &= ~(0x04); //output OFF
  }
}

/*
  checkInput(bit) - Checks the state of the input bit specified by the
  "bit" argument (0-7), and returns either 0 or 1 depending on its state.
  
  Write code to use the appropriate group's PIN register and determine if  
  the specified bit (which is passed as the argument) of that group is
  pressed or not.  Think carefully about what bit value means "pressed"
  when connected to a pushbutton.
 */
char checkInput(char bit)
{
  if(bit == 0){
    if((PINB & 0x01) == 0)
    {
      return 0; //pressed
    }
    return 1; //not pressed
  }
  else if(bit == 1){
    if((PINB & 0x02) == 0)
    {
      return 0;
    }
    return 1;
  } 
  else if(bit == 2){
    if((PINB & 0x04) == 0)
    {
      return 0;
    }
    return 1;
  }
  else if(bit == 3){
    if((PINB & 0x08) == 0)
    {
      return 0;
    }
    return 1;
  } 
  else if(bit == 4){
    if((PINB & 0x10) == 0)
    {
      return 0;
    }
    return 1;
  } 
  else if(bit == 5){
    if((PINB & 0x20) == 0)
    {
      return 0;
    }
    return 1;
  } 
  else if(bit == 6){
    if((PINB & 0x40) == 0)
    {
      return 0;
    }
    return 1;
  } 
  else if(bit == 7){
    if((PINB & 0x80) == 0)
    {
      return 0;
    }
    return 1;
  } 


}
