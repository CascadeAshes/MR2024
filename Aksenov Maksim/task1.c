#include <stdio.h>
#include <math.h>


typedef long long int Money;  // копейки

const double INFLATION = 0.08;  
const int START_MONTH = 9;  
const int START_YEAR = 2024;  
const int YEARS = 30;  

struct Mortgage
{
    double rate;  // ставка по ипотеке
    Money payment;  // ежемесячный платёж по ипотеке
};


struct Human  // структура для Алисы и Боба
{
    Money start;
    Money flat;  // стоимость квартиры
    Money account;  // счёт
    Money salary;  // зарплата
    double bank_percent;  // годовая ставка вклада в банке
    Money wastes;  // траты на существование
    Money rent;  // стоимость аренды
    Money monthly_payment;  // ежемесяная плата
    Money yacht;
    struct Mortgage mortgage;

};                             


struct Human Alice;
struct Human Bob;


void Alice_init()                               // инициализация Алисы
{
    Alice.start = 1 * 1000 * 1000 * 100;
    Alice.flat = 15 * 1000 * 1000 * 100;
    Alice.account = 0;
    Alice.salary = 300 * 1000 * 100;
    Alice.bank_percent = 0.2;
    Alice.mortgage.rate = 0.17;
    Alice.wastes = 40 * 1000 * 100;
    Alice.mortgage.payment = (Alice.flat - Alice.start) * ((Alice.mortgage.rate / 12) + ((Alice.mortgage.rate / 12))/ (pow((1 + Alice.mortgage.rate / 12), YEARS * 12) - 1));
    Alice.monthly_payment = Alice.wastes + Alice.mortgage.payment; 
}


void Bob_init()                                 // инициализация Боба
{
    Bob.flat = 15 * 1000 * 1000 * 100;
    Bob.account = 1 * 1000 * 1000 * 100;
    Bob.salary = 300 * 1000 * 100;
    Bob.bank_percent = 0.2;
    Bob.wastes = 40 * 1000 * 100;
    Bob.rent = 50 * 1000 * 100;
    Bob.yacht = 100 * 1000 * 100;
    Bob.monthly_payment = Bob.wastes + Bob.rent;
}


void Alice_salary(const int year, const int month)  // начисление зарплаты Алисе
{
    if (month == 1) {
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
    if (month == 1) {
	    Alice.wastes += Alice.wastes * INFLATION;
	}
	Alice.account -= Alice.monthly_payment;

}  


void Bob_salary(const int year, const int month)  // начисление зарплаты Бобу
{
    int is_salary;
    if (month == 1) {
        Bob.salary += Bob.salary * INFLATION;
    }

    if (month == 6 || month == 7 || month == 8) {
        is_salary = 0;
	} else {
        is_salary = 1;
    }

    if (is_salary == 1) {
        Bob.account += Bob.salary;
    }

}


void Bob_deposite(const int year, const int month)  // проценты по вкладу Бобу
{
    Bob.account += Bob.account * (Bob.bank_percent / 12);
}


void Bob_expenses(const int year, const int month)  //  расходы Боба
{
    if (month == 1) {
	Bob.wastes += Bob.wastes * INFLATION;
        Bob.rent += Bob.rent * INFLATION; 
	}
	Bob.account -= Bob.monthly_payment;
}


void flat_inflation(const int year, const int month)  // удорожание квартиры от инфляции
{
    if (month == 1) {
        Alice.flat += Alice.flat * INFLATION;
    }
}


void print_alice()
{
    printf("Alice's capital: %lld kopecks\n", Alice.account + Alice.flat);
}


void print_bob()
{
    printf("Bob's capital: %lld kopecks", Bob.account);
}


void Bob_holiday(const int year, const int month)  // нюанс
{
    if(month == 1){
        Bob.yacht += Bob.yacht * INFLATION;
    }

    if (month == 6 || month == 7 || month == 8) {
	    Bob.account -= Bob.yacht;
	}
}


void simulation()
{
    int month = START_MONTH;
    int year = START_YEAR;

    while (year < (START_YEAR + YEARS) || month < 9) {
        Alice_salary(year, month);
        Alice_expenses(year, month);
        Alice_deposite(year, month);

        Bob_salary(year, month);
        Bob_expenses(year, month);
        Bob_holiday(year, month);
        Bob_deposite(year, month);
        
        flat_inflation(year, month);

        ++month;
        if(month == 13) {
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

    print_alice();
    print_bob();

    return 0;
}
