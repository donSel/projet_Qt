#include <QApplication>
#include <QTime>
#include "MainWindow.h"
#include "WindowTwo.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
