/*
 * File:   main.c
 * Author: neddaoui
 *
 * Created on March 27, 2021, 4:11 PM
 */

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#define BV(P) (1 << P)
#define SETBIT(R,P)  R |= BV(P)

#include <xc.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void) {
    DDRB &= ~(1 << DDB0); // Clear the PB0 pin
    // PB0 (PCINT0 pin) is now an input

    PORTB |= (1 << PORTB0); // turn On the Pull-up
    // PB0 is now an input with pull-up enabled

    DDRD |= (1 << PD7) | (1 << PD6)| (1 << PD5) | (1 << PD4);
    PORTD |= (1 << PD7) | (1 << PD6)| (1 << PD5) | (1 << PD4);

    PCICR |= (1 << PCIE0); // Pin Change Interrupt Register 
    PCMSK0 |= (1 << PCINT0); // Pin Change Mask Register 

    sei();

    while (1) {
        PORTD |= (1 << PD7);
        _delay_ms(1000);
        PORTD &= ~(1 << PD7);
        _delay_ms(1000);
    }
    return 1;
}

ISR(PCINT0_vect) {
    if ((PINB & (1 << PB0)) == 1) {
        PORTD &= ~(1 << PD6);
        PORTD |= (1 << PD5);
    } else {
        PORTD |= (1 << PB6);
        PORTD &= ~(1 << PD5);
    }
}
