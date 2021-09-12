#ifndef QCLIENT_H
#define QCLIENT_H

#include "QtSocket.h"
#include "serializer.h"
#include <memory>
#include <cmath>
#include <QFile>

#define DEFAULT_FREQ 1
#define DEFAULT_SIZE 5

class QClient{
public:
    QClient(std::shared_ptr<Socket> sock,
            std::shared_ptr<Serializer> serializer,
            const int& freq = DEFAULT_FREQ,
            const int& dgramSize = DEFAULT_SIZE): freq_{freq}, dgramSize_{dgramSize}, serv{serializer}, socket{sock}{}

    void send(const QString &msg, QHostAddress addr, quint16 port);
    void sendFile(QFile &f, const QString &fileName, QHostAddress addr, quint16 port);
    void setPacketSize(const int &size);
    void setFrequency(const int &seconds);

    ~QClient(){}

private:
    std::shared_ptr<Serializer> serv;
    std::shared_ptr<Socket> socket;
    QHostAddress recv_;
    quint16 recvp_;
    int freq_;
    int dgramSize_;
};

#endif // QCLIENT_H
