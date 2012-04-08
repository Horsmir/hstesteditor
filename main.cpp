#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include "HsTestEditor.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
	QString openFile = "";
	
	app.setApplicationName("Hs Test Editor");
	app.setApplicationVersion("0.2");
	
	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(), "/usr/share/qt/translations");
	app.installTranslator(&qtTranslator);
	
	if(app.arguments().count() == 2)
		openFile = app.arguments().at(1);
	
	HsTestEditor foo(openFile);
	foo.show();
	
    return app.exec();
}
