#pragma once
#include<iostream>

using namespace std;

const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct Date
{
	unsigned day;
	unsigned month;
	unsigned year;
	void Output() const;
	void Input();
	void Edit(int d, int m, int y);
	friend ostream& operator<<(ostream& os, const Date& date);
};

bool isLeap(int year);    // функция для определения, високосным ли является год
int GetDaysInYear(int year);  //функія для знаходження кількості днів у році
int diff_between_dates(Date begin_date, Date end_date); // функция, определяющая количество дней между 2-мя датами датами
struct Time
{
	unsigned hours;
	unsigned minutes;
	unsigned seconds;
	void Output() const;
	void Input();
	void Edit(int sec, int min, int h);
	friend ostream& operator<<(ostream& os, const Time& time);
};
