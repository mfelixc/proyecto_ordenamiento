
#include <iostream>
#include <random>
using namespace std;

enum Patron { ALEATORIO, ASCENDENTE, DESCENDENTE, CASI_ORDENADO, DUPLICADOS };
const int NUM_PATRONES = 5;

const char* nombrePatron(int p) {
    if (p == ALEATORIO) return "aleatorio";
    if (p == ASCENDENTE) return "ascendente";
    if (p == DESCENDENTE) return "descendente";
    if (p == CASI_ORDENADO) return "casi ordenado";
    return "duplicados";
}

int main() {
    return 0;
}
