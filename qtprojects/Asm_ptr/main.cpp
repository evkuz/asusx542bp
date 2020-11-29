
#include <QCoreApplication>
#include <QDebug>


#include <qt_windows.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DWORD mxA[] = {1,2,3,2,3,4};
    DWORD mxB[] = {5,6,7,8,6,7,8,9,7,8,9,10};
    DWORD mxC[8];

    DWORD i,j,k,mxrA,mxrB, mxResult, mxcolC, C_11, C_12, C_13;
    i=0; j=0; k=0; //Строка, столбец, позиция в строке и столбце.
    mxrA =2; // Число строк матрица A (M)
    mxrB =3; // Число строк матрица В (и столбцов в Матрице А)  (K)
    mxcolC = 4; //Матрица С (итоговая), количество столбцов (N), а (строк как в матрице А)


    for (int i = 0; i < mxrA; ++i)
    {

        for (int j = 0; j < mxcolC; ++j) {
            mxC[i*mxcolC +j] =0;

           for (int k = 0; k < mxrB; ++k) {
                mxC[i*mxcolC +j] += mxA[i*mxrB +k] * mxB[k*mxcolC + j];


            }

        }

    }

/*
    C_11 = mxA[i] * mxB[j];
    i++;
    C_12 = mxA[i] * mxB[i*mxcolC];
    i++;
    C_13 = mxA[i] * mxB[i*mxcolC];
*/
    for (i=0; i<=7; i++)
     {
       qDebug() << "C[" << i <<"] = " << mxC[i];
    }
/*    qDebug() << "C_11 = " << C_11;
    qDebug() << "C_12 = " << C_12;
    qDebug() << "C_13 = " << C_13;

*/
    return a.exec();
}
