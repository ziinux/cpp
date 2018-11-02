//============================================================================
// Name        : Product.cc
// Author      : BADR EL HAFIDI badr@gatech.edu  
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : Implementation for Product class
//============================================================================

#include "Product.h"

// default constructor
Product::Product()
{
    name_ = "";
    price_ = 0.0;
    quantity_ = 0;
}

// overload constructor
Product::Product(std::string name, float price, int quantity)
{
    name_ = name;
    price_ = price;
    setQuantity(quantity);
}

// check if a product is available
bool Product::isAvailable()
{
    return (quantity_>0);
}

// getter of price
float Product::getPrice()
{
    return price_;
}

// getter of quantity
int Product::getQuantity()
{
    return quantity_;
}

// setter of quantity
void Product::setQuantity(int quantity)
{
    if(quantity>=0)
    {
        quantity_ = quantity;
    }
    else
    {
        std::string err = "Cannot set negative quantity for product: " + name_;
        throw err;
    }
}

// prefix increment operator
Product& Product::operator++()
{
    quantity_++;
    return *this;
}

// postfix increment operator   
Product Product::operator++(int __unused)
{
   Product tmp = *this;
   ++*this;
   return tmp;
}

// prefix decrement operator  
Product& Product::operator--()
{
    if(quantity_>0) quantity_--;
    return *this;
}

// postfix decrement operator
Product Product::operator--(int __unused)
{
   Product tmp = *this;
   --*this;
   return tmp;
}













