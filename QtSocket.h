#ifndef QTSOCKET_H
#define QTSOCKET_H
#include "basic_socket.h"
#include <QUdpSocket>

class QtSocket: public Socket{
public:

    QtSocket(){
        socket = new QUdpSocket();
//        QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
    }

    void close() override;

    void bind(const QHostAddress &address, const quint16 &port) override;

    void send(const QByteArray &msg, const QHostAddress &address, const quint16 &port) override;

    ~QtSocket() override{
        this->close();
    }

private:
    void readDatagrams();

private:
    QUdpSocket *socket;
};


void QtSocket::bind(const QHostAddress &address, const quint16 &port) {
    socket->bind(address, port);
};

void QtSocket::send(const QByteArray &msg, const QHostAddress &address, const quint16 &port){
    socket->writeDatagram(msg, address, port);
}

void QtSocket::readDatagrams(){
    QHostAddress sender;
    quint16 senderPort;
    while(socket->hasPendingDatagrams()){
        QByteArray dgram;
        dgram.resize(socket->pendingDatagramSize());
        socket->readDatagram(dgram.data(), dgram.size(), &sender, &senderPort);
//        emit dgramrecv(dgram, sender, senderPort);
    }
}

void QtSocket::close(){
    socket->close();
}

#endif // QTSOCKET_H
