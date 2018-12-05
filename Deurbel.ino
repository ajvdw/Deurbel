// Doorbell to DECT phone paging button
// Author: A.J. VAN DE WERKEN
// Date: 3 November 2018
//
// ATMEL ATTINY 25/45/85 / ARDUINO
//          --_-- 
//         1|   |8  Vcc
// SWITCH  2|   |7  
//         3|   |6  LED
//    Gnd  4|   |5  
//          -----
#include <avr/sleep.h>
#include <avr/interrupt.h>

const int switchPin = 3;
const int statusLED = 1;

void setup() 
{
    // Setup I/O
    pinMode(switchPin, INPUT);
    digitalWrite(switchPin, HIGH);
    pinMode(statusLED, OUTPUT);
}

ISR(PCINT0_vect) 
{
    // This is called when the interrupt occurs, but I don't need to do anything in it
}

void loop() 
{
    // Goto Sleep
    GIMSK |= _BV(PCIE);                     
    PCMSK |= _BV(PCINT3);                   
    ADCSRA &= ~_BV(ADEN);                  
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    
    sleep_enable();                         
    sei();                                  
    sleep_cpu();                            
    cli();                       
    PCMSK &= ~_BV(PCINT3);                  
    sleep_disable();                      
    ADCSRA |= _BV(ADEN);                   
    sei();                               
    // Awake
    digitalWrite(statusLED, HIGH);
    // Pulse
    delay(100);
    digitalWrite(statusLED, LOW);
    // Wait 30 seconds
    delay(30000);                         
}
