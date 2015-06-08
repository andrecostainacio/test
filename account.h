#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QtGlobal>

class Account
{
private:
    int m_number;
    qlonglong m_balance;
    //qlonglong m_bankbalance;

public:
    Account();
    Account(int number, qlonglong balance/*, qlonglong bankbalance*/);

    int getNumber();
    qlonglong getBalance();
    //qlonglong getBankBalance();

    void setNumber(int);
    void setBalance(qlonglong);
    //void setBankBalance(qlonglong);

    void withdraw(qlonglong);
    void deposit(qlonglong);
};


#endif // ACCOUNT_H
