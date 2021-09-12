#ifndef QSERVER_H
#define QSERVER_H

#include "serializer.h"
#include "basic_socket.h"
#include <QDebug>
#include <QMutex>
#include <QSharedPointer>

class QServer: public QObject{
    Q_OBJECT
public:
    QServer(QSharedPointer<Socket>, QSharedPointer<Serializer> serializer);

    void start();
    void stop();
    ~QServer() = default;

private:
    void initConnections();

private:
    QMutex strMu;
    QMutex fileMu;
    QVector<Msg> chunks_msg;
    QVector<Msg> chunks_file;
    QSharedPointer<Serializer> serv;
    QSharedPointer<Socket> socket;
    bool active = true;

signals:
    void msgends(QHostAddress);
    void fileEnds(QHostAddress, const QString &fileName);
    void msg(QString, QHostAddress);
    void datarecved(QHostAddress, quint16, int);

private slots:
    void recv(QByteArray, QHostAddress, quint16);
    void buildMsg(QHostAddress);
    void buildFile(QHostAddress, const QString &fileName);
};


#endif // QSERVER_H
