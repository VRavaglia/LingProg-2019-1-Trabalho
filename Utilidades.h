#ifndef TRABALHO_UTILIDADES_H
#define TRABALHO_UTILIDADES_H

#include <typeinfo>
#include <string>
#include <math.h>
#include <fstream>
#include "VariaveisConfig.h"
using namespace std;


template <typename T>
class vec2{
public:
    vec2<T>(T x_, T y_) : x(x_), y(y_) {}
    /// Calcula a distancia entre o proprio vetor e outro
    float distanciaAte(vec2<T> a){
        return sqrt(pow((x - a.x),2) + pow((y - a.y),2));
    }
    T x;
    T y;
};

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



#endif //TRABALHO_UTILIDADES_H
