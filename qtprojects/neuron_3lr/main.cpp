#include <QCoreApplication>
#include <QDebug>
#include <QtCore>
#include <QtMath>
#include "math.h"

double sigmoid(double x) {
     double result;
     result = 1 / (1 + exp(-x));
     return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    float mxA[] = {0.9, 0.3, 0.4, 0.2, 0.8, 0.2, 0.1, 0.5, 0.6};
    float mxB[] = {0.9, 0.1, 0.8};
    float mxC[3];
//    float m_sigmd[3];
//    float sigmd;

    uint32_t mxrA,mxrB, mxcolC;
   // i=0; j=0; k=0; //Строка, столбец, позиция в строке и столбце.
    mxrA =3; // Число строк матрица A (M)
    mxrB =3; // Число строк матрица В (и столбцов в Матрице А)  (K)
    mxcolC = 1; //Матрица С (итоговая), количество столбцов (N), а (строк как в матрице А)

   // sigmd = sigmoid(0.5);

    for (uint32_t i = 0; i < mxrA; ++i)
    {

        for (uint32_t j = 0; j < mxcolC; ++j) {
            mxC[i*mxcolC +j] =0;

           for (uint32_t k = 0; k < mxrB; ++k) {
                mxC[i*mxcolC +j] += mxA[i*mxrB +k] * mxB[k*mxcolC + j];


            }

        }

    }
// Выводим  Xскрытый
    for (int i=0; i<=2; i++)
     {
       qDebug() << "C[" << i <<"] = " << mxC[i];
    }
    // Выводим  Oскрытый
    for (int i=0; i<=2; i++)
     {
       qDebug() << "sigmoid[" << i <<"] = " << sigmoid(mxC[i]);
    }

    return a.exec();
}
