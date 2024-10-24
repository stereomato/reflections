#include <stdlib.h>
#include <iostream>

typedef float Matrix4x4 [4][4];

// "Añadir más vértices"
typedef float Matrix4x6 [4][6];

Matrix4x4 transformationMatrix;
Matrix4x4 testMatrix = {
   {0, 0.25, 0.5, 0.75},
   {0, 0.25, 0.25, 0.25},
   {0, 0, 0, 0},
   {1, 1, 1, 1},
};

Matrix4x4 test0 = {
   {0.2,0,0,0},
   {0,0.2,0,0},
   {0,0,0.2,0},
   {0,0,0,1},
};

Matrix4x4 test1 = {
   {1, 2, 3, 4},
   {5, 6, 7, 8},
   {9, 10, 11, 12},
   {13, 14, 15, 16},
};

Matrix4x6 test2 = {
   {17, 18, 19, 20, 41, 42},
   {21, 22, 23, 24, 43, 44},
   {25, 26, 27, 28, 45, 46},
   {29, 30, 31, 32, 47, 48},
};

void matrixMult(Matrix4x4 a, Matrix4x6 b, Matrix4x6 result){
   for (int j = 0; j < 4; j++)
   {
      
      for (int h = 0; h < 6; h++)
      {
         for (int i = 0; i < 4; i++)
         {
            // std::cout << "Printing multiplication iteration: " << i << " " << j << "\n";
            // std::cout << a[j][i] << " " << b[i][h] << "\n";
            result[j][h] += a[j][i] * b[i][h];
            // std::cout << "result: " << result[j][h] << "\n";
             
         }
      }
   }
}

int main(){
   Matrix4x6 test3 = {
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
   };
   matrixMult(test1, test2, test3);
   std::cout << "PRINTING TESTMATRIX\n";
   for (int j = 0; j < 4; j++)
   {
      for (int i = 0; i < 6; i++)
      {
         //toSet[i][j] = (i == j);
         std::cout << test3[j][i];
         if (i == 5)
         {
            std::cout << "\n";
         } else {
            std::cout << " ";
         }
         
      }
   }
}