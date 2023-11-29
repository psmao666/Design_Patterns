#include <iostream>

class IBrand{
public:
    void setBrand(const std::string& name);
    std::string getBrandName();
private:
    std::string brandName;
};

class Interior{
public:
    void setN_Seats(int n);
    int getN_Seats();
    void setBrand(const std::string& name);
    std::string getBrandName() {return this->brand.getBrandName();}
private:
    int n_seats;
    IBrand brand;
};

class LuxuryInterior final: public Interior{
public:
    LuxuryInterior() {
        setN_Seats(100);
        setBrand("Louis Vuitton Interior");
    }
};
class NormalInterior final: public Interior{
    NormalInterior() {
        setN_Seats(50);
        setBrand("Qantas Interior");
    }
};

class Engine: public IBrand{
public:
    void setSpeed(int spd);
    int getSpeed();
    void setBrand(const std::string& name);
private:
    int engineSpeed;
    IBrand brand;
};

class Plane{
public:
    void setEngine(Engine*);
    void setInterior(Interior*);
    void setBrand(IBrand*);
    std::string getInteriorBrandName() {return this->interior->getBrandName();}
    std::string getBrand() {return this->brand->getBrandName();}
private:
    Engine* engine;
    Interior* interior;
    IBrand* brand;
};

class Builder{
public:
    void setEngine() {

    }
private:
    Plane* plane;
};

class Director{
public:
  
};

int main() {
    Plane plane;
    plane.setInterior(new LuxuryInterior);
    std::cout << plane.getInteriorBrandName() << std::endl;
}

// implementing IBrand
void IBrand::setBrand(const std::string& name) {
    this->brandName = name;
}
std::string IBrand::getBrandName() {
    return this->brandName;
}
// implementing Interior
void Interior::setN_Seats(int n) {
    this->n_seats = n;
}
int Interior::getN_Seats() {
    return this->n_seats;
}
void Interior::setBrand(const std::string& name) {
    this->brand.setBrand(name);
}
// implementing Engine
void Engine::setSpeed(int spd) {
    this->engineSpeed = spd;
}
int Engine::getSpeed() {
    return this->engineSpeed;
}
void Engine::setBrand(const std::string& name) {
    this->brand.setBrand(name);
}
// implementing plane
void Plane::setEngine(Engine* engine) {
    this->engine = std::move(engine);
}
void Plane::setInterior(Interior* interior) {
    this->interior = std::move(interior);
}
void Plane::setBrand(IBrand* brand) {
    this->brand = std::move(brand);
}