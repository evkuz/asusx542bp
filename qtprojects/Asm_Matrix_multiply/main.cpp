
#include <QCoreApplication>
#include <QDebug>


#include <qt_windows.h>
#include <windows.h>
#include <QTimer>
#include <QElapsedTimer>

#include <QFile>
#include <QDataStream>
#include <QIODevice>

#include <iostream>
#include <conio.h>

#include <QVector>

#define data_A_path  "data_A.bin"
#define data_B_path  "data_B.bin"
#define data_C_path  "data_C.bin"
                      //D:\QT-Projects\Camac_USB\Asm_Matrix_multiply

#define mxrA 1000 // Число строк матрица A (M)
#define mxrB 1000 // Число строк матрица В (и столбцов в Матрице А)  (K)
#define mxcolC 1000 //Матрица С (итоговая), количество столбцов (N) (и в матрице В столбцов), а строк как в матрице А
//#define mxC_size mxrA * mxcolC *4

#define mxC_dw_size mxrA * mxcolC *4

//This will allocate in the DATA segment, which is a part of the heap too:

DWORD *mA, *mB;
DWORD  mxC[mxC_dw_size];
  char ek_a[mxrA * mxrB * 4];  //Храним DWORD числа
  char ek_b[mxrB * mxcolC * 4];//Храним DWORD числа


void Convert_Array_Dword_To_Char(DWORD * DW_Array, uint DW_Size, char * CH_Array); //uint DW_Size,


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QElapsedTimer timer;
    //int ctype;



    //QFile data_A, data_B, data_C;
    QFile mfile_A, mfile_B, mfile_C;
    QString str, fname, fstr;

    QByteArray data_A, data_B, data_C;
//    timer.start();
  //  ctype=timer.clockType();


// qDebug() << "Clock Type Value is : " << ctype;

  FILETIME  Idle_TIME, Kernel_TIME, User_TIME;
  FILETIME  Idle_TIME_2, Kernel_TIME_2, User_TIME_2;

 // DWORD   Start_Time, Finish_Time;
  quint64 Start_Idle_Time,Start_User_Time, Start_Kernel_Time, Start_Work_Time;
  quint64 Finish_Idle_Time, Finish_User_Time, Finish_Kernel_Time, Finish_Work_Time;
  quint64 CPU_Time, nsecs;

  UINT RESULT;
  UINT32 i,j,k; //,mxrA,mxrB,  mxcolC;

/*  quint32 mxrA = 1000; // Число строк матрица A (M)
  quint32 mxrB = 100; // Число строк матрица В (и столбцов в Матрице А)  (K)
  quint32 mxcolC = 1000; //Матрица С (итоговая), количество столбцов (N) (и в матрице В столбцов), а строк как в матрице А
  quint32 mxC_dw_size =  mxrA * mxcolC *4;
*/

/*  DWORD *mA, *mB;
  DWORD  mxC[mxC_dw_size];
    char ek_a[mxrA * mxrB * 4];  //Храним DWORD числа
    char ek_b[mxrB * mxcolC * 4];//Храним DWORD числа
 //   char ek_c[mxC_dw_size];
*/
    mfile_A.setFileName(data_A_path);

    if (!mfile_A.open(QIODevice::ReadOnly)) { qDebug() <<  "The file " <<  mfile_A.fileName() << " does not exist !";  return 0;}
 //   qDebug() << "Current file data_A name is " << mfile_A.fileName();


    quint64 readed = mfile_A.read(ek_a, mxrA * mxrB * 4); //mxA_data mxrA * mxrB * 4
    mfile_A.close();

    qDebug () << "A Readed bytes number is !" << readed;

/*    for (i=0; i<24; ++i)
     {
      //  str = sprintf("%x",*(ek_c +i) );
       str = QString("0x%1" ).arg(*(ek_a +i), 2, 16, QChar('0'));
       qDebug() << "A[" << i <<"] = " << str; //itoa(*(ek_c +i), buf, 10);
    }
*/

//########################################

    //mA = (DWORD *)ek_a; // Так компилит, но при работе отваливается
    // А так работает. Преобразуем указатель на массив char в указатель на массив DWORD
    mA = static_cast<DWORD *>(static_cast<void *>(ek_a));

//    str = QString("0x%4" ).arg(*(mA +5), 4, 16, QChar('0'));
//     qDebug() << "B[" << 5 <<"] = " << str; //itoa(*(ek_c +i), buf, 10);

     // Массив чисел DWORD матрицы А получили

    mfile_B.setFileName(data_B_path);
    if (!mfile_B.open(QIODevice::ReadOnly)) { qDebug() <<  "The file " <<  mfile_B.fileName() << " does not exist !";  return 0;}
//    qDebug() << "Current file data_B name is " << mfile_B.fileName();

    readed = mfile_B.read(ek_b, mxrB * mxcolC * 4); //mxB_data
//    qDebug () << "B Readed bytes number is !" << readed;
    mfile_B.close();



