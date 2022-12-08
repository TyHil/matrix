#include "matrix.h"
#include <iostream>

using namespace std;

int main() {
  int **x = new int*[3];
  for (int i = 0; i < 3; i++) {
    x[i] = new int[3];
    for (int j = 0; j < 3; j++) {
      x[i][j] = 3 * i + j + 1;
    }
  }
  Matrix<int> * matrix1 = new Matrix<int>(x, 3, 3);
  std::cout << "matrix1:\n" << *matrix1 << "\n\n";
  
  Matrix<int> * matrix2 = new Matrix<int>(3, 3);
  matrix2->setIdentity();
  std::cout << "matrix2:\n" << *matrix2 << "\n\n";

  *matrix2 += *matrix1;
  std::cout << "*matrix2 += *matrix1:\n" << *matrix2 << "\n\n";

  *matrix1 -= *matrix2;
  std::cout << "*matrix1 -= *matrix2:\n" << *matrix1 << "\n\n";

  *matrix1 *= *matrix2;
  std::cout << "*matrix1 *= *matrix2:\n" << *matrix1 << "\n\n";

  *matrix1 *= 8;
  std::cout << "*matrix1 *= 8:\n" << *matrix1 << "\n\n";

  *matrix1 /= -8;
  std::cout << "*matrix1 /= -8:\n" << *matrix1 << "\n\n";

  *matrix1 = *matrix1^2;
  std::cout << "*matrix1 = *matrix1^2:\n" << *matrix1 << "\n\n";

  matrix2->setAll(1);
  std::cout << "matrix2->setAll(1):\n" << *matrix2 << "\n\n";

  matrix2->setIdentity();
  std::cout << "matrix2->setIdentity():\n" << *matrix2 << "\n\n";

  matrix1->swapRows(0, 1);
  std::cout << "matrix1->swapRows(0, 1):\n" << *matrix1 << "\n\n";

  matrix1->transpose();
  std::cout << "matrix1->transpose():\n" << *matrix1 << "\n\n";

  std::cout << "*(matrix1[0][1]):\n" << *(matrix1[0][1]) << "\n";
  std::cout << "(*matrix1)(0,1):\n" << (*matrix1)(0,1) << "\n\n";
}
