#include "stdafx.h"


Player::Player(Field* iField, const std::string& iName) :mLoose(false), mWin(false), mPoints(0),mName(iName){

	this->mSnake = new Snake(iField);
	QObject::connect(this, SIGNAL(onKeyPressed(const char)), this->mSnake, SLOT(onPlayerEvent(const char)));

}

Player::~Player(){
	QObject::disconnect(this->mSnake);
	delete this->mSnake;
	this->mSnake = nullptr;

}
void Player::updateStatus(int elapsed){
	
	if (!this->mWin && !this->mLoose)
		this->mSnake->updatePositions(elapsed);
}

void Player::addPoint(const uint16_t iPoint){
	this->mPoints += iPoint;
}
uint16_t Player::getPoints()const{
	return this->mPoints;
}