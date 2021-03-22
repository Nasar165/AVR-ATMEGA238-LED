/*
 * File:   main.c
 * Author: Nasar Eddaoui
 *
 * Created on March 22, 2021, 10:41 PM
 */

#define F_CPU 16000000UL

#include <xc.h>
#include <avr/interrupt.h>

uint8_t pinValue;

void setBit(volatile uint8_t * reg, uint8_t pin){
    *reg |= (1 << pin);
}

void clearBit(volatile uint8_t  * reg, uint8_t pin){
    *reg &= ~(1 << pin);
}

int bitIsHigh(volatile uint8_t * reg, uint8_t pin){
    int result = 0;
    if((*reg & (1 << pin)) !=  (1 << pin)){
        result = 0;
    }
    return result;
}
 
int main(void) {
    DDRB |= 0b10010;    // Set Pin 1 and 5 as output
    PORTB |= 0b0;       // Set all pins as low
    
    // Enable Interrupt
    PCICR |= (1 << PCIE0);      // Enable interrupt
    PCMSK0 |= (1 << PCINT0);    // Enable interrupt pin 0 PB0
    
    sei();
    
    while(1){
      pinValue = (PINB & (1 << PINB5)) >> PINB5; // hover and check pin value
    }
    
    return 1;
}

ISR (PCINT0_vect){
    if(bitIsHigh(&PINB, PINB0) == 1){
        setBit(&PORTB, PB5);
    } else {
        clearBit(&PORTB, PB5);
    }
}
