#include "account.h"

Account::Account()
{
}

Account::Account(int number, qlonglong balance)
{
    this->m_number = number;
    this->m_balance = balance;
}

int Account::getNumber()
{
    return m_number;
}

qlonglong Account::getBalance()
{
    return m_balance;
}

void Account::setNumber(int number)
{
    m_number = number;
}

void Account::setBalance(qlonglong balance)
{
    m_balance = balance;
}

void Account::withdraw(qlonglong valor)
{
    m_balance -= valor;
}

void Account::deposit(qlonglong valor)
{
    m_balance += valor;
}
