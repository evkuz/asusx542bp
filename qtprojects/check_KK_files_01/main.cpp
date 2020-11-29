#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDataStream>

#include <iostream>
#include <conio.h>

#include <QList>
#include <QStringList>

using namespace std;

#define def_file "Camac_Thread_data_000.bin"
#define bin_path  "d:/QT-Projects/Camac_USB/Backup/bin/"

//#define f_path "d:\QT-Projects\Camac_USB\KK_Tab_09\release\"



//void File_Open(QString filename);

//void check_byte (char sample, char fbyte);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString str, fname;
    QFile mfile;
    QByteArray ba;
    quint64 i, position;
    uint data, data_2;
    uint num, fnum;
    char fdata, fdata2; // current first & last byte store

    char  first; //1st byte sample
    char   last; //7th byte sample

    bool file_is_ok;
    bool file_shifted;

    quint64 position_array[50];

//    QList <QString *> strList;
    QStringList strList;

    //QDir mdir("d:/QT-Projects/Camac_USB/Backup/bin");
    QDir mdir("../bin/");

    data = mdir.count();
    qDebug() << "Total number of files is : " << data << "\n";

    mdir.setFilter(QDir::Files);
    QStringList filters;
    filters << "*.bin";// << "*.cxx" << "*.cc";
    mdir.setNameFilters(filters);

    strList = mdir.entryList();

  //  qDebug() <<  "The 10 file is : " << strList[9] << "\n";


    qDebug() <<  "The size of list is : " << strList.size()<< "\n";



    str = mdir.path();
    qDebug() <<  "The start path is :" << str;

    QString f_path = "./"; //d:/QT-Projects/Camac_USB/KK_Tab_10/release/
    mdir.cd(f_path);

    str = mdir.path();
    str.append("/");
    qDebug() <<  "The cd-ed path is :" << str;

 //   fname = str + def_file;
    fname = str + strList.at(0);

 //   mfile.setFileName(fname);

//    qDebug() << "The file name is " << mfile.fileName();

    // 'true' means 0 but 'if' takes 0 as false
  //  if (!mfile.open(QIODevice::ReadOnly )) { qDebug() <<  "The file does not exist !";  return 0;}

    qDebug() << "Start checking file consistency :\n";
   // fsize = mfile.size();
    i =0; num=0; fnum=0; first = 0; last =0;

    while ( fnum != strList.size() )
     {

      mfile.setFileName(str + strList.at(fnum));
//      qDebug() << "The file name is " << mfile.fileName();

      if (!mfile.open(QIODevice::ReadOnly )) { qDebug() <<  "The file does not exist !";  return 0;}
//Открыли файл, задаем значения для 1 и 8 байта
      mfile.seek(0); mfile.read(&first, 1);
      mfile.seek(7); mfile.read(&last, 1);

      i =0; file_is_ok = true; file_shifted = false;

    while (!mfile.atEnd())
    {
        i+=8; file_is_ok = true;
        mfile.seek(i);
        mfile.read(&fdata, 1);
        mfile.seek(i+7);
        mfile.read(&fdata2, 1);
        if (fdata != first) {file_is_ok = false; position = i; file_shifted =true;}
        if (fdata2 != last) {file_is_ok = false; position = i+7; file_shifted =true;}
        if (!file_is_ok)
        {
            str.sprintf("0x%x ", position); qDebug() << "The file " << mfile.fileName() << " is corrupted !!! position : " << str;


              while (!((fdata == first) && (fdata2 == last))) //'\xf0'
              {
                  i++;  mfile.seek(i); mfile.read(&fdata, 1); mfile.seek(i+7); mfile.read(&fdata2, 1);
              }
        }//if (!file_is_ok)
//     file_is_ok = true;

    }//while (!mfile.atEnd()
mfile.close();
if (!file_shifted) qDebug() << "File " << mfile.fileName() << " is OK!!! \n";
    fnum++;
  }//while ( fnum != strList.size() )

/*    //Desired pause location
    _getch();
    cin.get();

    getchar();
*/
    qDebug() << "\nProgram is finished. Press CTRL+C to exit\n";

    return a.exec();
}
//+++++++==





/*
void File_Open(QString filename)
{
mfile.setFileName(fname);

if (!mfile.open(QIODevice::ReadOnly )) { qDebug() << "Началась проверка файла"; }
else { qDebug() << "Файл не существует"; return 1;}


//   EK_BUF(BUF_PTR, QIODevice::OpenModeFlag::ReadWrite);
}
*/
