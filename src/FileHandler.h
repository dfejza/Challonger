#pragma once

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDataStream>
#include "UserVar.h"

class FileHandler
{
public:
	FileHandler();
	~FileHandler();
	void saveCredentials();
	void loadCredentials(QString fileName);
};

