#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDataStream>

#include <iostream>
#include <conio.h>


#include <qt_windows.h>
#include <windows.h>


// using namespace std;

#define def_file "Camac_Thread_data_000.bin"
//#define bin_path  "d:/QT-Projects/Camac_USB/Backup/bin/"

//#define bin_path "./" //d:/QT-Projects/Camac_USB/KK_Tab_14/release/
//#define repaired_path "./" //d:/QT-Projects/Camac_USB/KK_Tab_14/release/
//#define f_path "d:\QT-Projects\Camac_USB\KK_Tab_09\release\"



void File_Open(QString filename);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString str, fname, fstr, fstr_repaired;
    QFile mfile, repaired_file;
    QByteArray ba;
    quint64 i, j,  data, fsize, bytes_to_write, result;
    uchar num;
    char fdata;
    QStringList file_list;


 //   QDir mdir("d:/QT-Projects/Camac_USB/Backup/bin");
    QDir mdir("./"); //d:/QT-Projects/Camac_USB/KK_Tab_14/release
    QDir repaired_dir("./0_repaired/");
    //QDir mdir("./");

    BOOL fopen, End_Of_File_Flag;

    char  dataSet[8] ; //= new char[8];

    End_Of_File_Flag = TRUE;
    //file_list = mdir.entryList();

     file_list << "*.bin";
     mdir.setNameFilters(file_list);

     data = mdir.count();
     qDebug() << "Total number of files is :" << data;
     file_list = mdir.entryList();

     data = file_list.size();
     qDebug() << "Total number of files in list is :" << data << "\n";

    /*
     *
     *
    QStringList filters;
    filters << "*.cpp" << "*.cxx" << "*.cc";
    dir.setNameFilters(filters);


*/

    bytes_to_write = 8;


    // "./" , ".." , Нумерация файлов с 000
 //   qDebug() << "The 4th file name is " << file_list.at(4).toLocal8Bit().constData();

//    qDebug() << "The 8th file name is " << file_list.at(8).toLocal8Bit().constData();

    str = mdir.absolutePath();
    qDebug() <<  "The start path is :" << str;

    QString f_path = "./";
    mdir.cd(f_path);

    str = mdir.absolutePath();
    str.append("/");
    qDebug() <<  "The cd-ed path is :" << str;

    fstr = repaired_dir.absolutePath();
    qDebug() <<  "The repaired path is :" << fstr;
//    fname = str + def_file;


//    mfile.setFileName(fname);

//    qDebug() << "The file name is " << mfile.fileName();

    // 'true' means 0 but 'if' takes 0 as false
    qDebug() << "Start checking file consistency ";

    //Перебираем вложенный цикл.
    i=0;

    fstr = mdir.path();
    fstr.append("/");

    /*
     * Проверяем, существует ли директория ./backup
     * если "ДА", то пропускаем, если "НЕТ", то создаем таковую
     *
     *
     */


    if (!repaired_dir.exists()) {fopen = repaired_dir.mkdir(repaired_dir.absolutePath());}


// Внешний цикл, обходим список файлов.
    while (i<= (file_list.size() -1)) //file_list.size()
    {

        fname = fstr + file_list.at(i); //str + def_file;
        mfile.setFileName(fname);

        if (!mfile.open(QIODevice::ReadOnly )) { qDebug() <<  "The file " <<  mfile.fileName() << " does not exist !";  return 0;}
        qDebug() << "Current file name is " << mfile.fileName();

        fstr_repaired.clear();

      //  fstr_repaired.append(repaired_dir.absolutePath()); //fname
        fstr_repaired = repaired_dir.absolutePath(); //fname;
        fstr_repaired.append("/");
        fstr_repaired.append(file_list.at(i));
        fstr_repaired.append("_repaired");

        repaired_file.setFileName(fstr_repaired);

        // repaired-file тоже надо октрывать с самого начала, и записывать туда даже если файл пока правильный.

        if (!repaired_file.open(QIODevice::ReadWrite | QIODevice::Truncate )) { qDebug() <<  "Can not open the repaired file  !";  return 0;}
        else {qDebug() << "Current repaired file name is " << repaired_file.fileName();}

        j =0; num=0;

    while (!mfile.atEnd())
    {

      if (!mfile.seek(j)) qDebug() <<  "Seek operation ERROR in string 146 " << "J value is " << j;
      mfile.read(&fdata, 1);
      num = reinterpret_cast<unsigned char&>(fdata);
      if (num == 0xf0) // Проверяем +7 байт и если да, то пишем все 8 байт, если нет, то j++ и вначало '\xf0'
      {

    // Проверяем флаг конца файла и выходим, если TRUE
    // ПРодолжаем, если не конец файла
    // Обрабатываем 1 порцию файла размером 8 байт
       if (!mfile.seek(j+7))  qDebug() <<  "Seek operation ERROR in string 175 " << "J value is " << j;

       if (!mfile.atEnd())
       {
           result =mfile.read(&fdata, 1); // Считали байт в конце порции
           num = reinterpret_cast<unsigned char&>(fdata);

          if (num == 0x80 ) // Записываем порцию данных в другой файл.  '\x80'
          { // Вот тут позиция то уже J+7, а надо считывать с позиции J !!!
            // поэтому сначала идем на позицию J
            if (!mfile.seek(j))  qDebug() <<  "Seek operation ERROR in string 193 " << "J value is " << j;


           result =  mfile.read(dataSet, 8 ); //bytes_to_write

           // И вот тут засада, если вначале часть файла была правильная, то repaired файл до сих пор не был открыт...
           result = repaired_file.write(dataSet, 8);
           j= j + 7;

          }//else 188'th String of code


       }//if (!mfile.atEnd())  177'th String of code
      } //if (fdata == '\xf0') 148'th string

    j++; //1 порцию обработали. Двигаемся дальше по файлу
    if (!mfile.seek(j))  qDebug() <<  "Seek operation ERROR in string 186 " << "J value is " << j;

    }//while (!mfile.atEnd())

mfile.close();
repaired_file.close();

i++;
}//while (i<=file_list.size()) 115'th String


    //    if (fdata != '\x80') { str.sprintf("0x%x", i);qDebug() << "The file is corrupted !!! position : " << str; return 1;}
    //    i+=1; mfile.seek(i); mfile.read(&fdata, 1);

    qDebug() << "Finished checking file consistency, file is OK !!! ";

//    return a.exec();
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
