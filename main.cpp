#include <QApplication>
#include "QServer.h"
#include "QClient.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    auto serverHost = QHostAddress::LocalHost;
    quint16 serverPort = 9000;
    QServer server(serverHost, serverPort);
    server.start();
    QClient client(serverHost, serverPort);
    client.send("приветт");
    client.send("медвед");
    return a.exec();
}
