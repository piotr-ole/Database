#pragma once
#include "Database.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

const int N = 15;

class record
{
private:
	int id;
	char name[N];
	char surname[N];
	int age;
	template <typename T>
	static void singleStyling(ostream& out, const char* field, T value, int wide_field, int wide_value, int color);
public:
	record();
	record(const char* name, const char* surname, int age);
	void changeName(char n[]);
	void changeSurname(char n[]);
	void changeAge(int a);
	int getID();
	const char* getName();
	const char* getSurname();
	int getAge();
	friend class Database;
	friend ostream& operator<<(ostream& out, record& rec);
};