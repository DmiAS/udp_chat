#include <QApplication>
#include "QServer.h"
#include "QClient.h"
#include "QSerializer.hpp"
#include "chatdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatDialog w;
    w.show();
    auto host = QHostAddress::LocalHost;
    quint16 serverPort = 9000;

    QSharedPointer<Socket> serverSocket = QSharedPointer<QtSocket>(new QtSocket(host, serverPort));
    QSharedPointer<Socket> clientSocket = QSharedPointer<QtSocket>(new QtSocket(host, 0));
    QSharedPointer<Serializer> serv = QSharedPointer<QSerializer>(new QSerializer);

    QServer server(serverSocket, serv);
//    server.start();
    QClient client(clientSocket, serv);


    client.send("приветт", host, serverPort);
    client.send("медвед", host, serverPort);
//    QFile f("C:\\summer_prac\\hello.txt");
//    f.open(QIODevice::ReadOnly);
//    client.sendFile(f, "C:\\summer_prac\\new.txt", host, serverPort);
    return a.exec();
}
