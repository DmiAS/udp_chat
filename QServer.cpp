#include "QServer.h"


QServer::QServer(const QHostAddress &address, const quint16 &port){
    socket = new QtSocket;
    socket->bind(address, port);
    serv = new QSerializer;
    QObject::connect(socket, &Socket::dgramrecv, this, &QServer::recv);
}


void QServer::start(){
}

void QServer::stop(){

}

void QServer::recv(QByteArray data, QHostAddress addr, quint16 port){
    auto msg = serv->deserialize(data);
    qDebug() << addr << port << msg.buf;
}
