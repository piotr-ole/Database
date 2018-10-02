#include "Database.h"
#include <iostream>
#include <fstream>

using namespace std;

Database::Database(string filename) : filename(filename)
{
	count = 0;
	fstream dataFile;
	dataFile.open((filename + ".bin").c_str(), ios::binary | ios::out | ios::in);
	dataFile.close();
}

Database::Database(string filename, list<record> listOfRecords) : Database(filename)
{
	fstream dataFile;
	dataFile.open((filename + ".bin").c_str(), ios::binary | ios::out);
	list<record>::iterator it;
	for (it = listOfRecords.begin(); it != listOfRecords.end(); ++it);
	{
		this->addRecordToDatabase(*it);
	}
	dataFile.close();

}

void Database::addRecordToDatabase(record& rec)
{
	count++;
	rec.id = count;
	fstream dataFile;
	dataFile.open((filename + ".bin").c_str(), ios::binary | ios::out | ios::app);
	dataFile.seekp(0, ios::end);
	dataFile.write((char*)&rec, sizeof(record));
	dataFile.close();
}

void Database::resetDatabase()
{
	fstream dataFile;
	dataFile.open((filename + ".bin").c_str(), ios::binary | ios::out | ios::trunc);
	dataFile.close();
}

void Database::deleteRecordFromDatabase(int serialNumber)
{
	fstream dataFile;
	list<record> listOfRecords = this->databaseToList();
	dataFile.open((filename + ".bin").c_str(), ios::binary | ios::out);
	list<record>::iterator it = listOfRecords.begin(), flag = it;
	bool isRecordDeleted = false;
	advance(flag, serialNumber - 1);
	for (it = listOfRecords.begin(); it != listOfRecords.end(); ++it)
	{
		if (it != flag)
		{
			if (isRecordDeleted == false)
				dataFile.write((char*)&(*it), sizeof(record));
			else
			{
				(*it).id--;
				dataFile.write((char*)&(*it), sizeof(record));
			}
		}
		else
			isRecordDeleted = true;
	}
	dataFile.close();
}

list<record> Database::databaseToList()
{ 
	list<record> listOfRecords;
	record tmp;
	fstream dataFile;
	dataFile.open((filename + ".bin").c_str(), ios::binary | ios::in);
	dataFile.seekg(0, ios::beg);
	while (dataFile.read((char*)&tmp, sizeof(record)))
		listOfRecords.push_back(tmp);
	dataFile.close();
	return listOfRecords;
}

record Database::getRecordFromDatabase(int serialNumber)
{
	record r;
	fstream dataFile;
	dataFile.open((filename + ".bin").c_str(), ios::binary | ios::in);
	dataFile.seekg(sizeof(record)*(serialNumber - 1), ios::beg);
	dataFile.read((char*)&r, sizeof(record));
	return r;
}

ostream & operator<<(ostream & out, Database & dt)
{
	fstream dataFile;
	record temporaryRecord;
	dataFile.open((dt.filename + ".bin").c_str(), ios::binary | ios::in);
	out << "DATABASE CONTENTS:\n\n";
	out << "-----------------------------" << endl;
	while (dataFile.read((char*)&temporaryRecord, sizeof(record)))
	{
		out << temporaryRecord;
	}
	dataFile.close();
	return out;
}

void Database::showRecords(list<record> listOfRecords)
{
	list<record>::iterator it = listOfRecords.begin();
	for (it; it != listOfRecords.end(); ++it)
		cout << (*it);
}

list<record> Database::searchForRecords(bool predicate(record parameter))
{
	list<record> listOfRecords;
	fstream dataFile;
	record temporaryRecord;
	dataFile.open((filename + ".bin").c_str(), ios::binary | ios::in);
	while (dataFile.read((char*)&temporaryRecord, sizeof(record)))
	{
		if (predicate(temporaryRecord))
			listOfRecords.push_back(temporaryRecord);
	}
	dataFile.close();
	return listOfRecords;
}
