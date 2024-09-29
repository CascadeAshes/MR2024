#include <stdio.h>

typedef long long int Money;

const int START_YEAR = 2024;
const int START_MONTH = 9;
const int PERIOD = 30;  // расчетный период симуляции


struct Mortgage {
    Money sum;
    Money first_pay;
    Money monthly_payments;
    double rate;
};


struct Person {
    Money salary;
    Money account;
    Money life_cost;
    Money flat_price;
    Money monthly_rent;
    struct Mortgage mortgage;
    double deposit_rate;
    double inflation_index;
};


struct Person alice;
struct Person bob;


void alice_init()
{
    alice.salary = 200 * 1000;
    alice.account = 1000 * 1000;
    alice.life_cost = 50 * 1000;
    alice.deposit_rate = 0.2;
    alice.inflation_index = 0.08;
    alice.mortgage.sum = 15 * 1000 * 1000;
    alice.mortgage.first_pay = 1000 * 1000;
    alice.mortgage.rate = 0.17;
    alice.mortgage.monthly_payments = 170*1000; // source: url...
    alice.account -= alice.mortgage.first_pay;
    alice.flat_price = alice.mortgage.sum;
}


void alice_salary(const int month)
{
    if(month == 1){
        alice.salary*=(1. + alice.inflation_index);
    }
    alice.account += alice.salary;
}


void alice_mortgage()
{
    alice.account -= alice.mortgage.monthly_payments;
}


void alice_life_cost(const int month)
{
    if (month == 1) {
        alice.life_cost *= (1. + alice.inflation_index);
    } 

    alice.account -= alice.life_cost;
}


void alice_flat_price(const int month)
{
    if (month == 1) {
        alice.flat_price *= (1. + alice.inflation_index);
    }
}


void alice_deposit()
{
    alice.account += alice.account * (alice.deposit_rate / 12);
}


void alice_print()
{
    printf("Alice summary capital: %lld \n", alice.account + alice.flat_price);
}


void bob_init()
{
    bob.account = 1 * 1000 * 1000;
    bob.salary = 200 * 1000;
    bob.life_cost = 50 * 1000;
    bob.deposit_rate = 0.2;
    bob.inflation_index = 0.08;
    bob.monthly_rent = 35*1000;
}


void bob_salary (const int month)
{
    if (month == 1){
        bob.salary *= (1. + bob.inflation_index);
    }
    bob.account += bob.salary;
}


void bob_rent(const int month)
{
    if (month == 1) {
        bob.monthly_rent *= (1. + bob.inflation_index);
    } 
    
    bob.account -= bob.monthly_rent;
}


void bob_life_cost(const int month)
{
    if (month == 1) {
        bob.life_cost *= (1. + bob.inflation_index);
    }
    
    bob.account -= bob.life_cost;
}


void bob_deposit()
{
    bob.account += bob.account * (bob.deposit_rate / 12);
}


void bob_print()
{
    printf("Bob summary capital: %lld \n", bob.account);
}


void conclusion()
{
    printf("----------------------------------\n");
    if ((alice.account + alice.flat_price) > bob.account) {
        printf("Alice is winner\n");
    } else {
        if ((alice.account + alice.flat_price) == bob.account) {
            printf("Alice and Bob are equal\n");
        } else {
            printf("Bob is winner\n");
        }
    }

}

void simulation ()
{
    int month = START_MONTH;
    int year = START_YEAR;

    while(!((year == START_YEAR + PERIOD) && (month == START_MONTH + 1))) {
        alice_salary(month);
        alice_mortgage(month);
        alice_life_cost(month);
        alice_flat_price(month);
        alice_deposit();
        
        bob_salary(month);
        bob_rent(month);
        bob_life_cost(month);
        bob_deposit();

        month++;
        if(month == 13){
            month = 1;
            year++;
        }
    }
}


void print_output()
{
    printf("Results for %d.%d are:\n",START_MONTH, START_YEAR + PERIOD);
    printf("----------------------------------\n");
    alice_print();
    bob_print();
    conclusion();
}


int main() {
    alice_init();
    bob_init();
    simulation();
    print_output();
    return 0;
}
