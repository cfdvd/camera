#include <iostream>
#include <QApplication>
#include <boost/assert.hpp>
#include "MainWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}