#include <bits/stdc++.h>
#include <chrono>
using namespace std;

// Función para fusionar dos subvectores
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Función principal de MergeSort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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

    mergeSort(arr, 0, arr.size() - 1);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;

    outFile << "Sorted Array\n";
    printVector(arr, outFile);
    outFile << "Time taken: " << elapsed.count() << " ms\n";

    return 0;
}
