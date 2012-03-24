#include <QtGui/QApplication>
#include "HsTestEditor.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    HsTestEditor foo;
    foo.show();
    return app.exec();
}
