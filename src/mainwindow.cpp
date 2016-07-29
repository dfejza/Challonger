#include "mainwindow.h"
#include <string>
#include <QtWidgets>
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
	p1Frame = new PlayerFrame("assets/p1.jpg", "Player 1");

	//PLayer 2
	p2Frame = new PlayerFrame("assets/p2.jpg", "Player 2");

	//Make increment score bush buttons
	p1_button = new QPushButton("Player 1 vote", this);
	p2_button = new QPushButton("Player 2 vote", this);
	p1_button->setGeometry(QRect(QPoint(100, 100),
		QSize(200, 50)));
	p2_button->setGeometry(QRect(QPoint(100, 100),
		QSize(200, 50)));

	QWidget *bottomFiller = new QWidget;
	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// Create the layout schemes
	// Add the qObjects to the layouts
	QHBoxLayout *centerHorizontalLayout = new QHBoxLayout;
	centerHorizontalLayout->setMargin(100);
	centerHorizontalLayout->addLayout(p1Frame);
	centerHorizontalLayout->addSpacing(100);
	centerHorizontalLayout->addLayout(p2Frame);

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

	challonge = new ChallongeParser();

}

MainWindow::~MainWindow(){}

void MainWindow::updatePlayer1Frame(std::string picPath, std::string name)
{
	p1Frame->updateFrame(QString::fromStdString(picPath), QString::fromStdString(name));
}

void MainWindow::updatePlayer2Frame(std::string picPath, std::string name)
{
	p2Frame->updateFrame(QString::fromStdString(picPath), QString::fromStdString(name));
}

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
	quitAct = new QAction(tr("&Force p1 win"),this);
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


void MainWindow::handleP1Button()
{
	challonge->incPlayerOneScore();
}

void MainWindow::handleP2Button()
{
	challonge->incPlayerTwoScore();
}