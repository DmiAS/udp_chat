//
// Created by dimon on 26.08.2021.
//
#ifndef SUMMER_PRACTICE_BASIC_SOCKET_H
#define SUMMER_PRACTICE_BASIC_SOCKET_H
#include <string>
#include <QByteArray>
#include <QHostAddress>


class Socket: public QObject{
    Q_OBJECT
public:
    virtual void close() = 0;

    virtual void bind(const QHostAddress& address, const quint16 &port) = 0;

    virtual void send(const QByteArray &msg, const QHostAddress& address, const quint16 &port) = 0;

    virtual ~Socket() = default;

signals:
    void dgramrecv(QByteArray, QHostAddress, quint16);
};

#endif //SUMMER_PRACTICE_BASIC_SOCKET_H
