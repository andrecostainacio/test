#include "bank.h"

Bank::Bank()
{
    m_bankBalance = 10000;
}

int clientNumber = 1;

void Bank::connectDB()
{
    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("Clients");
    db.setUserName("root");
    db.setPassword("tavinfor");
    db.setPort(3306);

    if(!db.open())
    {
        qDebug() << db.lastError();
    }
    else
        fetchData();
        mainConsole();
}

QList<Client> Bank::fetchData()
{
    QSqlQuery query("SELECT * FROM clientInfo");
//    QListIterator<Client> i(m_clientList);

    m_clientList.clear();

    while (query.next())
    {
        Account account(query.value(0).toInt(), query.value(1).toInt());
        Client client(account, query.value(2).toString(), query.value(3).toInt());

        m_clientList.append(client);
    }

//    QFile m_file("/home/andreinacio/Documents");

//    if(!m_file.open(QFile::WriteOnly | QFile::Text))
//    {
//        qDebug() << "Couldnt open file!";

//    }

//    while(i.hasNext())
//    {
//        Client tempClient = i.next();

//        qDebug() << endl << "Name: " << tempClient.getName();
//        qDebug() << "BI: " << tempClient.getBI();
//        qDebug() << "Balance: " << tempClient.getAccount().getBalance() << "€";
//        qDebug() << "Account Number: " << tempClient.getAccount().getNumber();

//        QTextStream out(&m_file);
//        out >> "Name: " << tempClient.getName();

//    }

    return m_clientList;
}

void Bank::updateData(Client &client, int balance)
{
    //QSqlQuery query("SELECT * FROM clientInfo");

    query->exec("SELECT * FROM clientInfo");

    query->prepare("UPDATE clientInfo SET balance=:balance WHERE idclientInfo=:id");
    query->bindValue(":balance", balance);
    query->bindValue(":id", client.getAccount().getNumber());
    query->exec();

}

void Bank::deleteData(QList<Client> &m_clientList)
{
    QProcess::execute("clear");
    QListIterator<Client> i(m_clientList);

    if(m_clientList.empty())
    {
        qDebug() << endl << "No clients available!";
        bankConsole();
    }
    else
    {
    while(i.hasNext())
        {
            Client tempClient = i.next();
            qDebug() << endl << "Name: " << tempClient.getName()
                     << "|| Account Number: " << tempClient.getAccount().getNumber();
        }
    }

    qDebug() << endl << "Enter the Account Number of the CLient that you want to delete:";

    QTextStream s(stdin);
    int accNumber = s.readLine().toInt();

    i.toFront();

    while(i.hasNext())
    {
        Client client = i.next();

        if(client.getAccount().getNumber() == accNumber)
        {
            query->exec("SELECT * FROM clientInfo");
            query->prepare("DELETE FROM clientInfo WHERE idclientInfo=:id");
            query->bindValue(":id", client.getAccount().getNumber());
            query->exec();
            fetchData();
            bankConsole();
        }
        else{}
    }

    qDebug() << endl << "There is no Account with that number! Please try again.";

    QTextStream s2(stdin);
    accNumber = s2.readLine().toInt();

    deleteData(m_clientList);
}

//BANK
void Bank::addClient()
{
    int last = 0;

    qDebug() << endl << "-------------------------------";
    qDebug() << "- Please enter the new Client -";
    qDebug() << "-------------------------------";
    qDebug() << "Client Name:";
    QTextStream s(stdin);
    QString name = s.readLine();

    qDebug() << endl << "Client BI:";
    QTextStream s2(stdin);
    int bi = s2.readLine().toInt();

    qDebug() << endl << "Client Balance:";
    QTextStream s3(stdin);
    int balance = s3.readLine().toInt();

    query->exec("SELECT idclientInfo FROM clientInfo");

    QListIterator<Client> i(m_clientList);
    while(i.hasNext())
    {
        Client first = i.next();
        if(i.hasNext())
        {
            Client next = i.peekNext();
            if(first.getAccount().getNumber() + 1 != next.getAccount().getNumber())
        {
            last = first.getAccount().getNumber() + 1;
            break;
        }
        else{}
        }
        last = first.getAccount().getNumber() + 1;
    }

    query->prepare("INSERT INTO clientInfo (idclientInfo, balance, name, bi) "
               "VALUES (:idclientInfo, :balance, :name, :bi)");

    query->bindValue(":idclientInfo", last);
    query->bindValue(":balance", balance);
    query->bindValue(":name", name);
    query->bindValue(":bi", bi);
    query->exec();

    fetchData();
}

void Bank::showClients(QList<Client> &m_clientList)
{
    QListIterator<Client> i(m_clientList);

    if(m_clientList.empty())
    {
        qDebug() << endl << "No clients available!";
        bankConsole();
    }
    else
    {
    while(i.hasNext())
        {
            Client tempClient = i.next();

            qDebug() << endl << "Name: " << tempClient.getName();
            qDebug() << "BI: " << tempClient.getBI();
            qDebug() << "Balance: " << tempClient.getAccount().getBalance() << "€";
            qDebug() << "Account Number: " << tempClient.getAccount().getNumber();
        }
    }
}

void Bank::showBankBalance()
{
    QListIterator<Client> i(m_clientList);

    m_bankBalance = 0;

    while(i.hasNext())
    {
        Client tempClient = i.next();
        m_bankBalance = m_bankBalance + tempClient.getAccount().getBalance();
    }

    qDebug() << "------------------------------";
    qDebug() << "-        Bank Balance:       -";
    qDebug() << "           "<< m_bankBalance <<"€      ";
    qDebug() << "------------------------------";
}

