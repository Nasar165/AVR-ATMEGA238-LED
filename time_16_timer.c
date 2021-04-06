/*
 * File:   main.c
 * Author: Nasar Eddaoui
 *
 * Created on April 6, 2021, 10:46 PM
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) {
    DDRD |= (1<<PD7);       // Data direction output PD7
    
    TCCR1B = (1 <<WGM12);    // Set Waveform Generation to CTC
    OCR1A = 15625;           // Set OCR0A to 156 Total timer ticks MAX 255 8Bit
    TIMSK1 |= (1 << OCIE1A); // Set interrupt Register enable 
    
    sei();                   // Enable interrupts
    
    TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler and start timer
    while (1) {
        
    }
}

ISR(TIMER1_COMPA_vect){
    PORTD ^= (1 << PD7); // Open toggle LED PD7 on and off
}
