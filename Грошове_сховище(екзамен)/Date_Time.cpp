#include"Date_Time.h"
#include<iostream>
#include<iomanip>

using namespace std;

void Date::Output() const
{
	cout << setw(2) << setfill('0') << day << "/" << setw(2) << setfill('0')
		<< setfill('0') << month << "/" << setw(2) << setfill('0') << year;
}
void Date::Input()
{
	while (true)
	{
		cout << "������ ���� �������: "; cin >> day;
		cout << "������ ����� �������: "; cin >> month;
		cout << "������ �� �������: "; cin >> year;
		if (year >= 2000 && year <= 2023)
		{
			if (month < 12)
			{
				if (month == 1)
				{
					if (day > 29)
					{
						cout << "����������� ����!!" << endl;
						continue;
					}
					else { break; }
				}
				else
				{
					if (day > daysInMonth[month])
					{
						cout << "����������� ����!!" << endl;
						continue;
					}
					else { break; }
				}
			}
			else { cout << "����������� �����(1-12)!!" << endl; continue; }
		}
		else { cout << "����������� �� (2000-2023)!!" << endl; continue; }
	}
}
void Date::Edit(int d, int m, int y)
{
	if (y >= 2000 && y <= 2023) { year = y; }
	else { cout << "����������� �� (2000-2023)!! (��������� ������� ���)" << endl; year = 2000 + rand() % 24; }
	if (m < 12) { month = m; }
	else { cout << "����������� �����(1-12)!! (��������� ������� ���)" << endl; month = 1 + rand() % 12; }
	if (m == 1)
	{
		if (d > 29)
		{
			cout << "����������� ����!! (��������� ������� ���)" << endl;
			day = 1 + rand() % 29;
		}
		else { day = d; }
	}
	else
	{
		if (d > daysInMonth[d-1])
		{
			cout << "����������� ����!! (��������� ������� ���)" << endl;
			day = 1 + rand() % 30;
		}
		else { day = d; }
	}
}
bool isLeap(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}
int GetDaysInYear(int year)
{
	return isLeap(year) ? 366 : 365;
}
int diff_between_dates(Date begin_date, Date end_date) // �������, ������������ ���������� ���� ����� 2-�� ������ ������
{
	int days = 0;

	// ���������� ��� �� ��������� ����
	for (int year = 2000; year < begin_date.year; ++year)
		days += GetDaysInYear(year);

	for (int month = 1; month < begin_date.month; ++month)
		days += daysInMonth[month+1];

	days += begin_date.day;

	// ���������� ��� �� ������ ����
	for (int year = 2000; year < end_date.year; ++year)
		days -= GetDaysInYear(year);

	for (int month = 1; month < end_date.month; ++month)
		days -= daysInMonth[month+1];

	days -= end_date.day;

	if (days < 0) { days *= -1; }
	// ��������� �������� ����
	if (isLeap(begin_date.year) && begin_date.month <= 2)
		--days;

	if (isLeap(end_date.year) && end_date.month > 2)
		++days;

	return days;
}
void Time::Output() const
{
	cout << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0')
		<< setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds;
}
void Time::Input()
{
	while (true)
	{
		cout << "������ ������ �������: "; cin >> hours;
		cout << "������ ������� �������: "; cin >> minutes;
		cout << "������ ������� �������: "; cin >> seconds;
		if (seconds < 60)
		{
			if (minutes < 60)
				if (hours > 24) { cout << "���������� ������(0-23)!!" << endl; continue; }
				else { break; }
			else { cout << "���������� �������(0-59)!!" << endl; continue; }
		}
		else { cout << "���������� �������(0-59)!!" << endl; continue; }
	}
}
void Time::Edit(int sec, int min, int h)
{
	if (sec < 60)
	{
		if (min < 60)
			if (h > 24) { cout << "���������� ������(0-23)!! (��������� ������� ���)" << endl; hours = rand() % 24; }
			else { seconds = sec; minutes = min; hours = h; }
		else { cout << "���������� �������(0-59)!! (��������� ������� ���)" << endl; minutes = rand() % 60; }
	}
	else { cout << "���������� �������(0-59)!! (��������� ������� ���)" << endl; seconds = rand() % 60; }
}

ostream& operator<<(ostream& os, const Time& time)
{
	os << time.hours << ":" << time.minutes << ":" << time.seconds << endl;
	return os;
}
ostream& operator<<(ostream& os, const Date& date)
{
	os << date.day << "/" << date.month << "/" << date.year << endl;
	return os;
}