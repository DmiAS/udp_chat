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
    void msgends(QHostAddress, quint16);
    void fileEnds(QHostAddress, quint16, const QString &fileName);
    void msg(QHostAddress, quint16, QString);
    void file(QHostAddress, quint16, QString fileName);
    void datarecved(QHostAddress, quint16, int);

private slots:
    void recv(QByteArray, QHostAddress, quint16);
    void buildMsg(QHostAddress, quint16);
    void buildFile(QHostAddress, quint16, const QString &fileName);
};


#endif // QSERVER_H
