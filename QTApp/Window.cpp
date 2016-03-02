#include <stdafx.h>


OptionWindow::OptionWindow() :QWidget(), mChangingColorField(false), mChangingColorSnake(false), mColorDialog(nullptr), mColorSnakeButton(nullptr),mColorFieldButton(nullptr){
	//QGridLayout *layout = new QGridLayout;

	this->setFixedSize(320, 240);
	setWindowTitle(tr("Opzioni"));


	this->mColorDialog = new QColorDialog();
	

	QVBoxLayout *layout = new QVBoxLayout();
	


	this->mColorSnakeButton = new QPushButton(tr("Snake Color"));
	connect(this->mColorSnakeButton, SIGNAL(clicked()), this, SLOT(selectSnakeColor()));

	this->mColorFieldButton = new QPushButton(tr("Field Color"));
	connect(this->mColorFieldButton, SIGNAL(clicked()), this, SLOT(selectFieldColor()));

	layout->addWidget(this->mColorSnakeButton);
	layout->addWidget(this->mColorFieldButton);


	connect(mColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(onColorChange(const QColor&)));

	connect(mColorDialog, SIGNAL(finished(int)), this, SLOT(onCloseColorDialog(int)));

	this->setLayout(layout);

}
OptionWindow::~OptionWindow(){ 

	disconnect(this->mColorDialog);
	disconnect(this->mColorFieldButton);
	disconnect(this->mColorSnakeButton);

	delete this->mColorDialog; 
	this->mColorDialog = nullptr;

	delete this->mColorFieldButton;
	this->mColorFieldButton = nullptr;

	delete this->mColorSnakeButton;
	this->mColorSnakeButton = nullptr;
}
void OptionWindow::closeEvent(QCloseEvent *bar){
	GameSettings::mPause = false;
}

void OptionWindow::onColorChange(const QColor& color){
	if (this->mChangingColorField)
		GameSettings::mFieldColor = color;
	else
		GameSettings::mSnakeColor = color;
}
void OptionWindow::onCloseColorDialog(int iResult){
	
	if (!iResult){
		if (this->mChangingColorField)
			GameSettings::mFieldColor = this->mBackUpColor;
		else
			GameSettings::mSnakeColor = this->mBackUpColor;
	}
	this->mChangingColorField = false;
	this->mChangingColorSnake = false;
}
void OptionWindow::selectFieldColor()
{
	this->mChangingColorField = true;
	this->mBackUpColor = GameSettings::mFieldColor;
	this->mColorDialog->show();
}
void OptionWindow::selectSnakeColor()
{
	this->mChangingColorSnake = true;
	this->mBackUpColor = GameSettings::mSnakeColor;
	this->mColorDialog->show();
}


Window:: ~Window(){
	delete this->mScene;
	delete this->mField;
	delete this->mPlayer;

	this->mScene = nullptr;
	this->mField = nullptr;
	this->mPlayer = nullptr;

	QObject::disconnect(this->mButtonRight);
	QObject::disconnect(this->mButtonLeft);
	QObject::disconnect(this->mButtonUp);
	QObject::disconnect(this->mButtonDown);

	delete this->mButtonRight;
	delete this->mButtonLeft;
	delete this->mButtonUp;
	delete this->mButtonDown;

	this->mButtonRight = nullptr;
	this->mButtonLeft = nullptr;
	this->mButtonUp = nullptr;
	this->mButtonDown = nullptr;

	delete this->mTimer;
	this->mTimer = nullptr;


	if (this->mOptionWnd){
		delete this->mOptionWnd;
		this->mOptionWnd = nullptr;
	}
	
	delete this->mOptionAct;
	this->mOptionAct;

	delete this->mExitAct;
	this->mExitAct;

	delete this->mButtonPause;
	this->mButtonPause = nullptr;

	delete this->mButtonRestart;
	this->mButtonRestart = nullptr;

	
	delete this->mLeftWidget;
	this->mLeftWidget = nullptr;

	
}


Window::Window() :QMainWindow(), mOptionWnd(nullptr), mScene(nullptr), mField(nullptr), 
mPlayer(nullptr), mButtonDown(nullptr), mButtonLeft(nullptr), mButtonRight(nullptr), mButtonUp(nullptr), mTimer(nullptr)
{
	this->setFixedSize(760,600);
	this->mScene = new Scene( this);
	this->mField = new Field(640, 480);
	this->mPlayer = new Player(this->mField, "Player 1");
	this->mScene->addPlayer(this->mPlayer);
	this->mScene->setField(this->mField);

	this->setFocusPolicy(Qt::StrongFocus);
	this->setAttribute(Qt::WA_QuitOnClose, true);

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


	QObject::connect(b1, &QPushButton::clicked,  [b1,this](const bool checked) {
		
		this->setFocus();
		this->mPlayer->onKeyPressed('A');
		
	});
	QObject::connect(b2, &QPushButton::clicked, [b2, this](const bool checked) {
		this->setFocus();
		this->mPlayer->onKeyPressed('D');
	});
	QObject::connect(b3, &QPushButton::clicked, [b3, this](const bool checked) {
		this->setFocus();
		this->mPlayer->onKeyPressed('W');
	});
	QObject::connect(b4, &QPushButton::clicked, [b4, this](const bool checked) {
		this->setFocus();
		this->mPlayer->onKeyPressed('S');
	});
	
	layout->addWidget(b3, 3, 2);
	layout->addWidget(b1, 4, 1);
	layout->addWidget(b2, 4, 3);
	layout->addWidget(b4, 5, 2);


	this->setActions();
	this->createMenu();


	
	layout->addWidget(this->mScene, 1, 1, 1, 3);

	this->mLeftWidget = new QWidget();
	this->mVLayout = new QVBoxLayout(mLeftWidget);
	this->mButtonPause = new QPushButton("Pause");
	this->mButtonRestart = new QPushButton("Restart");
	
	
	connect(this->mButtonPause, SIGNAL(clicked()), this, SLOT(GamePause()));

	connect(this->mButtonRestart, SIGNAL(clicked()), this, SLOT(GameRestart()));


	this->mLeftWidget->setFixedSize(100, 80);
	this->mVLayout->addWidget(this->mButtonPause);
	this->mVLayout->addWidget(this->mButtonRestart);

	this->setCentralWidget(centralWidget);
	

	layout->addWidget(mLeftWidget, 1, 4);
	centralWidget->setLayout(layout);
	this->mTimer = new QTimer(this);
	
	connect(this->mTimer, SIGNAL(timeout()), this->mScene, SLOT(animate()));
	this->mTimer->start(10);

	setWindowTitle(tr("SNAKE"));
}
void Window::closeEvent(QCloseEvent *bar){
	if (this->mOptionWnd){
		this->mOptionWnd->close();
		
	}
}

void Window::GameRestart(){
	GameSettings::mRestart = true;
}
void Window::GamePause(){
	GameSettings::mPause = !GameSettings::mPause;
	this->mButtonPause->setText(GameSettings::mPause ? "Resume" : "Pause");
}
void Window::OptionsWnd()
{

	if (!this->mOptionWnd){
		this->mOptionWnd = new OptionWindow();
	}
	GameSettings::mPause = true;
	this->mOptionWnd->show();

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
	
};