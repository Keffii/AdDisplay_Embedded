#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include <time.h>

int main(void){
    HD44780 lcd;

    lcd.Initialize(); // Initialize the LCD
    lcd.Clear();      // Clear the LCD

    lcd.WriteText((char *)"Hej hej");

int time(); 


char customers[][20] = {"Customer A", "Customer B", "Customer C", "Customer D", "Customer E"};
int numCustomers = sizeof(customers) / sizeof(customers[0]);  // Antal kunder i listan

char latestCustomer[20] = "";  // Håller reda på den senaste kunden
unsigned long lastTime = 0;  // För att hålla koll på senaste visningstid
const unsigned long showTime = 20000;  // 20 sekunder (i millisekunder)

void setup() {
  // Starta seriell kommunikation
  Serial.begin(9600);
  randomSeed(analogRead(0));  // Initiera slumpgeneratorn med ett noise-värde från analog pin 0
  Serial.println("Start customer display... ");
}

void loop() {
  // Kontrollera om 20 sekunder har gått
  if (millis() - lastTime >= showTime) {
    // Slumpa en ny kund, se till att det inte är samma kund som sist
    char* selectedCustomer = randomCustomer();

    // Visa den valda kunden i serialmonitor
    Serial.println(selectedCustomer);

    // Uppdatera tiden för senaste visning
    lastTime = millis();
  }
}

char* randomCustomer() {
  char* selectedCustomer;
  // Slumpa en kund som inte är den senaste kunden
  do {
    int index = random(numCustomers);  // Slumpa ett index från kunder-listan
    selectedCustomer = customers[index];  // Hämta kundens namn från listan
  } while (strcmp(selectedCustomer, latestCustomer) == 0);  // Om det är samma kund som sist, välj en ny

  // Uppdatera den senaste kunden
  strcpy(latestCustomer, selectedCustomer); 

  return selectedCustomer;
}
}

