#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define _WINSOCKAPI_

#include "json.hpp"
#include "PlayerFrame.h"
#include "ChallongeParser.h"
#include <QtWidgets>

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
	void handleP1Button();
	void handleP2Button();
	void updatePlayer1Frame(std::string picPath, std::string name);
	void updatePlayer2Frame(std::string picPath, std::string name);

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
	QPushButton *p1_button;
	QPushButton *p2_button;
	PlayerFrame *p1Frame;
	PlayerFrame *p2Frame;

	ChallongeParser *challonge;
	ImageManager *imgManager;
};

#endif // MAINWINDOW_H
