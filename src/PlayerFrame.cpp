#include "PlayerFrame.h"

PlayerFrame::PlayerFrame(QString picPath, QString picLabel)
{
	QImage *image = new QImage(picPath);
	QImage scaled = image->scaled(250, 400, Qt::KeepAspectRatio);
	picture = new QLabel();
	text = new QLabel(picLabel);
	picture->setPixmap(QPixmap::fromImage(scaled));
	picture->setAlignment(Qt::AlignCenter);
	text->setAlignment(Qt::AlignCenter);

	this->addWidget(picture);
	this->addWidget(text);
}

void PlayerFrame::setPicture(QString pic)
{
}

void PlayerFrame::setLabel(QString label)
{
}

void PlayerFrame::setScore(int score)
{
}
