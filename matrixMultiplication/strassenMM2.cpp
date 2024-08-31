#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

typedef long long lld;

// Función para sumar dos matrices
lld** MatrixAdd(lld** A, lld** B, int size) {
    lld** result = new lld*[size];
    for (int i = 0; i < size; i++) {
        result[i] = new lld[size];
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Función para restar dos matrices
lld** MatrixSubtract(lld** A, lld** B, int size) {
    lld** result = new lld*[size];
    for (int i = 0; i < size; i++) {
        result[i] = new lld[size];
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Función para multiplicar matrices usando el algoritmo de Strassen
lld** Strassen(lld** A, lld** B, int size) {
    if (size == 1) {
        lld** C = new lld*[1];
        C[0] = new lld[1];
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = size / 2;
    lld** C = new lld*[size];

    // Inicializar matrices
    for (int i = 0; i < size; i++) {
        C[i] = new lld[size];
    }

    lld** A11 = new lld*[newSize];
    lld** A12 = new lld*[newSize];
    lld** A21 = new lld*[newSize];
    lld** A22 = new lld*[newSize];
    lld** B11 = new lld*[newSize];
    lld** B12 = new lld*[newSize];
    lld** B21 = new lld*[newSize];
    lld** B22 = new lld*[newSize];

    // Dividir las matrices en submatrices
    for (int i = 0; i < newSize; i++) {
        A11[i] = new lld[newSize];
        A12[i] = new lld[newSize];
        A21[i] = new lld[newSize];
        A22[i] = new lld[newSize];
        B11[i] = new lld[newSize];
        B12[i] = new lld[newSize];
        B21[i] = new lld[newSize];
        B22[i] = new lld[newSize];

        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular los productos de Strassen
    lld** M1 = Strassen(MatrixAdd(A11, A22, newSize), MatrixAdd(B11, B22, newSize), newSize);
    lld** M2 = Strassen(MatrixAdd(A21, A22, newSize), B11, newSize);
    lld** M3 = Strassen(A11, MatrixSubtract(B12, B22, newSize), newSize);
    lld** M4 = Strassen(A22, MatrixSubtract(B21, B11, newSize), newSize);
    lld** M5 = Strassen(MatrixAdd(A11, A12, newSize), B22, newSize);
    lld** M6 = Strassen(MatrixSubtract(A21, A11, newSize), MatrixAdd(B11, B12, newSize), newSize);
    lld** M7 = Strassen(MatrixSubtract(A12, A22, newSize), MatrixAdd(B21, B22, newSize), newSize);

    // Calcular las submatrices de C
    lld** C11 = MatrixAdd(MatrixSubtract(MatrixAdd(M1, M4, newSize), M5, newSize), M7, newSize);
    lld** C12 = MatrixAdd(M3, M5, newSize);
    lld** C21 = MatrixAdd(M2, M4, newSize);
    lld** C22 = MatrixAdd(MatrixSubtract(MatrixAdd(M1, M3, newSize), M2, newSize), M6, newSize);

    // Combinar las submatrices en la matriz C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Liberar memoria
    for (int i = 0; i < newSize; i++) {
        delete[] A11[i];
        delete[] A12[i];
        delete[] A21[i];
        delete[] A22[i];
        delete[] B11[i];
        delete[] B12[i];
        delete[] B21[i];
        delete[] B22[i];
        delete[] M1[i];
        delete[] M2[i];
        delete[] M3[i];
        delete[] M4[i];
        delete[] M5[i];
        delete[] M6[i];
        delete[] M7[i];
        delete[] C11[i];
        delete[] C12[i];
        delete[] C21[i];
        delete[] C22[i];
    }

    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
    delete[] M1;
    delete[] M2;
    delete[] M3;
    delete[] M4;
    delete[] M5;
    delete[] M6;
    delete[] M7;
    delete[] C11;
    delete[] C12;
    delete[] C21;
    delete[] C22;

    return C;
}

// Función para medir el tiempo de ejecución
template <typename Func, typename... Args>
double measureTime(Func func, Args&&... args) {
    auto start = chrono::steady_clock::now();
    func(forward<Args>(args)...);
    auto end = chrono::steady_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

lld** StrassenWrapper(lld** A, lld** B, int N) {
    return Strassen(A, B, N);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size>" << endl;
        return 1;
    }

    size_t N = atoi(argv[1]);
    cout << "Matrix size: " << float(N * N * sizeof(int)) / 1e6 << " MB" << endl;

    // Crear matrices A y B de tamaño NxN
    lld** A = new lld*[N];
    lld** B = new lld*[N];

    // Inicializar matrices
    for (int i = 0; i < N; i++) {

        A[i] = new lld[N];
        B[i] = new lld[N];
        for (int j = 0; j < N; j++) {

            A[i][j] = j+1; 
            B[i][j] = 2*j + 1; 
        }
    }

    // Medir el tiempo de ejecución del algoritmo de Strassen
    auto start = chrono::steady_clock::now();
    lld** C = StrassenWrapper(A, B, N);
    auto end = chrono::steady_clock::now();

    // Calcular el tiempo transcurrido
    cout << "Strassen time: " << flush;
    chrono::duration<double, milli> duration = end - start;
    cout << duration.count() << " ms" << endl;

    // Liberar memoria
    for (int i = 0; i < N; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}