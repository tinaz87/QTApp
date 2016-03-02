#pragma once


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

private:

	bool mChangingColorSnake;
	bool mChangingColorField;
	QColorDialog* mColorDialog;
	QPushButton* mColorSnakeButton;
	QPushButton* mColorFieldButton;
	QColor mBackUpColor;

	void closeEvent(QCloseEvent *bar);
private slots:
	
	void selectSnakeColor();
	void selectFieldColor();
	
	// se iResult==1 allora ho premuto ok , 0 altrimenti
	void onCloseColorDialog(int iResult);
	void onColorChange(const QColor& color);
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

private slots:
	void OptionsWnd();
	void GamePause();
	void GameRestart();
private:
	Scene *mScene;
	Field* mField ;

	QTimer *mTimer;
	OptionWindow* mOptionWnd;
	QMenuBar* mMenuBar;
	QMenu* mSettingsMenu;
	QAction *mOptionAct;
	QAction *mExitAct;
	QWidget* mLeftWidget;
	QVBoxLayout *mVLayout;
	QPushButton *mButtonPause;
	QPushButton *mButtonRestart;

	void setActions();
	void createMenu();
	void closeEvent(QCloseEvent *bar);
};