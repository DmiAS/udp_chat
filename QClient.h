#ifndef QCLIENT_H
#define QCLIENT_H

//#include "basic_client.h"
#include "QtSocket.h"
#include "QSerializer.hpp"
#include <cmath>
#include <QFile>

#define DEFAULT_FREQ 1
#define DEFAULT_SIZE 5

class QClient{
public:
    QClient(const QHostAddress &recv, const quint16 &recvp, const int& freq = DEFAULT_FREQ,
            const int& dgramSize = DEFAULT_SIZE): recv_{recv}, recvp_{recvp},
            freq_{freq}, dgramSize_{dgramSize}{
        socket = new QtSocket;
        serv = new QSerializer;
        socket->bind(QHostAddress::LocalHost, 0);
    }

    void send(const QString &msg);
    void sendFile(QFile &f, const QString &fileName);
    void setPacketSize(const int &size);
    void setFrequency(const int &seconds);

    ~QClient(){}

private:
    QSerializer* serv;
    QtSocket* socket;
    QHostAddress recv_;
    quint16 recvp_;
    int freq_;
    int dgramSize_;
};

#endif // QCLIENT_H
