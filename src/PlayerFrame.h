#pragma once
#include <QtWidgets>
#include <QString>
#include <string>

class PlayerFrame : public QVBoxLayout
{
public:
	PlayerFrame(QString picPath, QString picLabel);
	//PlayerFrame(int playerId,QString name);
	void setPicture(QString pic);
	void setLabel(QString label);
	void setScore(int score);
	void updateFrame(QString picPath, QString picLabel);

private:
	QLabel *picture;
	QLabel *text;
	QLabel *score;
	QImage *image;
	QImage scaled;
};
