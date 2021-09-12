#include <QApplication>
#include "QServer.h"
#include "QClient.h"
#include "QSerializer.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    auto host = QHostAddress::LocalHost;
    quint16 serverPort = 9000;

    std::shared_ptr<Socket> serverSocket = std::make_shared<QtSocket>(host, serverPort);
    std::shared_ptr<Socket> clientSocket = std::make_shared<QtSocket>(host, 0);
    std::shared_ptr<Serializer> serv = std::make_shared<QSerializer>();

    QServer server(serverSocket, serv);
    server.start();
    QClient client(clientSocket, serv);


    client.send("приветт", host, serverPort);
    client.send("медвед", host, serverPort);
    QFile f("C:\\summer_prac\\hello.txt");
    f.open(QIODevice::ReadOnly);
    client.sendFile(f, "C:\\summer_prac\\new.txt", host, serverPort);
    return a.exec();
}
