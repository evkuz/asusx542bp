#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstring.h"

int32_t fin_value, start_value;
QString summa;


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

void MainWindow::on_pushButton_count_money_clicked()
{
    fin_value = ui->lineEdit_fin_value->text().toInt();
    start_value = ((fin_value/0.87)*1.3)/0.94;
    summa.setNum(start_value);
    ui->label_Start_value->setText(summa);

}
