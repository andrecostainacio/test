#ifndef BANK_H
#define BANK_H
#include <client.h>
#include <QList>
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class Bank
{
private:
    qlonglong m_bankBalance;
    QList<Client> m_clientList;
    QList<Account> m_accountList;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QSqlQuery *query = new QSqlQuery(db);

public:
    Bank();

    //SQL
    void connectDB();
    QList<Client> fetchData();
    void updateData(Client &, int);
    void deleteData(QList<Client> &);

    //BANK
    void addClient();
    void showClients(QList<Client> &);
    void showBankBalance();

    //CLIENT
    void showClientInfo(Client &client);
    void clientWithdraw(Client &client);
    void clientDeposit(Client &client);
    void clientTransfer(Client &, QList<Client> &);

    //CONSOLES
    void bankConsole();
    void clientLogin();
    void clientConsole(Client &client);
    void mainConsole();



};

#endif // BANK_H
