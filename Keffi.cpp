#include <avr/io.h>
#include <util/delay.h>
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

    int numCustomers = cl.getCustomerCount();

    // Skapa en array som representerar fördelningen av annonser baserat på betalning
    int adOrder[10]; // Maximal kapacitet för kundlistan
    int totalSlots = 0;

    // Bygg en array för visningsordning baserat på betalning
    for (int i = 0; i < numCustomers; i++) {
        int slots = cl.getPaidAmount(i) / 1000; // För varje 1000 betalning, lägg till en "plats"
        for (int j = 0; j < slots && totalSlots < 10; j++) {
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
            currentIndex = (currentIndex + 1) % totalSlots;

            // Vänta innan nästa visning
            _delay_ms(20000);
        } else {
            // Om samma, hoppa till nästa
            currentIndex = (currentIndex + 1) % totalSlots;
        }
    }

    return 0;
}