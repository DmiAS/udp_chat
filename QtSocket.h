#ifndef QTSOCKET_H
#define QTSOCKET_H

#include "basic_socket.h"
#include <QUdpSocket>

class QtSocket: public Socket{
    Q_OBJECT
public:

    QtSocket(const QHostAddress &address, const quint16 &port);

    void send(const QByteArray &msg, const QHostAddress &address, const quint16 &port) override;

    ~QtSocket() override;

private slots:
    void readDatagrams();

private:
    QUdpSocket *socket;
};

#endif // QTSOCKET_H
