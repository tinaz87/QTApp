#include <stdafx.h>


Scene::Scene(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

	this->mElapsedTime = 0;
	this->mPen.setWidth(1);
	this->mPen.setColor(Qt::black);
	setFixedSize(640, 480);
	setAutoFillBackground(false);

}
void Scene::addPlayer(Player* iPlayer){
	this->mPlayers.push_back(iPlayer);
}
void Scene::setField(Field* iField){
	this->mField = iField;
}

void Scene::animate()
{


	this->mElapsedTime = qobject_cast<QTimer*>(sender())->interval();

	update();
}

void Scene::paintEvent(QPaintEvent *event)
{

	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QBrush background = QBrush(GameSettings::mFieldColor);
	painter.fillRect(event->rect(), background);
	painter.setFont(QFont("Arial", 16));
	
	
	bool pDrawFood = true;

	painter.save();

	painter.setPen(this->mPen);

	if (GameSettings::mRestart){
		for each (Player* pPlayer in this->mPlayers)
		{
			pPlayer->Reset();
		}
		GameSettings::mRestart = false;
	}
	
	for each (Player* pPlayer in this->mPlayers)
	{
		
		
		auto pSnake = pPlayer->mSnake;
		const auto& pSnakeBody = pSnake->getSnakeBody();
		const Snake::BodyPiece* pSnakeHead = pSnake->getHead();
		
		if (!GameSettings::mPause){

			if (this->mField->isFoodEnable()){

				if (checkCollision(*pSnakeHead, this->mField->mFood))
				{
					pSnake->addPiece(this->mField->mFood);
					pPlayer->addPoint(1);
					this->mField->disableFood();
					if (pSnakeBody.length() % 5 == 0){
						pSnake->increaseSpeed();
					}
				}
			}
			else{

				Square pTmp;
				do
				{
					pTmp.mPosition.setX(qrand() % ((int)this->mField->mMaxXY.x() - pSnakeHead->mWidth * 2) + pSnakeHead->mWidth);
					pTmp.mPosition.setY(qrand() % ((int)this->mField->mMaxXY.y() - pSnakeHead->mHeight * 2) + pSnakeHead->mHeight);
				} while (checkCollision(*pSnakeHead, pTmp));

				this->mField->setFood(pTmp.mPosition.x(), pTmp.mPosition.y());


			}

			pPlayer->updateStatus(this->mElapsedTime);
		}
		

		if (pSnake->mCollidingItSelf){
			pSnake->mAlive = false;
			pPlayer->mLoose = true;
		}
		else if (pSnake->getLength() >= 50){
			pPlayer->mWin = true;

		}

		/* draw */
		painter.setBrush(GameSettings::mSnakeColor);

		for (auto it = pSnakeBody.cbegin(); it != pSnakeBody.end(); ++it){
			painter.drawRect((*it)->mPosition.x(), (*it)->mPosition.y(), (*it)->mWidth, (*it)->mHeight);

		}

		// disegno il cibo una volta sola nel caso avessi piu giocatori.
		if (pDrawFood && this->mField->isFoodEnable()){

			painter.setBrush(this->mField->mFood.mColor);
			painter.drawRect(this->mField->mFood.mPosition.x(), this->mField->mFood.mPosition.y(), this->mField->mFood.mWidth, this->mField->mFood.mHeight);
			pDrawFood = !pDrawFood;
		}
		
		QString pPointText = ( pPlayer->mName + " : " +std::to_string((LONGLONG)pPlayer->getPoints())).c_str();
		painter.drawText(rect(), Qt::AlignTop | Qt::AlignLeft, pPointText);

		if (pPlayer->mWin){
			painter.setPen(Qt::yellow);
			QString pWinText = "Hai Vinto :) !\n";
			pWinText += pPlayer->mName.c_str();
			painter.drawText(rect(), Qt::AlignCenter, pWinText);			
		}
		else if (pPlayer->mLoose){
			painter.setPen(Qt::red);
			QString pLooseText = "Hai Perso :( ! \n";
			pLooseText += pPlayer->mName.c_str();
			painter.drawText(rect(), Qt::AlignCenter, pLooseText);
		}


	}

	

	painter.restore();

	painter.end();
}