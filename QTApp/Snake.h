#pragma once


class Square{
public:
	Square();
	Square(uint16_t iWidth);
	virtual ~Square();
	QColor mColor;
	QVector2D mPosition;

	uint16_t mWidth;
	uint16_t mHeight;

};


class Snake :public QObject
{
	Q_OBJECT
public:
	class BodyPiece :public Square{
	public:
		BodyPiece();
		virtual ~BodyPiece();		
		QVector2D mDirection;
	};

	Snake(Field* iField);
	~Snake();
	
	void Reset();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void addPiece(Square iPiece);
	void addPiece();
	void updatePositions(int iElapsedTime);
	void increaseSpeed(int iIncrease = 1);
	uint16_t getLength()const;

	const BodyPiece* getHead();
	const QVector<BodyPiece*>& getSnakeBody()const;

	bool mCollidingItSelf;
	bool mAlive;

private:
	Field* mField;
	BodyPiece* mHead;
	QVector<BodyPiece*> mSnakeBody;
	QVector2D mDirection;
	std::map<QVector2D, BodyPiece*> mPiecePositions;

	void freeSnakePieces();
	void initSnake();

	int mVelocity;
	int mSupportVelocity;
signals:

public	slots:
	void onPlayerEvent(const char iKey);
};

