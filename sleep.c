/*
 * File:   main.c
 * Author: Nasar Eddaoui
 *
 * Created on March 21, 2021, 11:20 PM
 */


#include <xc.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

int main(void) {
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT0);
    sei();
    set_sleep_mode(0b00000110);
    sleep_mode();
    return 1;
}

ISR(PCINT0_vect){
   sleep_disable();
}
