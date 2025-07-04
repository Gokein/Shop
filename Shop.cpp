#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

struct Product {
	string name;
	int price;
	int quantity;
};
struct ShoppingCart {
	map<string, int> items;
	int TotCost = 0;
	int TotProd = 0;
};

class Store {
private:
	vector<Product> products;
	int UserMoney;
public:
	Store(const vector<Product>& initialProducts, int money)
		: products(initialProducts), UserMoney(money) {}
	ShoppingCart checkPurchase(const map<string, int>& userCart) {
		ShoppingCart cart;
		bool allAvailable = true;

		for (const auto& item : userCart) {
			string productName = item.first;
			int desiredQuantity = item.second;

			auto it = find_if(products.begin(), products.end(),
				[&productName](const Product& p) {return p.name == productName; });
			if (it != products.end() && it->quantity >= desiredQuantity) {
				cart.items[productName] = desiredQuantity;
				cart.TotCost += it->price * desiredQuantity;
				cart.TotProd += desiredQuantity;
			}
			else {
				allAvailable = false;
			}
		}
		if (!allAvailable || cart.TotCost > UserMoney) {
			cart.items.clear();
			cart.TotCost = 0;
			cart.TotProd = 0;

		}
		return cart;
	}

	bool makePurchase(const map<string, int>& userCart) {
		ShoppingCart cart = checkPurchase(userCart);
		if (cart.items.empty()) {
			cout << "Purchase cannot be completed. Either some items are not available or not enough money.\n";
			return false;
		}
		for (const auto& item : cart.items) {
			string productName = item.first;
			int purchasedQuantity = item.second;

			auto it = find_if(products.begin(), products.end(),
				[&productName](const Product& p) { return p.name == productName; });

			it->quantity -= purchasedQuantity;
		}

		UserMoney -= cart.TotCost;

		cout << "Purchase successful!\n";
		cout << "Total cost: " << cart.TotCost << "\n";
		cout << "Items bought: ";
		for (const auto& item : cart.items) {
			cout << item.first << " (" << item.second << "), ";
		}
		cout << "\nRemaining money: " << UserMoney << "\n";

		return true;


	}
	void printProducts() 
		const {
		cout << "Available products:\n";
		for (const auto& product : products) {
			cout << product.name << " - Price: " << product.price 
				<< ", Quantity: " << product.quantity << "\n";
		}

	}
};

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

	int UserMoney;
	cout << "Enter how many money you have: ";
	cin >> UserMoney;

	Store store(products, UserMoney);

	while (true) {
		cout << "\nMenu\n" 
			<< "1. Show available products\n"
			<< "2. Make a purchase\n"
			<< "3. Get recommendation to spend max money\n"
			<< "4. Get recommendation to buy max products\n"
			<< "5. Exit\n"
			<< "Enter you choice: ";

		int choice;
		cin >> choice;

		switch (choice) {
			case 1: 
				store.printProducts();
				break;
			case 2: {
				map<string, int> userCart;
				cout << "Enter products you want to buy (name and quantity), enter 'done' when finished: ";

				while (true) {
					string name;
					int quantity;
					cin >> name;
					if (name == "done") break;

					cin >> quantity;
					userCart[name] = quantity;
				}
				store.makePurchase(userCart);
				break;
			}	
			case 5:
				return 0;
			default: 
				cout << "\nWrong input\n";
		}
	}
}