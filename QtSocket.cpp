#include "QtSocket.h"

QtSocket::QtSocket(const QHostAddress &address, const quint16 &port): addr{address}, port{port}{
    socket = new QUdpSocket(this);
    socket->bind(address, port);
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
}

QPair<QHostAddress, quint16> QtSocket::getAddrPort(){
    return QPair<QHostAddress, quint16>(addr, port);
}

QtSocket::~QtSocket(){
    socket->close();
}

void QtSocket::readDatagrams(){
    QHostAddress sender;
    quint16 senderPort;
    while(socket->hasPendingDatagrams()){
        QByteArray dgram;
        dgram.resize(socket->pendingDatagramSize());
        socket->readDatagram(dgram.data(), dgram.size(), &sender, &senderPort);
        emit dgramrecv(dgram, sender, senderPort);
    }
}

void QtSocket::send(const QByteArray &msg, const QHostAddress &address, const quint16 &port){
    socket->writeDatagram(msg, address, port);
}

