#pragma once
#include"Storages.h"
/////////////////////////////////  ������� ����
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
	cout << "������ ���� ���������� - ";
	cin >> temp;
	if (temp <= 0) { cout << "������ ������ ���" << endl; temp = 0; }
	balance += temp;
}
void MoneyStorage::AddMoney(float money)
{
	system("cls");
	if (money <= 0) { cout << "������ ������ ���" << endl; money = 1; }
	balance += money;
}
void MoneyStorage::AddSpending()
{
	float money;
	int cat;
	Date dat;
	Time tm;
	system("cls");
	cout << "\t������ �������" << endl;
	cout << "������ ���� ������� - "; cin >> money;
	if (money <= 0 || money > balance)
	{
		cout << "��������� ��� ��� ����������� �����!" << endl;
		return;
	}
	while (true)
	{
		cout << "������ ����� ������� �������:" << endl;
		cout << "1 - �������; 2 - ��������; 3 - ��������;" << endl;
		cout << "4 - ��������� �������; 5 - �������; 6 - ���������;" << endl;
		cout << "7 - ����" << endl;
		cin >> cat;
		if (cat < 1 || cat > 7) { continue; }
		else { break; }
	}
	dat.Input();
	tm.Input();
	spendings.insert(Spending(money, cat, dat, tm));
}

//////////////////////////////////   ���� Card

Card::Card(long long num, float credit, string name) : MoneyStorage(num, credit) { card_name = name; }
Card::Card(multiset<Spending>& m, long long num, float t, float credit, string name) : MoneyStorage(m, num, credit, t) { card_name = name; }
void Card::Info()
{
	cout << "\t\t����� - " << card_name << endl;
	cout << "����� - " << number << endl;
	cout << "������ - " << balance << endl;
	cout << "��������� ��� - " << credit_limit << endl;
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
	cout << "\t���� ����������� �����" << endl;
	cout << "1) ������ �� ���" << endl;
	cout << "2) ������ ����� �����" << endl;
	cout << "3) ������ ����� �����" << endl;
	cout << "4) ������ ��������� ���" << endl;
	cin >> choise;
	switch (choise)
	{
	case 1:
		cout << "������ ����� ����� " << endl;
		cin >> t;
		number = t;
		cout << "������ ���� ����� �����" << endl;
		cin >> nam;
		card_name = nam;
		cout << "������ ����� ��������� ���" << endl;
		cin >> limit;
		if (limit <= 0) { cout << "������ ������ ���" << endl; credit_limit = 0; }
		else { credit_limit = limit; }
		break;
	case 2:
		cout << "������ ���� ����� �����" << endl;
		cin >> nam;
		card_name = nam;
		break;
	case 3:
		cout << "������ ����� ����� �����" << endl;
		cin >> t;
		number = t;
		break;
	case 4:
		cout << "������ ����� ��������� ���" << endl;
		cin >> limit;
		if (limit <= 0) { cout << "������ ������ ���" << endl; credit_limit = 0; }
		else { credit_limit = limit; }
		break;
	default:
		cout << "���� ������ ������ ����!" << endl;
	}
}

////////////////////////////////// ���� Wallet

Wallet::Wallet(long long num, float credit, string name) : MoneyStorage(num, credit) { wallet_name = name; }
Wallet::Wallet(multiset<Spending>& m, long long num, float t, float credit, string name) : MoneyStorage(m, num, credit, t) { wallet_name = name; }
void Wallet::Info()
{
	cout << "\t\t³��������� �������� - " << wallet_name << endl;
	cout << "����� - " << number << endl;
	cout << "������ - " << balance << endl;
	cout << "��������� ��� - " << credit_limit << endl;
	for (const auto& i : spendings) {
		i.Info();
	}
}
void Wallet::Edit()
{
	int choise, limit;
	long long t;
	string nam;
	cout << "\t���� ����������� �������" << endl;
	cout << "1) ������ �� ���" << endl;
	cout << "2) ������ ����� �������" << endl;
	cout << "3) ������ ����� �������" << endl;
	cout << "4) ������ ��������� ���" << endl;
	cin >> choise;
	switch (choise)
	{
	case 1:
		cout << "������ ����� ����� " << endl;
		cin >> t;
		number = t;
		cout << "������ ���� �����" << endl;
		cin >> nam;
		wallet_name = nam;
		cout << "������ ����� ��������� ���" << endl;
		cin >> limit;
		if (limit <= 0) { cout << "������ ������ ���" << endl; credit_limit = 0; }
		else { credit_limit = limit; }
		break;
	case 2:
		cout << "������ ���� ����� �����" << endl;
		cin >> nam;
		wallet_name = nam;
		break;
	case 3:
		cout << "������ ����� ����� �����" << endl;
		cin >> t;
		number = t;
		break;
	case 4:
		cout << "������ ����� ��������� ���" << endl;
		cin >> limit;
		if (limit <= 0) { cout << "������ ������ ���" << endl; credit_limit = 0; }
		else { credit_limit = limit; }
		break;
	default:
		cout << "���� ������ ������ ����!" << endl;
	}
}