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

class Engine{
public:
    void setSpeed(int spd);
    int getSpeed();
    void setBrand(const std::string& name);
    std::string getBrandName() {return this->brand.getBrandName();}
private:
    int engineSpeed;
    IBrand brand;
};

class BMWEngine final: public Engine{
public:
    BMWEngine() {
        setSpeed(100);
        setBrand("BMW Engine");
    }
};
class MercedezEngine final: public Engine{
public:
    MercedezEngine() {
        setSpeed(80);
        setBrand("Mercedez Engine");
    }
};

class Plane{
public:
    void setEngine(Engine*);
    void setInterior(Interior*);
    void setBrand(IBrand*);
    std::string getEngine() {return this->engine->getBrandName();}
    std::string getInterior() {return this->interior->getBrandName();}
    std::string getBrand() {return this->brand->getBrandName();}
private:
    Engine* engine;
    Interior* interior;
    IBrand* brand;
};


class Builder{
public:
    Builder() {plane = new Plane;}
    void setEngine(Engine* engine) {
        plane->setEngine(engine);
    }
    void setInterior(Interior* interior) {
        plane->setInterior(interior);
    }
    void setBrand(IBrand* brand) {
        plane->setBrand(brand);
    }
    Plane* getPlane() {
        return this->plane;
    }
private:
    Plane* plane;
};

class Director{
public:
    Director() {builder = new Builder;}
    Plane* createPlane(Engine* engine, Interior* interior, IBrand* brand) {
        builder->setEngine(engine);
        builder->setInterior(interior);
        builder->setBrand(brand);
        return builder->getPlane();
    }
private:
    Builder* builder;
};

int main() {
    Director director;
    MercedezEngine benz_engine;
    LuxuryInterior lv_interior;
    IBrand Virgin;
    Virgin.setBrand("Virgin Airline");
    
    Plane* plane = director.createPlane(&benz_engine, &lv_interior, &Virgin);
    std::cout << plane->getEngine() << ',' << plane->getInterior() << ',' << plane->getBrand() << std::endl;
    return 0;
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
