#include "client.h"

Client::Client()
{
}

Client::Client(Account &account, QString name, int bi)
{
    this->m_name = name;
    this->m_bi = bi;
    this->m_account = account;
}

QString Client::getName()
{
    return m_name;
}

int Client::getBI()
{
    return m_bi;
}

Account& Client::getAccount()
{
    return m_account;
}

void Client::setName(QString name)
{
    m_name = name;
}

void Client::setBI(int bi)
{
    m_bi = bi;
}

void Client::setAccount(Account account)
{
    m_account = account;
}




