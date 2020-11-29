#include <QCoreApplication>
#include <QtDebug>
#include <QFile>
#include <QFileInfo>
#include <iostream>

//#include <QRandomGenerator>

#define accum_buffer_SIZE  0x400000 // это 4 194 304 байт !
//#define mx_size 10000000 // Количество 4-байтовых элементов в матрице
//#define arr_size 1000000
#define fpath  "/home/evkuz/asm/matrix_mul/data.bin"   //"./data.bin" // путь к создаваемому файлу на уровень вверх из папки debug/release

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString fname;
    QString target_name;
    QFile   mfile;
    quint32 i,j,k;
    quint32 bot, top;
    int numBytes;

    //char byInputBuffer[accum_buffer_SIZE]; //4096  0x40000// USB_Buffer_Size Buffer to hold data readed from


    fname = fpath;
    mfile.setFileName(fname);


    int ftdi_error_code = 0;
    if (!mfile.open(QIODevice::ReadWrite | QIODevice::Truncate )) { ftdi_error_code = 0x000D; } // Ошибка
    else ftdi_error_code = 0x0013; // Нормально открылся



    bot =  536870911; // Минимальное 32-битное число
    top = 4294967294; // 0xFFFFFFFE

    quint32 mx_size = 10000000;  // Количество dword-слов
    quint32 arr_size = 1000000;

    quint32 mybuffer [arr_size];

    target_name = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    qDebug() << "YEs !";
    // ЗАполняем массив mybuffer в цикле.

       for (i=0; i< mx_size; i++ )
       {

       mybuffer[i]=bot + i;
       }
    //j = mfile.write(byInputBuffer, numBytes);
    // Так работает, но пишет как 1-байтовое число. ТОгда пишем 4 байта как 4 однобайтовых числа.
    // Цикл задает количество операций записи в файл. Каждый раз при записи, указатель сдвигается.
    // Т.к. операция write работает с массивом "const char *", а у нас массив quint32, то выполняем
    // Приведение указателя типов.

    // Записываем k раз массив в файл, чтобы получить файл нужного размера.
    // Тупо в одном цикле записать большой файл не получается, ошибки.
    k = mx_size/arr_size;
    for (j=0; j< k; j++)
    {
    qint64  written = mfile.write(reinterpret_cast<const char*>(&mybuffer), arr_size*4);
    } //for j

    qDebug() << "Cycle finished !";
    mfile.close();
    //return a.exec();
   return 0;
}
