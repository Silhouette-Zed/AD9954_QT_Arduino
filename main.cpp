#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setFixedSize(700,350);
    w.setWindowTitle("AD9954 GUI");
    w.show();

    return a.exec();
}
