#include "Finance_menegement.h"

int main()
{
	setlocale(LC_CTYPE, "ukr");
	MoneyStorage* stor_ptr1;  // указатели на базовый абстрактный класс "Хранилище денег"
	MoneyStorage* stor_ptr2;
	MoneyStorage* stor_ptr3;
	MoneyStorage* stor_ptr4;
	MoneyStorage* stor_ptr5;
	MoneyStorage* stor_ptr6;
	Date d1, d2, d3; 
	d1.Edit(6, 2, 2020); 
	d2.Edit(11, 2, 2020); 
	d3.Edit(3, 2, 2020);
	Time t1, t2, t3; t1.Edit(24, 45, 19); t2.Edit(44, 22, 11); t3.Edit(20, 40, 1);
	multiset<Spending> sp1; sp1.insert(Spending(100, 3, d1, t1)); sp1.insert(Spending(450, 2, d2, t2)); sp1.insert(Spending(200, 2, d3, t3));
	d1.Edit(7, 2, 2020); d2.Edit(9, 2, 2020); d3.Edit(3, 4, 2020);
	multiset<Spending> sp2; sp2.insert(Spending(125, 2, d1, t1)); sp2.insert(Spending(220, 6, d2, t2)); sp2.insert(Spending(1000, 2, d3, t3));
	stor_ptr1 = new Card(sp1, 1, 5000, 2000, "Oschadbank");
	stor_ptr2 = new Wallet(2, 1000, "Paypal");
	stor_ptr3 = new Card(sp2, 3, 3000, 0, "Mono");
	stor_ptr4 = new Wallet(4, 0, "ApplePay");
	stor_ptr5 = new Card(5, 2000, "UkrBisBank");
	stor_ptr6 = new Card(6, 0, "Pryvat");

	FinanceManagement system; // создаём систему управления финансами
	system.AddStorage(stor_ptr1); // добавляем в систему "храналища денег"
	system.AddStorage(stor_ptr2);
	system.AddStorage(stor_ptr3);
	system.AddStorage(stor_ptr4);
	system.AddStorage(stor_ptr5);
	system.AddStorage(stor_ptr6);
	system.Menu();
}
