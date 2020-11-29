#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDataStream>

#include <iostream>
#include <conio.h>


#include <qt_windows.h>
#include <windows.h>


using namespace std;

#define def_file "Camac_Thread_data_000.bin"
//#define bin_path  "d:/QT-Projects/Camac_USB/Backup/bin/"

#define bin_path "d:/QT-Projects/Camac_USB/KK_Tab_14/release/"
#define repaired_path "d:/QT-Projects/Camac_USB/KK_Tab_14/release/"
//#define f_path "d:\QT-Projects\Camac_USB\KK_Tab_09\release\"



void File_Open(QString filename);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString str, fname, fstr, fstr_repaired;
    QFile mfile, repaired_file;
    QByteArray ba;
    quint64 i, j,  data, fsize, bytes_to_write, result;
  //  uint data_2;
    uint num;
    char fdata;
 //   char *dataSet;
    QStringList file_list;

 //  quint64 position_array[50];
 //   QDir mdir("d:/QT-Projects/Camac_USB/Backup/bin");
    QDir mdir("d:/QT-Projects/Camac_USB/KK_Tab_14/release");
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
     *    QStringList filters;
    filters << "*.cpp" << "*.cxx" << "*.cc";
    dir.setNameFilters(filters);


*/

    bytes_to_write = 8;


    // "./" , ".." , Нумерация файлов с 000
    qDebug() << "The 4th file name is " << file_list.at(4).toLocal8Bit().constData();

    qDebug() << "The 8th file name is " << file_list.at(8).toLocal8Bit().constData();
  //  for (int i = 0; i < fonts.size(); ++i)
  //           cout << fonts.at(i).toLocal8Bit().constData() << endl;


    str = mdir.path();
    qDebug() <<  "The start path is :" << str;

    QString f_path = "./"; //d:/QT-Projects/Camac_USB/KK_Tab_10/release/
    mdir.cd(f_path);

    str = mdir.path();
    str.append("/");
    qDebug() <<  "The cd-ed path is :" << str;

    fname = str + def_file;


    mfile.setFileName(fname);

    qDebug() << "The file name is " << mfile.fileName();

    // 'true' means 0 but 'if' takes 0 as false
 //   if (!mfile.open(QIODevice::ReadOnly )) { qDebug() <<  "The file does not exist !";  return 0;}

    qDebug() << "Start checking file consistency ";

    //Перебираем вложенный цикл.
    i=0;

    fstr = mdir.path();
    fstr.append("/");

// Внешний цикл, обходим список файлов.
    while (i<=file_list.size()) //
    {



        fname = fstr + file_list.at(i); //str + def_file;
        mfile.setFileName(fname);

        if (!mfile.open(QIODevice::ReadOnly )) { qDebug() <<  "The file " <<  mfile.fileName() << " does not exist !";  return 0;}
        qDebug() << "Current file name is " << mfile.fileName();

        fstr_repaired.clear();

        fstr_repaired.append(fname);
        fstr_repaired = fname;
        fstr_repaired.append("_repaired");

        repaired_file.setFileName(fstr_repaired);

        // repaired-file тоже надо октрывать с самого начала, и записывать туда даже если файл пока правильный.

        if (!repaired_file.open(QIODevice::ReadWrite | QIODevice::Truncate )) { qDebug() <<  "Can not open the repaired file  !";  return 0;}
        else {qDebug() << "Current repaired file name is " << repaired_file.fileName();}

 //   fsize = mfile.size();
    j =0; num=0;

    while (!mfile.atEnd())
    {
        //  qDebug() << "I am Inside of a seek cycle, current J position is " << j;

         if (!mfile.seek(j)) qDebug() <<  "Seek operation ERROR in string 146 " << "J value is " << j;
        mfile.read(&fdata, 1);
    if (fdata == '\xf0') // Проверяем +7 байт и если да, то пишем все 8 байт, если нет, то j++ и вначало
      {

       //       str.sprintf("0x%x ", j); qDebug() << "The file " << fname << " is corrupted, start of frame !!! position : " << str;
       //       position_array[num] = j;
       // Ага и вот тут нужен код обработки, убирающий "неправильную" порцию данных
           //   num++;
   /*           while ((fdata != '\xf0') | !mfile.atEnd() )
              {
                  j++;  if (!mfile.seek(j)) qDebug() <<  "Seek operation ERROR in string 157 " << "J value is " << j;

                  if (mfile.atEnd() )  {

                      // А вот тут надо вообще выйти из цикла...
                      // Ставим флаг конца файла
                       End_Of_File_Flag = TRUE;
                  }

                  mfile.read(&fdata, 1);

              }
    */
    //}//if (fdata != '\xf0') 148'th String of code

    // Проверяем флаг конца файла и выходим, если TRUE

    // ПРодолжаем, если не конец файла

    // Обрабатываем 1 порцию файла размером 8 байт
       if (!mfile.seek(j+7))  qDebug() <<  "Seek operation ERROR in string 175 " << "J value is " << j;

         if (!mfile.atEnd())
          {
           mfile.read(&fdata, 1);

           if (fdata != '\x80') // ТОгда просто идем на следующую позицию
            {
        //  j = j - 6;
          //str.sprintf("0x%x", j);qDebug() << "The file is corrupted, end of frame !!! position : " << str; return 1;
          //    qDebug() << "Find corrupted frame in file  " << repaired_file.fileName();
            }  // Возвращаемся на проверку

          else
          { // Записываем порцию данных в другой файл. //       qDebug() << "I am Inside of a WRITE_TO_FILE cycle ";


      //  j = j -7;
        if (!mfile.seek(j))  qDebug() <<  "Seek operation ERROR in string 193 " << "J value is " << j;
        result =  mfile.read(dataSet, 8 ); //bytes_to_write
       // if (!result) {qDebug() <<  "Error READING the repaired file  !";  return 0;}

   //     qDebug() <<  " The repaired file is " << repaired_file.fileName() <<  "Before Writing";

  //      if (repaired_file.isOpen()) {qDebug() <<  " The repaired file is Opened !"; }
  //      else {
 //       fopen = repaired_file.open(QIODevice::ReadWrite | QIODevice::Truncate );
//        if (fopen)
 //       }

        // И вот тут засада, если вначале часть файла была правильная, то repaired файл до сих пор не был открыт...
        result = repaired_file.write(dataSet, 8);
        j= j + 7;

      }//else 188'th String of code


  }//if (!mfile.atEnd()) 177'th String of code
} //if 148'th string

    j++; //1 порцию обработали. Двигаемся дальше по файлу
      mfile.seek(j);

    }//while (!mfile.atEnd())

mfile.close();
repaired_file.close();

i++;
}//while (i<=file_list.size()) 115'th String


    //    if (fdata != '\x80') { str.sprintf("0x%x", i);qDebug() << "The file is corrupted !!! position : " << str; return 1;}
    //    i+=1; mfile.seek(i); mfile.read(&fdata, 1);

    qDebug() << "Finished checking file consistency, file is OK !!! ";

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
