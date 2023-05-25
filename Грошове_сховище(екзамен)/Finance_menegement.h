#pragma once
#include<set>
#include"Storages.h"
class FinanceManagement
{
	set<MoneyStorage*> storages;
public:
	FinanceManagement();
	void AddStorage(MoneyStorage* ptr); //додати сховище
	void DeleteStorage(long long number);  // видалити сховище
	void Info(); //вивід даних всіх сховищ
	void TopUpStorage();   //поповнити сховище
	void AddSpendingToStorage(); // додати витрату до сховища
	void Menu();    // меню
	 //звіти
	void DayReport();
	void WeekReport();
	void MonthReport();
	//рейтинги
	void RatingMonth();
	void RatingWeek();
	//рейтинги категорій
	void RatingMonthCategory();
	void RatingWeekCategory();
};
