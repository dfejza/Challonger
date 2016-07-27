#include "mainwindow.h"
#include <QtWidgets>
#include <string>
//#include "lib\anilist\anilistapi.h"

//AniListAPI *apiFetch = new AniListAPI(NULL, "brah-gkee1","oVNN5Ky9wJdoyMPpcZV2b2DlfpwJYz");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	QWidget *topFiller = new QWidget;
	topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	//Player 1
	p1 = new PlayerFrame("assets/p1.jpg", "Player 1");

	//PLayer 2
	p2 = new PlayerFrame("assets/p2.jpg", "Player 2");

	QWidget *bottomFiller = new QWidget;
	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// Create the layout schemes
	// Add the qObjects to the layouts
	QHBoxLayout *centerHorizontalLayout = new QHBoxLayout;
	centerHorizontalLayout->setMargin(100);
	centerHorizontalLayout->addLayout(p1);
	centerHorizontalLayout->addSpacing(100);
	centerHorizontalLayout->addLayout(p2);


	QVBoxLayout *mainVerticalLayout = new QVBoxLayout;
	mainVerticalLayout->setMargin(5);


	//layout->addWidget(infoLabel);
	mainVerticalLayout->addWidget(topFiller);
	mainVerticalLayout->addLayout(centerHorizontalLayout);
	mainVerticalLayout->addWidget(bottomFiller);
	widget->setLayout(mainVerticalLayout);

	createActions();
	createMenus();

	QString message = tr("A context menu is available by right-clicking");
	statusBar()->showMessage(message);

	setWindowTitle(tr("Menus"));
	setMinimumSize(160, 160);
	resize(960, 640);
	quit();
}

MainWindow::~MainWindow(){}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	//menu.addAction(cutAct);
	//menu.addAction(copyAct);
	//menu.addAction(pasteAct);
	menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU


void MainWindow::quit()
{
  aniList = new AniListParser();
  challonge = new ChallongeParser();
  challonge.getCaughtUp();//TODO maybe call this in consturctor of ChallongeParser?
  challonge.loadPlayerFrames(p1, p2);

  //currently p1 and p2 and pointers to PlayerFrames. Let them point to new ones?


}

void MainWindow::credentials()
{
	//Event Listener, What happens when credentials is pressed?
}

void MainWindow::match()
{
	//Event Listener, What happens when match is pressed?
}

void MainWindow::about()
{
	//Event Listener, What happens when about is pressed?
}

void MainWindow::createActions()
{
	quitAct = new QAction(tr("&Quit"), this);
	quitAct->setShortcuts(QKeySequence::Quit);
	quitAct->setStatusTip(tr("Create a new file"));
	connect(quitAct, &QAction::triggered, this, &MainWindow::quit);

	credentialsAct = new QAction(tr("&Edit Credentials"), this);
	//credentialsAct->setShortcuts(QKeySequence::EditCredetials);
	credentialsAct->setStatusTip(tr("Create a new file"));
	connect(credentialsAct, &QAction::triggered, this, &MainWindow::credentials);

	matchAct = new QAction(tr("&Change Match"), this);
	//matchAct->setShortcuts(QKeySequence::New);
	matchAct->setStatusTip(tr("Create a new file"));
	connect(matchAct, &QAction::triggered, this, &MainWindow::match);

	aboutAct = new QAction(tr("&About brah"), this);
	//aboutAct->setShortcuts(QKeySequence::New);
	aboutAct->setStatusTip(tr("Create a new file"));
	connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(quitAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(credentialsAct);
	editMenu->addAction(matchAct);

	formatMenu = menuBar()->addMenu(tr("&Format"));

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
}
