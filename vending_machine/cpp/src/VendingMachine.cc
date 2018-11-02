//============================================================================
// Name        : VendingMachine.cc
// Author      : BADR EL HAFIDI badr@gatech.edu 
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : Implementation for VendingMachine class
//============================================================================

#include "VendingMachine.h"

VendingMachine::VendingMachine(std::string pathToInventory, std::string pathToTransactions)
{
    pathToInventory_ = pathToInventory;
    pathToTransactions_ = pathToTransactions;
    getInventory();
    getTransactions();
}

void VendingMachine::getInventory()
{
    // check if the pathToInventory_ exists
    std::ifstream infile(pathToInventory_.c_str());

    if(access( pathToInventory_.c_str(), R_OK ) == -1)
    {
        std::string exception = "The file: " + pathToInventory_ + " doesn't exist or can't be opened!";
        throw exception;
    }

    // if pathToInventory_ exists, check if it is a file 
    struct stat buf;
    stat(pathToInventory_.c_str(), &buf);
    bool isFile = S_ISREG(buf.st_mode);
    if( !isFile )
    {
        std::string exception = "The file: " + pathToInventory_ + " is not a file! \n";
        throw exception;
    }
    
    // Read the pathToInventory_ and store it in: const char* json
    std::string line,text;
    while(std::getline(infile, line))
    {
        text += line + "\n";
    }
    const char* json = text.c_str();

    // Parse the JSON and convert it to DOM
    rapidjson::Document document;
    document.Parse(json);

    // Extract products and save them
    std::string nameOfProduct;
    int quantity;
    float price;
    for (rapidjson::Value::ConstMemberIterator it = document.MemberBegin(); it != document.MemberEnd(); it++)
    {
        nameOfProduct = it->name.GetString();
        quantity = it->value["quantity"].GetInt();
        price = it->value["price"].GetFloat();

        inventory_[it->name.GetString()] = Product(nameOfProduct,price,quantity);
    }

}

void VendingMachine::getTransactions()
{
    // check if the pathToTransactions_ exists
    std::ifstream infile(pathToTransactions_.c_str());

    if(access( pathToTransactions_.c_str(), R_OK ) == -1)
    {
        std::string exception = "The file: " + pathToTransactions_ + " doesn't exist or can't be opened! \n";
        throw exception;
    }

    // if pathToTransactions_ exists, check if it is a file 
    struct stat buf;
    stat(pathToTransactions_.c_str(), &buf);
    bool isFile = S_ISREG(buf.st_mode);
    if( !isFile )
    {
        std::string exception = "The file: " + pathToTransactions_ + " is not a file! \n";
        throw exception;
    }
    
    // Read the pathToTransactions_ and store it in: const char* json
    std::string line,text;
    while(std::getline(infile, line))
    {
        text += line + "\n";
    }
    const char* json = text.c_str();

    // Parse the JSON and convert it to DOM
    rapidjson::Document document;
    document.Parse(json);

    // Extract transactions and save them
    const rapidjson::Value & transactions = document;
    std::string nameOfProduct;
    std::vector<int> funds;
    for (int i=0; i<transactions.Size(); i++)
    {
        nameOfProduct = transactions[i]["name"].GetString();
        funds.clear();
        for(int k=0; k<transactions[i]["funds"].Size(); k++)
        {
            funds.push_back(transactions[i]["funds"][k].GetInt());
        }
        transactions_.push_back(Transaction(nameOfProduct,funds));
    }
}

void VendingMachine::processTransactions()
{
    std::string nameOfProduct;
    float price;
    for(int i=0; i<transactions_.size(); i++)
    {
        // get the name of the product for transaction i
        nameOfProduct = transactions_[i].getNameOfProduct();
        // check if the product is available
        if(inventory_[nameOfProduct].isAvailable())
        {
            // get the price of the product
            price = inventory_[nameOfProduct].getPrice();
            // process the transaction i
            transactions_[i].processTransaction(price);
            // if the transaction is approved, deliver the product
            if(transactions_[i].isApproved())
            {
                --inventory_[nameOfProduct];
                transactions_[i].setProductDelivered();
            }
        }
        else
        {
            transactions_[i].refund();
        }
    }
}

void VendingMachine::printTransactions()
{
    std::cout << "[" << std::endl;
    for(int i=0; i<transactions_.size(); i++)
    {
        std::cout << transactions_[i];
        if(i<transactions_.size()-1)
            std::cout << "," << std::endl;
        else
            std::cout << std::endl;
    }
    std::cout << "]" << std::endl;
}

