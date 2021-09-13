#include "user.h"
#include <QDateTime>
User::User(QSharedPointer<Socket> sock){
    auto serializer = QSharedPointer<Serializer>(new QSerializer);
    srv = QSharedPointer<QServer>(new QServer(sock, serializer));
    cli = QSharedPointer<QClient>(new QClient(sock, serializer));
    auto data = sock->getAddrPort();
    addr = data.first;
    port = data.second;

    connect(srv.get(), &QServer::datarecved, this, &User::onchunkrecv);
    connect(srv.get(), &QServer::msg, this, &User::onmsgrcv);

}

User::User(const User &u){
    this->cli = u.cli;
    this->srv = u.srv;
    this->addr = u.addr;
    this->port = u.port;
}

QPair<QHostAddress, quint16> User::getAddrPort() const{
    return QPair<QHostAddress, quint16>(addr, port);
}

void User::onchunkrecv(QHostAddress addr, quint16 port, int len){
    auto s = QString("%1:%2").arg(addr.toString(), QString::number(port));
    auto t = QDateTime::currentDateTime().toString();
    qDebug() << "info" << t << s << len;
    emit chunkrecv(t, s, len);
}

void User::onmsgrcv(QHostAddress addr, quint16 port, QString msg){
    auto sender = QString("%1:%2").arg(addr.toString(), QString::number(port));
    emit msgrcv(sender, msg);
}

void User::onfilercv(QString sender, QString fileName){
    emit filercv(sender, fileName);
}
