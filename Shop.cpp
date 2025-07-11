#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Product {
    string name;
    int price;
    int quantity;
};

void DisplayProduct(const vector<Product>& products, int us_money) {
    cout << "\nAvailable products\n";
    for (auto& Product : products) {
        cout << Product.name << " - price: " << Product.price << "| quantity: " << Product.quantity << "\n";
    }
    cout << "You have " << us_money << " Money\n";
}

bool Shop(vector<Product>& products, string& us_name, int us_quantity, int& us_money) {
    bool product_found = false;

    for (int i = 0; i < products.size(); i++) {
        if (us_name == products[i].name) {
            product_found = true;
            if (us_quantity <= 0) {
                cout << "Invalid quantity. Please enter positive number.\n";
                return false;
            }

            int tot_Cost = us_quantity * products[i].price;

            if (tot_Cost > us_money) {
                cout << "You haven't enough money:\nProduct cost: " << tot_Cost << " You have: " << us_money;
                return false;
            }
            if (products[i].quantity < us_quantity) {
                cout << "Not enough " << us_name << " in stock (available: " << products[i].quantity << ")\n";
                return false;
            }

            us_money -= tot_Cost;
            products[i].quantity -= us_quantity;
            cout << "You have bought " << us_name << " in the size " << us_quantity << " of pieces\n";
            return true;
        }
    }
    if (!product_found) {
        cout << "Product '" << us_name << "' not found\n";
        cin.clear();
        return false;
    }
}

int GetMoney() {
    int money = 0;
    cout << "Enter how many money you have: ";
    while (!(cin >> money) || money < 0) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Invalid input. Please enter positive number: ";
    }
    return money;
}

int main() {
    vector<Product> products = {
        {"bagel", 30, 20},
        {"bread", 40, 8},
        {"cabbage", 120, 4},
        {"cake", 220, 2},
        {"corn", 80, 6},
        {"eggs", 100, 5},
        {"milk", 80, 14},
        {"salt", 70, 4},
        {"sausage", 90, 8}
    };

    int us_money = GetMoney();
    string menu[3] = {
        "1. Show available products\n",
        "2. Make a purchase\n",
        "3. Exit\n" };

    while (true) {
        cout << "\nMenu\n"
            << "1. Show available products\n"
            << "2. Make a purchase\n"
            << "3. Exit\n"
            << "Enter you choice: ";
        int choice;
        while (!(cin >> choice)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Invalid input. Please enter number 1-3: ";
        }
        switch (choice) {
        case 1:
            DisplayProduct(products, us_money);
            break;
        case 2: {
            cout << "Enter products you want to buy (name and quantity), enter 'done' when finished: ";

            while (true) {
                string us_name;
                int us_quantity;

                cin >> us_name;
                if (us_name == "done") break;

                if (!(cin >> us_quantity) || us_quantity <= 0) {
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "Invalid quantity. Please enter positive number (rewrite you'r request):\n ";
                    continue;
                }

                Shop(products, us_name, us_quantity, us_money);
            }
            break;
        }
        case 3:
            cout << "Thank you for shopping with us!\n";
            return 0;
        default:
            cout << "\nWrong input\n";
        }
    }
}