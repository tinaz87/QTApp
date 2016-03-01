#pragma once

class Drawer;
class QPaintEvent;
class QWidget;

class Field;
class Player;
class Scene : public QGLWidget
{
	Q_OBJECT

public:
	Scene(QWidget *parent);
	void addPlayer(Player* iPlayer);
	void setField(Field* iField);

public slots:
	void animate();

protected:
	void paintEvent(QPaintEvent *event);

private:

	QPen mPen;
	QBrush mBackgroundColor;
	QVector<Player*> mPlayers;
	Field* mField;
	int mElapsedTime;
};
