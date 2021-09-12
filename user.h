#ifndef USER_H
#define USER_H

#include "QServer.h"
#include "QClient.h"
#include "QSerializer.hpp"
class User
{
public:
    User() = delete;
    User(std::shared_ptr<Socket> sock);
private:
    std::shared_ptr<QServer> srv;
    std::shared_ptr<QClient> cli;
};

#endif // USER_H
