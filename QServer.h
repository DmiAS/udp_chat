#ifndef QSERVER_H
#define QSERVER_H

#include "QSerializer.hpp"
#include "QtSocket.h"
#include <QDebug>

class QServer{
public:
    QServer(const QHostAddress &address, const quint16 &port){
        socket = new QtSocket;
        socket->bind(address, port);
        serv = new QSerializer;
    }

    void start();
    void stop();
    ~QServer(){}

private:
    QSerializer *serv;
    QtSocket* socket;
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
