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
public:
    QSharedPointer<QServer> srv;
    QSharedPointer<QClient> cli;
signals:
    void chunkrecv(QString, QString, int);
    void msgrcv(QString sender, QString msg);
    void filercv(QString sender, QString fileName);
private slots:
    void onmsgrcv(QString sender, QString msg);
    void onfilercv(QString sender, QString file);
    void onchunkrecv(QHostAddress, quint16, int);
};

#endif // USER_H
