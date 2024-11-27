#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "CustomerList.h"


int CustomerList::addCustomer(int payment, char *m){
    customerList[customerCount].paidAmount = payment;
    strcpy(customerList[customerCount].message, m);
    customerCount++;
    totalPayment += payment;
    return 0;
    }

char* CustomerList::getMessage(int index){
    return customerList[index].message;
    }

int CustomerList::paidAmount(int index){
    return customerList[index].paidAmount;
}

int CustomerList::getTotalPayment(){
  return totalPayment;
}

