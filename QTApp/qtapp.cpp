#include "stdafx.h"
#include "qtapp.h"

QTApp::QTApp(QWidget *parent)
	: QMainWindow(parent)
{
	//
	const auto* pp = this->layout();
//	delete pp;

	// Horizontal layout with 3 buttons
	QHBoxLayout *hLayout = new QHBoxLayout;
	QPushButton *b1 = new QPushButton("A");
	QPushButton *b2 = new QPushButton("B");
	QPushButton *b3 = new QPushButton("C");
	hLayout->addWidget(b1);
	hLayout->addWidget(b2);
	hLayout->addWidget(b3);

	// Vertical layout with 3 buttons
	QVBoxLayout *vLayout = new QVBoxLayout;
	QPushButton *b4 = new QPushButton("D");
	QPushButton *b5 = new QPushButton("E");
	QPushButton *b6 = new QPushButton("F");
	vLayout->addWidget(b4);
	vLayout->addWidget(b5);
	vLayout->addWidget(b6);

	// Outer Layer
	QVBoxLayout *mainLayout = new QVBoxLayout;

	// Add the previous two inner layouts
	mainLayout->addLayout(hLayout);
	mainLayout->addLayout(vLayout);

	// Create a widget
	//QWidget *w = new QWidget();

	// Set the outer layout as a main layout 
	// of the widget
	this->setLayout(mainLayout);
	//w->setLayout(mainLayout);

	// Window title
	this->setWindowTitle("layouts");

	//ui.setupUi(this);
	//this->show();

}

QTApp::~QTApp()
{

}
