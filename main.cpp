#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> // För rand()
#include "lcd.h"
#include "CustomerList.h"

// Funktion för att välja en annons baserat på betalningar, utan att upprepa samma annons
int selectAdvertisement(CustomerList *cl, int lastDisplayedIndex) {
    int totalTickets = 0;
    int numCustomers = cl->getNumberOfCustomers();

    // Beräkna totala antalet "lotter"
    for (int i = 0; i < numCustomers; i++) {
        totalTickets += cl->getPayment(i);
    }

    // Slumpa ett tal tills vi hittar en annons som inte är samma som senast
    int selectedCustomer = -1;
    do {
        int randomTicket = rand() % totalTickets;

        // Identifiera vilken kund som har denna "lott"
        int cumulativeTickets = 0;
        for (int i = 0; i < numCustomers; i++) {
            cumulativeTickets += cl->getPayment(i);
            if (randomTicket < cumulativeTickets) {
                selectedCustomer = i;
                break;
            }
        }
    } while (selectedCustomer == lastDisplayedIndex);

    return selectedCustomer;
}

int main(void) {
    HD44780 lcd;
    lcd.Initialize();
    lcd.Clear();

    CustomerList cl;
    cl.addCustomer(5000, "En god bilaffar (for Harry!)");
    cl.addCustomer(3000, "Skynda Marten ater alla pajer");
    cl.addCustomer(1500, "Bygga svart? Ring Petter");
    cl.addCustomer(4000, "Mysterier? Ring Langben");

    // Sätt upp slumpgenerering (seed baserad på tid eller annan variabel)
    srand(1234); // Exempel: fast seed för testning

    int lastDisplayedIndex = -1; // Inget visat ännu

    while (1) {
        int selectedCustomer = selectAdvertisement(&cl, lastDisplayedIndex);
        if (selectedCustomer != -1) {
            lcd.Clear();
            lcd.WriteText(cl.getMessage(selectedCustomer));
            lastDisplayedIndex = selectedCustomer; // Uppdatera senast visade index
        }

        _delay_ms(5000); // Vänta 5 sekunder innan nästa visning
    }

    return 0;
}

