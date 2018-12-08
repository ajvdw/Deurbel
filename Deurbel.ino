// Doorbell to DECT phone paging button
// Author: A.J. VAN DE WERKEN
// Date: 3 November 2018
//
//    VCC   LED
//   __#__#__#__#__
//  |  8  7  6  5  |     
//  )   ATTINY85   |
//  |__1__2__3__4__|
//     #  #  #  #
//       SW    GND
//
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
    // This is called when the interrupts PCINT0..5 occur, 
    // but I don't need to do anything in it
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
    // Sleep and wait for wakeup                              
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
