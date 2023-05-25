#include<iostream>
#include <fstream>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include"Finance_menegement.h"

using namespace std;

FinanceManagement::FinanceManagement() {}
void FinanceManagement::AddStorage(MoneyStorage* ptr) //додати сховище
{
	storages.insert(ptr);
}
void FinanceManagement::DeleteStorage(long long number)  // видалити сховище
{
	for (auto st : storages)
	{
		if (st->GetNumber() == number)
		{
			storages.erase(st);
			delete st; // Видалення об'єкту рахунку з пам'яті
			cout << "Грошове сховище із номером  " << number << " було видалено." << endl;
			return;
		}
	}
	cout << "Грошове сховище за номером " << number << " не знайдено." << endl;
}
void FinanceManagement::Info() //вивід даних
{
	for (const auto& store : storages)
	{
		store->Info();
	}
}
void FinanceManagement::TopUpStorage()   //поповнити сховище
{
	long long number;
	cout << "Введіть номер карти/гаманця для поповнення" << endl;
	cin >> number;
	for (auto& it : storages)
	{
		if (it->GetNumber() == number)
		{
			it->AddMoney();
			return;
		}
	}
	cout << "Карти/Гаманця з таким номером(" << number << ") не знайдено." << endl;
}
void FinanceManagement::AddSpendingToStorage() // додати витрату до сховища
{
	long long number;
	cout << "Введіть номер карти/гаманця для додавання витрати" << endl;
	cin >> number;
	for (auto& storage : storages)
	{
		if (storage->GetNumber() == number)
		{
			storage->AddSpending();
			return;
		}
	}
	cout << "Карти/Гаманця з таким номером(" << number << ") не знайдено." << endl;

}
void FinanceManagement::Menu()    // меню
{
	unsigned choise;
	do
	{
		system("pause");
		system("cls");
		cout << "\n\tМеню\n";
		cout << "1 - Поповнити карту/гаманець\n";
		cout << "2 - Здійснити оплату картою/гаманцем\n";
		cout << "3 - Вивести всі карти і гаманці на екран\n";
		cout << "4 - Показати звіт по витратам за день\n";  // із записом у файл
		cout << "5 - Показати звіт по витратам за тиждень\n";  // із записом у файл
		cout << "6 - Показати звіт по витратам за місяць\n";  // із записом у файл
		cout << "7 - Рейтинг витрат за тиждень\n";  //  ТОП-3 витрати за тиждень із записом у файл
		cout << "8 - Рейтинг витрат за місяць\n";  // ТОП-3 витрати за місяць із записом у файл
		cout << "9 - Рейтинг категорій за тиждень\n";  // ТОП-3 категорії за тиждень із записом у файл
		cout << "10 - Рейтинг категорій за місяць\n"; // ТОП-3 категорії за місяць із записом у файл
		cout << "11 - Exit\n";
		cin >> choise;
		switch (choise)
		{
		case 1:
			TopUpStorage();
			break;
		case 2:
			AddSpendingToStorage();
			break;
		case 3:
			Info();
			break;
		case 4:
			DayReport();
			break;
		case 5:
			WeekReport();
			break;
		case 6:
			MonthReport();
			break;
		case 7:
			RatingWeek();
			break;
		case 8:
			RatingMonth();
			break;
		case 9:
			RatingWeekCategory();
			break;
		case 10:
			RatingMonthCategory();
			break;
		case 11:
			cout << "Bye!\n";
			break;
		default:
			cout << "Такого пункту меню немає!\n";
		}
	} while (choise != 11);
}
//звіти
void FinanceManagement::DayReport()   // за день
{
	ofstream file_report_day("day_report.txt");
	if (!file_report_day)
	{
		cout << "Помилка відкриття файлу для звіту." << endl;
		return;
	}
	cout << "Введіть дату, за яку хочите отримати звіт" << endl;
	Date dat;
	dat.Input();
	system("cls");
	for (auto &storage : storages)
	{
		for (auto &spend : storage->GetSpendings())
		{
			Date temp = spend.GetDate();
			if (temp.day == dat.day)
			{
				cout << "\tЗвіт за день: " << spend.GetDate()
					<< "\nСховище: " << storage->GetNumber();
				spend.Info();
				file_report_day << "\tЗвіт за день: " << spend.GetDate()
					<< "\nСховище: " << storage->GetNumber() << "\nСума витрати: " << spend.GetMoney()
					<< "\nКатегорія: " << spend.GetCategory() << "(" << categoryes[spend.GetCategory()-1] << ")"
					<< "\nЧас: " << spend.GetTime() << endl;
			}
		}
	}
	file_report_day.close();
}
void FinanceManagement::WeekReport()     // за тиждень
{
	float totalSpends = 0.0;
	ofstream file_report_week("week_report.txt");
	if (!file_report_week)
	{
		cout << "Помилка відкриття файлу для звіту" << endl;
		return;
	}
	Date dat;
	cout << "Введіть дату для формування тижневого звіту" << endl;
	dat.Input();
	system("cls");
	cout << "\tЗвіт за тиждень: ";
	file_report_week << "\tЗвіт за тиждень: \n";
	for (auto& storage : storages)
	{
		for (auto& spends : storage->GetSpendings())
		{
			if (diff_between_dates(spends.GetDate(), dat) < 7)
			{
				cout << storage->GetNumber() << endl;
				spends.Info();
				totalSpends += spends.GetMoney();
				file_report_week << spends.GetDate() << "\nСховище: " << storage->GetNumber() << "\nСума витрати: " << spends.GetMoney()
					<< "\nКатегорія: " << spends.GetCategory() << "(" << categoryes[1 - spends.GetCategory()] << ")"
					<< "\nЧас: " << spends.GetTime() << endl;
			}
		}
	}
	file_report_week << "Витрачено за тиждень - " << totalSpends << " грн.";
	file_report_week.close();
}
void FinanceManagement::MonthReport()      // за місяць
{
	float totalSpends = 0.0;
	ofstream file_report_month("month_report.txt");
	if (!file_report_month)
	{
		cout << "Помилка відкриття файлу для звіту" << endl;
		return;
	}
	unsigned mon, year;
	while (true)
	{
		cout << "Введіть рік(2000-2023) для створення звіту" << endl;
		cin >> year;
		if (year >= 2000 && year <= 2023) { break; }
	}
	while (true)
	{
		cout << "Введіть номер місяця(1-12), для якого буде створено звіт" << endl;
		cin >> mon;
		if (mon >= 1 && mon <= 12) { break; }
	}
	system("cls");
	cout << "\tЗвіт за " << mon << "місяць: " << endl;
	file_report_month << "\tЗвіт за " << " місяць " << mon << ": \n";
	for (auto& storage : storages)
	{
		for (auto& spends : storage->GetSpendings())
		{
			if (spends.GetDate().month == mon && spends.GetDate().year == year)
			{
				cout << storage->GetNumber() << endl;
				spends.Info();
				totalSpends += spends.GetMoney();
				file_report_month << spends.GetDate() << "Сховище: " << storage->GetNumber() << "\nСума витрати: " << spends.GetMoney()
					<< "\nКатегорія: " << spends.GetCategory() << "(" << categoryes[spends.GetCategory()-1] << ")"
					<< "\nЧас: " << spends.GetTime() << endl;
			}
		}
	}
	file_report_month << "Витрачено "<< mon << "-го місяця - " << totalSpends << " грн.";
	file_report_month.close();
}
//рейтинги витрат
void FinanceManagement::RatingWeek()  //за тиждень
{
	set<Spending> rating;
	ofstream file_rating_week("week_rating.txt");
	if (!file_rating_week)
	{
		cout << "Помилка відкриття файлу" << endl;
		return;
	}
	Date dat;
	int count = 0;
	cout << "Введіть дату для формування тижневого рейтингу" << endl;
	dat.Input();
	for (auto& storage : storages)
	{
		for (auto& spends : storage->GetSpendings())
		{
			if (diff_between_dates(spends.GetDate(), dat) < 7)
			{
				rating.insert(spends);
			}
		}
	}
	system("cls");
	cout << "Рейтинг витрат за тиждень" << endl;
	file_rating_week << "Рейтинг витрат за тиждень\n";
	int i = 0;
	for (const auto& elem : rating)
	{
		i++;
		cout << "\n\tТОП " << i << endl;
		elem.Info();
		file_rating_week << "\nТоп " << i  << "\nДата - " 
			<< elem.GetDate() << "Час - " << elem.GetTime() << "Сума витрати - " << elem.GetMoney()
			<< "\nКатегорія - " << elem.GetCategory() << "(" << categoryes[elem.GetCategory() - 1] << ")"
			<< endl;
		if (i >= 3) { break; }
	}
	file_rating_week.close();
}
void FinanceManagement::RatingMonth()   // за місяць
{
	set<Spending> rating;
	ofstream file_rating_month("month_rating.txt");
	if (!file_rating_month)
	{
		cout << "Помилка відкриття файлу" << endl;
		return;
	}
	unsigned m, y;
	int count = 0;
	while (true)
	{
		cout << "Введіть рік(2000-2023) для створення рейтингу" << endl;
		cin >> y;
		if (y >= 2000 && y <= 2023) { break; }
	}
	while (true)
	{
		cout << "Введіть номер місяця(1-12), для якого буде створено рейтинг" << endl;
		cin >> m;
		if (m >= 1 && m <= 12) { break; }
	}
	for (auto& storage : storages)
	{
		for (auto& spends : storage->GetSpendings())
		{
			if (spends.GetDate().month == m && spends.GetDate().year == y)
			{
				rating.insert(spends);
			}
		}
	}
	system("cls");
	cout << "Рейтинг витрат за " << m << "-ий місяць" << endl;
	int i = 0;
	file_rating_month << "Рейтинг витрат за " << m << "-ий місяць\n";
	for (const auto& el : rating)
	{
		i++;
		cout << "\nТОП " << i << endl;
		el.Info();
		file_rating_month << "\n\tТоп " << i << "\nДата - "
			<< el.GetDate() << "\nЧас - " << el.GetTime() << "\nСума витрати - " 
			<< el.GetMoney() << "\nКатегорія - " << el.GetCategory() << "(" << categoryes[el.GetCategory()-1] << ")"
			<< endl;
		if (i >= 3) { break; }
	}
	file_rating_month.close();
}
//рейтинги категорій
void FinanceManagement::RatingWeekCategory()  //за тиждень
{
	map<int, int> cat_count;
	ofstream file_rating_week_cat("week_rating_category.txt");
	if (!file_rating_week_cat)
	{
		cout << "Помилка відкриття файлу." << endl;
		return;
	}
	Date dat;
	int count = 0;
	cout << "Введіть дату для формування тижневого рейтингу" << endl;
	dat.Input();
	for (auto& storage : storages)
	{
		for (auto& spends : storage->GetSpendings())
		{
			if (diff_between_dates(spends.GetDate(), dat) < 7)
			{
				cat_count[spends.GetCategory()]++;
			}
		}
	}
	system("cls");
	cout << "Рейтинг категорій витрат за тиждень" << endl;
	file_rating_week_cat << "Рейтинг категорій витрат за тиждень" << endl;
	int i = 0;
	for (auto& cat : cat_count)
	{
		i++;
		cout << "\nТОП " << i << "\nКатегорія - " << cat.first << "(" << categoryes[cat.first - 1] << ")"
			<< "\nКількість витрат за цією категорією за тиждень - " << cat.second << endl;
		file_rating_week_cat << "\nТОП " << i << "\nКатегорія - " << cat.first << "(" << categoryes[cat.first - 1] << ")"
			<< "\nКількість витрат за цією категорією за тиждень - " << cat.second << endl;
		if (i >= 3) { break; }
	}
	file_rating_week_cat.close();
}
void FinanceManagement::RatingMonthCategory()  //за місяць
{
	map<int, int> cat_count;
	ofstream file_rating_month_cat("month_rating_category.txt");
	if (!file_rating_month_cat)
	{
		cout << "Помилка відкриття файлу." << endl;
		return;
	}
	unsigned m, y;
	int count = 0;
	while (true)
	{
		cout << "Введіть рік(2000-2023) для створення рейтингу" << endl;
		cin >> y;
		if (y >= 2000 && y <= 2023) { break; }
	}
	while (true)
	{
		cout << "Введіть номер місяця(1-12), для якого буде створено рейтинг" << endl;
		cin >> m;
		if (m >= 1 && m <= 12) { break; }
	}
	for (auto& storage : storages)
	{
		for (auto& spends : storage->GetSpendings())
		{
			if (spends.GetDate().month == m && spends.GetDate().year == y)
			{
				cat_count[spends.GetCategory()]++;
			}
		}
	}
	system("cls");
	cout << "Рейтинг витрат за " << m << "-ий місяць" << endl;
	file_rating_month_cat << "Рейтинг витрат за " << m << "-ий місяць\n";
	int i = 0;
	for (auto& cat : cat_count)
	{
		i++;
		cout << "\nТОП " << i << "\nКатегорія - " << cat.first << "(" << categoryes[cat.first - 1] << ")"
			<< "\nКількість витрат за цією категорією за " << m << "-й місяць - " << cat.second << endl;
		file_rating_month_cat << "\nТОП " << i << "\nКатегорія - " << cat.first << "(" << categoryes[cat.first - 1] << ")"
			<< "\nКількість витрат за цією категорією за " << m << "-й місяць - " << cat.second << endl;
		if (i >= 3) { break; }
	}
	file_rating_month_cat.close();
}