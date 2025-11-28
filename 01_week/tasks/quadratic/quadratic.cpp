#include <iostream>
#include <iomanip>
#include <cmath>

void SolveQuadratic(int a, int b, int c) {
    //Установка точности вывода в 6 символов
    std::cout << std::setprecision(6);

    double eps = 1e-3;     // Погрешность при сравнении double
    double x1{0}, x2{0};
    long long d = static_cast<long long>(b) * b - 4 * static_cast<long long>(a) * c;
    if(d < 0){
        std::cout << "no solutions";
    }
    else if(a == 0 && b == 0 && c != 0){
        std::cout << "no solutions";
    }
    else if(a != 0){
        x1 = (-b + sqrt(d)) / (2*a);
        x2 = (-b - sqrt(d)) / (2*a);

        if((x1 - x2) < eps){
            std::cout << x1;
        }
        else{
            if(x1 > x2){
                std::swap(x1, x2);
            }
            std::cout << x1 << " " << x2;
        }
    }
    else if(a == 0 && b == 0 && c == 0){
        std::cout << "infinite solutions";
    }
    else if(b != 0){
        x1 = -c / static_cast<double>(b);
        std::cout << x1;
    }
}