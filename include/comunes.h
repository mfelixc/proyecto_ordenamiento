#ifndef COMUNES_H
#define COMUNES_H

#include <iostream>
#include <random>
using namespace std;

enum Patron { ALEATORIO, ASCENDENTE, DESCENDENTE, CASI_ORDENADO, DUPLICADOS };
const int NUM_PATRONES = 5;

const unsigned RANGO_ALEATORIO = 1000000;


const unsigned VALORES_UNICOS = 15;


const int PORCENTAJE_CASI = 5;

inline const char* nombrePatron(int p) {
    if (p == ALEATORIO) return "aleatorio";
    if (p == ASCENDENTE) return "ascendente";
    if (p == DESCENDENTE) return "descendente";
    if (p == CASI_ORDENADO) return "casi_ordenado";   
    return "duplicados";
}

inline void generarArreglo(int arr[], int n, int patron, unsigned semilla) {
    mt19937 gen(semilla);
    if (patron == ALEATORIO) {
        for (int i = 0; i < n; i++) {
            arr[i] = gen() % RANGO_ALEATORIO;
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
        int cambios = (n * PORCENTAJE_CASI / 100) / 2;
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
            arr[i] = gen() % VALORES_UNICOS;
        }
    }
}

inline void copiar(const int origen[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

inline bool estaOrdenado(const int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

inline bool sonIguales(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

#endif
