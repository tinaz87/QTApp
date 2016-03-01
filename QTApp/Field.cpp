#include <stdafx.h>


Field::Field(const uint16_t iWidth, const uint16_t iHeight) :mWidth(iWidth), mHeight(iHeight), mMinXY(0, 0), mMaxXY(iWidth, iHeight), mFoodEnable(false){
	this->mFood.mPosition.setX(-1);
	this->mFood.mPosition.setY(-1);
	this->mColor.setRgb(64, 32, 64);
}

void Field::setFood(const uint16_t iCoordX, const uint16_t iCoordY){
	this->mFoodEnable = true;

	this->mFood.mColor.setRgb(qrand() % 250, qrand() % 250, qrand() % 250);
	this->mFood.mPosition.setX(iCoordX);
	this->mFood.mPosition.setY(iCoordY);

}

bool Field::isFoodEnable()const{
	return this->mFoodEnable;
}
void Field::disableFood(){
	this->mFoodEnable = false;
}