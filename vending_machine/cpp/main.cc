//============================================================================
// Name        : main.cc
// Author      : BADR EL HAFIDI badr@gatech.edu 
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : main file for Vending Machine software
//============================================================================

#include "src/VendingMachine.h"
#include "src/Product.h"
#include "src/Transaction.h"

int main(int argc, char** argv)
{   
    std::string pathToInventory = argv[1];
    std::string pathToTransactions = argv[2];
    try
    {
        VendingMachine vm(pathToInventory,pathToTransactions);
        vm.processTransactions();
        vm.printTransactions();
    }
    catch (std::string err)
    {
        std::cerr << err << std::endl;
    }

    return 0;
}
