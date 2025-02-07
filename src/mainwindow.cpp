#include "mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	widget = new QWidget;
	setCentralWidget(widget);

	QVBoxLayout *mainVerticalLayout = new QVBoxLayout; //TODO MEM LEAK
	mainVerticalLayout->setMargin(1);
	QLabel *intro = new QLabel("New API and Tournament? \n File->New Tournament\n"
		 "\nContinuing a previous tournament?\n File->Load Tournament\n"
		 "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	intro->setAlignment(Qt::AlignCenter);

	mainVerticalLayout->addWidget(intro);
	widget->setLayout(mainVerticalLayout);

	createActions();
	createMenus();

	QString message = tr("A context menu is available by right-clicking");
	statusBar()->showMessage(message);

	setWindowTitle(tr("Menus"));
	setMinimumSize(160, 160);
	resize(1100, 900);

}

MainWindow::~MainWindow(){}

void MainWindow::initTournamentUI() 
{
	widget = new QWidget;
	setCentralWidget(widget);

	progressdialog = new QProgressDialog("Downloading images...", "Cancel", 0, 10000, this);
	progressdialog->setWindowModality(Qt::WindowModal);

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

	// Create the layout schemes
	// Add the qObjects to the layouts
	QHBoxLayout *centerHorizontalLayout = new QHBoxLayout;
	centerHorizontalLayout->setMargin(100);
	centerHorizontalLayout->addLayout(p1Frame);
	centerHorizontalLayout->addSpacing(100);
	centerHorizontalLayout->addLayout(p2Frame);
	//centerHorizontalLayout->addStretch(1);


	QHBoxLayout *bottomHorizontalLayout = new QHBoxLayout;
	bottomHorizontalLayout->setMargin(100);
	bottomHorizontalLayout->addWidget(p1_button);
	bottomHorizontalLayout->addSpacing(100);
	bottomHorizontalLayout->addWidget(p2_button);
	//bottomHorizontalLayout->addStretch(1);

	QVBoxLayout *mainVerticalLayout = new QVBoxLayout;
	mainVerticalLayout->setMargin(1);


	//layout->addWidget(infoLabel);
	mainVerticalLayout->addLayout(centerHorizontalLayout);
	//mainVerticalLayout->addLayout(centerHorizontalLayout);
	mainVerticalLayout->addLayout(bottomHorizontalLayout);

	widget->setLayout(mainVerticalLayout);
	

	challonge = new ChallongeParser(&p1Frame, &p2Frame, &progressdialog);

	connect(p1_button, SIGNAL(released()), this, SLOT(handleP1Button()));
	connect(p2_button, SIGNAL(released()), this, SLOT(handleP2Button()));
}

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



void MainWindow::loadTourn()
{
	fileHandler.loadCredentials(QFileDialog::getOpenFileName(this,
		tr("Open Tournament Cred"), "",
		tr("Tournament File (*.brah);;All Files (*)")));

	//check if the wizard was canceld
	if (UserVar::challongerKey.size() > 5)
	{
		delete widget;

		// Start the GUI
		initTournamentUI();
	}
}

void MainWindow::quit()
{
	exit(1);
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
	newAct = new QAction(tr("&New Tournament"), this);
	newAct->setShortcuts(QKeySequence::Quit);
	newAct->setStatusTip(tr("Start a new tournament"));
	connect(newAct, &QAction::triggered, this, &MainWindow::newTourn);

	loadAct = new QAction(tr("&Load Tournament"), this);
	loadAct->setShortcuts(QKeySequence::Quit);//todo
	loadAct->setStatusTip(tr("Load a previous tournament"));
	connect(loadAct, &QAction::triggered, this, &MainWindow::loadTourn);

	quitAct = new QAction(tr("&Exit"), this);
	quitAct->setShortcuts(QKeySequence::Quit);//todo
	quitAct->setStatusTip(tr("Exit challonger"));
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
	fileMenu->addAction(newAct);
	fileMenu->addAction(loadAct);
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


void MainWindow::newTourn()
{
	newWizardDialogue wizard;
	wizard.exec();
	//check if the wizard was canceld
	if (UserVar::challongerKey.size() > 5)
	{
		delete widget;
		// Save the credentials
		fileHandler.saveCredentials();
		// Start the GUI
		initTournamentUI();
	}
}
