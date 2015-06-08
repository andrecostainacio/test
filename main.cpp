#include <QCoreApplication>
#include <bank.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Bank newBank;

    newBank.connectDB();

    return a.exec();
}
