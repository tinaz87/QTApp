#pragma once

class Snake;


class Player :public QObject{
	Q_OBJECT
public:
	Player(Field* iFieldm,const std::string& iName );
	~Player();
	void updateStatus(int iElapsed);	
	void addPoint(const uint16_t iPoint);
	uint16_t getPoints()const;
	
	Snake* mSnake;
	bool mWin;
	bool mLoose;
	std::string mName;
signals:
	void onKeyPressed(const char iKey);

private:

	uint16_t mPoints;
};