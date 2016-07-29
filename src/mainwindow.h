#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define _WINSOCKAPI_

#include <QMainWindow>
#include "json.hpp"
#include "PlayerFrame.h"
#include "ChallongeParser.h"
#include "AniListParser.h"
#include "ImageManager.h"
#include "Player.h"

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

	Player *p1;
	PlayerFrame *p1Frame;
	Player *p2;
	PlayerFrame *p2Frame;
	ChallongeParser *challonge;
	AniListParser *aniList;
	ImageManager *imgManager;
};

#endif // MAINWINDOW_H
