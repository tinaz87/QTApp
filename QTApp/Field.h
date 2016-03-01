#pragma once

class Square;

class Field{
public:
	Field(const uint16_t iWidth,const uint16_t iHeight);
	void setFood(const uint16_t iCoordX , const uint16_t iCoordY );
	void disableFood();
	bool isFoodEnable()const;

	uint16_t mHeight;
	uint16_t mWidth;
	QVector2D mMinXY;
	QVector2D mMaxXY;
	QColor mColor;
	Square mFood;

private:
	bool mFoodEnable;

};