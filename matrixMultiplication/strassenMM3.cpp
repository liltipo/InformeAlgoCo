#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;

template <typename T>
struct AbstractMatrix
{
    typedef T Type;

    size_t rows;
    size_t cols;
    T* elements;

    T& at(size_t i, size_t j)
    {
        // Row major
        return elements[j + i * cols];
    }

    const T& at(size_t i, size_t j) const
    {
        // Row major
        return elements[j + i * cols];
    }

    void allocate(size_t n_rows, size_t n_cols)
    {
        rows = n_rows;
        cols = n_cols;
        elements = new T[rows * cols];
    }

    void free()
    {
        rows = 0;
        cols = 0;
        delete[] elements;
    }
};

using Matrix = AbstractMatrix<float>;

Matrix add(const Matrix& A, const Matrix& B, size_t N)
{
    Matrix C;
    C.allocate(N, N);

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            C.at(i, j) = A.at(i, j) + B.at(i, j);
        }
    }

    return C;
}

Matrix subtract(const Matrix& A, const Matrix& B, size_t N)
{
    Matrix C;
    C.allocate(N, N);

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            C.at(i, j) = A.at(i, j) - B.at(i, j);
        }
    }

    return C;
}

void strassen(Matrix &C, const Matrix &A, const Matrix &B, size_t N)
{
    if (N == 1) {
        C.at(0, 0) = A.at(0, 0) * B.at(0, 0);
        return;
    }

    size_t K = N / 2;

    Matrix A11, A12, A21, A22, B11, B12, B21, B22;
    Matrix C11, C12, C21, C22;
    A11.allocate(K, K); A12.allocate(K, K); A21.allocate(K, K); A22.allocate(K, K);
    B11.allocate(K, K); B12.allocate(K, K); B21.allocate(K, K); B22.allocate(K, K);
    C11.allocate(K, K); C12.allocate(K, K); C21.allocate(K, K); C22.allocate(K, K);

    for (size_t i = 0; i < K; i++) {
        for (size_t j = 0; j < K; j++) {
            A11.at(i, j) = A.at(i, j);
            A12.at(i, j) = A.at(i, j + K);
            A21.at(i, j) = A.at(i + K, j);
            A22.at(i, j) = A.at(i + K, j + K);

            B11.at(i, j) = B.at(i, j);
            B12.at(i, j) = B.at(i, j + K);
            B21.at(i, j) = B.at(i + K, j);
            B22.at(i, j) = B.at(i + K, j + K);
        }
    }

    Matrix S1 = subtract(B12, B22, K);
    Matrix S2 = add(A11, A12, K);
    Matrix S3 = add(A21, A22, K);
    Matrix S4 = subtract(B21, B11, K);
    Matrix S5 = add(A11, A22, K);
    Matrix S6 = add(B11, B22, K);
    Matrix S7 = subtract(A12, A22, K);
    Matrix S8 = add(B21, B22, K);
    Matrix S9 = subtract(A11, A21, K);
    Matrix S10 = add(B11, B12, K);

    Matrix P1, P2, P3, P4, P5, P6, P7;
    P1.allocate(K, K); P2.allocate(K, K); P3.allocate(K, K); P4.allocate(K, K); P5.allocate(K, K);
    P6.allocate(K, K); P7.allocate(K, K);

    strassen(P1, A11, S1, K);
    strassen(P2, S2, B22, K);
    strassen(P3, S3, B11, K);
    strassen(P4, A22, S4, K);
    strassen(P5, S5, S6, K);
    strassen(P6, S7, S8, K);
    strassen(P7, S9, S10, K);

    C11 = add(subtract(add(P5, P4, K), P2, K), P6, K);
    C12 = add(P1, P2, K);
    C21 = add(P3, P4, K);
    C22 = subtract(subtract(add(P5, P1, K), P3, K), P7, K);

    for (size_t i = 0; i < K; i++) {
        for (size_t j = 0; j < K; j++) {
            C.at(i, j) = C11.at(i, j);
            C.at(i, j + K) = C12.at(i, j);
            C.at(i + K, j) = C21.at(i, j);
            C.at(i + K, j + K) = C22.at(i, j);
        }
    }

    A11.free(); A12.free(); A21.free(); A22.free();
    B11.free(); B12.free(); B21.free(); B22.free();
    C11.free(); C12.free(); C21.free(); C22.free();
    S1.free(); S2.free(); S3.free(); S4.free(); S5.free();
    S6.free(); S7.free(); S8.free(); S9.free(); S10.free();
    P1.free(); P2.free(); P3.free(); P4.free(); P5.free();
    P6.free(); P7.free();
}

template <void Function(Matrix&, const Matrix&, const Matrix&, size_t)>
double measureTime(Matrix& c, const Matrix& a, const Matrix& b, size_t N)
{
    const int iterations = 1;

    auto start_time = chrono::steady_clock::now();
    for (int i = 0; i < iterations; i++) {
        Function(c, a, b, N);
    }
    auto end_time = chrono::steady_clock::now();

    return chrono::duration<double, milli>(end_time - start_time).count() / iterations;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size>" << endl;
        return 1;
    }

    size_t N = atoi(argv[1]);
    cout << "Matrix size: " << float(N * N * sizeof(Matrix::Type)) / 1e6 << " MB" << endl;

    Matrix a, b, c;

    a.allocate(N, N);
    b.allocate(N, N);
    c.allocate(N, N);

    cout << "Init matrices" << endl;
    for (size_t i = 0; i < N*N; i++)
    {
        a.elements[i] = i + 1;
        b.elements[i] = 2 * i + 1;
    }

    cout << "Strassen time: " << flush;
    const auto strassenTime = measureTime<strassen>(c, a, b, N);
    cout << strassenTime << " ms" << endl;

    a.free();
    b.free();
    c.free();

    return 0;
}
