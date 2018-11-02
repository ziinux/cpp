//============================================================================
// Name        : VendingMachine.h
// Author      : BADR EL HAFIDI badr@gatech.edu 
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : Header for Transaction class
//============================================================================

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class Transaction {
        private:
            std::string nameOfProduct_;
            std::vector<int> funds_;
            std::vector<int> change_;
            bool transactionProcessed_;
            bool transactionApproved_;
            bool productDelivered_;
            void giveChange(int balance);
            friend std::ostream& operator<<(std::ostream&, const Transaction&);
        public:
            //Transaction();
            Transaction(std::string nameOfProduct, std::vector<int> funds);
            std::string getNameOfProduct();
            // void setChange(std::vector<int> change);
            // void setProductDelivered(bool productDelivered);
            bool isApproved();
            void setProductDelivered();
            void refund();
            void processTransaction(float priceDollars);
};

// std::ostream& operator<<(std::ostream &stm, const Transaction &trs) 
// {
//     stm << "{" << "\n" 
//         << "  \"product_delivered\":" << ((trs.productDelivered_)? "true" : "false") << ",\n"
//         << "  \"change\": [ " << "\n";
// 
//     for(int i=0; i<trs.change_.size()-1; i++)
//     {
//         stm << trs.change_[i] << ",\n";
//     }
// 
//     stm << trs.change_[trs.change_.size()-1] << "\n"
//         << "  ]\n"
//         << "}\n";
//     return stm;
// }

#endif
