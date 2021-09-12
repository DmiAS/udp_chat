#ifndef QCLIENT_H
#define QCLIENT_H

#include "basic_client.h"
#include "QtSocket.h"
#include "QSerializer.hpp"
#include <cmath>

#define DEFAULT_FREQ 1
#define DEFAULT_SIZE 2

class QClient: public Client{
public:
    QClient(const QHostAddress &recv, const quint16 &recvp, const int& freq = DEFAULT_FREQ,
            const int& dgramSize = DEFAULT_SIZE): recv_{recv}, recvp_{recvp},
            freq_{freq}, dgramSize_{dgramSize}{
        socket = new QtSocket;
        serv = new QSerializer;
        socket->bind(QHostAddress::LocalHost, 0);
    }

    void send(const QString &msg) override;
    void setPacketSize(const int &size) override;
    void setFrequency(const int &seconds) override;

    ~QClient() override{}

private:
    Serializer* serv;
    Socket* socket;
    QHostAddress recv_;
    quint16 recvp_;
    int freq_;
    int dgramSize_;
};

void QClient::setFrequency(const int &seconds){
    freq_ = seconds;
}

void QClient::setPacketSize(const int &size){
    dgramSize_ = size;
}

void QClient::send(const QString &msg){
    int cnt = std::ceil(float(msg.length()) / float(dgramSize_));
    for (int i = 0; i < cnt; i++){
        auto chunk = msg.mid(i * dgramSize_, dgramSize_);
        Msg msg(STRING_TYPE, chunk, i, i == cnt - 1 ? true : false);
        auto packet = serv->serialize(msg);
        socket->send(packet, recv_, recvp_);
    }
}

#endif // QCLIENT_H
