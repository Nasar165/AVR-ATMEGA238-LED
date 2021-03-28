/*
 * File:   main.c
 * Author: Nasar Eddaoui
 *
 * Created on March 27, 2021, 4:11 PM
 */

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <xc.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BV(P) (1 << P)
#define CLEARBIT(R,P) R &= ~(BV(P))
#define SETBIT(R,P)  R |= BV(P)

#define ONLINELED PD7
#define RELAY1 PD6
#define STANDBYLED PD5
#define BUTTON PD4
#define WATERLED PD3

#define MS 1000

int main(void) {
    DDRB &= ~(1 << DDB0); // Clear the PB0 pin
    DDRB &= ~(1 << DDB1); // Clear the PB0 pin
    // PB0 (PCINT0 pin) is now an input
    PORTB |= (1 << PORTB0) | (1 << PORTB1); // turn On the Pull-up
    // PB0 is now an input with pull-up enabled

    DDRC &= ~(1 << DDC0); // Clear the PB0 pin
    // PB0 (PCINT0 pin) is now an input
    PORTC |= (1 << PORTC0); // turn On the Pull-up
    // PB0 is now an input with pull-up enabled

    //DDRD |= 0b11111000;
    DDRD |= ((1 << ONLINELED) | (1 << RELAY1) | (1 << STANDBYLED) | (1 << BUTTON) | (1 << WATERLED));
    PORTD |= ((1 << ONLINELED) | (1 << STANDBYLED) | (1 << BUTTON));

    PCICR |= ((1 << PCIE0) | (1 << PCIE1)); // Pin Change Interrupt Register 
    PCMSK0 |= ((1 << PCINT0) | (1 << PCINT1)); // Pin Change Mask Register 
    PCMSK1 |= ((1 << PCINT8));

    sei();

    while (1) {
        SETBIT(PORTD, ONLINELED);
        _delay_ms(MS);
        CLEARBIT(PORTD, ONLINELED);
        _delay_ms(MS);
    }
    return 1;
}

ISR(PCINT0_vect) { // Interrupt detecting button click 
    if ((PINB & (1 << PB0)) == 1) {
        CLEARBIT(PORTD, RELAY1);
        SETBIT(PORTD, STANDBYLED);
    } else {
        CLEARBIT(PORTD, STANDBYLED);
        SETBIT(PORTD, RELAY1);
    }
}

ISR(PCINT1_vect) { // Interrupt when water sensor is triggered
    if ((PINC & (1 << PC0)) == 1) {
        SETBIT(PORTD, WATERLED);
    } else {
        CLEARBIT(PORTD, WATERLED);
    }
}
