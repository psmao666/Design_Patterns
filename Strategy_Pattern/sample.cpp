#include <iostream>
#include <memory>

class IQuackStrategy;
class IFlyStrategy;

class IQuackStrategy{
public:
    virtual ~IQuackStrategy() = default;
    virtual void quack() = 0;
};
class IFlyStrategy{
public:
    virtual void fly() = 0;
};

class SimpleQuack final: public IQuackStrategy{
public:
    virtual void quack() override{
        std::cout << "quack!\n";
    }
};
class SimpleFly final: public IFlyStrategy{
public:
    virtual void fly() override {
        std::cout << "Fly!\n";
    }
};

class WildQuack final: public IQuackStrategy{
public:
    virtual void quack() override{
        std::cout << "WOW! QUACK!\n";
    }
};

class Duck{
public:
    IQuackStrategy* quack_behavior;
    IFlyStrategy* fly_behavior;

    Duck(IQuackStrategy* quack_strat, IFlyStrategy* fly_strat) {
        quack_behavior = quack_strat;
        fly_behavior = fly_strat;
    }
    virtual void quack() {
        this->quack_behavior->quack();
    }
    virtual void fly() {
        this->fly_behavior->fly();
    }
};

class RubberDuck final: public Duck{
public:
    RubberDuck(IQuackStrategy* quack_strat, IFlyStrategy* fly_strat): Duck(quack_strat, fly_strat) {
    }
    virtual void fly() {}
};
class WildDuck final: public Duck{
public:
    WildDuck(IQuackStrategy* quack_strat, IFlyStrategy* fly_strat): Duck(quack_strat, fly_strat) {
    }
};

int main() {
    WildQuack wild_quack;
    SimpleQuack simple_quack;
    SimpleFly simple_fly;

    Duck* rubber_duck = new RubberDuck(&simple_quack, &simple_fly);
    rubber_duck->quack();
    rubber_duck->fly();
    Duck* wild_duck = new WildDuck(&wild_quack, &simple_fly);
    wild_duck->quack();
    wild_duck->fly();

    return 0;
}
