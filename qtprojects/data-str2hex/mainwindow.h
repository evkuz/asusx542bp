#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QBitArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QBitArray ToDev_Command;

    void set_bits(void); //Для размещения кода.

    ~MainWindow();

private slots:
    void on_pushButton_clicked();


    void on_Sel_Bit_toggled(bool checked);

    void on_Sel_Bit_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
