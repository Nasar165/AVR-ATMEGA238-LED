/*
 * File:   main.c
 * Author: mcsunity
 *
 * Created on March 23, 2021, 10:30 PM
 */

#define F_CPU 16000000UL

#include <xc.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define LED PB5
#define BV(x)           (1 << x)
#define setBit(P,B)     P |= BV(B)
#define clearBit(P,B)   P &= ~BV(B)
#define toggleBit(P,B)  P ^= BV(B)
#define bitIsHigh(P,B)  P & BV(B)) != BV(B)

int main(void) {
    DDRB |= (1 << LED);  // Set data direction register B. 
    
    PCICR |= (1 << PCIE0); // Pin Change Interrupt Register 
    PCMSK0 |= (1 << PCINT0); // Pin Change Mask Register 
    
    sei(); // enable global interrupt.
    setBit(PORTB,LED);
    
    while(1){
        clearBit(PORTB,LED);
        _delay_loop_1(1000);
        toggleBit(PORTB, LED);
    }
    return 1;
}

ISR(PCINT0_vect){
    if((PINB & (1 << PINB5)) == (1 << PINB5)){
        toggleBit(PORTB, LED);
    }
}
