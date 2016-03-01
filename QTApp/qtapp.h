#ifndef QTAPP_H
#define QTAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_qtapp.h"

class QTApp : public QMainWindow
{
	Q_OBJECT

public:
	QTApp(QWidget *parent = 0);
	~QTApp();
private:
	Ui::QTAppClass ui;
};

#endif // QTAPP_H
