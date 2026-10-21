#include <iostream>
using namespace std;

int particion(int arr[], int bajo, int alto) {
    int pivote = arr[alto]; 
    int i = bajo - 1;      

    for (int j = bajo; j < alto; j++) {
        if (arr[j] <= pivote) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
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

void imprimirArreglo(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Arreglo original: ";
    imprimirArreglo(arr, n);

    quickSort(arr, 0, n - 1);

    cout << "Arreglo ordenado: ";
    imprimirArreglo(arr, n);

    return 0;
}