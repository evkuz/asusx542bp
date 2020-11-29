#include <QCoreApplication>
#include <QtDebug>
#include <QFile>
#include <QTextStream>

#define accum_buffer_SIZE  0x400000 // это 4 194 304 байт !
#define mx_size 1000 // Количество 4-байтовых элементов в матрице
#define fpath "/home/evkuz/qtprojects/data.bin" // путь к создаваемому файлу

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString fname;
    QFile   mfile;
    uint i,j,k,l;
    int numBytes;

    char byInputBuffer[accum_buffer_SIZE]; //4096  0x40000// USB_Buffer_Size Buffer to hold data readed from

    int ftdi_error_code = 0;


    qDebug() << "YEs !";

    for (i=0; i<= mx_size; i++ )
    {
       byInputBuffer[i] = i;
    }
    //uint fdata=0x12345678;
    fname = fpath;
    mfile.setFileName(fname);

    if (!mfile.open(QIODevice::ReadWrite | QIODevice::Truncate )) { ftdi_error_code = 0x000D; } // Ошибка
    else ftdi_error_code = 0x0013; // Нормально открылся

    numBytes = mx_size;
    j = mfile.write(byInputBuffer, numBytes);

    mfile.close();
    return a.exec();

}

