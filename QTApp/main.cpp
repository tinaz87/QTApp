#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(38055);
	QApplication a(argc, argv);
	Window window;
	window.show();
	return a.exec();
}
