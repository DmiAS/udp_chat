#include <QApplication>
#include "QServer.h"
#include "QClient.h"
#include "user.h"
#include "QSerializer.hpp"
#include "chatdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto host = QHostAddress::LocalHost;
    quint16 serverPort = 9000;

    QSharedPointer<Socket> serverSocket = QSharedPointer<QtSocket>(new QtSocket(host, serverPort));
    QSharedPointer<Socket> clientSocket = QSharedPointer<QtSocket>(new QtSocket(host, 0));
    QSharedPointer<Serializer> serv = QSharedPointer<QSerializer>(new QSerializer);

    User cli(clientSocket);
    User srv(serverSocket);

    ChatDialog w(cli, srv);
    w.show();

    return a.exec();
}
