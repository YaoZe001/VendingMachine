#include <iostream>
#include <iomanip>
#include "VendingMachine.h"
using namespace std;

StockItem::StockItem() //Constructor for Stock Item
{
    headerName = ""; 
    itemName = ""; 
    price = 0.0; 
    displayChar = ' '; 
}

StockStack::StockStack() //Constructor for Stock Stack
{
    topNode = NULL;
    currentSize = 0;
    maxCapacity = 10;
}

StockStack::~StockStack() //Destructor for Stock Stack
{
    clear();
}

bool StockStack::push(char c) //Add stock item into stack
{
    if (currentSize >= maxCapacity) 
	{
	    return false;
    }	
    Node* n = new Node(c);
    n->next = topNode;
    topNode = n;
    currentSize++;
    return true;
}

bool StockStack::pop() //Remove stock item
{
    if (isEmpty())
    {
	    return false;
    }	
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
    currentSize--;
    return true;
}

bool StockStack::isEmpty() const //Check whether stack is empty
{
    return topNode == NULL;
}

int StockStack::size() const // Return current number of items
{
    return currentSize;
}

int StockStack::getCapacity() const // Return max capacity of stack
{
    return maxCapacity;
}

void StockStack::clear() //Clear Stack
{
    while (!isEmpty())
    {
        pop();
    }
}

VendingMachine::VendingMachine(int size) //Constructor for Vending Machine
{
    numStocks = size;
    machineTitle = "[INTI Vending Machine]";
    stocks = new StockItem[numStocks];
}

VendingMachine::~VendingMachine() //Destructor for Vending Machine
{
    delete[] stocks;
}

void VendingMachine::adminMenuOption() //Admin Menu for all admin opeartions
{
    int choice = -1;

    while (choice != 6) //Loop until exit
    {
        cout << "\n-------------------------------------" << endl;
        cout << "             ADMIN MENU                 " << endl;
        cout << "-------------------------------------" << endl;
        cout << "1. Replenish Stock" << endl;
        cout << "2. Reset All Stock" << endl;
        cout << "3. Change Price" << endl;
        cout << "4. Change Machine Title" << endl;
        cout << "5. Change Stock Header Name" << endl;
        cout << "6. Exit" << endl;
        cout << "-------------------------------------" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        if (cin.fail()) //Input validation
        {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
            cout << "Invalid input." << endl;
            continue;
        }

        if (choice == 1) //Replenish stock
        {
            int item, quantity;

            cout << "\n---------- REPLENISH STOCK ----------" << endl;

            for (int i = 0; i < numStocks; i++)
            {
                cout << i + 1 << ". " << stocks[i].itemName
                     << " (Current: " << stocks[i].inventory.size()
                     << "/" << stocks[i].inventory.getCapacity() << ")" << endl;
            }

            cout << "Select Item: ";
            cin >> item;

            if (cin.fail() || item < 1 || item > numStocks)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid stock selection." << endl;
                continue;
            }

            if (stocks[item - 1].inventory.size() >=
                stocks[item - 1].inventory.getCapacity())
            {
                cout << "Stock is already full." << endl;
                continue;
            }

            cout << "Quantity to Add: ";
            cin >> quantity;

            if (cin.fail() || quantity <= 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid quantity." << endl;
                continue;
            }

            char characterToPush = stocks[item - 1].displayChar;
            int added = 0;

            for (int i = 0; i < quantity; i++)
            {
                if (stocks[item - 1].inventory.push(characterToPush))
                    added++;
                else
                    break;
            }

            cout << added << " item(s) successfully added." << endl;
        }

        else if (choice == 2) //Reset all stock
        {
            char confirm;

            cout << "\nAre you sure? This will remove all stocks (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y')
            {
                for (int i = 0; i < numStocks; i++)
                    stocks[i].inventory.clear();

                cout << "All stocks have been reset." << endl;
            }
            else
            {
                cout << "Reset cancelled." << endl;
            }
        }

        else if (choice == 3) //Change Price
        {
            int item;
            double newPrice;

            cout << "\n---------- CHANGE PRICE ----------" << endl;

            for (int i = 0; i < numStocks; i++)
            {
                cout << i + 1 << ". " << stocks[i].itemName << " (RM " << fixed << setprecision(2) << stocks[i].price << ")" << endl;
            }

            cout << "Select Item: ";
            cin >> item;

            if (cin.fail() || item < 1 || item > numStocks)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid selection." << endl;
                continue;
            }

            cout << "Enter New Price: ";
            cin >> newPrice;

            if (cin.fail() || newPrice < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid price." << endl;
                continue;
            }

            stocks[item - 1].price = newPrice;
            cout << "Price updated successfully." << endl;
        }

        else if (choice == 4) //Change machine title
        {
            cin.ignore(1000, '\n');

            cout << "\nCurrent Title: " << machineTitle << endl;
            cout << "Enter New Title: ";

            getline(cin, machineTitle);

            machineTitle = "[" + machineTitle + "]";
            cout << "Machine title updated successfully." << endl;
        }

        else if (choice == 5) //Change header name
        {
            int item;

            cout << "\n---------- CHANGE HEADER ----------" << endl;

            for (int i = 0; i < numStocks; i++)
            {
                cout << i + 1 << ". " << stocks[i].headerName << endl;
            }

            cout << "Select Header: ";
            cin >> item;

            if (cin.fail() || item < 1 || item > numStocks)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid selection." << endl;
                continue;
            }

            cin.ignore(1000, '\n');

            cout << "Enter New Header Name: ";
            getline(cin, stocks[item - 1].headerName);

            cout << "Header updated successfully." << endl;
        }

        else if (choice == 6) //Exit admin menu
        {
            cout << "\nLeaving Admin Menu." << endl;
        }
        else
        {
            cout << "Invalid menu choice." << endl;
        }
    }
}
