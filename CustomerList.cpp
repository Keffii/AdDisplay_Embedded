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

int CustomerList::getPaidAmount(int index){
    return customerList[index].paidAmount;
}

int CustomerList::getTotalPayment(){
  return totalPayment;
}

int CustomerList::getCustomerCount(){
    return customerCount;
}

//I want a customerlist with information about message and paidamount
//I want to be able to add a customer to the list
int customerListTest(){
    CustomerList cl;
    cl.addCustomer(5000, "En god bilaffär (för Harry!)");
    cl.addCustomer(3000, "Skynda innan Mårten ätit alla pajer");
    cl.addCustomer(1500, "Bygga svart? Ring Petter");
    cl.addCustomer(4000, "Mysterier? Ring Långben");
    printf("Total payment: %d\n", cl.getTotalPayment());
    printf("Customer count: %d\n", cl.getCustomerCount());
    printf("Customer 0 message: %s\n", cl.getMessage(0));
    printf("Customer 0 paid amount: %d\n", cl.getPaidAmount(0));
    return 0;
}