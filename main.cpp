#include "cihmapprs232c.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CIhmAppRs232c w;
    w.show();

    return a.exec();
}
