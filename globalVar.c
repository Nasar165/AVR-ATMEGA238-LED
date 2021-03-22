/*
 * File:   main.c
 * Author: Nasar Eddaoui
 *
 * Created on March 22, 2021, 10:00 PM
 */

#define F_CPU 16000000UL

#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int infiniteLoop = 0b1;

int main(void) {
    DDRB |= (1 << PB5);
    PORTB |= 0b00000000;
   
    
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT0);
    
    sei();
    
    while (infiniteLoop){
        PORTB |= (1 << PB5);
        PORTB &= ~(1 << PB5);
    }
    
    return 1;
}

ISR (PCINT0_vect) {
    infiniteLoop = 0b0;
}
