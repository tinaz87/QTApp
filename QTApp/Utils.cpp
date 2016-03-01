#include <stdafx.h>

bool checkCollision(const Square& iSquare1, const Square& iSquare2){

	return (iSquare1.mPosition.x() < iSquare2.mPosition.x() + iSquare2.mWidth &&
		iSquare1.mPosition.x() + iSquare1.mWidth > iSquare2.mPosition.x() &&
		iSquare1.mPosition.y() < iSquare2.mPosition.y() + iSquare2.mHeight &&
		iSquare1.mHeight + iSquare1.mPosition.y() > iSquare2.mPosition.y());
	


}


bool checkOutOfBoundaries(const Square& iSquare, const QVector2D& iMinXY, const QVector2D& iMaxXY){
	
	bool a1 = (iSquare.mPosition.x() + iSquare.mWidth / 2) > iMaxXY.x();
	bool a2 = (iSquare.mPosition.y() + iSquare.mHeight / 2) > iMaxXY.y();
	bool a3 = (iSquare.mPosition.x() - iSquare.mWidth / 2) < iMinXY.x();
	bool a4 = (iSquare.mPosition.y() - iSquare.mHeight / 2) < iMinXY.y();
	return ( ( a1 || a2 ) || ( a3 || a4 ));
}