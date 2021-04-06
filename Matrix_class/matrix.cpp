#include <iostream>
#include <iomanip>

namespace CustomMatrix{

    const unsigned int WIDTH = 3;


    template <class Element> class Matrix{
    private:
        int rows = 1, cols = 1;       // кол-во строк и столбцов
        Element** matrix = nullptr;   // указатель на матрицу

    public:
        Matrix(int, int);             // конструктор
        Matrix(int, int, Element*);   // конструктор с линеаризованным массивом
        Matrix(int, int, Element**);  // конструктор с двумерным массивом
        Matrix(const Matrix&);        // конструктор копирования
        ~Matrix();                    // деструктор

        int get_rows_num() { return rows; }      // получение числа строк
        int get_cols_num() { return cols; }      // получение числа столбцов

        //обмен местами
        Matrix change_rows(int, int);
        Matrix change_cols(int, int);
        Matrix get_minor(int, int);         // минор
        Matrix transpose_matrix();          // транспонированная матрица
        Element det();    // определитель
        Element calculate_algebraic_complement(int, int); // алгебраическое дополнение


        Element* operator [](int);          // обращение по индексу: matrix[i]
        Matrix& operator = (const Matrix&); // присваивание

        //сложение
        Matrix operator +(Matrix);
        Matrix operator +(Element);

        //вычитание
        Matrix operator -(Matrix);
        Matrix operator -(Element);

        //умножение
        Matrix operator *(Matrix);
        Matrix operator *(Element);

        Matrix operator /(Element);   // деление

        operator bool();              // приведение к типу bool

        //сравнение матриц
        bool operator ==(Matrix);
        bool operator !=(Matrix);
    };


