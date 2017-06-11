#include "FileHandler.h"

FileHandler::FileHandler()
{
}


FileHandler::~FileHandler()
{
}

// Save the credentials provided in the configuration wizard to a file, for later use
void FileHandler::saveCredentials()
{
	//Create the file
	QFile file(UserVar::tournamentName + ".brah");
	if (!file.open(QIODevice::WriteOnly))
	{
		qDebug() << "Could not open " << UserVar::tournamentName;
		return;
	}

	// Create the stream
	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_5_1);

	// Push to the stream
	out << UserVar::apiKey
		<< UserVar::apiId
		<< UserVar::challongerKey
		<< UserVar::tournamentId
		<< UserVar::tournamentName;

	// Flush
	file.flush();
	file.close();
}

// Load the credentials, skipping the new tournament wizard
void FileHandler::loadCredentials(QString fileName)
{
	if (fileName.isEmpty())
		return;
	else {
		QFile file(fileName);
		file.open(QIODevice::ReadOnly);
		QDataStream in(&file);
		in.setVersion(QDataStream::Qt_5_1);
		in >> UserVar::apiKey >> UserVar::apiId >> UserVar::challongerKey >> UserVar::tournamentId >> UserVar::tournamentName;
	}

}