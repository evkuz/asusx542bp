#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int square [3][3];
    square[0,0] = 2;


    return a.exec();
}
