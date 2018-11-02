//============================================================================
// Name        : VendingMachine.h
// Author      : BADR EL HAFIDI badr@gatech.edu 
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : Header for Product class
//============================================================================

#ifndef PRODUCT_H
#define PRODUCT_H

#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class Product {
        private:
            std::string name_;
            float price_;
            int quantity_;
        public:
            Product();
            Product(std::string name, float price, int quantity);
            bool isAvailable();
            float getPrice();
            int getQuantity();
            void setQuantity(int quantity);
            Product& operator++();                  //Prefix  increment operator
            Product operator++(int __unused);       //Postfix increment operator
            Product& operator--();                  //Prefix  decrement operator
            Product operator--(int __unused);       //Postfix decrement operator
};

#endif
