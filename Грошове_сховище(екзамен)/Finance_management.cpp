#include<iostream>
#include <fstream>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include"Finance_menegement.h"

using namespace std;

FinanceManagement::FinanceManagement() {}
void FinanceManagement::AddStorage(MoneyStorage* ptr) //������ �������
{
	storages.insert(ptr);
}
void FinanceManagement::DeleteStorage(long long number)  // �������� �������
{
	for (auto st : storages)
	{
		if (st->GetNumber() == number)
		{
			storages.erase(st);
			delete st; // ��������� ��'���� ������� � ���'��
			cout << "������� ������� �� �������  " << number << " ���� ��������." << endl;
			return;
		}
	}
	cout << "������� ������� �� ������� " << number << " �� ��������." << endl;
}
void FinanceManagement::Info() //���� �����
{
	for (const auto& store : storages)
	{
		store->Info();
	}
}
void FinanceManagement::TopUpStorage()   //��������� �������
{
	long long number;
	cout << "������ ����� �����/������� ��� ����������" << endl;
	cin >> number;
	for (auto& it : storages)
	{
		if (it->GetNumber() == number)
		{
			it->AddMoney();
			return;
		}
	}
	cout << "�����/������� � ����� �������(" << number << ") �� ��������." << endl;
}
void FinanceManagement::AddSpendingToStorage() // ������ ������� �� �������
{
	long long number;
	cout << "������ ����� �����/������� ��� ��������� �������" << endl;
	cin >> number;
	for (auto& storage : storages)
	{
		if (storage->GetNumber() == number)
		{
			storage->AddSpending();
			return;
		}
	}
	cout << "�����/������� � ����� �������(" << number << ") �� ��������." << endl;

}
void FinanceManagement::Menu()    // ����
{
	unsigned choise;
	do
	{
		system("pause");
		system("cls");
		cout << "\n\t����\n";
		cout << "1 - ��������� �����/��������\n";
		cout << "2 - �������� ������ ������/��������\n";
		cout << "3 - ������� �� ����� � ������� �� �����\n";
		cout << "4 - �������� ��� �� �������� �� ����\n";  // �� ������� � ����
		cout << "5 - �������� ��� �� �������� �� �������\n";  // �� ������� � ����
		cout << "6 - �������� ��� �� �������� �� �����\n";  // �� ������� � ����
		cout << "7 - ������� ������ �� �������\n";  //  ���-3 ������� �� ������� �� ������� � ����
		cout << "8 - ������� ������ �� �����\n";  // ���-3 ������� �� ����� �� ������� � ����
		cout << "9 - ������� �������� �� �������\n";  // ���-3 ������� �� ������� �� ������� � ����
		cout << "10 - ������� �������� �� �����\n"; // ���-3 ������� �� ����� �� ������� � ����
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
			cout << "������ ������ ���� ����!\n";
		}
	} while (choise != 11);
}
//����
void FinanceManagement::DayReport()   // �� ����
{
	ofstream file_report_day("day_report.txt");
	if (!file_report_day)
	{
		cout << "������� �������� ����� ��� ����." << endl;
		return;
	}
	cout << "������ ����, �� ��� ������ �������� ���" << endl;
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
				cout << "\t��� �� ����: " << spend.GetDate()
					<< "\n�������: " << storage->GetNumber();
				spend.Info();
				file_report_day << "\t��� �� ����: " << spend.GetDate()
					<< "\n�������: " << storage->GetNumber() << "\n���� �������: " << spend.GetMoney()
					<< "\n��������: " << spend.GetCategory() << "(" << categoryes[spend.GetCategory()-1] << ")"
					<< "\n���: " << spend.GetTime() << endl;
			}
		}
	}
	file_report_day.close();
}
void FinanceManagement::WeekReport()     // �� �������
{
	float totalSpends = 0.0;
	ofstream file_report_week("week_report.txt");
	if (!file_report_week)
	{
		cout << "������� �������� ����� ��� ����" << endl;
		return;
	}
	Date dat;
	cout << "������ ���� ��� ���������� ��������� ����" << endl;
	dat.Input();
	system("cls");
	cout << "\t��� �� �������: ";
	file_report_week << "\t��� �� �������: \n";
	for (auto& storage : storages)
	{
		for (auto& spends : storage->GetSpendings())
		{
			if (diff_between_dates(spends.GetDate(), dat) < 7)
			{
				cout << storage->GetNumber() << endl;
				spends.Info();
				totalSpends += spends.GetMoney();
				file_report_week << spends.GetDate() << "\n�������: " << storage->GetNumber() << "\n���� �������: " << spends.GetMoney()
					<< "\n��������: " << spends.GetCategory() << "(" << categoryes[1 - spends.GetCategory()] << ")"
					<< "\n���: " << spends.GetTime() << endl;
			}
		}
	}
	file_report_week << "��������� �� ������� - " << totalSpends << " ���.";
	file_report_week.close();
}
void FinanceManagement::MonthReport()      // �� �����
{
	float totalSpends = 0.0;
	ofstream file_report_month("month_report.txt");
	if (!file_report_month)
	{
		cout << "������� �������� ����� ��� ����" << endl;
		return;
	}
	unsigned mon, year;
	while (true)
	{
		cout << "������ ��(2000-2023) ��� ��������� ����" << endl;
		cin >> year;
		if (year >= 2000 && year <= 2023) { break; }
	}
	while (true)
	{
		cout << "������ ����� �����(1-12), ��� ����� ���� �������� ���" << endl;
		cin >> mon;
		if (mon >= 1 && mon <= 12) { break; }
	}
	system("cls");
	cout << "\t��� �� " << mon << "�����: " << endl;
	file_report_month << "\t��� �� " << " ����� " << mon << ": \n";
	for (auto& storage : storages)
	{
		for (auto& spends : storage->GetSpendings())
		{
			if (spends.GetDate().month == mon && spends.GetDate().year == year)
			{
				cout << storage->GetNumber() << endl;
				spends.Info();
				totalSpends += spends.GetMoney();
				file_report_month << spends.GetDate() << "�������: " << storage->GetNumber() << "\n���� �������: " << spends.GetMoney()
					<< "\n��������: " << spends.GetCategory() << "(" << categoryes[spends.GetCategory()-1] << ")"
					<< "\n���: " << spends.GetTime() << endl;
			}
		}
	}
	file_report_month << "��������� "<< mon << "-�� ����� - " << totalSpends << " ���.";
	file_report_month.close();
}
//�������� ������
void FinanceManagement::RatingWeek()  //�� �������
{
	set<Spending> rating;
	ofstream file_rating_week("week_rating.txt");
	if (!file_rating_week)
	{
		cout << "������� �������� �����" << endl;
		return;
	}
	Date dat;
	int count = 0;
	cout << "������ ���� ��� ���������� ��������� ��������" << endl;
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
	cout << "������� ������ �� �������" << endl;
	file_rating_week << "������� ������ �� �������\n";
	int i = 0;
	for (const auto& elem : rating)
	{
		i++;
		cout << "\n\t��� " << i << endl;
		elem.Info();
		file_rating_week << "\n��� " << i  << "\n���� - " 
			<< elem.GetDate() << "��� - " << elem.GetTime() << "���� ������� - " << elem.GetMoney()
			<< "\n�������� - " << elem.GetCategory() << "(" << categoryes[elem.GetCategory() - 1] << ")"
			<< endl;
		if (i >= 3) { break; }
	}
	file_rating_week.close();
}
void FinanceManagement::RatingMonth()   // �� �����
{
	set<Spending> rating;
	ofstream file_rating_month("month_rating.txt");
	if (!file_rating_month)
	{
		cout << "������� �������� �����" << endl;
		return;
	}
	unsigned m, y;
	int count = 0;
	while (true)
	{
		cout << "������ ��(2000-2023) ��� ��������� ��������" << endl;
		cin >> y;
		if (y >= 2000 && y <= 2023) { break; }
	}
	while (true)
	{
		cout << "������ ����� �����(1-12), ��� ����� ���� �������� �������" << endl;
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
	cout << "������� ������ �� " << m << "-�� �����" << endl;
	int i = 0;
	file_rating_month << "������� ������ �� " << m << "-�� �����\n";
	for (const auto& el : rating)
	{
		i++;
		cout << "\n��� " << i << endl;
		el.Info();
		file_rating_month << "\n\t��� " << i << "\n���� - "
			<< el.GetDate() << "\n��� - " << el.GetTime() << "\n���� ������� - " 
			<< el.GetMoney() << "\n�������� - " << el.GetCategory() << "(" << categoryes[el.GetCategory()-1] << ")"
			<< endl;
		if (i >= 3) { break; }
	}
	file_rating_month.close();
}
//�������� ��������
void FinanceManagement::RatingWeekCategory()  //�� �������
{
	map<int, int> cat_count;
	ofstream file_rating_week_cat("week_rating_category.txt");
	if (!file_rating_week_cat)
	{
		cout << "������� �������� �����." << endl;
		return;
	}
	Date dat;
	int count = 0;
	cout << "������ ���� ��� ���������� ��������� ��������" << endl;
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
	cout << "������� �������� ������ �� �������" << endl;
	file_rating_week_cat << "������� �������� ������ �� �������" << endl;
	int i = 0;
	for (auto& cat : cat_count)
	{
		i++;
		cout << "\n��� " << i << "\n�������� - " << cat.first << "(" << categoryes[cat.first - 1] << ")"
			<< "\nʳ������ ������ �� ���� �������� �� ������� - " << cat.second << endl;
		file_rating_week_cat << "\n��� " << i << "\n�������� - " << cat.first << "(" << categoryes[cat.first - 1] << ")"
			<< "\nʳ������ ������ �� ���� �������� �� ������� - " << cat.second << endl;
		if (i >= 3) { break; }
	}
	file_rating_week_cat.close();
}
void FinanceManagement::RatingMonthCategory()  //�� �����
{
	map<int, int> cat_count;
	ofstream file_rating_month_cat("month_rating_category.txt");
	if (!file_rating_month_cat)
	{
		cout << "������� �������� �����." << endl;
		return;
	}
	unsigned m, y;
	int count = 0;
	while (true)
	{
		cout << "������ ��(2000-2023) ��� ��������� ��������" << endl;
		cin >> y;
		if (y >= 2000 && y <= 2023) { break; }
	}
	while (true)
	{
		cout << "������ ����� �����(1-12), ��� ����� ���� �������� �������" << endl;
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
	cout << "������� ������ �� " << m << "-�� �����" << endl;
	file_rating_month_cat << "������� ������ �� " << m << "-�� �����\n";
	int i = 0;
	for (auto& cat : cat_count)
	{
		i++;
		cout << "\n��� " << i << "\n�������� - " << cat.first << "(" << categoryes[cat.first - 1] << ")"
			<< "\nʳ������ ������ �� ���� �������� �� " << m << "-� ����� - " << cat.second << endl;
		file_rating_month_cat << "\n��� " << i << "\n�������� - " << cat.first << "(" << categoryes[cat.first - 1] << ")"
			<< "\nʳ������ ������ �� ���� �������� �� " << m << "-� ����� - " << cat.second << endl;
		if (i >= 3) { break; }
	}
	file_rating_month_cat.close();
}