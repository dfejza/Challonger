#pragma once
#include "newWizardDialogue.h"

#include <QtWidgets>


IntroPage::IntroPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle("API Info");
	setSubTitle("Please enter your challong API information.\n"
		"While logged in to Challonge.com, access the following URL :\n"
		"https://challonge.com/settings/developer \n"
		"Copy the API Key field found and place it in the following box.");

	nameLabel = new QLabel("API Key:");
	nameLineEdit = new QLineEdit;
	layout = new QGridLayout;

	layout->addWidget(nameLabel, 0, 0);
	layout->addWidget(nameLineEdit, 0, 1);

	registerField("challonge*", nameLineEdit);

	setLayout(layout);
}

ApiPage::ApiPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle("API Info");
	setSubTitle("Select the API that will be used to fetch images and follow the instructions.\n"
		"Each API has it's strength and weaknesses. \nSelect the API and press next for more information on"
		" selected API");

	comboBox = new QComboBox;
	comboBox->addItem(("AniList"));
	comboBox->addItem(("Google"));
	comboBox->addItem(("IMDB"));

	layoutPageTwo = new QGridLayout;

	nameLabel = new QLabel("API Choice:");
	layoutPageTwo->addWidget(nameLabel, 0, 0);
	layoutPageTwo->addWidget(comboBox, 0, 1);

	setLayout(layoutPageTwo);
}

AnilistPage::AnilistPage(QWidget *parent)
	: QWizardPage(parent)
{
	nextBtn = false;
	setTitle("API Info");
	setSubTitle("Anilist - Specialized for anime");

	layoutPageTwo = new QGridLayout;


	directions = new QLabel("While already logged in to anilist.co, access the following website:\n"
		"http://anilist.co/settings/developer \n"
		"Create a new client, and copy the specified fields to down below.");
	clientID = new QLabel("Client ID:");
	clientIDEdit = new QLineEdit;
	clientSecret = new QLabel("Client Secret:");
	clientSecretEdit = new QLineEdit;
	valButton = new QPushButton("Validate Settings", this);
	valButton->setGeometry(QRect(QPoint(100, 100),
		QSize(200, 50)));

	layoutPageTwo->addWidget(directions, 0, 0);
	layoutPageTwo->addWidget(clientID, 2, 0);
	layoutPageTwo->addWidget(clientIDEdit, 2, 1);
	layoutPageTwo->addWidget(clientSecret, 3, 0);
	layoutPageTwo->addWidget(clientSecretEdit, 3, 1);
	layoutPageTwo->addWidget(valButton, 5, 1);

	registerField("clientIDEdit*", clientIDEdit);
	registerField("clientSecretEdit*", clientSecretEdit);
	//UserVar::apiId = field("register.clientIDEdit").toString().toStdString();
	//UserVar::apiKey = field("register.clientSecretEdit").toString().toStdString();

	setLayout(layoutPageTwo);
	connect(valButton, SIGNAL(released()), this, SLOT(checkAnilistApi()));
}

void AnilistPage::checkAnilistApi() {
	nextBtn = true;
	emit completeChanged();
}

GooglePage::GooglePage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle("API Info"); 
	setSubTitle("Google");

	layoutPageTwo = new QGridLayout;


	directions = new QLabel("While already logged in to google.com, access the following website:\n"
		"https://cse.google.com/cse/ \n"
		"Follow the onscreen instructions, and get the API key. \n "
		"	NOTE: While google is the most flexable search engine, \n	you are limited to 100 searches per day.\n"
		"	This means only the first 100 contestants will have images associated with their names.");
	clientID = new QLabel("API Key:");
	clientIDEdit = new QLineEdit;
	valButton = new QPushButton("Validate Settings", this);
	valButton->setGeometry(QRect(QPoint(100, 100),
		QSize(200, 50)));

	layoutPageTwo->addWidget(directions, 0, 0);
	layoutPageTwo->addWidget(clientID, 2, 0);
	layoutPageTwo->addWidget(clientIDEdit, 3, 0);
	layoutPageTwo->addWidget(valButton, 4, 0);

	registerField("register.clientIDEdit*", clientIDEdit);

	setLayout(layoutPageTwo);
	connect(valButton, SIGNAL(released()), this, SLOT(checkGoogleApi()));
}

