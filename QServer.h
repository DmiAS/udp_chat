#ifndef QSERVER_H
#define QSERVER_H

#include "basic_server.h"
#include "QSerializer.hpp"
#include "QtSocket.h"
#include <QDebug>

class QServer: public BasicServer{
public:
    QServer(const QHostAddress &address, const quint16 &port){
        socket = new QtSocket;
        socket->bind(address, port);
        serv = new QSerializer;
    }

    void start() override;
    void stop() override;
    ~QServer() override{}

private:
    Serializer *serv;
    Socket* socket;
    bool active = true;
};


void QServer::start(){
}

void QServer::stop(){

}

//void QServer::recv(QByteArray data, QHostAddress addr, quint16 port){
//    auto msg = serv->deserialize(data);
//    qDebug() << addr << port << msg.buf;
//}


#endif // QSERVER_H
