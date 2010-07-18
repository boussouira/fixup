#include <QApplication>
#include "Registry.h"
#include "MainClass.h"


int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	MainClass Fenetre;
	Fenetre.show();
	return app.exec();
}

