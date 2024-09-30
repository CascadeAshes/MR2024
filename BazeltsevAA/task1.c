#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int Money;

const int START_YEAR = 2024;
const int START_MONTH = 9;
const int PERIOD = 30;  // период симуляции

typedef struct Person  {
    long long int account; //свободные деньги
    Money capital; //капитал
    Money salary; //зарплата
    Money monthly_payment; //ежемесячный платёж
    Money necessary_expenses; //необходимые траты
    Money contribution; //вклад
    Money cost_house; //стоимость дома
    double rate_contribution; //ставка по вкладу
} Person;


Person Alice;
Person Bob;


void Bob_init()
{
    Bob.capital = 0;
    Bob.account = 0;
    Bob.salary = 300 * 1000;
    Bob.monthly_payment = 50 * 1000;
    Bob.necessary_expenses = 50 * 1000;
    Bob.contribution = 1500 * 1000;
    Bob.rate_contribution = 1.014; // вклад под 17% годовых
}


void Alice_init()
{
    Alice.capital = 0;
    Alice.account = 0;
    Alice.salary = 300 * 1000;
    Alice.monthly_payment = 192466; //на 30 лет через калькулятор ипотеки от яндекса под 17%
    Alice.necessary_expenses = 50 * 1000;
    Alice.contribution = 0;
    Alice.cost_house = 15 * 1000 * 1000;
    Alice.rate_contribution = 1.014; // вклад под 17% годовых
}


 double search_inflation() // данные взяты с https://calcus.ru/inflyaciya с 2010-2023 год
{ 
    int probability = (rand() % 100);
    double inflation;

    if (probability > 90) {
        inflation = (1001 + rand() % 2);
    }
    if (probability <= 90 && probability > 60) {
        inflation=(1004 + rand() % 2);
    }
    if (probability <= 60 && probability > 10) {
        inflation = (1007 + rand() % 2);
    }
    if (probability <= 10) {
        inflation = (1010 + rand() % 4);
    }
    return((double) inflation / 1000.0);
}


double indexation()
{
    return((double) (100 + rand() % 9) / 100.0);
}


void Bob_salary(const int month)
{
    if (month == 1) {
        Bob.salary *= indexation();
    }
    Bob.account = Bob.salary;
}


void Alice_salary(const int month)
{
    if (month == 1) {
        Alice.salary *= indexation();
    }

    Alice.account = Alice.salary;

    if (month % 3 == 0) {
        Alice.account += 4*1000;
    }
    if (month == 12) {
        Alice.account += Alice.salary;
    }
}


void Bob_expenses(const double inflation)
{
    Bob.necessary_expenses *= inflation;
    Bob.account -= Bob.necessary_expenses;
    Bob.monthly_payment *= inflation;
    Bob.account -= Bob.monthly_payment;
}


void Alice_expenses(const double inflation)
{
    Alice.necessary_expenses *= inflation;
    Alice.account -= Alice.necessary_expenses;
    Alice.account -= Alice.monthly_payment;
}


void Bob_contribution()
{
    Bob.contribution = (Bob.contribution + Bob.account) * Bob.rate_contribution;
}


void Alice_contribution()
{
    Alice.contribution = (Alice.contribution + Alice.account) * Alice.rate_contribution;
}


void Alice_capital(const double inflation)
{
    Alice.cost_house *= inflation;
    Alice.capital = Alice.contribution + Alice.cost_house;
}


void Bob_capital(const double inflation)
{
    Bob.capital = Bob.contribution;
}


void simulation()
{
    int month = START_MONTH, year = START_YEAR;

    while (year < START_YEAR + PERIOD)  {

        Money inflation = search_inflation();

        Alice_salary(month);
        Alice_expenses(inflation);
        Alice_contribution();
        Alice_capital(inflation);

        Bob_salary(month);
        Bob_expenses(inflation);
        Bob_contribution();
        Bob_capital(inflation); 

        month++;
        if (month > 12)  {
            year++;
            month = 1;
        }
    }
}


void print()
{
    printf("%lld\n", Alice.capital);
    printf("%lld\n", Bob.capital);

    if (Alice.capital > Bob.capital)  {
        printf("Alice win!\n");
    }
    else  {
        printf("Bob win!\n");
    }
}


int main()
{
    Bob_init();
    Alice_init();

    simulation();

    print();
}
