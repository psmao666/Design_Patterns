#include <iostream>
#include <vector>
#include <memory>

class Pizza{
public:
    void printSize() {
        std::cout << this->inch << '*' << this->inch << std::endl;
    }
    virtual std::string printName() {
        return "pizza";
    }
private:
    double inch;
};

class PepproniPizza: public Pizza{
    virtual std::string printName() override {
        return "Pepproni Pizza";
    }
};

class HawaiiPizza: public Pizza{
    virtual std::string printName() override{
        return "Hawaii Pizza";
    }
};

class PizzaFactory{
public:
    enum PizzaType {
        Normal_Pizza,
        Pepproni_Pizza,
        Hawaii_Pizza  
    };
    std::unique_ptr<Pizza> createPizza(PizzaType o) {
        if (o == PizzaType::Normal_Pizza) {
            return std::make_unique<Pizza>();
        }
        if (o == PizzaType::Pepproni_Pizza) {
            return std::make_unique<PepproniPizza>();
        }
        if (o == PizzaType::Hawaii_Pizza) {
            return std::make_unique<HawaiiPizza>();
        }
        return nullptr;
    }
};

int main() {
    PizzaFactory pizzaFactory;
    std::vector<std::unique_ptr<Pizza>> pizzas;
    int n_orders;
    std::cin >> n_orders;
    for (int i = 0; i < n_orders; ++ i) {
        pizzas.push_back(pizzaFactory.createPizza(PizzaFactory::PizzaType::Normal_Pizza));
        pizzas.push_back(pizzaFactory.createPizza(PizzaFactory::PizzaType::Pepproni_Pizza));
        pizzas.push_back(pizzaFactory.createPizza(PizzaFactory::PizzaType::Hawaii_Pizza));
    }
    for (const auto& pizza: pizzas) {
        std::cout << (*pizza).printName() << std::endl;
    }
}