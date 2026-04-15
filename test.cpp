#include <iostream>
#include <vector>
#include <string>
#include "core_numeric.h"

using namespace std;

struct Coordenadas {
    double x, y;

    Coordenadas operator+(const Coordenadas& otra) const {
        return {x + otra.x, y + otra.y};
    }

    Coordenadas operator/(size_t n) const {
        return {x / n, y / n};
    }
};

int main() {

    vector<double> valores = {2.0, 4.0, 6.0, 8.0, 10.0};

    cout << "Suma: " << core_numeric::sum(valores) << "\n";
    cout << "Promedio: " << core_numeric::mean(valores) << "\n";
    cout << "Varianza: " << core_numeric::variance(valores) << "\n";
    cout << "Max: " << core_numeric::max(valores) << "\n";

    auto tr_result = core_numeric::transform_reduce(valores, [](double x) { return x * x; });
    cout << "Transform Reduce (x^2): " << tr_result << "\n\n";

    cout << "Variadic Templates:\n";
    cout << "Suma Variadic: " << core_numeric::sum_variadic(1, 2, 3, 4, 5) << "\n";
    cout << "Promedio Variadic (if constexpr): " << core_numeric::mean_variadic(1, 2, 3) << "\n";
    cout << "Max Variadic: " << core_numeric::max_variadic(1.5, 9.9, 3.2, 4.1) << "\n\n";

    cout << "clase propias\n";
    vector<Coordenadas> ruta = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    Coordenadas suma_ruta = core_numeric::sum(ruta);
    cout << "Suma " << suma_ruta.x << ", (Y): " << suma_ruta.y << "\n";

    return 0;
}