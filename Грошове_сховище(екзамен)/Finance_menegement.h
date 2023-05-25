#pragma once
#include<set>
#include"Storages.h"
class FinanceManagement
{
	set<MoneyStorage*> storages;
public:
	FinanceManagement();
	void AddStorage(MoneyStorage* ptr); //������ �������
	void DeleteStorage(long long number);  // �������� �������
	void Info(); //���� ����� ��� ������
	void TopUpStorage();   //��������� �������
	void AddSpendingToStorage(); // ������ ������� �� �������
	void Menu();    // ����
	 //����
	void DayReport();
	void WeekReport();
	void MonthReport();
	//��������
	void RatingMonth();
	void RatingWeek();
	//�������� ��������
	void RatingMonthCategory();
	void RatingWeekCategory();
};