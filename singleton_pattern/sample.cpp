#include <iostream>

class Singleton{
public:
    static Singleton& getInstance() {
        static Singleton obj;
        return obj;
    }
    int getX() {
        return this->x;
    }
    void setX(int v) {
        this->x = v;
    }
    Singleton(const Singleton& that) = delete;
    Singleton& operator=(const Singleton& that) = delete;
private:
    int x;
    Singleton() = default;
};

int main() {
    return 0;
}