//Piotr Makulec, 2025
//Written for and tested on Arduino (ATmega328p).

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN (1 << PB5)          //internal LED
#define LED_ON PORTB |= LED_PIN     //set the LED pin HIGH
#define LED_OFF PORTB &= ~LED_PIN   //set the LED pin LOW
#define LED_TOG PORTB ^= LED_PIN    //change the current state of the LED
#define KEY_PIN1 (1 << PD2)         //tact switch 1
#define KEY_PIN2 (1 << PD3)         //tact switch 2
#define KEY_PIN3 (1 << PD4)         //tact switch 3

uint8_t buttonPressed(uint8_t button);

int main(void) {
  DDRB |= LED_PIN;                            //set the LED pin as output
  PORTB &= ~LED_PIN;                          //set the LED pin low
  DDRD &= ~(KEY_PIN1 | KEY_PIN2 | KEY_PIN3);  //set the tact switch pins as inputs (redundant)
  PORTD |= KEY_PIN1 | KEY_PIN2 | KEY_PIN3;    //pull up the tact switch pins

  while (1) {                                 //infinite loop
    if (buttonPressed(KEY_PIN1)) LED_ON;      //turn on the LED if tact switch 1 is pressed
    if (buttonPressed(KEY_PIN2)) LED_OFF;     //turn off the LED if tact switch 2 is pressed
    if (buttonPressed(KEY_PIN3)) LED_TOG;     //change the LED state if tact switch 3 is pressed
  }
}

uint8_t buttonPressed(uint8_t button) {
  if (!(PIND & button)) {                     //if the pin state is low
    _delay_ms(80);                            //debounce the switch
    if (!(PIND & button))                     //if the pin state is still low
      return 1;
  }
  return 0;
}
