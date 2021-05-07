#include <avr/io.h>

#include "adc.h"


void adc_init(void)
{
    // Initialize the ADC
    ADMUX &= ~(1 << REFS0); //set reference voltage
    ADMUX |= (1 << REFS0);
    ADMUX |= (1 << ADLAR);
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //set the clock 128 
    ADCSRA |= (1 << ADEN); //enable adc
}

unsigned char adc_sample(unsigned char channel)
{
    // Set ADC input mux bits to 'channel' value
    ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
    if(channel == 0){
    	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0)); 
    }
    else if(channel ==1)
    {
    	ADMUX |= (1 << MUX0); 
    }
    else if(channel == 2)
    {
    	ADMUX |= (1 << MUX1); 
    }
    else if(channel == 3)
    {
    	ADMUX |= (1 << MUX1) | (1 << MUX0); 
    }
    else if(channel == 4)
    {
    	ADMUX |= (1 << MUX2); 
    }
    else if(channel == 5)
    {
    	ADMUX |= (1 << MUX2) | (1 << MUX0); 
    }
    ADCSRA |= 1 << ADSC;
    while((ADCSRA & (1 << ADSC)) != 0 )
    { }

    // Convert an analog input and return the 8-bit result
    unsigned char result = ADCH;
    return result;
}
