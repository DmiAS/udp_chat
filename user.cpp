#include "user.h"

User::User(QSharedPointer<Socket> sock){
    auto serializer = QSharedPointer<Serializer>(new QSerializer);
    srv = QSharedPointer<QServer>(new QServer(sock, serializer));
    cli = QSharedPointer<QClient>(new QClient(sock, serializer));
}
