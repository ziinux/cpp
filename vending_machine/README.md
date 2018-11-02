Vending Machine
===============

This is a software for a vending machine. 

This software takes two command-line arguments.  The first argument is the
path to the inventory JSON file.  The second argument is the path to the transactions
JSON file.

* Inventory: specifies how the vending machine is stocked, with product names,
  and a quantity and price (in dollars) for each product
* Transactions: a list of purchase transactions, with the product name, and the
  value (in cents) of coins deposited

It produces a JSON document, on stdout, containing a list of transaction results.

Each result identifies the product name, whether a product was delivered, 
and the change given, as a list of coin values.

To compile use the following commands:
```
cd cpp/build
rm -r *
cmake ../
make
```

To run the program use the folowing command
```
cd cpp/build
./VendingMachine <path_to_inventory_json_file> <path_to_transactions_json_file>
```

To run all the tests, use the run_tests.py script with Python 3.x:
```
python3 run_tests.py
```

