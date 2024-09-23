#include <stdio.h>
#include <math.h>

const int YEAR_START = 2024;
const int MONTH_START = 9;
const int DURATION = 30;
const int TAX_DEDUCTION = 13;

const double INFLATION = 8;  // проценты

typedef long long int Money;


struct Person {
    Money bank_account;
    Money salary;
    Money monthly_expenses;
    Money big_teeth_expenses;
    Money half_year_teeth_expenses;
    Money rent;
} bob, alice;


struct Mortgage {
    Money first_installment;
    Money apartment_cost;
    Money monthly_payment;
    double interest_rate, total_rate, monthly_rate;
} mortgage;


struct Deposit {
    int duration;
    double rate;
    Money capital, monthly_payment;
} bob_deposit, alice_deposit;


void mortgage_payment()
{
    mortgage.first_installment = 1*1000*1000;  // рубли
    mortgage.apartment_cost = 15*1000*1000;
    mortgage.interest_rate = 18;

    mortgage.monthly_rate = mortgage.interest_rate / 12 / 100;
    mortgage.total_rate = pow(1 + mortgage.monthly_rate, DURATION * 12);
    mortgage.monthly_payment = (mortgage.apartment_cost - mortgage.first_installment) * mortgage.monthly_rate * mortgage.total_rate / (mortgage.total_rate - 1);

}


void bob_dep()
{   
    bob_deposit.rate = 17.0;
    bob_deposit.capital += bob.bank_account;
    bob.bank_account = 0;  // весь остаток положил на вклад
    bob_deposit.monthly_payment = bob_deposit.capital * bob_deposit.rate / 100. / 12.;
    bob.bank_account += bob_deposit.monthly_payment;
}


void alice_dep()
{   
    alice_deposit.rate = 17.0;
    alice_deposit.capital += alice.bank_account;
    alice.bank_account = 0;  // весь остаток положил на вклад
    alice_deposit.monthly_payment = alice_deposit.capital * alice_deposit.rate / 100. / 12.;
    alice.bank_account += alice_deposit.monthly_payment;
}


void bob_init()
{
    bob.bank_account = 1*1000*1000;
    bob.salary = 300 * 1000;  // рубли
    bob.monthly_expenses = 40 * 1000;
    bob.big_teeth_expenses = 70 * 1000;
    bob.half_year_teeth_expenses = 25 * 1000;
    bob.rent = 30 * 1000;
}


void alice_init()
{
    alice.bank_account = 0;
    alice.salary = 300 * 1000;  // рубли
    alice.monthly_expenses = 40 * 1000;
    alice.rent = 0;
}


void bob_salary(const int month)
{
    bob.bank_account += bob.salary;

    if (month == 12) {
        bob.salary *= 1 + INFLATION / 100;  // индексация
    }
}


void alice_salary(const int month)
{
    alice.bank_account += alice.salary;

    if (month == 12) {
        alice.salary *= 1 + INFLATION / 100;  // индексация
    }
}


void bob_expenses(const int month, const int year)
{
    bob.bank_account -= bob.monthly_expenses;
    bob.bank_account -= bob.rent;

    if (year == 2028 && (month == 4 || month == 6)) {
        bob.bank_account -=  bob.big_teeth_expenses;
    }

    if (year > 2028 && (month == 9 || month == 3)) {
        bob.bank_account -= bob.half_year_teeth_expenses;
    }

    if (month == 12) {
        bob.monthly_expenses *= 1 + INFLATION / 100;
        bob.rent *= 1 + INFLATION / 100;
    }
}


void alice_expenses(const int month)
{
    alice.bank_account -= alice.monthly_expenses;
    alice.bank_account -= mortgage.monthly_payment;
    if (month == 12) {
        alice.monthly_expenses *= 1 + INFLATION / 100;
    }
}


void bob_print()
{
    printf("Капитал Боба: %lld\n", bob.bank_account + bob_deposit.capital);
}


void alice_print()
{
    printf("Капитал Алисы: %lld", alice.bank_account + mortgage.apartment_cost + alice_deposit.capital);
}


void simulation(int year, int month)
{
    while(year <= YEAR_START + DURATION)
    {
        while(month <= 12 && year != YEAR_START + DURATION && month != MONTH_START)
        {
            bob_salary(month);
            bob_expenses(month);
            bob_dep();

            alice_salary(month);
            alice_expenses(month);
            alice_dep();

            if (month == 12) {
                mortgage.apartment_cost *= 1 + INFLATION / 100;
            }

            month++;
        }
        month = 1;
        year++;
    }
}


int main()
{
    bob_init();
    alice_init();

    mortgage_payment();

    simulation(YEAR_START, MONTH_START);

    bob_print();
    alice_print();
}