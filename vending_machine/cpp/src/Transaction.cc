//============================================================================
// Name        : Transaction.cc
// Author      : BADR EL HAFIDI badr@gatech.edu
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : Implementation for Transaction class
//============================================================================

#include "Transaction.h"

// overload constructor 
Transaction::Transaction(std::string nameOfProduct, std::vector<int> funds)
{
    nameOfProduct_ = nameOfProduct;
    funds_ = funds;
    transactionProcessed_ = false;
    transactionApproved_ = false;
    productDelivered_ = false;
}

// get the name of product
std::string Transaction::getNameOfProduct()
{
    return nameOfProduct_;
}

// check if the transaction is approved
bool Transaction::isApproved()
{
    return transactionApproved_;
}

// set the productDelivered_ to true
void Transaction::setProductDelivered()
{
    productDelivered_ = true;
}

// process the transaction
void Transaction::processTransaction(float priceDollars)
{
    transactionProcessed_ = true;

    // compute price (cents)
    int price = priceDollars * 100;

    // compute total funds
    int totalFunds = 0;
    for (int i=0; i<funds_.size(); i++)
    {
        totalFunds += funds_[i];
    }

    // check if funds are enough
    if(price > totalFunds)
    {
        transactionApproved_ = false;
        giveChange(totalFunds);
    }
    else
    {
        transactionApproved_ = true;
        giveChange(totalFunds-price);
    }
}

void Transaction::refund()
{
    // compute total funds
    int totalFunds = 0;
    for (int i=0; i<funds_.size(); i++)
    {
        totalFunds += funds_[i];
    }
    giveChange(totalFunds);
}

void Transaction::giveChange(int balance)
{
    int change100, change25, change10, change5;
    // compute change for 100
    change100 = balance/100;
    // update balance
    balance -= 100*change100;
    // compute change for 25
    change25 = balance/25;
    // update balance
    balance -= 25*change25;
    // compute change for 10
    change10 = balance/10;
    // update balance
    balance -= 10*change10;
    // compute change for 5
    change5 = balance/5;

    if(change5>0) 
        for(int i=0; i<change5; i++)
            change_.push_back(5);
    if(change10>0) 
        for(int i=0; i<change10; i++)
            change_.push_back(10);
    if(change25>0) 
        for(int i=0; i<change25; i++)
            change_.push_back(25);
    if(change100>0) 
        for(int i=0; i<change100; i++)
            change_.push_back(100);
}

// overload operator<< for class Transaction
std::ostream& operator<<(std::ostream &stm, const Transaction &trs) 
{
    stm << "  {" << "\n" 
        << "    \"name\": " << "\"" << trs.nameOfProduct_ << "\",\n"
        << "    \"product_delivered\": " << ((trs.productDelivered_)? "true" : "false") << ",\n"
        << "    \"change\": [ " << "\n";

    for(int i=0; i<trs.change_.size(); i++)
    {
        stm << "      " << trs.change_[i];
        if(i<trs.change_.size()-1)
            stm << ",\n";
        else
            stm << "\n";
    }

    stm << "    ]\n"
        << "  }";
    return stm;
}