//##########################################

    // mB = (DWORD *)ek_b;
    mB = static_cast<DWORD *>(static_cast<void *>(ek_b));
 //    str = QString("0x%1" ).arg(*(mB +5), 4, 16, QChar('0'));
 //    qDebug() << "B[" << 5 <<"] = " << str; //itoa(*(ek_c +i), buf, 10);

  //   RESULT=GetSystemTimes(Old_IdleTime, Old_KernelTime, Old_UserTime);
 //   Start_Time = 0xCDB4DDAA;
   // Start_Time =  Old_KernelTime->dwLowDateTime; // ТАк прога вылетает
      RESULT=GetSystemTimes(&Idle_TIME, &Kernel_TIME, &User_TIME );

    //  Start_Time = User_TIME.dwLowDateTime;
      Start_Idle_Time = Idle_TIME.dwLowDateTime;
      Start_User_Time = User_TIME.dwLowDateTime;
      Start_Kernel_Time = Kernel_TIME.dwLowDateTime;
      Start_Work_Time = Start_Kernel_Time + Start_User_Time ;
/*
      if (RESULT) //If the function succeeds, the return value is nonzero.
        { // Сработало успешно

         qDebug() << "Start Kernel Time is :" << Kernel_TIME.dwLowDateTime; //Old_KernelTime;
         qDebug() << "Start User Time   is :" << User_TIME.dwLowDateTime;
         qDebug() << "Start Work   Time is :" << Start_Work_Time;
      }
*/





timer.start();
    i=0; j=0; k=0; //Строка, столбец, позиция в строке и столбце.
//=============================================
    for ( i = 0; i < mxrA; ++i)
    {

        for ( j = 0; j < mxcolC; ++j) {
            mxC[i*mxcolC +j] =0;

           for ( k = 0; k < mxrB; ++k) {
                mxC[i*mxcolC +j] += (*(mA + i*mxrB +k)) * (*(mB + k*mxcolC + j));


            }

        }

    }
 nsecs = timer.nsecsElapsed();
 RESULT=GetSystemTimes(&Idle_TIME_2, &Kernel_TIME_2, &User_TIME_2 );

 //Преобразуем указатель на DWORD в указатель на char
   //mB = static_cast<DWORD *>(static_cast<void *>(ek_b));
//   ek_c = static_cast<char>(static_cast<void *>(mxC));
     char * ek_c = (char *)mxC;
 //   mxC_data = (char*)mxC; // incopatible type of assignment


 //   fname = fstr + file_list.at(i); //str + def_file;
    mfile_C.setFileName(data_C_path);

    if (!mfile_C.open(QIODevice::ReadWrite | QIODevice::Truncate )) { qDebug() <<  "The file " <<  mfile_C.fileName() << " does not exist !";  return 0;}
 //   qDebug() << "Current file data_C name is " << mfile_C.fileName();


    mfile_C.write(ek_c, mxC_dw_size); //mxC_data
    mfile_C.close();


  //    Finish_Time = User_TIME.dwLowDateTime;
      Finish_User_Time = User_TIME_2.dwLowDateTime  - Start_User_Time;
      Finish_Kernel_Time = Kernel_TIME_2.dwLowDateTime - Start_Kernel_Time;
      Finish_Idle_Time = Idle_TIME_2.dwLowDateTime;
      CPU_Time = Finish_Kernel_Time + Finish_User_Time + Finish_Idle_Time - Start_Idle_Time;
/*
      if (RESULT) //If the function succeeds, the return value is nonzero.
        { // Сработало успешно

         qDebug() << "Finish Kernel Time is :" << Kernel_TIME_2.dwLowDateTime; //Old_KernelTime;
         qDebug() << "Finish User Time   is :" << User_TIME_2.dwLowDateTime;
       //  qDebug() << "Finish Work Time   is :" << Finish_Work_Time;

         qDebug() << "CPU Time elapsed   is :" << CPU_Time;
      }
*/

qDebug() << "CPU Time elapsed nsecs is :" << nsecs;
qDebug() << "CPU System WORK Time   is :" << CPU_Time;
/*    for (i=0; i<=7; i++)
     {
       qDebug() << "C[" << i <<"] = " << mxC[i];
    }
*/
//    return a.exec();



}//main.c
//+++++++++++++++++++++++++++
void Convert_Array_Dword_To_Char (DWORD * DW_Array, uint DW_Size, char * CH_Array) // uint DW_Size,
{
// DWORD * DW_Array - массив DWORD
// char * CH_Array  - массив char
// uint DW_Size     - размер массива dword (количество элементов в массиве) в байтах будет в 4 раза больше
  //int i;

  for (uint i =0; i < DW_Size; i++)
  {
 /*     *mxC_data =  char (static_cast<DWORD> (*mxC));
      mxC_data[4] =  char (static_cast<DWORD> (mxC[1]));
      * (mxC_data +4) =  char (static_cast<DWORD> (mxC[1]));
  */
      for (int j=0; j<3; j++)
        {
          CH_Array[i*4 +j] =  char (static_cast<DWORD> (DW_Array[i] >> (j*8)));

      //    CH_Array[i*4 +j] =  ( DW_Array[i] >> (j*8)) && 0x00ff ;
    //      qDebug() << "C[" << i <<"] = " <<DW_Array[i];
    //      qDebug() << "Byte[" << i <<"] = " <<CH_Array[i*4];
      }
  }

}


