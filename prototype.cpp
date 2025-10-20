#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class Product {
private:
    string name;
    double price;
    int quantity;
public:
    Product(string n, double p, int q) : name(n), price(p), quantity(q) {}

    unique_ptr<Product> clone() const {
        return make_unique<Product>(name, price, quantity);
    }

    void show() const {
        cout << "- " << name << " | Цена: " << price << " KZT | Кол-во: " << quantity << endl;
    }
};

class Discount {
private:
    string description;
    double percent;
public:
    Discount(string d, double p) : description(d), percent(p) {}

    unique_ptr<Discount> clone() const {
        return make_unique<Discount>(description, percent);
    }

    void show() const {
        cout << "Скидка: " << description << " (" << percent << "%)\n";
    }
};

class Order {
private:
    vector<unique_ptr<Product>> products;
    unique_ptr<Discount> discount;
    double deliveryCost;
    string paymentMethod;

public:
    Order(double delivery, string payment)
        : deliveryCost(delivery), paymentMethod(payment) {}

    void addProduct(const Product& p) {
        products.push_back(p.clone());
    }

    void setDiscount(const Discount& d) {
        discount = d.clone();
    }

    unique_ptr<Order> clone() const {
        auto newOrder = make_unique<Order>(deliveryCost, paymentMethod);
        for (const auto& p : products)
            newOrder->addProduct(*p);
        if (discount)
            newOrder->setDiscount(*discount);
        return newOrder;
    }

    void show() const {
        cout << "\n=== Заказ ===\n";
        for (const auto& p : products)
            p->show();
        if (discount)
            discount->show();
        cout << "Доставка: " << deliveryCost << " KZT\n";
        cout << "Оплата: " << paymentMethod << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Order baseOrder(1500, "Банковская карта");
    baseOrder.addProduct(Product("Ноутбук", 350000, 1));
    baseOrder.addProduct(Product("Мышь", 8000, 2));
    baseOrder.setDiscount(Discount("Осенняя акция", 10));

    cout << "📦 Базовый заказ:";
    baseOrder.show();

    auto clonedOrder = baseOrder.clone();
    clonedOrder->addProduct(Product("Наушники", 25000, 1));

    cout << "\n🆕 Клонированный заказ (с изменениями):";
    clonedOrder->show();

    cout << "\n✅ Демонстрация паттерна 'Прототип' завершена.\n";

    return 0;
}
 
