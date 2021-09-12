#include "QtSocket.h"

QtSocket::QtSocket(){
    socket = new QUdpSocket(this);
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
}

QtSocket::~QtSocket(){
    this->close();
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


void QtSocket::bind(const QHostAddress &address, const quint16 &port) {
    socket->bind(address, port);
};

void QtSocket::send(const QByteArray &msg, const QHostAddress &address, const quint16 &port){
    socket->writeDatagram(msg, address, port);
}

void QtSocket::close(){
    socket->close();
}
