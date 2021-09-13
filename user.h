#ifndef USER_H
#define USER_H

#include "QServer.h"
#include "QClient.h"
#include "QSerializer.hpp"
class User: public QObject
{
    Q_OBJECT
public:
    User() = default;
    User(QSharedPointer<Socket> sock);
    User(const User &u);
    QPair<QHostAddress, quint16> getAddrPort() const;
public:
    QSharedPointer<QServer> srv;
    QSharedPointer<QClient> cli;
private:
    QHostAddress addr;
    quint16 port;
signals:
    void chunkrecv(QString, QString, int);
    void msgrcv(QString sender, QString msg);
    void filercv(QString sender, QString fileName);
private slots:
    void onmsgrcv(QHostAddress addr, quint16 port, QString msg);
    void onfilercv(QString sender, QString file);
    void onchunkrecv(QHostAddress, quint16, int);
};

#endif // USER_H
