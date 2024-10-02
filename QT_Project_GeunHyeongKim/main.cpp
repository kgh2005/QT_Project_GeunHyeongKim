#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <string>

using namespace std;

class Player {
public:
    string name;
    int score;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
