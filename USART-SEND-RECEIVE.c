/*
 * File:   main.c
 * Author: Nasar Eddaoui
 *
 * Created on March 28, 2021, 9:52 PM
 */

#define F_CPU 16000000UL

#include <xc.h>
#include <string.h>
#include <util/delay.h>


#define FOSC 16000000UL
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

// FRAME
#define ONE_STOP_BIT (1 << USBS0)
#define FRAME8BIT (3 << UCSZ00)
#define BUFFER 4096


void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
char USART_Receive(void);

void printMessage(char *message);
void clearCommand(char *message);

int main(void) {
    USART_Init(UBRR);
    DDRD = 0b10000000;
    PORTD = 0b00000000;

    char init[] = "Initialize USART\r\n";

    printMessage(init);
    char command[BUFFER];
    int index = 0;
    while (1) {
        char temp = USART_Receive();
        if (temp == 0) {
            continue;
        } else if (temp != '0') {
            command[index] = temp;
            index++;
        }

        if (temp == '0') {
            command[index] = '\r';
            command[index + 1] = '\n';
            printMessage(command);
            index = 0;
            clearCommand(command);
            continue;
        }
        temp = 0;
    }
    return 1;
}

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) ubrr;

    // SEt frame format: 8bit 1 stop bit
    UCSR0C = FRAME8BIT | ONE_STOP_BIT;

    // Enable RX and TX transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void USART_Transmit(unsigned char ata) {
    // await for the buffer to be empty
    while (!(UCSR0A & (1 << UDRE0))) {
    }

    // Put data into buffer, send the data
    UDR0 = data;
}

char USART_Receive(void) {
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0))) {
    }
    /* Get and return received data from buffer */
    return UDR0;
}

void printMessage(char *message) {
    for (int i = 0; i <= strlen(message); i++) {
        if (message == 0) {
            break;
        }
        USART_Transmit(message[i]);
    }
}

void clearCommand(char *command){
   memset(command, 0, sizeof command);
}

