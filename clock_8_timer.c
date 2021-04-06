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

int interrupts = 0; // count number of interrupts triggered

int main(void) {
    DDRD |= (1<<PD7);       // Data direction output PD7
    TCCR0A = (1 <<WGM01);   // Set Waveform Generation to CTC
    OCR0A = 156;            // Set OCR0A to 156 Total timer ticks MAX 255 8Bit
    TIMSK0 |= (1 << OCIE0A); // Set interrupt Register enable 
    
    sei();                   // Enable interrupts
    
    TCCR0B = (1 << CS02) | (1 << CS00); // enable timer clock
    while (1) {
        
    }
}

ISR(TIMER0_COMPA_vect){
    interrupts++; // 
    if(interrupts > 100){ // If more than 100 loops amounts to ~1 sec
        PORTD ^= (1 << PD7); // Open toggle LED PD7 on and off
        interrupts = 0;   // Reset counter to 0
    }
}
