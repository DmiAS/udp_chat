#ifndef QSERVER_H
#define QSERVER_H

#include "QSerializer.hpp"
#include "QtSocket.h"
#include <QDebug>
#include <QMutex>

class QServer: public QObject{
    Q_OBJECT
public:
    QServer(const QHostAddress &address, const quint16 &port);

    void start();
    void stop();
    ~QServer() = default;

private:
    QMutex strMu;
    QMutex fileMu;
    QVector<Msg> chunks_msg;
    QVector<Msg> chunks_file;
    QSerializer *serv;
    Socket* socket;
    bool active = true;

signals:
    void msgends(QHostAddress);
    void msg(QString, QHostAddress);

private slots:
    void recv(QByteArray, QHostAddress, quint16);
    void buildMsg(QHostAddress);
};


#endif // QSERVER_H
