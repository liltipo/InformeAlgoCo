//implementacion: https://www.mgaillard.fr/2020/08/29/matrix-multiplication-optimizing.html

#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;

// Estructura de datos para matrices
template <typename T>
struct AbstractMatrix
{
    typedef T Type;

    size_t rows;
    size_t cols;
    T* elements;

    T& at(size_t i, size_t j)
    {
        return elements[j + i * cols];
    }

    const T& at(size_t i, size_t j) const
    {
        return elements[j + i * cols];
    }

    void allocate(size_t n_rows, size_t n_cols)
    {
        rows = n_rows;
        cols = n_cols;
        elements = new T[rows*cols];
    }

    void free()
    {
        rows = 0;
        cols = 0;
        delete[] elements;
    }
};

using Matrix = AbstractMatrix<float>;

// Función para multiplicar dos matrices de forma con optimización de caché
void MatMulCacheOptimizedOpenMP(Matrix& c, const Matrix& a, const Matrix& b)
{
    fill_n(c.elements, c.rows * c.cols, 0.f);
    
    #pragma omp parallel for
    for (size_t i = 0; i < c.rows; i++)
    {
        for (size_t k = 0; k < a.cols; k++)
        {
            for (size_t j = 0; j < c.cols; j++)
            {
                c.at(i, j) += a.at(i, k) * b.at(k, j);
            }
        }
    }
}

// Función para medir el tiempo de ejecución
template <void Function(Matrix&, const Matrix&, const Matrix&)>
double measureTime(Matrix& c, const Matrix& a, const Matrix& b)
{
    const int N = 1;

    auto start_time = chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        Function(c, a, b);
    }
    auto end_time = chrono::steady_clock::now();

    return chrono::duration<double, milli> (end_time - start_time).count() / N;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size>" << endl;
        return 1;
    }       

    size_t N = atoi(argv[1]);

    cout << "Matrix size: " << float(N * N * sizeof(Matrix::Type)) / 1e6 << " MB" << endl;

    // Crear matrices A, B, C y R de tamaño NxN
    Matrix a, b, c, r;

    a.allocate(N, N);
    b.allocate(N, N);
    c.allocate(N, N);

    // Inicializar matrices
    cout << "Init matrices" << endl;
    for (size_t i = 0; i < N*N; i++)
    {
        a.elements[i] = i + 1;
        b.elements[i] = 2*i + 1;
    }

    // Medir el tiempo de ejecución del algoritmo de Strassen
    cout << "MatMulCacheOptimizedOpenMP time: " << flush;
    const auto matMulCacheOptimizedOpenMPTime = measureTime<MatMulCacheOptimizedOpenMP>(c, a, b);
    cout << matMulCacheOptimizedOpenMPTime << " ms" << endl;
    
    // Liberar memoria
    a.free();
    b.free();
    c.free();

    return 0;
}
