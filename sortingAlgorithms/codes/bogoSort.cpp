#include <bits/stdc++.h>
#include <chrono>
using namespace std;

// Función para verificar si el vector está ordenado
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// Función para generar una permutación aleatoria
void shuffleVector(vector<int>& arr) {
    random_shuffle(arr.begin(), arr.end());
}

// Función para imprimir un vector en un archivo
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

    // BogoSort
    while (!isSorted(arr)) {
        shuffleVector(arr);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    outFile << "Sorted Array\n";
    printVector(arr, outFile);
    outFile << "Time taken: " << elapsed.count() << " seconds\n";

    return 0;
}
