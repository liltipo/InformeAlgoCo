#include <iostream>
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

bool areMatricesEqual(const Matrix& a, const Matrix& b)
{
    for (size_t i = 0; i < a.rows; i++)
    {
        for (size_t j = 0; j < a.cols; j++)
        {
            if (a.at(i, j) != b.at(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

void MatMul(Matrix& c, const Matrix& a, const Matrix& b)
{
    fill_n(c.elements, c.rows * c.cols, 0.f);

    for (size_t i = 0; i < c.rows; i++)
    {
        for (size_t j = 0; j < c.cols; j++)
        {
            for (size_t k = 0; k < a.cols; k++)
            {
                c.at(i, j) += a.at(i, k) * b.at(k, j);
            }
        }
    }
}

template <void Function(Matrix&, const Matrix&, const Matrix&)>
double measureTime(Matrix& c, const Matrix& a, const Matrix& b)
{
    const int N = 1;

    auto start_time = chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        Function(c, a, b);
    }
    auto end_time = chrono::steady_clock::now();

    return chrono::duration<double, milli>(end_time - start_time).count() / N;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size>" << endl;
        return 1;
    }

    size_t N = atoi(argv[1]);
    cout << "Matrix size: " << float(N * N * sizeof(Matrix::Type)) / 1e6 << " MB" << endl;

    Matrix a, b, c, r;

    a.allocate(N, N);
    b.allocate(N, N);
    c.allocate(N, N);
    r.allocate(N, N);

    cout << "Init matrices" << endl;
    for (size_t i = 0; i < N*N; i++)
    {
        a.elements[i] = i + 1;
        b.elements[i] = 2*i + 1;
    }

    cout << "MatMul time: " << flush;
    const auto matMulTime = measureTime<MatMul>(r, a, b);
    cout << matMulTime << " ms" << endl;

    a.free();
    b.free();
    c.free();
    r.free();

    return 0;
}
