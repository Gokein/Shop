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
	std::cin >> UserMoney;
	int TotCost = 0;
	int TotProd = 0;
	string menu[5] = {
	"1. Show available products\n",
	"2. Make a purchase\n",
	"3. Get recommendation to spend max money\n",
	"4. Get recommendation to buy max products\n",
	"5. Exit\n" };
	


	while (true) {
		cout << "\nMenu\n"
			<< menu[0]
			<< menu[1]
			<< menu[2]
			<< menu[3]
			<< menu[4]
			<< "Enter you choice: ";
		int choice;
		std::cin >> choice;

		switch (choice) {
			case 1:	
				for (auto& Product : products)
					cout << Product.name << " - price: " << Product.price << "| quantity: " << Product.quantity << "\n";
				break;
			case 2: {
				cout << "Enter products you want to buy (name and quantity), enter 'done' when finished: ";

				while (true) {
					string name;
					int quantity;
					std::cin >> name;
					if (name == "done") break;

					std::cin >> quantity;
				}
				break;
			}	
			case 5:
				return 0;
			default: 
				cout << "\nWrong input\n";
				return 0;
		}
	}
}