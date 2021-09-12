#ifndef USER_H
#define USER_H

#include "QServer.h"
#include "QClient.h"
#include "QSerializer.hpp"
class User
{
public:
    User() = delete;
    User(QSharedPointer<Socket> sock);
private:
    QSharedPointer<QServer> srv;
    QSharedPointer<QClient> cli;
};

#endif // USER_H
