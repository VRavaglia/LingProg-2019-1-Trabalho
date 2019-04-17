#include "Utilidades.h"
#include <typeinfo>
#include <string>
#include <math.h>
using namespace std;

template<typename T>
float vec2<T>::distanciaAte(vec2<T> a){
    return sqrt(pow((x - a.x),2) + pow((y - a.y),2));
}

template<typename T>
bool isNumber(T num){
    string tipo = typeid(num).name();
    if(tipo == typeid(int).name())
        return true;
    if(tipo == typeid(unsigned).name())
        return true;
    if(tipo == typeid(float).name())
        return true;
    if(tipo == typeid(double).name())
        return true;
};

template<typename T>
vec2<T>::vec2(T x_, T y_) {
    x = x_;
    y = y_;
}
