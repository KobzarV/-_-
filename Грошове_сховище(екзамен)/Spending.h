#pragma once
#include"Date_Time.h"

///////////////////  �������

class Spending
{
	float money;
	int category;
	Date date;
	Time time;
public:
	Spending();
	Spending(float mon, int cat, Date d, Time t);
	void Info() const;
	void Input();
	void Edit(float mon, int cat, Date d, Time t);
	float GetMoney() const
	{
		return money;
	}
	int GetCategory() const
	{
		return category;
	}
	bool operator<(const Spending b) const
	{
		return money > b.money;
	}
	const Date GetDate() const { return date; }
	const Time GetTime() const { return time; }
	bool operator>(const Spending& sp) const;
};
// �������: 1 - ��������, 2 - ��������, 3 - ��������, 4 - ��������� ����., 5 - �������, 6 - ���������, 7 - ����
static string categoryes[]{ "��������", "��������", "��������", "��������� ����.", "�������", "���������", "����" };