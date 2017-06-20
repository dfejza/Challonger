#pragma once

#include <QtWidgets>
#include "UserVar.h"
#include <QAbstractButton>

class newWizardDialogue : public QWizard
{
	Q_OBJECT
public:
	enum {
		Page_Intro, Page_API, Page_ANILIST, Page_GOOGLE, Page_IMDB,
		Page_Conclusion
	};

	newWizardDialogue(QWidget *parent = 0);
	~newWizardDialogue();
	void accept();
	QAbstractButton *nxtBtn;
private:

};


class IntroPage : public QWizardPage
{
	Q_OBJECT

public:
	IntroPage(QWidget *parent = 0);

	int nextId() const Q_DECL_OVERRIDE;

private:
	QLabel *nameLabel;
	QLineEdit *nameLineEdit;
	QLabel *nameTournLabel;
	QLineEdit *nameTournLineEdit;
	QGridLayout *layout;
};


class ApiPage : public QWizardPage
{
	Q_OBJECT

public:
	ApiPage(QWidget *parent = 0);

	int nextId() const Q_DECL_OVERRIDE;

private:
	QComboBox *comboBox;
	QGridLayout *layoutPageTwo;
	QLabel *nameLabel;
};


class AnilistPage : public QWizardPage
{
	Q_OBJECT

public:
	AnilistPage(QWidget *parent = 0);

	int nextId() const Q_DECL_OVERRIDE;

private slots:
	void checkAnilistApi();
private:
	QLabel *directions;
	QLabel *clientID;
	QLineEdit *clientIDEdit;
	QLabel *clientSecret;
	QLineEdit *clientSecretEdit;
	QGridLayout *layoutPageTwo;
	QPushButton *valButton;
	bool isComplete() const;
	bool nextBtn;
};


class GooglePage : public QWizardPage
{
	Q_OBJECT

public:
	GooglePage(QWidget *parent = 0);

	int nextId() const Q_DECL_OVERRIDE;

private slots:
	void checkGoogleApi();

private:
	QGridLayout *layoutPageTwo;
	QLabel *directions;
	QLabel *clientID;
	QLineEdit *clientIDEdit;
	QPushButton *valButton;
	bool isComplete() const;
	bool nextBtn;
};



class ImdbPage : public QWizardPage
{
	Q_OBJECT

public:
	ImdbPage(QWidget *parent = 0);

	int nextId() const Q_DECL_OVERRIDE;

private:
	QGridLayout *layoutPageTwo;
	QLabel *directions;
	QPushButton *valButton;
	bool isComplete() const;
};



class ConclusionPage : public QWizardPage
{
	Q_OBJECT

public:
	ConclusionPage(QWidget *parent = 0);

private:
	QLabel *label;
	QVBoxLayout *layout;
	QLineEdit *tournamentName;
	bool isFinalPage() const;
};
