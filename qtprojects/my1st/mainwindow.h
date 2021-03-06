#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ekgym.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString getCPUID();
    ~MainWindow();

private slots:
    void on_my1st_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
