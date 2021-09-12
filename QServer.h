#ifndef QSERVER_H
#define QSERVER_H

#include "QSerializer.hpp"
#include "QtSocket.h"
#include <QDebug>

class QServer: public QObject{
    Q_OBJECT
public:
    QServer(const QHostAddress &address, const quint16 &port);

    void start();
    void stop();
    ~QServer() = default;

private:
    QSerializer *serv;
    Socket* socket;
    bool active = true;

private slots:
    void recv(QByteArray, QHostAddress, quint16);
};


#endif // QSERVER_H
