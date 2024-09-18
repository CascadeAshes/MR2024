#include <stdio.h>
#include <math.h>
#include <locale.h>

#define YEARS 30
#define MONTHS_IN_YEAR 12

typedef struct {
    long long int capital;           // �������
    long long int salary;            // ��������
    long long int monthly_expenses;  // �������� ������� �� ���, ������������ � �.�.
    long long int rent;              // ������
    float deposit_rate;              // ������� �� �������
    bool has_house;                  // ����, ���� ����� ��������
} Person;


typedef struct {
    float inflation_rate;            // ��������
    float indexation_rate;           // ����������
    long long int house_cost;        // ��������� ��������
    float mortgage_rate;             // ��������� ������
} Money;


Person Alice;
Person Bob;

long long int apply_interest(long long int amount, long long int rate)
{
    return amount * (1 + rate);
}


void simulate_months(Person* person, Money* money, int month)
{
    person->capital -= person->monthly_expenses;
    person->capital += person->salary;

    if (!person->has_house)
        person->capital -= person->rent;
    else
        person->capital -= apply_interest(money->house_cost, money->mortgage_rate / 12);
}


void simulate_years(Person* person, Money* money)
{
    for (int year = 1; year <= YEARS; year++)
        for (int month = 0; month < MONTHS_IN_YEAR; month++)
            simulate_months(person, money, month);

    person->monthly_expenses = apply_interest(person->monthly_expenses, money->inflation_rate);
    person->rent = apply_interest(person->rent, money->inflation_rate);
    money->house_cost = apply_interest(money->house_cost, money->inflation_rate);

    person->salary = apply_interest(person->salary, money->indexation_rate);
    person->capital = apply_interest(person->capital, person->deposit_rate);
}


void compare_strategies(Person* alice, Money* m_alice, Person* bob, Money* m_bob)
{
    double alice_final_capital = alice->capital + m_alice->house_cost + YEARS * m_alice->house_cost * m_alice->mortgage_rate * YEARS;

    double bob_final_capital = bob->capital;
    if (bob->has_house)
        bob_final_capital += m_bob->house_cost;

    printf("����� %d ���:\n", YEARS);
    printf("�������� ������� ����: %.2f\n", alice_final_capital);
    printf("�������� ������� ����: %.2f\n", bob_final_capital);

    if (alice_final_capital > bob_final_capital)
        printf("��������� ���� ����� ����������.\n");
    else if (alice_final_capital < bob_final_capital)
        printf("��������� ���� ����� ����������.\n");
    else
        printf("��������� �����������.\n");
}


int main() {
    setlocale(LC_ALL, "Rus");

    Money m_alice = {
    0.1,                             // ��������
    0.1,                             // ����������
    13 * 1000000,                    // ��������� ��������
    0.16                             // ��������� ������
    };

    Money m_bob = {
    0.1,                             // ��������
    0.1,                             // ����������
    13 * 1000000,                    // ��������� ��������
    0                                // ��������� ������
    };

    // ������������� ��������� ������ ��� ����� (������� � �������)
    Alice = {
    1200000,                         // �������
    200 * 1000,                      // ��������
    20 * 1000,                       // �������� �������
    0,                               // ������
    0.2,                             // ������� �� �������
    true                             // ����, ���� ����� ��������
    };

    // ������������� ��������� ������ ��� ���� (������� ����� � ����� �� �������)
    Bob = {
    1000000,                         // �������
    200 * 1000,                      // ��������
    20 * 1000,                       // �������� �������
    0,                               // ������
    0.2,                             // ������� �� �������
    false                            // ����, ���� ����� ��������
    };

    simulate_years(&Alice, &m_alice);
    simulate_years(&Bob, &m_bob);

    compare_strategies(&Alice, &m_alice, &Bob, &m_bob);

    return 0;
}