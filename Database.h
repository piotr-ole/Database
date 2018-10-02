#pragma once
#include <string>
#include "record.h"
#include <list>
#include <vector>

using namespace std;

class record;

class Database
{
private:
	int count;
	string filename;
public:
	Database(string filename);
	Database(string filename, list<record> list_of_records);
	void addRecordToDatabase(record& r);
	void resetDatabase();
	void deleteRecordFromDatabase(int serialNumber);
	list<record> databaseToList();
	record getRecordFromDatabase(int serialNumber);
	friend ostream& operator<<(ostream& out, Database& dt);
	void showRecords(list<record> listOfRecords);
	list<record> searchForRecords(bool predicate(record parameter));
};
