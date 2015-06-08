#ifndef CLIENT_H
#define CLIENT_H
#include <account.h>
#include <QString>

class Client
{
private:
    QString m_name;
    int m_bi;
    Account m_account;

public:
    Client();
    Client(Account&, QString, int);

    QString getName();
    int getBI();
    Account &getAccount();

    void setName(QString);
    void setBI(int);
    void setAccount(Account);

};

#endif // CLIENT_H
