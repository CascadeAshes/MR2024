#include <stdio.h>
#include <math.h>


typedef long long int Money;  // увеличиваем диапазон счёта, который будем вести в копейках

const double INFLATION = 0.08;  // инфляция в год
const int START_MONTH = 9;  // начальный месяц
const int START_YEAR = 2024;  // начальный год
const int YEARS = 30;  // количество лет


struct Human  // структура для Алисы и Боба
{
    Money target;  // стоимость квартиры
    Money account;  // счёт
    Money salary;  // зарплата
    double bank_percent;  // годовая ставка вклада в банке
    double mortgage_rate;  // ставка по ипотеке
    Money wastes;  // траты на существование
    Money mortgage_payment;  // ежемесячный платёж по ипотеке
    Money rent;  // стоимость аренды
    Money monthly_payment;  // ежемесяная плата
};                             


struct Human Alice;
struct Human Bob;


void Alice_init()                               // инициализация Алисы
{
    Alice.target = 15 * 1000 * 1000 * 100;
    Alice.account = 1 * 1000 * 1000 * 100;
    Alice.salary = 300 * 1000 * 100;
    Alice.bank_percent = 0.2;
    Alice.mortgage_rate = 0.17;
    Alice.wastes = 40 * 1000 * 100;
    Alice.mortgage_payment = (Alice.target - Alice.account) * ((Alice.mortgage_rate / 12) + ((Alice.mortgage_rate / 12))/ (pow((1 + Alice.mortgage_rate / 12), YEARS * 12) - 1));
    Alice.monthly_payment = Alice.wastes + Alice.mortgage_payment; 
}


void Bob_init()                                 // инициализация Боба
{
    Bob.target = 15 * 1000 * 1000 * 100;
    Bob.account = 1 * 1000 * 1000 * 100;
    Bob.salary = 300 * 1000 * 100;
    Bob.bank_percent = 0.2;
    Bob.wastes = 40 * 1000 * 100;
    Bob.rent = 50 * 1000 * 100;
    Bob.monthly_payment = Bob.wastes + Bob.rent;
}


void Alice_income(const int year, const int month)  // начисление зарплаты Алисе
{
    if (month == 1) 
    {
        Alice.salary += Alice.salary * INFLATION;
    }
    Alice.account += Alice.salary;
}


void Alice_deposite(const int year, const int month)  // проценты по вкладу Алисе
{
    Alice.account += Alice.account * (Alice.bank_percent / 12);

}


void Alice_expenses(const int year, const int month)  //  расходы Алисы
{
    if (month == 1) 
    {
		Alice.wastes += Alice.wastes * INFLATION;
	}
	Alice.account -= Alice.monthly_payment;

}  


void Bob_income(const int year, const int month)  // начисление зарплаты Бобу
{
    if (month == 1) 
    {
        Bob.salary += Bob.salary * INFLATION;
    }
    Bob.account += Bob.salary;
}


void Bob_deposite(const int year, const int month)  // проценты по вкладу Бобу
{
    Bob.account += Bob.account * (Bob.bank_percent / 12);
}


void Bob_expenses(const int year, const int month)  //  расходы Боба
{
    if (month == 1) 
    {
		Bob.wastes += Bob.wastes * INFLATION;
        Bob.rent += Bob.rent * INFLATION; 
	}
	Bob.account -= Bob.monthly_payment;
}


void price_inflation(const int year, const int month)  // удорожание квартиры от инфляции
{
    if (month == 1) 
    {
        Alice.target += Alice.target * INFLATION;
    }
}

void simulation()
{
    int month = START_MONTH;
    int year = START_YEAR;

    while (year < (START_YEAR + YEARS) || month < 8)
    {
        Alice_income(year, month);
        Alice_expenses(year, month);
        Alice_deposite(year, month);

        Bob_income(year, month);
        Bob_expenses(year, month);
        Bob_deposite(year, month);
        
        price_inflation(year, month);

        ++month;
        if(month == 13)
        {
            ++year;
            month = 1;
        }
    }
}


int main()
{
    Alice_init();
    Bob_init();

    simulation();
    
    printf("Alice's capital; %lld kopecks", Alice.account + Alice.target);
    printf("\n");
    printf("Bob's capital %lld kopecks", Bob.account);

    return 0;
}
