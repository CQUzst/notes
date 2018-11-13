#include "calculator.h"
#include <QApplication>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calculator w;
    w.show();
    cout<<"test"<<endl;
    return a.exec();
}
