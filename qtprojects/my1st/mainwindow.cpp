#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ekgym.h>
//#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_my1st_button_clicked()
{
    ui->my1st_button->setText("Hello World !");
    QString info = getCPUID();
    int pullups = pullups_stair(5);
    ui->textEdit->setText("The CPU ID is "+info+" pullups "+QString::number(pullups));
}
//+++++++++++++++++++++++++++++++++++++++++++++++
QString MainWindow::getCPUID()
{
    QString CPUID;
    int b;
    for (int a = 0; a < 5; a++) {
        asm ( "mov %1, %%eax; cpuid; mov %%eax, %0;"
        :"=r"(b) /* output */
                :"r"(a) /* input */
                :"%eax","%ebx","%ecx","%edx" /* clobbered register */
                  );
        //        qDebug() << "The code " << a << " gives " << b;
        CPUID.append(QString("%1").arg(b));
    }
    return CPUID;
}
