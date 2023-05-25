#include"Spending.h"
#include<iostream>

using namespace std;
Spending::Spending()
{
	money = 1;
	category = 7;
	date.Input();
	time.Input();
}
Spending::Spending(float mon, int cat, Date d, Time t)
{
	if (mon <= 0) { money = 1; }
	else { money = mon; }
	if (cat >= 1 && cat <= 7) { category = cat; }
	else {
		while (true)
		{
			cout << "Введіть номер категорії витрати:" << endl;
			cout << "1 - магазин; 2 - перекази; 3 - мобільний;" << endl;
			cout << "4 - комунальні послуги; 5 - розваги; 6 - транспорт;" << endl;
			cout << "7 - інше" << endl;
			cin >> cat;
			if (cat < 1 || cat > 7) { continue; }
			else { break; }
		}
	}
	date = d;
	time = t;
}
void Spending::Info() const
{
	cout << "\nВитрата" << endl;
	cout << "Витрачено грошей - " << money << endl;
	cout << "Категорія витрати - " << category << "(" << categoryes[category-1] << ")" << endl;
	cout << "Дата витрати" << endl;
	date.Output();
	cout << "\nЧас витрати" << endl;
	time.Output();
	cout << endl;
}
void Spending::Input()
{
	cout << "Введіть суму витрати - "; cin >> money;
	if (money <= 0) { money = 1; }
	while (true)
	{
		cout << "Введіть номер категорії витрати:" << endl;
		cout << "1 - магазин; 2 - перекази; 3 - мобільний;" << endl;
		cout << "4 - комунальні послуги; 5 - розваги; 6 - транспорт;" << endl;
		cout << "7 - інше" << endl;
		cin >> category;
		if (category < 1 || category > 7) { continue; }
		else { break; }
	}
	date.Input();
	time.Input();
}
void Spending::Edit(float mon, int cat, Date d, Time t)
{
		if (money <= 0) { money = 1; }
		else { money = mon; }
		if (category < 1 || category > 7) { category = 7; }
		else { category = cat; }
		date = d;
		time = t;
}
bool Spending::operator>(const Spending& sp) const { return this->GetMoney() < sp.GetMoney(); }
