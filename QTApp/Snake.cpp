#include "stdafx.h"



Square::Square() :mPosition(0, 0), mHeight(20), mWidth(20),mColor(Qt::cyan){}
Square::Square(uint16_t iWidth) : mPosition(0, 0), mWidth(iWidth), mHeight(iWidth), mColor(Qt::cyan){}
Square::~Square(){}


Snake::BodyPiece::BodyPiece(): mDirection(0, 1){}
Snake::BodyPiece::~BodyPiece(){}

Snake::Snake(Field* iField) : mDirection(0, 1), mVelocity(5),mField(iField), mAlive(true),mCollidingItSelf(false){
	mHead = new BodyPiece;
	mHead->mPosition.setX(mHead->mWidth / 2);
	mHead->mPosition.setY(mHead->mHeight / 2);
	mHead->mDirection = this->mDirection;
	mSnakeBody.push_back(mHead);

	this->mSupportVelocity = this->mVelocity;
	this->addPiece();
}
Snake::~Snake(){
	for (size_t i = 0; i < this->mSnakeBody.size(); ++i){
		delete this->mSnakeBody.at(i);
	}
	this->mSnakeBody.clear();
	this->mHead = nullptr;
}
uint16_t Snake::getLength()const{
	return this->mSnakeBody.size();
}
void Snake::increaseSpeed(int iIncrease /*=1*/){
	this->mVelocity -= iIncrease;
}

void Snake::moveLeft(){
	if (this->mDirection.x() == 0){
		
		this->mDirection.setX(-1);
		this->mDirection.setY(0);
		
	}
}

void Snake::moveRight(){
	if (this->mDirection.x() == 0){
		this->mDirection.setX(1);
		this->mDirection.setY(0);
	}
}
void Snake::moveUp(){
	if (this->mDirection.y() == 0){
		
		this->mDirection.setX(0);
		this->mDirection.setY(-1);
	}
}
void Snake::moveDown(){
	if (this->mDirection.y() == 0){
		
		this->mDirection.setX(0);
		this->mDirection.setY(1);
	}
	
}


void Snake::onPlayerEvent(const char iKey){

	QVector2D pNewDirection;
	switch (iKey){
	case '+':{
		this->addPiece();
		break;
	}
	case 'A':{
		
		this->moveLeft();
		break;
	}
	case 'D':{

		this->moveRight();
		break;
	}
	case 'W':{
		this->moveUp();
		
		break;
	}
	case 'S':{
		this->moveDown();
		break;
	}
	default: break;
	}

	
	
}

void Snake::addPiece(){
	this->addPiece(Square());
}

void Snake::addPiece(Square iPiece){

	const BodyPiece* pLast = this->mSnakeBody.at(this->mSnakeBody.size() - 1);

	BodyPiece* pNewPiece = new BodyPiece();

	pNewPiece->mPosition.setX(pLast->mPosition.x() - pLast->mDirection.x() * (pLast->mWidth));
	pNewPiece->mPosition.setY(pLast->mPosition.y() - pLast->mDirection.y() * (pLast->mHeight));

	pNewPiece->mDirection = pLast->mDirection;
	pNewPiece->mColor = pLast->mColor;
	pNewPiece->mHeight = iPiece.mHeight;
	pNewPiece->mWidth = iPiece.mWidth;

	this->mSnakeBody.push_back(pNewPiece);
}
const Snake::BodyPiece* Snake::getHead(){
	
	return this->mHead;
	
}
void Snake::updatePositions(int iElapsedTime){

	
	
	if ( this->mSupportVelocity-- <= 0 && this->mAlive){

		this->mHead->mDirection = this->mDirection;


			if (this->mSnakeBody.size() > 1){

				auto pNewHead = this->mSnakeBody[this->mSnakeBody.length() - 1];
				this->mSnakeBody.pop_back();


				pNewHead->mPosition = this->mHead->mPosition + this->mHead->mDirection * QVector2D(this->mHead->mWidth, this->mHead->mHeight);
				

				if (this->mVelocity<0 && this->mVelocity>-10){
					pNewHead->mPosition += this->mHead->mDirection * ( QVector2D(.2f, .2f) * -this->mVelocity);
				}

				this->mSnakeBody.push_front(pNewHead);

				this->mHead = pNewHead;

			}

			
			if ( checkOutOfBoundaries(*this->mHead, this->mField->mMinXY, this->mField->mMaxXY) ){
				if (this->mHead->mPosition.x() - this->mHead->mWidth / 2 < 0){
					this->mHead->mPosition.setX(this->mField->mMaxXY.x() - this->mHead->mWidth / 2);
				}
				if (this->mHead->mPosition.y() - this->mHead->mHeight / 2 < 0){
					this->mHead->mPosition.setY(this->mField->mMaxXY.y() - this->mHead->mHeight / 2);
				}


				if (this->mHead->mPosition.x() - this->mHead->mWidth / 2 > this->mField->mMaxXY.x()){
					this->mHead->mPosition.setX(this->mHead->mWidth / 2);
				}
				if (this->mHead->mPosition.y() - this->mHead->mHeight / 2 > this->mField->mMaxXY.y()){
					this->mHead->mPosition.setY(this->mHead->mHeight / 2);
				}

			}

		
			for (size_t idx = 1; idx < this->mSnakeBody.size(); ++idx){
				
				if (this->mSnakeBody.at(idx)->mPosition.distanceToPoint(this->mHead->mPosition) < this->mHead->mWidth){
				
					this->mCollidingItSelf = true;
					break;
				}
			}


		this->mSupportVelocity = this->mVelocity;
	} 
	
}
const QVector<Snake::BodyPiece*>& Snake::getSnakeBody() const{
	return this->mSnakeBody;
}

