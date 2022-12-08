#include <iostream>

template <typename T>
class Matrix {
  public:
    Matrix(int, int);
    Matrix(T **, int, int);
    ~Matrix();
    Matrix(const Matrix<T> &);
    Matrix<T> & operator = (const Matrix<T> &);

    T * operator [] (int);
    T & operator () (int, int);

    Matrix<T> & operator += (const Matrix<T> &);
    Matrix<T> & operator -= (const Matrix<T> &);
    Matrix<T> & operator *= (const Matrix<T> &);
    Matrix<T> & operator *= (T);
    Matrix<T> & operator /= (T);
    Matrix<T> operator ^ (T);

    template <typename U>
    friend std::ostream & operator << (std::ostream &, Matrix<U> &);

    Matrix<T> * setAll(T);
    Matrix<T> * setIdentity();
    Matrix<T> * swapRows(int, int);
    Matrix<T> * transpose();

    static Matrix<T> createIdentity(int);

  private:
    int rows, cols;
    T ** matrix;
    void clear();
    void allocateSpace();
    Matrix<T> exponentRecusion(const Matrix<T> &, T);
};



/* Public */

template <typename T>
Matrix<T>::Matrix(int r, int c) : rows(r), cols(c) { //Constructor
  allocateSpace();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = 0;
    }
  }
}

template <typename T>
Matrix<T>::Matrix(T ** m, int r, int c) : rows(r), cols(c) { //Constructor
  allocateSpace();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = m[i][j];
    }
  }
}

template <typename T> Matrix<T>::~Matrix() { //Destructor
  clear();
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> & m) : rows(m.rows), cols(m.cols) { //Constructor
  allocateSpace();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = m.matrix[i][j];
    }
  }
}

template <typename T>
Matrix<T> & Matrix<T>::operator = (const Matrix<T> & m) { //Assignment
  if (this == &m) {
    return *this;
  }
  if (rows != m.rows || cols != m.cols) {
      clear();
      rows = m.rows;
      cols = m.cols;
      allocateSpace();
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = m.matrix[i][j];
    }
  }
  return *this;
}

template <typename T>
T * Matrix<T>::operator [] (int c) { //Access
  return matrix[c];
}

template <typename T>
T & Matrix<T>::operator () (int c, int r) { //Access
  return matrix[r][c];
}

template <typename T>
Matrix<T> & Matrix<T>::operator += (const Matrix<T> & m) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] += m.matrix[i][j];
    }
  }
  return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator -= (const Matrix<T> & m) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] -= m.matrix[i][j];
    }
  }
  return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator *= (const Matrix<T> & m) {
  Matrix<T> temp = Matrix(rows, m.cols);
  for (int i = 0; i < temp.rows; i++) {
    for (int j = 0; j < temp.cols; j++) {
      for (int k = 0; k < cols; k++) {
        temp.matrix[i][j] += (matrix[i][k] * m.matrix[k][j]);
      }
    }
  }
  return (*this = temp);
}

template <typename T>
Matrix<T> & Matrix<T>::operator *= (T num) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] *= num;
    }
  }
  return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator /= (T num) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] /= num;
    }
  }
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator ^ (T num) {
  Matrix<T> temp = Matrix(*this);
  return exponentRecusion(temp, num);
}

template <typename T>
std::ostream & operator << (std::ostream & out, Matrix<T> & m) { //ostream overload
  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.cols; j++) {
      out << m.matrix[i][j];
      if (j < m.cols - 1) {
        out << ' ';
      }
    }
    if (i < m.rows - 1) {
      out << '\n';
    }
  }
  return out;
}

template <typename T>
Matrix<T> * Matrix<T>::setAll(T set) { //Set all to 0
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = set;
    }
  }
  return this;
}

template <typename T>
Matrix<T> * Matrix<T>::setIdentity() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == j) {
        matrix[i][j] = 1;
      } else {
        matrix[i][j] = 0;
      }
    }
  }
  return this;
}

template <typename T>
Matrix<T> * Matrix<T>::swapRows(int row1, int row2) { //Swap row1 and row2
  T *temp = matrix[row1];
  matrix[row1] = matrix[row2];
  matrix[row2] = temp;
  return this;
}

template <typename T>
Matrix<T> * Matrix<T>::transpose() {
  Matrix<T> temp = Matrix(cols, rows);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      temp.matrix[j][i] = matrix[i][j];
    }
  }
  *this = temp;
  return this;
}

template <typename T>
Matrix<T> Matrix<T>::createIdentity(int size) {
  Matrix<T> temp = Matrix(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        temp.matrix[i][j] = 1;
      } else {
        temp.matrix[i][j] = 0;
      }
    }
  }
  return temp;
}



/* Private */

template <typename T>
void Matrix<T>::clear() {
  for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

template <typename T>
void Matrix<T>::allocateSpace() { //create space for matrix
  matrix = new T * [rows];
  for (int i = 0; i < rows; i++) {
    matrix[i] = new T [cols];
  }
}

template <typename T>
Matrix<T> Matrix<T>::exponentRecusion(const Matrix<T> & m, T num) {
  if (num == 0) {
    return createIdentity(m.rows);
  } else if (num == 1) {
    return m;
  } else if (num % 2 == 0) {
    return exponentRecusion(m * m, num/2);
  } else {
    return m * exponentRecusion(m * m, (num-1)/2);
  }
}



/* Non-self operator overloads */

template <typename T>
Matrix<T> operator + (const Matrix<T> & m1, const Matrix<T> & m2) {
  Matrix<T> temp = Matrix(m1);
  return (temp += m2);
}

template <typename T>
Matrix<T> operator - (const Matrix<T> & m1, const Matrix<T> & m2) {
  Matrix<T> temp = Matrix(m1);
  return (temp -= m2);
}

template <typename T>
Matrix<T> operator * (const Matrix<T> & m1, const Matrix<T> & m2) {
  Matrix<T> temp = Matrix(m1);
  return (temp *= m2);
}

template <typename T>
Matrix<T> operator * (const Matrix<T> & m, T num) {
  Matrix<T> temp = Matrix(m);
  return (temp *= num);
}

template <typename T>
Matrix<T> operator * (T num, const Matrix<T> & m) {
  return (m * num);
}

template <typename T>
Matrix<T> operator / (const Matrix<T> & m, T num) {
  Matrix<T> temp = Matrix(m);
  return (temp /= num);
}
