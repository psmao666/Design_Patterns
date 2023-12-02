#include <iostream>
#include <memory>
#include <unordered_set>
/*
implement a news feed, whenever a important news come in, 
feed the data to corresponding strategies.
*/

class IProducer;
class IObserver;
class Strategy_MeanReversion;
class Strategy_Volatility;
class Strategy_Arbitrager;

class IObserver{
public:
    bool printTradeMode() {
        return ifTrade;
    }
    virtual void update(const std::string& msg) = 0;
    virtual ~IObserver() = default;
protected:
    bool ifTrade{false};
};

class IProducer{
public:
    void addObserver(std::shared_ptr<IObserver> observer) {
        observers.insert(observer);
    }
    void removeObserver(std::shared_ptr<IObserver> observer) {
        observers.erase(observer);
    }
    void notify_all(const std::string& msg) {
        for (const auto& observer: observers) {
            observer->update(msg);
        }
    }
private:
    std::unordered_set<std::shared_ptr<IObserver>> observers;
};

class Strategy_MeanReversion final: public IObserver{
public:
    virtual void update(const std::string& msg) override {
        if (msg.find("but") != std::string::npos) {
            ifTrade = true;
        }
    }
};
class Strategy_Volatility final: public IObserver{
public:
    virtual void update(const std::string& msg) override {
        if (msg.find("large") != std::string::npos) {
            ifTrade = true;
        }
    }
};
class Strategy_Arbitrager final: public IObserver{
public:
    virtual void update(const std::string& msg) override {
        if (msg.find("related") != std::string::npos) {
            ifTrade = true;
        }
    }
};

int main() {
    IProducer producer;
    std::shared_ptr<IObserver> strategy_arbitrager = std::make_shared<Strategy_Arbitrager>(); 
    std::shared_ptr<IObserver> strategy_meanreversion = std::make_shared<Strategy_MeanReversion>();
    std::shared_ptr<IObserver> strategy_volatility = std::make_shared<Strategy_Volatility>();

    producer.addObserver(strategy_arbitrager);
    producer.addObserver(strategy_meanreversion);
    producer.addObserver(strategy_volatility);

    while (1) {
        std::string msg;
        std::getline(std::cin, msg);
        std::cout << msg << std::endl;
        if (msg == "fuck volatility") {
            producer.removeObserver(strategy_volatility);
        }
        producer.notify_all(msg);
        std::cout << "arbitrage: " << strategy_arbitrager->printTradeMode() << std::endl;
        std::cout << "volatility: " << strategy_volatility->printTradeMode() << std::endl;
        std::cout << "mean reversion: " << strategy_meanreversion->printTradeMode() << std::endl;
    }
}