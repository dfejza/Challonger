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

	//picture->setFixedHeight(400);
	//picture->setMinimumSize(800, 800);
	//picture->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	this->addWidget(picture);
	this->addWidget(text);
	delete(image);
}

void PlayerFrame::setPicture(QString pic)
{
	//TODO Incomming pic will be a URL. What will you do?
}

void PlayerFrame::setLabel(QString label)
{
}

void PlayerFrame::setScore(int score)
{
}

void PlayerFrame::updateFrame(QString picPath, QString picLabel) {
	QImage *image = new QImage(picPath);
	QImage scaled = image->scaled(250, 400, Qt::KeepAspectRatio);

	picture->setPixmap(QPixmap::fromImage(scaled));
	text->setText(picLabel);
	delete(image);
}