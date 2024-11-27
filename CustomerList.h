struct Customer{            
    int paidAmount;
    char message[32];
};

class CustomerList {    
  private: 
  Customer customerList[10]; 
    int customerCount = 0;
    int totalPayment = 0;

  
public: 
    int addCustomer(int payment, char *m);

char* getMessage(int index);

int paidAmount(int index);
    
int getTotalPayment();
};

