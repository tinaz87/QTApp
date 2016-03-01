#pragma once

class Square;
bool checkCollision(const Square& iSquare1, const Square& iSquare2);


bool checkOutOfBoundaries(const Square& iSquare, const QVector2D& iMinXY, const QVector2D& iMaxXY);