#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QByteArray>
#include <stdlib.h>
#include <stdio.h>
#include <QDataStream>
//#include <wintypes.h>
#include <windows.h>
//#include <QBitArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ToDev_Command.resize(32);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str, filename;
    //QString top4byte, bot4byte;
    //char buf [8];
    QFile mfile;
    uint data;
    //unsigned long hexdata;

    ui->Data2Send_lineEdit->update();
    str = ui->Data2Send_lineEdit->text();
    //Каждый байт в hex-формате - это 2 символа,
    //Значит на 8 байт надо 16 символов,
    //str="2a3b4cde";

    //QByteArray mystr = QByteArray::fromHex("2a3b4cde");// ТАК РАБОТАЕТ !!!
    QByteArray mystr = QByteArray::fromHex(str.toLocal8Bit().constData()); // !!!! THE BEST !!!!
   // const char *mydata = "2a3b4cde";//mystr.constData();



    //data=str.toUInt(&ok, 16);
    //rdData = str.toInt(0,16);
   // mystr = str.toUtf8().toHex();//выдает ascii-код каждого символа строки
    //bool ok =0;
    data = 0x2a3b4cde;



    //mystr = QByteArray::fromRawData(reinterpret_cast<const char*>(data),sizeof(data)); ошибка
    //mystr = QByteArray::number(data,16);//выдает ascii-код каждого символа стр



    /*sscanf(mydata, "%x", &hexdata);

    string string_test = mydata;
    std::stringstream ss;
    ss << std::hex << string_test;
*/
   // data = str.toInt(0,16);
    //int ret = snprintf(buf, sizeof(buf), "%d", data);
    //char *p = reinterpret_cast <char *>(&data);// УРРРААА !!! так работает, но байты наоборот

    //buf = reinterpret_cast <char >(p);

    filename = "/home/evkuz/camac_data.bin";
    mfile.setFileName(filename);



    if (!mfile.open(QIODevice::ReadWrite | QIODevice::Truncate ))
    {
       // ui->File_Open_label->setText("File does not exist");
        str.sprintf("File does not exist");ui->Status_label->setText(str);
        return;
    }

    else
    {
        // ui->File_Open_label->setText("File is opened");
         str.sprintf("File is opened");ui->Status_label->setText(str);
         /*
         QDataStream out( &mfile );
         //out.setByteOrder( QDataStream::LittleEndian ); //младший байт пишется первым
         out.setByteOrder(QDataStream::BigEndian);  //Старший байт пишется первым
         out << 0x92025428;
*/


    }

   // sprintf (buf,"%x", data);
    mfile.write(mystr, 8);
}

//Меняет цвет кнопки по нажатию
// Т.е. бит выбран, если цвет не серый и выбран - если серый.
// lightgray - обычный, стандартный
// gray - темнее стандартного
// ui->Sel_Bit->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 115, 255);"));
// ui->Sel_Bit->setStyleSheet(QString::fromUtf8("background-color: yellow"));

void MainWindow::on_Sel_Bit_toggled(bool checked)
{

 if(checked) { ui->Sel_Bit->setStyleSheet("background-color: yellow");ToDev_Command.setBit(12,true);}
 else { ui->Sel_Bit->setStyleSheet("background-color: lightgray");    ToDev_Command.setBit(12,false);}
}


/*
 * https://en.wikipedia.org/wiki/Endianness
 *
QBitArray bits = ...;

// Resulting byte array
QByteArray bytes;

// Convert from QBitArray to QByteArray
for(int b=0; b<bits.count(); ++b)
    bytes[b/8] = (bytes.at(b/8) | ((bits[b]?1:0)<<(b%8)));
*/

void MainWindow::on_Sel_Bit_clicked()
{
   // unsigned char ToDev_Bits[16];
    UINT16 ToDev_Bits;

    if(checked) {
       ui->Sel_Bit->setStyleSheet("background-color: yellow");

       ToDev_Bits |= 0x0800; //12 bit set to '1'

    }
    else
    {
        ui->Sel_Bit->setStyleSheet("background-color: lightgray");
        ToDev_Bits &= 0xf7ff; //12 bit set to '0'


    }

}


//+++++++++++++++++

void set_bits(void)
{
       UINT16 ToDev_Bits;
       // Bit 16
         ToDev_Bits |= 0x8000; //16 bit set to '1'
         ToDev_Bits &= 0x7fff; //16 bit set to '0'
      // Bit 15
         ToDev_Bits |= 0x4000; //15 bit set to '1'
         ToDev_Bits &= 0xBfff; //15 bit set to '0'
      // Bit 14
         ToDev_Bits |= 0x2000; //14 bit set to '1'
         ToDev_Bits &= 0xDfff; //14 bit set to '0'
      // Bit 13
         ToDev_Bits |= 0x1000; //13 bit set to '1'
         ToDev_Bits &= 0xEfff; //13 bit set to '0'

  // Bit 12
     ToDev_Bits |= 0x0800; //12 bit set to '1'
     ToDev_Bits &= 0xf7ff; //12 bit set to '0'
  // Bit 11
     ToDev_Bits |= 0x0400; //11 bit set to '1'
     ToDev_Bits &= 0xfBff; //11 bit set to '0'
  // Bit 10
     ToDev_Bits |= 0x0200; //10 bit set to '1'
     ToDev_Bits &= 0xfDff; //10 bit set to '0'
  // Bit 09
     ToDev_Bits |= 0x0100; //09 bit set to '1'
     ToDev_Bits &= 0xfEff; //09 bit set to '0'
      // Bit 08
        ToDev_Bits |= 0x0080; //08 bit set to '1'
        ToDev_Bits &= 0xff7f; //08 bit set to '0'
     // Bit 07
        ToDev_Bits |= 0x0040; //07 bit set to '1'
        ToDev_Bits &= 0xffBf; //07 bit set to '0'
     // Bit 06
        ToDev_Bits |= 0x0020; //06 bit set to '1'
        ToDev_Bits &= 0xffDf; //06 bit set to '0'
     // Bit 05
        ToDev_Bits |= 0x0010; //05 bit set to '1'
        ToDev_Bits &= 0xffEf; //05 bit set to '0'
  // Bit 04
     ToDev_Bits |= 0x0008; //04 bit set to '1'
     ToDev_Bits &= 0xfff7; //04 bit set to '0'
  // Bit 03
     ToDev_Bits |= 0x0004; //03 bit set to '1'
     ToDev_Bits &= 0xfffB; //03 bit set to '0'
  // Bit 02
     ToDev_Bits |= 0x0002; //02 bit set to '1'
     ToDev_Bits &= 0xfffD; //02 bit set to '0'
  // Bit 01
     ToDev_Bits |= 0x0001; //01 bit set to '1'
     ToDev_Bits &= 0xfffE; //01 bit set to '0'


}



