
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <string>
#include "comunes.h"
using namespace std;

long long comparaciones = 0;
long long intercambios = 0;  
int profundidadActual = 0;
int profundidadMax = 0;

void reiniciarContadores() {
    comparaciones = 0;
    intercambios = 0;
    profundidadActual = 0;
    profundidadMax = 0;
}

// ALGORITMOS DE ORDENAMIENTO 

// Insercion
void insercion(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;


        while (j >= 0) {
            comparaciones++;
            if (arr[j] <= key) break;
            arr[j + 1] = arr[j];
            intercambios++;
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
    intercambios++;

    int pivote = arr[alto];
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        comparaciones++;
        if (arr[j] <= pivote) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            intercambios++;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = temp;
    intercambios++;
    return i + 1;
}

void quickSort(int arr[], int bajo, int alto) {

    profundidadActual++;
    if (profundidadActual > profundidadMax) profundidadMax = profundidadActual;

    if (bajo < alto) {
        int pi = particion(arr, bajo, alto);
        quickSort(arr, bajo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }

    profundidadActual--;
}

// MEDICION

double medirInsercion(int arr[], int n) {
    reiniciarContadores();
    auto inicio = chrono::steady_clock::now();
    insercion(arr, n);
    auto fin = chrono::steady_clock::now();
    return chrono::duration<double, milli>(fin - inicio).count();
}

double medirQuicksort(int arr[], int n) {
    reiniciarContadores();
    auto inicio = chrono::steady_clock::now();
    quickSort(arr, 0, n - 1);
    auto fin = chrono::steady_clock::now();
    return chrono::duration<double, milli>(fin - inicio).count();
}

void escribirFila(ofstream& csv, const char* algoritmo, int n, const char* patron,
                  int rep, double tiempo, int profundidad, unsigned semilla,
                  const string& commit) {

    csv << algoritmo << "," << n << "," << patron << "," << rep << ","
        << tiempo << "," << comparaciones << "," << intercambios << ","
        << profundidad << "," << semilla << "," << commit << "\n";
}

int main(int argc, char* argv[]) {
    string commit = "sin_commit";
    string rutaCsv = "results/resultados.csv";
    int REPETICIONES = 30;           
    if (argc > 1) commit = argv[1];
    if (argc > 2) rutaCsv = argv[2];
    if (argc > 3) REPETICIONES = atoi(argv[3]);

    const int TAMANIOS[] = {1000, 10000, 100000};
    const int NUM_TAMANIOS = 3;
    const unsigned SEMILLA_BASE = 2024;   

    ofstream csv(rutaCsv.c_str());
    if (!csv) {
        cout << "No pude abrir " << rutaCsv << endl;
        return 1;
    }
    csv << "algoritmo,n,patron,repeticion,tiempo_ms,comparaciones,intercambios,"
        << "profundidad_recursion,semilla,commit_hash\n";

    for (int t = 0; t < NUM_TAMANIOS; t++) {
        int n = TAMANIOS[t];
        int* original = new int[n];
        int* a = new int[n];
        int* b = new int[n];

        for (int p = 0; p < NUM_PATRONES; p++) {
            cout << "n = " << n << ", patron = " << nombrePatron(p) << " ..." << endl;

            for (int r = 1; r <= REPETICIONES; r++) {
                unsigned semilla = SEMILLA_BASE + r;
                generarArreglo(original, n, p, semilla);

                
                copiar(original, a, n);
                copiar(original, b, n);

                double tIns = medirInsercion(a, n);
                escribirFila(csv, "insercion", n, nombrePatron(p), r, tIns, 0, semilla, commit);

                double tQuick = medirQuicksort(b, n);
                escribirFila(csv, "quicksort", n, nombrePatron(p), r, tQuick, profundidadMax, semilla, commit);

                
                if (!estaOrdenado(a, n) || !estaOrdenado(b, n) || !sonIguales(a, b, n)) {
                    cout << "ERROR: algo salio mal (n = " << n << ", patron = "
                         << nombrePatron(p) << ", rep = " << r << ")" << endl;
                    return 1;
                }
            }
        }

        delete[] original;
        delete[] a;
        delete[] b;
    }

    csv.close();
    cout << "Listo. Resultados en " << rutaCsv << endl;
    return 0;
}
