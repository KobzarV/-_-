#pragma once
#include<set>
#include<iostream>
#include"Spending.h"

using namespace std;

class MoneyStorage
{
protected:
	long long number; // ����� �����
	float balance;  // ������
	multiset<Spending> spendings;  // �������
	float credit_limit; // �������� ����� ��� ��������
public:
	// ������������
	MoneyStorage();
	MoneyStorage(long long num, float credit);
	MoneyStorage(multiset<Spending>& spends, long long num, float balans, float limit);
	virtual void Info() = 0;  // ���� ���������� ��� �������
	virtual void Edit() = 0; // ���������� ���������� ��� �������
	void AddMoney(); // ���������� �����/�������
	void AddMoney(float money); // ���������� �����/�������
	void AddSpending();  // ������ �������
	long long GetNumber() const { return number; }  // ������� ����� �������
	multiset<Spending> GetSpendings() const { return spendings; }  // �������� ������� ���� �����
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