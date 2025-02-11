#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define _WINSOCKAPI_

#include "json.hpp"
#include "PlayerFrame.h"
#include "ChallongeParser.h"
#include "UserVar.h"
#include "newWizardDialogue.h"
#include "FileHandler.h"
#include <QtWidgets>
#include <QMessageBox>

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
	void newTourn();
	void loadTourn();
	void about();
	void quit();
	void handleP1Button();
	void handleP2Button();
	void updatePlayer1Frame(std::string picPath, std::string name);
	void updatePlayer2Frame(std::string picPath, std::string name);

private:
	void createActions();
	void createMenus();
	void initTournamentUI();

	QWidget *widget;
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *formatMenu;
	QMenu *helpMenu;
	QActionGroup *alignmentGroup;
	QAction *credentialsAct;
	QAction *matchAct;
	QAction *newAct;
	QAction *loadAct;
	QAction *aboutAct;
	QAction *quitAct;
	QPushButton *p1_button;
	QPushButton *p2_button;
	PlayerFrame *p1Frame;
	PlayerFrame *p2Frame;

	ChallongeParser *challonge;
	ImageManager *imgManager;
	FileHandler fileHandler;

	double progressBar;
	QProgressDialog *progressdialog;
};

#endif // MAINWINDOW_H
