#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <time.h>
#include "lcd.h"
#include "CustomerList.h"


int main(void) {
    srand(time(NULL)); 
    HD44780 lcd;
    lcd.Initialize();
    lcd.Clear();

    CustomerList cl;
    cl.addCustomer(5000, "En god bilaffar (for Harry!)");
    cl.addCustomer(3000, "Skynda Marten ater alla pajer");
    cl.addCustomer(1500, "Bygga svart? Ring Petter");
    cl.addCustomer(4000, "Mysterier? Ring Langben");

    int numCustomers = cl.getCustomerCount();

    // Skapa en array som representerar fördelningen av annonser baserat på betalning
    char adOrder[27]; // Maximal kapacitet för kundlistan.
    int totalSlots = 0;

    // Bygg en array för visningsordning baserat på betalning
    for (int i = 0; i < numCustomers; i++) {
        int slots = cl.getPaidAmount(i) / 500; // För varje 500 betalning, lägg till en "plats"
        for (int j = 0; j < slots && totalSlots < 27; j++) {
            adOrder[totalSlots++] = i;
        }
    }

    // Enkel cyklisk visning av annonser utan upprepning
    int currentIndex = 0;
    int lastIndex = -1; // Ingen annons visad ännu

    while (1) {
        // Välj nästa annons
        int currentAd = adOrder[currentIndex];

        // Kontrollera att det inte är samma som den senaste annonsen
        if (currentAd != lastIndex) {
            // Visa annonsen
            lcd.Clear();
            lcd.WriteText(cl.getMessage(currentAd));

            // Uppdatera senaste visade index
            lastIndex = currentAd;

            // Gå till nästa index i ordningen
            currentIndex = rand() % totalSlots;

            // Vänta innan nästa visning
            _delay_ms(20000);
        } else {
            // Om samma, hoppa till nästa
            currentIndex = rand() % totalSlots;
        }

    }

    return 0;
}
