#include <bits/stdc++.h>
#include <chrono>
using namespace std;

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

    // Ordenamiento utilizando std::sort
    std::sort(arr.begin(), arr.end());

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    outFile << "Sorted Array\n";
    printVector(arr, outFile);
    outFile << "Time taken: " << elapsed.count() << " seconds\n";

    return 0;
}
