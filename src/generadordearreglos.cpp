

#include <iostream>
#include <random>
using namespace std;


// GENERADOR DE ARREGLOS POR SEMILLA

enum Patron { ALEATORIO, ASCENDENTE, DESCENDENTE, CASI_ORDENADO, DUPLICADOS };
const int NUM_PATRONES = 5;

const char* nombrePatron(int p) {
    if (p == ALEATORIO) return "aleatorio";
    if (p == ASCENDENTE) return "ascendente";
    if (p == DESCENDENTE) return "descendente";
    if (p == CASI_ORDENADO) return "casi ordenado";
    return "duplicados";
}


void generarArreglo(int arr[], int n, int patron, unsigned semilla) {
    mt19937 gen(semilla);   

    if (patron == ALEATORIO) {

        for (int i = 0; i < n; i++) {
            arr[i] = gen() % 1001;
        }
    } else if (patron == ASCENDENTE) {

        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
    } else if (patron == DESCENDENTE) {

        for (int i = 0; i < n; i++) {
            arr[i] = n - i;
        }
    } else if (patron == CASI_ORDENADO) {

        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
        int cambios = n / 10;
        if (cambios < 1) cambios = 1;
        for (int k = 0; k < cambios; k++) {
            int a = gen() % n;
            int b = gen() % n;
            int temp = arr[a];
            arr[a] = arr[b];
            arr[b] = temp;
        }
    } else {

        for (int i = 0; i < n; i++) {
            arr[i] = gen() % 5;
        }
    }
}

int main() {
    return 0;
}