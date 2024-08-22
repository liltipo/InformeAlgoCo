#include <bits/stdc++.h>
#include <chrono>
using namespace std;

// Función de partición para QuickSort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Función principal de QuickSort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Función para imprimir un vector
void printVector(const vector<int>& arr, ofstream& outFile) {
    for (int val : arr) {
        outFile << val << " ";
    }
    outFile << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);

    vector<int> arr;
    int num;
    while (inFile >> num) {
        arr.push_back(num);
    }

    auto start = chrono::high_resolution_clock::now();

    quickSort(arr, 0, arr.size() - 1);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    outFile << "Sorted Array\n";
    printVector(arr, outFile);
    outFile << "Time taken: " << elapsed.count() << " seconds\n";

    return 0;
}