void GooglePage::checkGoogleApi() {

	nextBtn = true;
	emit completeChanged();
}

ImdbPage::ImdbPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle("API Info");
	setSubTitle("IMDB");

	layoutPageTwo = new QGridLayout;


	directions = new QLabel(" Not implemented, you ought to go back and select something different");
	valButton = new QPushButton("Validate Settings", this);
	valButton->setGeometry(QRect(QPoint(100, 100),
		QSize(200, 50)));

	layoutPageTwo->addWidget(directions, 0, 0);

	setLayout(layoutPageTwo);
}

ConclusionPage::ConclusionPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle("Conclusion");

	label = new QLabel("What would you like to name this tournament?");
	label->setWordWrap(true);
	tournamentName = new QLineEdit;

	layout = new QVBoxLayout;
	layout->addWidget(label);
	layout->addWidget(tournamentName);

	registerField("tournamentName*", tournamentName);

	setLayout(layout);
}

newWizardDialogue::newWizardDialogue(QWidget *parent)
	: QWizard(parent)
{
	nxtBtn = button(QWizard::NextButton);

	setPage(Page_Intro, new IntroPage);
	setPage(Page_API, new ApiPage);
	setPage(Page_ANILIST, new AnilistPage);
	setPage(Page_GOOGLE, new GooglePage);
	setPage(Page_IMDB, new ImdbPage);
	setPage(Page_Conclusion, new ConclusionPage);
	setStartId(Page_Intro);

	connect(button(QWizard::CancelButton), SIGNAL(clicked()), this, SLOT(~newWizardDialogue()));
	//connect(button(QWizard::FinishButton), SIGNAL(clicked()), this, SLOT(accept()));

}

bool AnilistPage::isComplete() const
{
	if (nextBtn)
		return true;
	else
		return false;
}
bool GooglePage::isComplete() const
{
	if (nextBtn)
		return true;
	else
		return false;
}
bool ImdbPage::isComplete() const
{
	return false;
}

bool ConclusionPage::isFinalPage() const
{
	return true;
}

void newWizardDialogue::accept()
{
	UserVar::challongerKey = field("challonge").toString();
	UserVar::tournamentName = field("tournamentName").toString();
	if (UserVar::apiChoice == 0)
	{
		UserVar::apiId = field("clientIDEdit").toString();
		UserVar::apiKey = field("clientSecretEdit").toString();
	}
	else if (UserVar::apiChoice == 1)
	{
		UserVar::challongerKey = field("googleAPI").toString();
	}
	else
	{
		//UserVar::challongerKey = field("register.challonge").toString().toStdString();
	}
	QDialog::accept();
}
newWizardDialogue::~newWizardDialogue()
{
	//todo?
}



int IntroPage::nextId() const
{
	return newWizardDialogue::Page_API;
}

int ApiPage::nextId() const
{
	int pageSel = comboBox->currentIndex();
	if (pageSel == 0)
	{
		UserVar::apiChoice = 0;
		return newWizardDialogue::Page_ANILIST;
	}
	else if (pageSel == 1)
	{
		UserVar::apiChoice = 1;
		return newWizardDialogue::Page_GOOGLE;
	}
	else
	{
		UserVar::apiChoice = 2;
		return newWizardDialogue::Page_IMDB;
	}
}

int AnilistPage::nextId() const
{
	return newWizardDialogue::Page_Conclusion;
}

int GooglePage::nextId() const
{
	return newWizardDialogue::Page_Conclusion;
}

int ImdbPage::nextId() const
{
	return newWizardDialogue::Page_Conclusion;
}
