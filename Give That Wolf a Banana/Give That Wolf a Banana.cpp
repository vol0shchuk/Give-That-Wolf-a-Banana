#include <iostream>
#include <string>
using namespace std;

const int MAX_PRODUCTS = 10;

class Product {
public:
    Product() : Product("", 0.0) {}

    Product(const string& name, double price) : name(name), price(price) {}

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

private:
    string name;
    double price;
};

class Order {
public:
    Order(int orderNumber) : Order(orderNumber, "", "") {}

    Order(int orderNumber, const string& customerName, const string& deliveryAddress)
        : orderNumber(orderNumber), customerName(customerName), deliveryAddress(deliveryAddress), productCount(0) {}

    void addProduct(const string& productName, double productPrice) {
        if (productCount < MAX_PRODUCTS) {
            products[productCount++] = Product(productName, productPrice);
        }
        else {
            cout << "Error: Too many products in the order." << endl;
        }
    }

    void removeProduct(const string& productName) {
        for (int i = 0; i < productCount; i++) {
            if (products[i].getName() == productName) {
                products[i] = products[productCount--];
                cout << "Product '" << productName << "' removed from the order." << endl;
                return;
            }
        }
        cout << "Product '" << productName << "' not found in the order." << endl;
    }

    double calculateTotalOrderPrice() const {
        double total = 0.0;
        for (int i = 0; i < productCount; i++) {
            total += products[i].getPrice();
        }
        return total;
    }

    void displayOrderDetails() const {
        cout << "Order Number: " << orderNumber << endl;
        cout << "Customer: " << customerName << endl;
        cout << "Delivery Address: " << deliveryAddress << endl;

        cout << "Products in the order:" << endl;
        for (int i = 0; i < productCount; i++) {
            const auto& product = products[i];
            cout << "  - " << product.getName() << " ($" << product.getPrice() << ")" << endl;
        }

        double total = calculateTotalOrderPrice();
        cout << "Total Price: $" << total << endl;
    }

private:
    int orderNumber;
    string customerName;
    string deliveryAddress;
    Product products[MAX_PRODUCTS];
    int productCount;
};

void addNewProductToOrder(Order& order) {
    string productName;
    double productPrice;

    cout << "Enter product name: ";
    getline(cin, productName);

    cout << "Enter product price: ";
    cin >> productPrice;

    order.addProduct(productName, productPrice);
}

void removeProductFromOrder(Order& order) {
    string productName;
    cout << "Enter the name of the product to remove: ";
    getline(cin, productName);

    order.removeProduct(productName);
}

int main() {
    // Створення замовлення
    int orderNumber;
    cout << "Enter order number: ";
    cin >> orderNumber;
    cin.ignore(); // Clear newline from the buffer

    string customerName, deliveryAddress;
    cout << "Enter customer name: ";
    getline(cin, customerName);

    cout << "Enter delivery address: ";
    getline(cin, deliveryAddress);

    Order order(orderNumber, customerName, deliveryAddress);

    char choice;
    do {
        cout << "Choose an action:\n";
        cout << "1. Add a new product\n";
        cout << "2. Remove a product\n";
        cout << "3. Display order details\n";
        cout << "4. Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from the buffer

        switch (choice) {
        case '1':
            addNewProductToOrder(order);
            break;
        case '2':
            removeProductFromOrder(order);
            break;
        case '3':
            order.displayOrderDetails();
            break;
        case '4':
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please choose a valid action.\n";
        }
    } while (choice != '4');

    return 0;
}