    // Конструкторы, оператор копирования, деструктор
    template <class Element> Matrix<Element>::Matrix(int rows, int cols){
        matrix = new Element * [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new Element[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = 0;
    }

    template <class Element> Matrix<Element>::Matrix(int rows, int cols, Element* arr){
        matrix = new Element * [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new Element[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = arr[i * cols + j];
    }

    template <class Element> Matrix<Element>::Matrix(int rows, int cols, Element** arr){
        matrix = new Element * [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new Element[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = arr[i][j];
    }

    template <class Element> Matrix<Element>::Matrix(const Matrix& copy){
        rows = copy.rows;
        cols = copy.cols;

        matrix = new Element * [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new Element[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = copy.matrix[i][j];
    }

    template <class Element> Matrix<Element>::~Matrix(){
        for (int i = 0; i < rows; i++)
            delete[] matrix[i];
        delete[] matrix;
    }


    // Оператор обращения по индексу и оператор присваивания
    template <class Element> Element* Matrix<Element>::operator [](int i){
        return matrix[i];
    }

    template <class Element> Matrix<Element>& Matrix<Element>::operator =(const Matrix<Element>& other){
        if (matrix != nullptr) {
            for (int i = 0; i < rows; i++)
                delete[] matrix[i];
            delete[] matrix;
        }

        rows = other.rows;
        cols = other.cols;

        matrix = new Element * [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new Element[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = other.matrix[i][j];

        return *this;
    }


    // Арифметические операции
    template <class Element> Matrix<Element> Matrix<Element>::operator +(Matrix arr){
        if (arr.get_rows_num() == rows && arr.get_cols_num() == cols) {
            Matrix res = *this;
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    res[i][j] += arr[i][j];
            return res;
        }
        return Matrix(1, 1);
    }

    template <class Element> Matrix<Element> Matrix<Element>::operator +(Element num){
        Matrix res = *this;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                res[i][j] += num;
        return res;
    }

    template <class Element> Matrix<Element> Matrix<Element>::operator -(Matrix arr){
        if (arr.get_rows_num() == rows && arr.get_cols_num() == cols) {
            Matrix res = *this;
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    res[i][j] -= arr[i][j];
            return res;
        }
        return Matrix(1, 1);
    }

    template <class Element> Matrix<Element> Matrix<Element>::operator -(Element num){
        Matrix res = *this;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                res[i][j] -= num;
        return res;
    }

    template <class Element> Matrix<Element> Matrix<Element>::operator *(Matrix arr){
        if (cols == arr.get_rows_num()) {
            Matrix res(rows, arr.get_cols_num());
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < arr.get_cols_num(); j++) {
                    Element sum = 0;
                    for (int k = 0; k < cols; k++)
                        sum += matrix[i][k] * arr[k][j];
                    res[i][j] = sum;
                }
            return res;
        }
        return Matrix(1, 1);
    }

    template <class Element> Matrix<Element> Matrix<Element>::operator *(Element num){
        Matrix res = *this;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                res[i][j] *= num;
        return res;
    }

    template <class Element> Matrix<Element> Matrix<Element>::operator /(Element num){
        Matrix res = *this;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                res[i][j] /= num;
        return res;
    }


    // Логические операции
    template <class Element> Matrix<Element>::operator bool(){
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (matrix[i][j])
                    return true;
        return false;
    }

    template <class Element> bool Matrix<Element>::operator ==(Matrix arr){
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (matrix[i][j] != arr[i][j])
                    return false;
        return true;
    }

    template <class Element> bool Matrix<Element>::operator !=(Matrix arr){
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (matrix[i][j] != arr[i][j])
                    return true;
        return false;
    }


    // Ввод и вывод
    template <class Element> std::ostream& operator<<(std::ostream& stream, Matrix<Element> obj){
        for (int i = 0; i < obj.get_rows_num(); i++) {
            stream << "[ ";
            for (int j = 0; j < obj.get_cols_num(); j++)
                stream << std::setw(WIDTH) << std::right << obj[i][j] << "  ";
            stream << " ]\n";
        }
        return stream;
    }

    template <class Element> std::istream& operator>>(std::istream& stream, Matrix<Element>& obj){
        // ввод производится в одну строку
        for (int i = 0; i < obj.get_rows_num(); i++)
            for (int j = 0; j < obj.get_cols_num(); j++)
                stream >> obj[i][j];
        return stream;
    }


    // Матричные операции
    template <class Element> Matrix<Element> Matrix<Element>::change_rows(int row1, int row2){
        Matrix res = *this;
        Element* temp_row = new Element[cols];
        for (int i = 0; i < cols; i++)
            temp_row[i] = res[row1][i];
        for (int i = 0; i < cols; i++)
            res[row1][i] = res[row2][i];
        for (int i = 0; i < cols; i++)
            res[row2][i] = temp_row[i];
        return res;
    }

    template <class Element> Matrix<Element> Matrix<Element>::change_cols(int col1, int col2)
    {
        Matrix res = *this;
        Element* temp_col = new Element[rows];
        for (int i = 0; i < rows; i++)
            temp_col[i] = res[i][col1];
        for (int i = 0; i < rows; i++)
            res[i][col1] = res[i][col2];
        for (int i = 0; i < rows; i++)
            res[i][col2] = temp_col[i];
        return res;
    }

    template <class Element> Matrix<Element> Matrix<Element>::get_minor(int row, int col){
        Matrix minor(rows - 1, cols - 1);
        for (int i = 0; i < rows; i++)
            if (i == row) continue;
            else
                for (int j = 0; j < cols; j++)
                    if (j == col) continue;
                    else
                        minor[(i > row) ? i - 1 : i][(j > col) ? j - 1 : j] = matrix[i][j];

        return minor;
    }

    template <class Element> Matrix<Element> Matrix<Element>::transpose_matrix() {
        Matrix res = *this;
        Element temp;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < i; j++){
                temp = res[i][j];
                res[i][j] = res[j][i];
                res[j][i] = temp;
            }
        return res;
    }

    template <class Element> Element Matrix<Element>::calculate_algebraic_complement(int row, int col) {
        return (((row + col) % 2) ? -1 : 1) * (get_minor(row, col).det());
    }

    template <class Element> Element Matrix<Element>::det() {
        if (rows == cols)
        {
            if (cols == 1)
                return matrix[0][0];
            double det = 0;
            for (int i = 0; i < cols; i++)
                det += matrix[0][i] * calculate_algebraic_complement(0, i);
            return det;
        }
        return 0;
    }

    //Double
    template <> class Matrix<double>
    {
    private:
        int rows = 1, cols = 1;      // число строк и столбцов
        double** matrix = nullptr;   // указатель на матрицу

    public:
        Matrix(int, int);            // конструктор
        Matrix(int, int, double*);   // конструктор с линеаризованным массивом
        Matrix(int, int, double**);  // конструктор с двумерным массивом
        Matrix(const Matrix&);       // конструктор копирования
        ~Matrix();                   // деструктор

        int get_rows_num() { return rows; };      // получение числа строк
        int get_cols_num() { return cols; };      // получение числа столбцов

        Matrix change_rows(int, int);        // поменять местами две строки матрицы
        Matrix change_cols(int, int);        // поменять местами два столбца матрицы
        Matrix get_minor(int, int);          // получение минора матрицы для элемента с индексами i и j
        double calculate_algebraic_complement(int, int);  // вычисление алгебраического дополнения
        double det();      // вычисление определителя матрицы
        Matrix transpose_matrix();           // получения транспонированной матрицы
        Matrix inverse_matrix();         // получение обратной матрицы
        Matrix Kramer();           // решение системы методом Крамера
        Matrix Gauss();            // решение системы методом Гаусса


        double* operator [](int);            // обращение по индексу: matrix[i]
        Matrix& operator = (const Matrix&);  // присваивание

        Matrix operator +(Matrix);    // сложение матриц
        Matrix operator +(double);    // сложение матрицы с числом (поэлементно)

        Matrix operator -(Matrix);    // вычитание матриц
        Matrix operator -(double);    // вычитание из матрицы числа (поэлементно)

        Matrix operator *(Matrix);    // умножение мариц
        Matrix operator *(double);    // умножение матрицы на число (поэлементно)

        Matrix operator /(Matrix);    // деление матриц (умножение на обратную справа: A * B^(-1)
        Matrix operator /(double);    // деление матрицы на число (поэлементно)

        operator bool();              // приведение к типу bool
        bool operator ==(Matrix);     // сравнение матриц на равенство (поэлементно)
        bool operator !=(Matrix);     // сравнение матриц на неравенство (поэлементно)
    };


    // Конструкторы, оператор копирования, деструктор
    Matrix<double>::Matrix(int r, int c)
    {
        rows = r;
        cols = c;

        matrix = new double* [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new double[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = 0;
    }

    Matrix<double>::Matrix(int r, int c, double* arr)
    {
        rows = r; cols = c;

        matrix = new double* [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new double[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = arr[i * cols + j];
    }

    Matrix<double>::Matrix(int r, int c, double** arr)
    {
        rows = r; cols = c;

        matrix = new double* [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new double[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = arr[i][j];
    }

    Matrix<double>::Matrix(const Matrix& other)
    {
        rows = other.rows;
        cols = other.cols;

        matrix = new double* [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new double[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = other.matrix[i][j];
    }

    Matrix<double>::~Matrix()
    {
        for (int i = 0; i < rows; i++)
            delete[] matrix[i];
        delete[] matrix;
    }


    // Оператор обращения по индексу и оператор присваивания
    double* Matrix<double>::operator [](int i)
    {
        return matrix[i];
    }

    Matrix<double>& Matrix<double>::operator =(const Matrix& other)
    {
        if (matrix != nullptr) {
            for (int i = 0; i < rows; i++)
                delete[] matrix[i];
            delete[] matrix;
        }

        rows = other.rows;
        cols = other.cols;

        matrix = new double* [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new double[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = other.matrix[i][j];

        return *this;
    }


    // Арифметические операции
    Matrix<double> Matrix<double>::operator +(Matrix arr)
    {
        if (arr.get_rows_num() == rows && arr.get_cols_num() == cols) {
            Matrix result = *this;
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result[i][j] += arr[i][j];
            return result;
        }
        return Matrix(1, 1);
    }

    Matrix<double> Matrix<double>::operator +(double num)
    {
        Matrix result = *this;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result[i][j] += num;
        return result;
    }

    Matrix<double> Matrix<double>::operator -(Matrix arr)
    {
        if (arr.get_rows_num() == rows && arr.get_cols_num() == cols) {
            Matrix result = *this;
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result[i][j] -= arr[i][j];
            return result;
        }
        return Matrix(1, 1);
    }

    Matrix<double> Matrix<double>::operator -(double num)
    {
        Matrix result = *this;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result[i][j] -= num;
        return result;
    }

    Matrix<double> Matrix<double>::operator *(Matrix arr)
    {
        if (cols == arr.get_rows_num()) {
            Matrix result(rows, arr.get_cols_num());
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < arr.get_cols_num(); j++) {
                    double sum = 0;
                    for (int k = 0; k < cols; k++)
                        sum += matrix[i][k] * arr[k][j];
                    result[i][j] = sum;
                }
            return result;
        }
        return Matrix(1, 1);
    }

    Matrix<double> Matrix<double>::operator *(double num)
    {
        Matrix result = *this;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result[i][j] *= num;
        return result;
    }

    Matrix<double> Matrix<double>::operator /(Matrix arr)
    {
        if (cols == arr.get_rows_num() && arr.get_cols_num() == arr.get_rows_num())
            return *this * arr.inverse_matrix();
        return Matrix(1, 1);
    }

    Matrix<double> Matrix<double>::operator /(double num)
    {
        Matrix result = *this;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result[i][j] /= num;
        return result;
    }


    //Логические операторы:
    Matrix<double>::operator bool()
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (matrix[i][j])
                    return true;
        return false;
    }

    bool Matrix<double>::operator ==(Matrix arr)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (matrix[i][j] != arr[i][j])
                    return false;
        return true;
    }

    bool Matrix<double>::operator !=(Matrix arr)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (matrix[i][j] != arr[i][j])
                    return true;
        return false;
    }


    // Операторы ввода-вывода
    std::ostream& operator<<(std::ostream& stream, Matrix<double> obj)
    {
        for (int i = 0; i < obj.get_rows_num(); i++) {
            stream << "[ ";
            for (int j = 0; j < obj.get_cols_num(); j++)
                stream << std::setw(WIDTH) << std::right << obj[i][j] << "  ";
            stream << " ]\n";
        }
        return stream;
    }

    std::istream& operator>>(std::istream& stream, Matrix<double>& obj)
    {
        // ввод производится в одну строку
        for (int i = 0; i < obj.get_rows_num(); i++)
            for (int j = 0; j < obj.get_cols_num(); j++)
                stream >> obj[i][j];
        return stream;
    }


    // Матричные операции
    Matrix<double> Matrix<double>::change_rows(int row1, int row2)
    {
        Matrix result = *this;
        double* temp_row = new double[cols];
        for (int i = 0; i < cols; i++) temp_row[i] = result[row1][i];
        for (int i = 0; i < cols; i++) result[row1][i] = result[row2][i];
        for (int i = 0; i < cols; i++) result[row2][i] = temp_row[i];
        return result;
    }

    Matrix<double> Matrix<double>::change_cols(int col1, int col2)
    {
        Matrix result = *this;
        double* temp_col = new double[rows];
        for (int i = 0; i < rows; i++) temp_col[i] = result[i][col1];
        for (int i = 0; i < rows; i++) result[i][col1] = result[i][col2];
        for (int i = 0; i < rows; i++) result[i][col2] = temp_col[i];
        return result;
    }

    Matrix<double> Matrix<double>::get_minor(int row, int col)
    {
        Matrix minor(rows - 1, cols - 1);
        for (int i = 0; i < rows; i++)
            if (i == row) continue;
            else
                for (int j = 0; j < cols; j++)
                    if (j == col) continue;
                    else
                        minor[(i > row) ? i - 1 : i][(j > col) ? j - 1 : j] = matrix[i][j];

        return minor;
    }

    Matrix<double> Matrix<double>::transpose_matrix() {
        Matrix result = *this;
        double temp;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < i; j++) {
                temp = result[i][j];
                result[i][j] = result[j][i];
                result[j][i] = temp;
            }
        return result;
    }


    double Matrix<double>::calculate_algebraic_complement(int row, int col) {
        return (((row + col) % 2) ? -1 : 1) * (get_minor(row, col).det());
    }

    double Matrix<double>::det() {
        if (rows == cols)
        {
            if (cols == 1)
                return matrix[0][0];
            double det = 0;
            for (int i = 0; i < cols; i++)
                det +=  matrix[0][i] * calculate_algebraic_complement(0, i);
            return det;
        }
        return 0;
    }

    Matrix<double> Matrix<double>::inverse_matrix() {
        if (rows == cols) {
            Matrix ac_matrix(rows, cols);  // Матрица алгебраических дополнений
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    ac_matrix[i][j] = calculate_algebraic_complement(i, j);

            double det_ = det();

            if (det_ != 0)
                return ac_matrix.transpose_matrix() * (1 / det_);
        }
        return Matrix(1, 1);
    }

    Matrix<double> Matrix<double>::Kramer() {

        if (rows == cols - 1) {  // проверка на размерность

            Matrix result(rows, 1);   // результирующий вектор
            Matrix X(rows, cols - 1); // рабочая матрица

            for (int i = 0; i < rows; i++)   // копирование значений исходной матрицы в рабочую
                for (int j = 0; j < cols - 1; j++)
                    X[i][j] = matrix[i][j];

            double det = X.det(), detX_i = 0;   // вычисление определителя

            if (det != 0) {
                for (int i = 0; i < rows; i++) {
                    Matrix X_i(rows, rows);

                    for (int j = 0; j < rows; j++)  // замена столбцов
                        for (int k = 0; k < rows; k++)
                            X_i[j][k] = matrix[j][(k == i) ? rows : k];

                    detX_i = X_i.det();   // вычисление определителей
                    result[i][0] = detX_i / det;      // заполнение результирующего массива
                }
                return result;
            }
        }
        return Matrix(1, 1);
    }

    Matrix<double> Matrix<double>::Gauss(){
        if (rows == cols - 1) {       // проверка на размерность

            Matrix res(rows, 1);   // результирующий вектор
            Matrix X = *this; // рабочая матрица

            for (int k = 0; k < rows - 1; k++) {    // прямой ход Гаусса
                if (X[k][k] == 0)
                    for (int i = k + 1; i < rows; i++)
                        if (X[i][k] != 0) {
                            X = X.change_rows(i, k);
                        }
                if (X[k][k] == 0)
                    return Matrix(1, 1);
                else
                    for (int i = k + 1; i < rows; i++)
                        for (int j = cols - 1; j >= k; j--)
                            X[i][j] -= X[k][j] * X[i][k] / X[k][k];
            }

            // обратный ход Гаусса
            res[rows - 1][0] = X[rows - 1][cols - 1] / X[rows - 1][cols - 2];
            for (int i = rows - 2; i >= 0; i--) {
                double sum = 0;
                for (int j = rows - 1; j > i; j--)
                    sum += X[i][j] * res[j][0];
                res[i][0] = (X[i][cols - 1] - sum) / X[i][i];
            }
            return res;
        }
        return Matrix(1, 1);
    }

}


using namespace std;
using namespace CustomMatrix;


int main(){
    int arr[] = {1, 2, 3, 4};
    Matrix <int> m(2, 2, arr);

    cout << m.calculate_algebraic_complement(0, 0);

    return 0;
}