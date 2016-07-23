#pragma once
#include <QtWidgets>
#include <QString>

class PlayerFrame : public QVBoxLayout
{
public:
	PlayerFrame(QString picPath, QString picLabel);
	void setPicture(QString pic);
	void setLabel(QString label);
	void setScore(int score);

private:
	QLabel *picture;
	QLabel *text;
	QLabel *score;
	QImage *image;
	QImage scaled;
};