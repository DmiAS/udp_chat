#include "user.h"

User::User(std::shared_ptr<Socket> sock){
    auto serializer = std::shared_ptr<Serializer>(new QSerializer);
    srv = std::make_shared<QServer>(sock, serializer);
    cli = std::make_shared<QClient>(sock, serializer);
}
