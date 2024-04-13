#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

// Structure to hold item details
struct Item
{
    string name;
    double price;
    int quantity;
};

// Function to read item details from CSV file
vector<Item> readItemsFromCSV(const string &filename)
{
    vector<Item> items;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return items;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name, price, quantity;
        getline(ss, name, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');
        Item item = {name, stod(price), stoi(quantity)};
        items.push_back(item);
    }

    file.close();
    return items;
}

// Function to display menu
void displayMenu(const vector<Item> &items)
{
    cout << "=============================" << endl;
    cout << "Welcome to the E-Cart" << endl;
    cout << "=============================" << endl;
    cout << "Available Items:" << endl;
    cout << setw(20) << left << "Name" << setw(10) << "Price" << endl;
    cout << "----------------------------" << endl;
    for (const auto &item : items)
    {
        cout << setw(20) << left << item.name << setw(10) << item.price << endl;
    }
    cout << "----------------------------" << endl;
}

// Function to process order
void processOrder(vector<Item> &items, vector<Item> &order)
{
    string itemName;
    int quantity;
    cout << "Enter the name of the item you want to purchase: ";
    cin >> itemName;
    cout << "Enter the quantity: ";
    cin >> quantity;

    for (auto &item : items)
    {
        if (item.name == itemName)
        {
            if (item.quantity >= quantity)
            {
                cout << "Your order for " << quantity << " " << itemName << "(s) has been added." << endl;
                item.quantity -= quantity;

                bool found = false;
                for (auto &orderedItem : order)
                {
                    if (orderedItem.name == itemName)
                    {
                        orderedItem.quantity += quantity;
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    order.push_back({itemName, item.price, quantity});
                }
            }
            else
            {
                cout << "Sorry, only " << item.quantity << " " << itemName << "(s) are available." << endl;
            }
            return;
        }
    }
    cout << "Item not found." << endl;
}

void evaluateBill(vector<Item> &order){
    double totalAmount = 0.0;

    cout << "Order Summary:" << endl;
    cout << setw(20) << left << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(15) << "Total" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (const auto& item : order) {
        double itemTotal = item.price * item.quantity;
        totalAmount += itemTotal;
        cout << setw(20) << left << item.name << setw(10) << item.price << setw(10) << item.quantity << setw(15) << itemTotal << endl;
    }
    cout << "-----------------------------------------------------------" << endl;
    cout << "Net Amount Payable: $" << fixed << setprecision(2) << totalAmount << endl;
}
void buyer(vector<Item> &items)
{
    int choice;
    vector<Item> order;
    displayMenu(items);
    do
    {
        cout << "Options:" << endl;
        cout << "1. Place Order" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            processOrder(items, order);
            break;
        case 2:
            evaluateBill(order);
            cout << "Thank you for shopping with us!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 2);
}

void seller(vector<Item> &items)
{
    int choice;
    do
    {
        cout << "Options:" << endl;
        cout << "1. Add New Item" << endl;
        cout << "2. Update Item Quantity" << endl;
        cout << "3. Update Item Price" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name;
            double price;
            int quantity;
            cout << "Enter the name of the new item: ";
            cin.ignore(); // Ignore the newline character from the previous input
            getline(cin, name);
            cout << "Enter the price of the new item: ";
            cin >> price;
            cout << "Enter the quantity of the new item: ";
            cin >> quantity;
            Item newItem = {name, price, quantity};
            items.push_back(newItem);
            cout << "New item added successfully." << endl;
        }
        break;
        case 2:
        {
            string name;
            int newQuantity;
            cout << "Enter the name of the item you want to update: ";
            cin.ignore(); // Ignore the newline character from the previous input
            getline(cin, name);
            bool found = false;
            for (auto &item : items)
            {
                if (item.name == name)
                {
                    found = true;
                    cout << "Enter the new quantity for " << name << ": ";
                    cin >> newQuantity;
                    item.quantity = newQuantity;
                    cout << "Item quantity updated successfully." << endl;
                    break;
                }
            }
            if (!found)
            {
                cout << "Item not found." << endl;
            }
        }
        break;
        case 3:
        {
            string name;
            double newPrice;
            cout << "Enter the name of the item you want to update: ";
            cin.ignore(); // Ignore the newline character from the previous input
            getline(cin, name);
            bool found = false;
            for (auto &item : items)
            {
                if (item.name == name)
                {
                    found = true;
                    cout << "Enter the new price for " << name << ": ";
                    cin >> newPrice;
                    item.price = newPrice;
                    cout << "Item price updated successfully." << endl;
                    break;
                }
            }
            if (!found)
            {
                cout << "Item not found." << endl;
            }
        }
        break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}

int main()
{
    const string filename = "items.csv";
    vector<Item> items = readItemsFromCSV(filename);
    if (items.empty())
    {
        cerr << "No items available. Exiting." << endl;
        return 1;
    }

    int choice;
    do
    {
        cout << "Enter your choice:" << endl;
        cout << "1. Buy Items\n2. Sell Items\n3. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            buyer(items);
            break;
        case 2:
            seller(items);
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    // Update CSV file with new item quantities
    ofstream outFile(filename);
    for (const auto &item : items)
    {
        outFile << item.name << "," << item.price << "," << item.quantity << endl;
    }
    outFile.close();

    return 0;
}