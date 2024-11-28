#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "CustomerList.h"

// https://wokwi.com/projects/383283130065573889

// PORTB B (digital pin 8 to 13)
// C (analog input pins)
// PORTD D (digital pins 0 to 7)
#define LED_PIN 2
#define BUTTON_PIN 1

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)

int main(void){
    HD44780 lcd;
    lcd.Initialize(); // Initialize the LCD
    lcd.Clear();      // Clear the LCD

    CustomerList cl;
    cl.addCustomer(5000, "En god bilaffar (for Harry!)");
    cl.addCustomer(3000, "Skynda Marten ater alla pajer");
    cl.addCustomer(1500, "Bygga svart? Ring Petter");
    cl.addCustomer(4000, "Mysterier? Ring Langben");
    lcd.WriteText(cl.getMessage(0));  // getMessage(index of customers)
    // lcd.GoTo(0, 1); // Go to the second line
    // lcd.WriteText((char *)"Skynda innan Mårten ätit alla pajer");

    // //Sätt till INPUT_PULLUP
    // BIT_CLEAR(DDRB,BUTTON_PIN); // INPUT MODE
    // BIT_SET(PORTB,BUTTON_PIN); 

    // DATA DIRECTION = avgör mode
    // om output så skickar vi  1 eller 0 på motsvarande pinne på PORT
    // om input så läser vi  1 eller 0 på motsvarande pinne på PIN
    //bool blinking = false;
    while(1){
     
    }
    return 0;
}

// Hederlige Harrys Bilar:

// Betalat 5000. Vill slumpmässigt visa en av tre meddelanden

// "Köp bil hos Harry"  (scroll)

// "En god bilaffär (för Harry!)" text

// "Hederlige Harrys Bilar" text (blinkande)
