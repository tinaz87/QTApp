#include <stdafx.h>


OptionWindow::OptionWindow() :QWidget(){
	//QGridLayout *layout = new QGridLayout;

	this->setFixedSize(660, 600);
	setWindowTitle(tr("Opzioni"));

}
OptionWindow::~OptionWindow(){}

Window:: ~Window(){
	delete this->mScene;
	delete this->mField;
	delete this->mPlayer;

	QObject::disconnect(this->mButtonRight);
	QObject::disconnect(this->mButtonLeft);
	QObject::disconnect(this->mButtonUp);
	QObject::disconnect(this->mButtonDown);

	delete this->mButtonRight;
	delete this->mButtonLeft;
	delete this->mButtonUp;
	delete this->mButtonDown;

}


Window::Window():QMainWindow()
{
	this->setFixedSize(660,600);
	this->mScene = new Scene( this);
	this->mField = new Field(640, 480);
	this->mPlayer = new Player(this->mField, "Player 1");
	this->mScene->addPlayer(this->mPlayer);
	this->mScene->setField(this->mField);

	QGridLayout *layout = new QGridLayout;

	
	QWidget *centralWidget = new QWidget(this);
	

	QPushButton *b1 = new QPushButton("LEFT");
	QPushButton *b2 = new QPushButton("RIGHT");
	QPushButton *b3 = new QPushButton("UP");
	QPushButton *b4 = new QPushButton("DOWN");
	//QPushButton *b5 = new QPushButton("ADD");
	
	this->mButtonDown = b4;
	this->mButtonUp = b3;
	this->mButtonRight = b2;
	this->mButtonLeft = b1;

	//QSlider* pRedSlider = new QSlider(Qt::Horizontal,this);
	//QSlider* pGreenSlider = new QSlider(Qt::Horizontal, this);
	//QSlider* pBlueSlider = new QSlider(Qt::Horizontal, this);


	//pRedSlider->setFocusPolicy(Qt::StrongFocus);
	//pRedSlider->setTickPosition(QSlider::TicksBothSides);
	//pRedSlider->setTickInterval(255);
	//pRedSlider->setSingleStep(1);

	QObject::connect(b1, &QPushButton::clicked,  [b1,this](const bool checked) {
		
		this->mPlayer->onKeyPressed('A');
		
	});
	QObject::connect(b2, &QPushButton::clicked, [b2, this](const bool checked) {
		this->mPlayer->onKeyPressed('D');
	});
	QObject::connect(b3, &QPushButton::clicked, [b3, this](const bool checked) {
		this->mPlayer->onKeyPressed('W');
	});
	QObject::connect(b4, &QPushButton::clicked, [b4, this](const bool checked) {
		this->mPlayer->onKeyPressed('S');
	});
	/*QObject::connect(b5, &QPushButton::clicked, [b4, this](const bool checked) {
		this->mPlayer->onKeyPressed('A');
	});*/
	
	layout->addWidget(b3, 3, 2);
	layout->addWidget(b1, 4, 1);
	layout->addWidget(b2, 4, 3);
	layout->addWidget(b4, 5, 2);


	this->setActions();
	this->createMenu();


	//layout->addWidget(centralWidget, 0, 1, 1, 3);
	layout->addWidget(this->mScene, 1, 1, 1, 3);
	//layout->addWidget(pRedSlider, 1, 4);
	//layout->addWidget(pGreenSlider, 2, 4);
	//layout->addWidget(pBlueSlider, 3, 4);
	//layout->addWidget(b5, 2, 3);
	/*
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
	
	*/
	this->setCentralWidget(centralWidget);
	centralWidget->setLayout(layout);

	QTimer *timer = new QTimer(this);
	//connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
	connect(timer, SIGNAL(timeout()), this->mScene, SLOT(animate()));
	timer->start(50);

	setWindowTitle(tr("SNAKE"));
}

void Window::OptionsWnd()
{

	OptionWindow* pOptionWnd = new OptionWindow();
	pOptionWnd->show();

}

void Window::createMenu(){


	this->mSettingsMenu = menuBar()->addMenu(tr("&Impostazioni"));
	mSettingsMenu->addAction(this->mOptionAct);

	mSettingsMenu->addSeparator();
	mSettingsMenu->addAction(this->mExitAct);

}
void Window::setActions(){
	this->mOptionAct = new QAction(tr("&Opzioni"), this);
	this->mOptionAct->setStatusTip(tr("Vai alle impostazioni..."));


	connect(this->mOptionAct, SIGNAL(triggered()), this, SLOT(OptionsWnd()));

	this->mExitAct = new QAction(tr("&Chiudi"), this);
	this->mExitAct->setShortcuts(QKeySequence::Quit);
	this->mExitAct->setStatusTip(tr("Chiudi applicazione"));
	connect(this->mExitAct, SIGNAL(triggered()), this, SLOT(close()));
}


void Window::keyPressEvent(QKeyEvent* e)
{
	
	char pkey = 0;
	switch (e->key())
	{
	case Qt::Key_Up:
		pkey = 'W';
		break;
	case Qt::Key_Left:
		pkey = 'A';
		break;
	case Qt::Key_Right:
		pkey = 'D';
		break;
	case Qt::Key_Down:
		pkey = 'S';
	default:{
		if (e->text().length()){
			pkey = e->text().at(0).toUpper().toLatin1();
		}
	}
		break;
	}
	this->mPlayer->onKeyPressed(pkey);
	
	/*
	QMessageBox* box = new QMessageBox();
	box->setWindowTitle(QString("Hello"));
	box->setText(QString("You Pressed: ") + e->text());
	box->show();*/
};