#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include <curl/curl.h>
#include <cpr/cpr.h>
#include <QMainWindow>
#include "json.hpp"
#include "PlayerFrame.h"
#include "ChallongeParser.h"
#include "AniListParser.h"
// for convenience
using json = nlohmann::json;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
	void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
#endif // QT_NO_CONTEXTMENU

private slots:
	void credentials();
	void match();
	void quit();
	void about();

private:
	void createActions();
	void createMenus();

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *formatMenu;
	QMenu *helpMenu;
	QActionGroup *alignmentGroup;
	QAction *credentialsAct;
	QAction *matchAct;
	QAction *quitAct;
	QAction *aboutAct;
	QLabel *pOneLabelPicture;
	QLabel *pOneLabelText;
	QLabel *pTwoLabelPicture;
	QLabel *pTwoLabelText;
	PlayerFrame *p1;
	PlayerFrame *p2;
  ChallongeParser *challonge;
  AniListParser *aniList;
};

#endif // MAINWINDOW_H

/*

QImage *image = new QImage("p1.jpg");
QImage scaled = image->scaled(250, 400, Qt::KeepAspectRatio);
QPainter* painter = new QPainter(&scaled);
painter->setPen(Qt::white);
painter->setFont(QFont("Arial", 30));
painter->drawText(scaled.rect(), Qt::AlignBottom, "Player 1");
pOneLabel = new QLabel();
pOneLabel->setPixmap(QPixmap::fromImage(scaled));
pOneLabel->setAlignment(Qt::AlignCenter);

QImage *image2 = new QImage("p2.jpg");
QImage scaled2 = image2->scaled(250, 400, Qt::KeepAspectRatio);
QPainter* painter2 = new QPainter(&scaled2);
painter2->setPen(Qt::blue);
painter2->setFont(QFont("Arial", 30));
painter2->drawText(scaled2.rect(), Qt::AlignBottom, "Player 2");
pTwoLabel = new QLabel();
pTwoLabel->setPixmap(QPixmap::fromImage(scaled2));
pTwoLabel->setAlignment(Qt::AlignCenter);

*/
