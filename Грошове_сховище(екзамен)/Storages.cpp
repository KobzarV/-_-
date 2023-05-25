#pragma once
#include"Storages.h"
/////////////////////////////////  базовий клас
MoneyStorage::MoneyStorage()
{
	int temp = 10000000 + rand() % 1000000000;
	number = (rand() % 100000) + temp;
	credit_limit = 0;
	balance = 1;
}
MoneyStorage::MoneyStorage(long long num, float credit)
{
	number = num;
	if (credit <= 0) { credit_limit = 0; }
	else { credit_limit = credit; }
	balance = 1;
}
MoneyStorage::MoneyStorage(multiset<Spending>& spends, long long num, float balans, float limit)
{
	number = num;
	if (limit <= 0) { credit_limit = 0; }
	else { credit_limit = limit; }
	if (balans <= 0) { balance = 0; }
	else { balance = balans; }
	spendings = spends;
}
void MoneyStorage::AddMoney()
{
	float temp;
	system("cls");
	cout << "Введіть суму поповнення - ";
	cin >> temp;
	if (temp <= 0) { cout << "Невірно введені дані" << endl; temp = 0; }
	balance += temp;
}
void MoneyStorage::AddMoney(float money)
{
	system("cls");
	if (money <= 0) { cout << "Невірно введені дані" << endl; money = 1; }
	balance += money;
}
void MoneyStorage::AddSpending()
{
	float money;
	int cat;
	Date dat;
	Time tm;
	system("cls");
	cout << "\tДодати витрату" << endl;
	cout << "Введіть суму витрати - "; cin >> money;
	if (money <= 0 || money > balance)
	{
		cout << "Некоректні дані або недостатньо коштів!" << endl;
		return;
	}
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
	dat.Input();
	tm.Input();
	spendings.insert(Spending(money, cat, dat, tm));
}

//////////////////////////////////   клас Card

Card::Card(long long num, float credit, string name) : MoneyStorage(num, credit) { card_name = name; }
Card::Card(multiset<Spending>& m, long long num, float t, float credit, string name) : MoneyStorage(m, num, credit, t) { card_name = name; }
void Card::Info()
{
	cout << "\t\tКарта - " << card_name << endl;
	cout << "Номер - " << number << endl;
	cout << "Баланс - " << balance << endl;
	cout << "Кредитний ліміт - " << credit_limit << endl;
	for (const auto& i : spendings) {
		i.Info();
	}
}
void Card::Edit()
{
	int choise;
	float limit;
	long long t;
	string nam;
	cout << "\tМеню редагування карти" << endl;
	cout << "1) Змінити всі дані" << endl;
	cout << "2) Змінити назву карти" << endl;
	cout << "3) Змінити номер карти" << endl;
	cout << "4) Змінити кредитний ліміт" << endl;
	cin >> choise;
	switch (choise)
	{
	case 1:
		cout << "Введіть новий номер " << endl;
		cin >> t;
		number = t;
		cout << "Введіть нову назву карти" << endl;
		cin >> nam;
		card_name = nam;
		cout << "Введіть новий кредитний ліміт" << endl;
		cin >> limit;
		if (limit <= 0) { cout << "Невірно введені дані" << endl; credit_limit = 0; }
		else { credit_limit = limit; }
		break;
	case 2:
		cout << "Введіть нову назву карти" << endl;
		cin >> nam;
		card_name = nam;
		break;
	case 3:
		cout << "Введіть новий номер карти" << endl;
		cin >> t;
		number = t;
		break;
	case 4:
		cout << "Введіть новий кредитний ліміт" << endl;
		cin >> limit;
		if (limit <= 0) { cout << "Невірно введені дані" << endl; credit_limit = 0; }
		else { credit_limit = limit; }
		break;
	default:
		cout << "Немає такого пункту меню!" << endl;
	}
}

////////////////////////////////// клас Wallet

Wallet::Wallet(long long num, float credit, string name) : MoneyStorage(num, credit) { wallet_name = name; }
Wallet::Wallet(multiset<Spending>& m, long long num, float t, float credit, string name) : MoneyStorage(m, num, credit, t) { wallet_name = name; }
void Wallet::Info()
{
	cout << "\t\tВіртуальний гаманець - " << wallet_name << endl;
	cout << "Номер - " << number << endl;
	cout << "Баланс - " << balance << endl;
	cout << "Кредитний ліміт - " << credit_limit << endl;
	for (const auto& i : spendings) {
		i.Info();
	}
}
void Wallet::Edit()
{
	int choise, limit;
	long long t;
	string nam;
	cout << "\tМеню редагування гаманця" << endl;
	cout << "1) Змінити всі дані" << endl;
	cout << "2) Змінити назву гаманця" << endl;
	cout << "3) Змінити номер гаманця" << endl;
	cout << "4) Змінити кредитний ліміт" << endl;
	cin >> choise;
	switch (choise)
	{
	case 1:
		cout << "Введіть новий номер " << endl;
		cin >> t;
		number = t;
		cout << "Введіть нову назву" << endl;
		cin >> nam;
		wallet_name = nam;
		cout << "Введіть новий кредитний ліміт" << endl;
		cin >> limit;
		if (limit <= 0) { cout << "Невірно введені дані" << endl; credit_limit = 0; }
		else { credit_limit = limit; }
		break;
	case 2:
		cout << "Введіть нову назву карти" << endl;
		cin >> nam;
		wallet_name = nam;
		break;
	case 3:
		cout << "Введіть новий номер карти" << endl;
		cin >> t;
		number = t;
		break;
	case 4:
		cout << "Введіть новий кредитний ліміт" << endl;
		cin >> limit;
		if (limit <= 0) { cout << "Невірно введені дані" << endl; credit_limit = 0; }
		else { credit_limit = limit; }
		break;
	default:
		cout << "Немає такого пункту меню!" << endl;
	}
}