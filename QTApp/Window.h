#pragma once
#include "Drawer.h"

class QLabel;
class QWidget;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class OptionWindow :public QWidget{


	Q_OBJECT

public:
	OptionWindow();
	~OptionWindow();

};

class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window();
	virtual ~Window();
	void keyPressEvent(QKeyEvent* e);
	Player* mPlayer;
	QPushButton* mButtonUp;
	QPushButton* mButtonDown;
	QPushButton* mButtonLeft;
	QPushButton* mButtonRight;
	
protected:
	//void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private slots:
	void OptionsWnd();
private:
	Scene *mScene;
	Field* mField ;

	QMenuBar* mMenuBar;
	QMenu* mSettingsMenu;
	QAction *mOptionAct;
	QAction *mExitAct;


	void setActions();
	void createMenu();

};