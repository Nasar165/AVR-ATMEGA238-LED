/*
 * File:   main.c
 * Author: Nasar Eddaoui
 * Company: MCS UNITY Co.,LTD
 *
 * Created on March 20, 2021, 5:14 PM
 */

#define F_CPU 16000000UL

#include <xc.h>
#include <util/delay.h>

typedef enum {
    INPUT = 0b00000000,
    OUTPUT = 0b11111111
} portState;

void togglePin(volatile uint8_t *port,int pin, int low) {
    if (low == 1) {
        *port &= ~(1 << pin);
    } else {
        *port |= (1 << pin);
    }
}

void setPorts(volatile uint8_t *ports, portState state){
       *ports |= state;
}

int main(void) {
    setPorts(&DDRB, OUTPUT);
    setPorts(&PORTB,INPUT);
    // DDRB = 0b11111111; // make port B pin 5 (PB5) a digital output
    //PORTB = 0b00000000; // make Port B pin 5 (PB5) go to 0 volts (logic low)

    while (1) {
        togglePin(&PORTB,PB5, 0);
        //PORTB |= (1 <<PB5);
        _delay_ms(2000);
        togglePin(&PORTB,PB5, 1);
        //PORTB &= ~(1 << PB5);
        _delay_ms(2000);
    }

    return 0;
}