//CLIENT
void Bank::showClientInfo(Client &client)
{
    qDebug() << endl << "Name: " << client.getName();
    qDebug() << "BI: " << client.getBI();
    qDebug() << "Balance: " << client.getAccount().getBalance() << "€";
    qDebug() << "Account Number: " << client.getAccount().getNumber();
}

void Bank::clientWithdraw(Client &client)
{
    qDebug() << "How much do you want to withdraw?";

    QTextStream s(stdin);
    qlonglong in = s.readLine().toInt();

    client.getAccount().withdraw(in);
    updateData(client, client.getAccount().getBalance());
    clientConsole(client);

}

void Bank::clientDeposit(Client &client)
{
    qDebug() << "How much do you want to deposit?";

    QTextStream s(stdin);
    qlonglong in = s.readLine().toInt();

    client.getAccount().deposit(in);
    updateData(client, client.getAccount().getBalance());
    clientConsole(client);
}

void Bank::clientTransfer(Client &client, QList<Client> &m_clientList)
{
    qDebug() << "How much money do you want to transfer?";
    QTextStream s(stdin);
    qlonglong in = s.readLine().toInt();

    qDebug() << endl << "Enter the name of the other client you want to transfer the money to:";
    QTextStream s2(stdin);
    QString name = s2.readLine();

    for(int i = 0; i != m_clientList.size(); i++)
    {
        if(m_clientList[i].getName() == name && client.getAccount().getBalance() >= in)
        {
            client.getAccount().withdraw(in);
            updateData(client, client.getAccount().getBalance());

            m_clientList[i].getAccount().deposit(in);
            updateData(m_clientList[i], m_clientList[i].getAccount().getBalance());

            qDebug() << endl << "Money transfered!";
            clientConsole(client);
        }

        else if(client.getAccount().getBalance() < in)
        {
            qDebug() << endl << "You only have" << client.getAccount().getBalance() << ". Please try again." << endl;
            clientTransfer(client, m_clientList);
        }
    }
    qDebug() << endl << "There is no client with that name. Please try again." << endl;
    clientTransfer(client, m_clientList);
}

//CONSOLES
void Bank::bankConsole()
{
    qDebug() << endl << "----------BankConsole---------";
    qDebug() << "------------------------------";
    qDebug() << "-      1. Add a client       -";
    qDebug() << "-      2. Delete client      -";
    qDebug() << "-    3. Show bank balance    -";
    qDebug() << "-      4. Show clients       -";
    qDebug() << "------------------------------";

    QTextStream s(stdin);
    int in = s.readLine().toInt();

    switch (in) {
    case 1:
        QProcess::execute("clear");
        addClient();
        bankConsole();
        break;
    case 2:
        QProcess::execute("clear");
        deleteData(m_clientList);
        bankConsole();
        break;
    case 3:
        QProcess::execute("clear");
        showBankBalance();
        bankConsole();
        break;
    case 4:
        QProcess::execute("clear");
        showClients(m_clientList);
        bankConsole();
        break;   
    default:
        QProcess::execute("clear");
        mainConsole();
    }
}

void Bank::clientLogin()
{
    if(m_clientList.empty())
    {
        qDebug() << endl << "No clients available!";
        mainConsole();
    }
    else{
    qDebug() << endl << "----------ClientLogin---------";
    qDebug() << "------------------------------";
    qDebug() << "-       Client Login!        -";
    qDebug() << "-     Please enter your      -";
    qDebug() << "-        client name:        -";
    qDebug() << "------------------------------";

    QTextStream s(stdin);
    QString in = s.readLine();

    for(int i = 0; i < m_clientList.size(); i++)
    {
        if(m_clientList[i].getName() == in)
        {
            clientConsole(m_clientList[i]);
        }
        else
        {
        continue;
        }
    }
    qDebug() << endl <<"No client with that name! Please try again" << endl;
    clientLogin();
    }
}

void Bank::clientConsole(Client &client)
{
    qDebug() << endl << "---------ClientConsole--------";
    qDebug() << "------------------------------";
    qDebug() << "-        1. Withdraw         -";
    qDebug() << "-        2. Deposit          -";
    qDebug() << "-        3. Transfer         -";
    qDebug() << "-   4. Show account info     -";
    qDebug() << "------------------------------";

    QTextStream s(stdin);
    int in = s.readLine().toInt();

    switch (in) {
    case 1:
        QProcess::execute("clear");
        clientWithdraw(client);
        clientConsole(client);
        break;
    case 2:
        QProcess::execute("clear");
        clientDeposit(client);
        clientConsole(client);
        break;
    case 3:
        QProcess::execute("clear");
        clientTransfer(client, m_clientList);
        break;
    case 4:
        QProcess::execute("clear");
        showClientInfo(client);
        clientConsole(client);
        break;
    default:
        QProcess::execute("clear");
        mainConsole();
    }
}

void Bank::mainConsole()
{
    qDebug() << endl << "----------MainConsole---------";
    qDebug() << "------------------------------";
    qDebug() << "-      1. Bank area          -";
    qDebug() << "-     2. Client area         -";
    qDebug() << "-        3. Exit             -";
    qDebug() << "------------------------------";

    QTextStream s(stdin);
    int in = s.readLine().toInt();

    switch (in) {
    case 1:
        QProcess::execute("clear");
        bankConsole();
        break;
    case 2:
        QProcess::execute("clear");
        clientLogin();
        break;
    case 3:
        QCoreApplication::instance()->quit();
        QCoreApplication::instance()->exit();
        break;
    default:
        QProcess::execute("clear");
        mainConsole();
    }
}




