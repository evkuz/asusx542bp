#include <QCoreApplication>
#include <QtDebug>
#include <QFile>
#include <QFileInfo>
#include <iostream>

//#include <QRandomGenerator>

#define accum_buffer_SIZE  0x400000 // это 4 194 304 байт !
//#define mx_size 10000000 // Количество 4-байтовых элементов в матрице
//#define arr_size 1000000
//#define fpath  "/home/evkuz/asm/matrix_mul/data.bin"   //"./data.bin" // путь к создаваемому файлу на уровень вверх из папки debug/release

#define A_fpath  "A_sample_data.bin"
#define B_fpath  "B_sample_data.bin"

#define A_size 20
#define B_aize 15


int gen_sample (QString fname, quint32 *databuf, quint32 buf_sz);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString fname;
    int numBytes;

    quint32 mybuffer_A[]  = {11,13,15,17,19,12,14,16,18,20,31,33,35,37,39,42,44,46,48,50}; // mxA 4x5 arr_size
    quint32 mybuffer_B[]  = {19,17,15,13,11,9,8,10,12,22,24,26,28,32,34};  // mxB 5x3

    //char byInputBuffer[accum_buffer_SIZE]; //4096  0x40000// USB_Buffer_Size Buffer to hold data readed from


    fname = A_fpath;
    numBytes = gen_sample(fname, mybuffer_A, sizeof(mybuffer_A)/4);
    fname = B_fpath;
    numBytes += gen_sample(fname, mybuffer_B, sizeof(mybuffer_B)/4);
return 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ВНИМАНИЕ ! размер буфера (аргумент #3) передается в quint32
// Т.е. не в байтах, а в dword-элементах по 4 байта.
int gen_sample (QString fname, quint32 *databuf, quint32 buf_sz)
{
    QFile   mfile;
    QString target_name;
    quint32 j;
    int ftdi_error_code = 0;

    mfile.setFileName(fname);
    if (!mfile.open(QIODevice::ReadWrite | QIODevice::Truncate )) { ftdi_error_code = 0x000D; } // Ошибка
    else ftdi_error_code = 0x0013; // Нормально открылся

    target_name = QFileInfo(QCoreApplication::applicationFilePath()).fileName();

    for (j=0; j< buf_sz; j++)
    {
      ftdi_error_code = mfile.write(reinterpret_cast<const char*>(databuf + j), 4);
    } //for j

    qDebug() << target_name  << "/" << fname << " matrix file of " << buf_sz << " elements created !";
    mfile.close(); // Тоже нужна проверка, что файл закрылся...
   return ftdi_error_code;


}

