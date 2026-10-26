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

// ALGORITMOS DE ORDENAMIENTO

// Insercion
void insercion(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];    
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;     
    }
}

// Quicksort 

int particion(int arr[], int bajo, int alto) {

    int medio = (bajo + alto) / 2;
    int temp = arr[medio];
    arr[medio] = arr[alto];
    arr[alto] = temp;

    int pivote = arr[alto];
    int i = bajo - 1;  

    for (int j = bajo; j < alto; j++) {
        if (arr[j] <= pivote) {
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

void quickSort(int arr[], int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arr, bajo, alto);
        quickSort(arr, bajo, pi - 1);    
        quickSort(arr, pi + 1, alto);  
    }
}


//DEMO

void imprimir(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void copiar(const int origen[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

bool estaOrdenado(const int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

bool sonIguales(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main() {
    const int N = 10;
    const unsigned SEMILLA = 42;
    int original[N], a[N], b[N];

    cout << "=== Patrones (n = " << N << ", semilla = " << SEMILLA << ") ===" << endl;
    for (int p = 0; p < NUM_PATRONES; p++) {
        generarArreglo(original, N, p, SEMILLA);
        copiar(original, a, N);
        copiar(original, b, N);

        insercion(a, N);
        quickSort(b, 0, N - 1);

        cout << "\nPatron: " << nombrePatron(p) << endl;
        cout << "  Original:  ";
        imprimir(original, N);
        cout << "  Insercion: ";
        imprimir(a, N);
        cout << "  Quicksort: ";
        imprimir(b, N);

        if (estaOrdenado(a, N) && estaOrdenado(b, N) && sonIguales(a, b, N)) {
            cout << "  -> Ambos ordenaron bien" << endl;
        } else {
            cout << "  -> ERROR: algo salio mal" << endl;
        }
    }

    cout << "\n=== Prueba de la semilla (patron aleatorio) ===" << endl;
    int x[N], y[N], z[N];
    generarArreglo(x, N, ALEATORIO, 42);
    generarArreglo(y, N, ALEATORIO, 42);
    generarArreglo(z, N, ALEATORIO, 43);

    cout << "semilla 42: "; imprimir(x, N);
    cout << "semilla 42: "; imprimir(y, N);
    cout << "semilla 43: "; imprimir(z, N);

    if (sonIguales(x, y, N)) cout << "Misma semilla -> mismo arreglo (correcto)" << endl;
    if (!sonIguales(x, z, N)) cout << "Otra semilla  -> otro arreglo (correcto)" << endl;

    return 0;
}