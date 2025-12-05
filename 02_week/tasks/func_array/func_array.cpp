#include <cstddef>


double ApplyOperations(double a, double b, double (**functions)(double, double), size_t size) {
    if(size == 0) return 0.0;

    double res{};
    for(size_t i = 0; i < size; ++i){
        res += functions[i] == nullptr ? 0.0 : functions[i](a, b);
    }

    return res;
}