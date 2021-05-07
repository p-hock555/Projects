#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/eeprom.h>

#include "lcd.h"
#include "thermostat.h"
#include "encoder.h"
#include "ds18b20.h"

int main(void) {
	changed = 0;
	unsigned char buttonState = 1;
	char buffer[12];
	unsigned char t[2]; //for the temperature data

    // Initialize the LCD
    lcd_init();
    lcd_writecommand(1);

    //initialize the ISR
    initialize_ISR();

    //initialize the temperature sensor
    if (ds_init() == 0) {    // Initialize the DS18B20
         // Sensor not responding
    	return 1;
    }

    //read the values from the eeprom
    unsigned char lowCount = eeprom_read_byte((void *) 100);
    unsigned char highCount = eeprom_read_byte((void *) 200);
    if((lowCount < 40) | (lowCount > 100) | (highCount < 40) | (highCount > 100))
    {
    	//set the initial values of the low and high thresholds
    	lowCount = 72;
    	highCount = 76;
    	eeprom_update_byte((void *) 100, lowCount);
    	eeprom_update_byte((void *) 200, highCount);
    }
    count = highCount;

    //splash screen 
    lcd_moveto(0,0);
    lcd_stringout("EE109 Fall 2020");
    lcd_moveto(1,3);
    lcd_stringout("Thermostat");
    _delay_ms(1000);
    lcd_writecommand(1);

    //rotary encoder state
    a = PINB & (1 << PB3);
    b = PINB & (1 << PB4); 

    if (!b && !a)
	old_state = 0;
    else if (!b && a)
	old_state = 1;
    else if (b && !a)
	old_state = 2;
    else
	old_state = 3;

    new_state = old_state;

    //declare the variables for the button presses
    DDRC |= 0x00; //initally all inputs, not necessary
    PORTC |= (1 << PC1) | (1 << PC2); //initialize the low-set and high-set buttons (PC1 and PC2 respectively)
    DDRD |= (1 << PD2) | (1 << PD3); //make the LEDs outputs
    unsigned char low = 1, high = 1; //store the value of low-set and high-set buttons

    //write to the lcd low and high thresholds
    lcd_moveto(1,0);
    snprintf(buffer, 20, "Low=%3d High?%3d", lowCount, highCount);
    lcd_stringout(buffer);

    ds_convert();    // Start first temperature conversion
    int f;

    while(1){	//loop forever
    	if(changed){
    		if(count < 40)
    		{
    			count = 40;
    		}
    		else if(count > 100)
    		{
    			count = 100;
    		}
    		if(buttonState == 0){	//change the low threshold		
    			lowCount = count; //the low threshold has changed
                if(lowCount > highCount){
                    lowCount = highCount; //make sure the low threshold doesnt go above the high threshold
                    count = lowCount;
                }
    			eeprom_update_byte((void *) 100, lowCount); //store this changed value on eeprom
    			lcd_moveto(1,0);
    			snprintf(buffer, 20, "Low?%3d High=%3d", lowCount, highCount);
    			lcd_stringout(buffer);
    		}
    		else{	//change the high threshold
    			highCount = count;
                if(highCount < lowCount){
                    highCount = lowCount; //make sure the high threshold doesnt go below the low threshold
                    count = highCount;
                }
    			eeprom_update_byte((void *) 200, highCount); //store this changed value on eeprom
    			lcd_moveto(1,0);
    			snprintf(buffer, 20, "Low=%3d High?%3d", lowCount, highCount);
    			lcd_stringout(buffer);
    		}
    		changed = 0; //set flag back to 0 for ISR
    	}

    	if (ds_temp(t)) {    // True if conversion complete
            /*
              Process the values returned in t[0]
              and t[1] to find the temperature.
            */
            int dec;
            f = (t[1] << 8) | t[0];//store the two 8-bit chars in a 16-bit int
            								//most significant byte first
            f = (f*9)/8 + 320; //simplified from ((f/16)(9/5)+32)*10
            dec = f%10; //mod by 10 to get the 
            f = f/10; //to go back to our actual value 
            lcd_moveto(0,0);
            snprintf(buffer, 20, "Temp: %d.%d", f, dec); 
            lcd_stringout(buffer);
            ds_convert(); //for our next temp we convert
        }

        //only go in these if statements if the value of the buttons CHANGE, not entering and writing to the lcd every time.
    	if(low && ((PINC & (1 << PC1)) == 0)){
    		//we are in the low state
    		lcd_moveto(1,0);
    		snprintf(buffer, 20, "Low?%3d High=%3d", lowCount, highCount);
    		lcd_stringout(buffer);
    		count = lowCount;
    		buttonState = 0; //change the state and set the count on the low button press
    	}
    	if(high && ((PINC & (1 << PC2)) == 0)){
    		//we are in the high state
    		lcd_moveto(1,0);
    		snprintf(buffer, 20, "Low=%3d High?%3d", lowCount, highCount);
    		lcd_stringout(buffer);
    		count = highCount;
    		buttonState = 1; //change the state and set the count on the high button press
    	}

    	//read the value of the button presses
    	low = PINC & (1 << PC1);
    	high = PINC & (1 << PC2);

    	//turn the A/C and heater on/off based on the temperature
    	if(f > highCount)
    	{
    		PORTD |= (1 << PD3); //turn on the A/C LED
    	}
    	else if(f < lowCount){
    		PORTD |= (1 << PD2); //turn on the heater LED
    	}
    	else{
    		PORTD &= ~((1 << PD3) | (1 << PD2)); //turn off the heater LED
    	}
    	_delay_ms(20);
    }

	return 0; //never reached
}
