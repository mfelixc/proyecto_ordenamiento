// estabilidad.cpp
#include <iostream>
#include "comunes.h"
using namespace std;

struct Elemento {
    int clave;
    int id;
};

void insercion(Elemento arr[], int n) {
    for (int i = 1; i < n; i++) {
        Elemento key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].clave > key.clave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int particion(Elemento arr[], int bajo, int alto) {
    int medio = (bajo + alto) / 2;
    Elemento temp = arr[medio];
    arr[medio] = arr[alto];
    arr[alto] = temp;

    int pivote = arr[alto].clave;
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        if (arr[j].clave <= pivote) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = temp;
    return i + 1;
}

void quickSort(Elemento arr[], int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arr, bajo, alto);
        quickSort(arr, bajo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}


int contarInversionesDeEstabilidad(const Elemento arr[], int n) {
    int cuenta = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i - 1].clave == arr[i].clave && arr[i - 1].id > arr[i].id) {
            cuenta++;
        }
    }
    return cuenta;
}

int main() {
    const int N = 1000;
    const unsigned SEMILLA = 2025;
    int original[N];
    Elemento a[N], b[N];

    cout << "=== Estabilidad (n = " << N << ", semilla = " << SEMILLA << ") ===" << endl;

    int patrones[] = {ALEATORIO, DUPLICADOS};
    for (int k = 0; k < 2; k++) {
        int p = patrones[k];
        generarArreglo(original, N, p, SEMILLA);
        for (int i = 0; i < N; i++) {
            a[i].clave = original[i]; a[i].id = i;
            b[i].clave = original[i]; b[i].id = i;
        }

        insercion(a, N);
        quickSort(b, 0, N - 1);

        cout << "\nPatron: " << nombrePatron(p) << endl;
        cout << "  Insercion: " << contarInversionesDeEstabilidad(a, N)
             << " pares de claves iguales fuera de su orden original" << endl;
        cout << "  Quicksort: " << contarInversionesDeEstabilidad(b, N)
             << " pares de claves iguales fuera de su orden original" << endl;
    }
    return 0;
}
