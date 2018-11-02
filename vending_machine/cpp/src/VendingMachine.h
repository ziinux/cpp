//============================================================================
// Name        : VendingMachine.h
// Author      : BADR EL HAFIDI badr@gatech.edu
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : Header for VendingMachine class
//============================================================================

#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <Product.h>
#include <Transaction.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <map>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class VendingMachine {
        private:
            std::string pathToInventory_;
            std::string pathToTransactions_;
            std::map <std::string, Product> inventory_;
            std::vector <Transaction> transactions_;
            void getInventory();
            void getTransactions();
        public:
            VendingMachine(std::string pathToInventory, std::string pathToTransactions);
            void processTransactions();
            void printTransactions();
};

#endif
