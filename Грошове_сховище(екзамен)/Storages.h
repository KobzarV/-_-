#pragma once
#include<set>
#include<iostream>
#include"Spending.h"

using namespace std;

class MoneyStorage
{
protected:
	long long number; // номер карти
	float balance;  // баланс
	multiset<Spending> spendings;  // витрати
	float credit_limit; // кредитна карта або дебитова
public:
	// конструктори
	MoneyStorage();
	MoneyStorage(long long num, float credit);
	MoneyStorage(multiset<Spending>& spends, long long num, float balans, float limit);
	virtual void Info() = 0;  // вив≥д ≥нформац≥њ про сховище
	virtual void Edit() = 0; // редагувати ≥нформац≥ю про сховище
	void AddMoney(); // поповненн€ карти/гаманц€
	void AddMoney(float money); // поповненн€ карти/гаманц€
	void AddSpending();  // додати витрату
	long long GetNumber() const { return number; }  // вивести номер сховища
	multiset<Spending> GetSpendings() const { return spendings; }  // отримати витрати ц≥Їњ карти
};

class Card : public MoneyStorage
{
	string card_name;
public:
	Card() : MoneyStorage() {}
	Card(long long num, float credit, string name);
	Card(multiset<Spending>& m, long long num, float t, float credit, string name);
	void Info();
	void Edit(); 
};

class Wallet : public MoneyStorage
{
	string wallet_name;
public:
	Wallet() : MoneyStorage() {}
	Wallet(long long num, float credit, string name);
	Wallet(std::multiset<Spending>& m, long long num, float t, float credit, string name);
	void Info();
	void Edit();
};