#ifndef TRABALHO_UTILIDADES_H
#define TRABALHO_UTILIDADES_H



template <typename T>
class vec2{
public:
    vec2<T>(T x, T y);
    /// Calcula a distancia entre o proprio vetor e outro
    float distanciaAte(vec2<T> a);

    T x;
    T y;
};

#endif //TRABALHO_UTILIDADES_H
