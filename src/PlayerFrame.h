#pragma once
#include <QtWidgets>
#include <QString>

class PlayerFrame : public QVBoxLayout
{
public:
	PlayerFrame(QString picPath, QString picLabel);
	PlayerFrame(int playerId,Qtring name);
	void setPicture(QString pic);
	void setLabel(QString label);
	void setScore(int score);
	void setPlayerId(int pid);
	int getPlayerId();

private:
	QLabel *picture;
	QLabel *text;
	QLabel *score;
	QImage *image;
	QImage scaled;
	int playerId;
};
