#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> // För rand()
#include "lcd.h"
#include "CustomerList.h"

int main(void) {
    HD44780 lcd;
    lcd.Initialize();
    lcd.Clear();

    CustomerList cl;
    cl.addCustomer(5000, "En god bilaffar (for Harry!)");
    cl.addCustomer(3000, "Skynda Marten ater alla pajer");
    cl.addCustomer(1500, "Bygga svart? Ring Petter");
    cl.addCustomer(4000, "Mysterier? Ring Langben");

    int numCustomers = cl.getNumberOfCustomers();
    int lastIndex = -1; // Ingen annons visad ännu

    while (1) {
        int currentIndex;

        // Välj en ny annons som inte är samma som den senaste
        do {
            currentIndex = rand() % numCustomers; // Slumpa ett index
        } while (currentIndex == lastIndex);

        // Visa den valda annonsen
        lcd.Clear();
        lcd.WriteText(cl.getMessage(currentIndex));

        // Uppdatera senaste visade annons
        lastIndex = currentIndex;

        // Vänta innan nästa visning
        _delay_ms(5000);
    }

    return 0;
}

