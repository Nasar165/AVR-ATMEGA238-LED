/*
 * File:   main.c
 * Author: mcsunity
 *
 * Created on March 21, 2021, 7:59 PM
 */


#define F_CPU 16000000UL

#include <util/delay.h>
#include <xc.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int main(void) {
    DDRB |= 0b00100000; // Set pin B5 as output
    PORTB |= 0b00000000; // Set port B pins to low
    
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT0);
    
    sei();
    
    while(1){
    }
    return 1;
}

ISR (PCINT0_vect){
    if((PINB & (1 << PINB0)) == 1){ // If pin B0 is high
        PORTB |= (1<< PB5);  
    }else {
        PORTB &= ~(1 << PB5);
    }
}
