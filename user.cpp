#include "user.h"
#include <QDateTime>
User::User(QSharedPointer<Socket> sock){
    auto serializer = QSharedPointer<Serializer>(new QSerializer);
    srv = QSharedPointer<QServer>(new QServer(sock, serializer));
    cli = QSharedPointer<QClient>(new QClient(sock, serializer));

    connect(srv.get(), &QServer::datarecved, this, &User::onchunkrecv);

}


void User::onchunkrecv(QHostAddress addr, quint16 port, int len){
    auto s = QString("%s:%d").arg(addr.toString(), port);
    auto t = QDateTime::currentDateTime().toString();
    emit chunkrecv(t, s, len);
}
