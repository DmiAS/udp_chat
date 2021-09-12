//
// Created by dimon on 26.08.2021.
//
#ifndef SUMMER_PRACTICE_BASIC_CLIENT_H
#define SUMMER_PRACTICE_BASIC_CLIENT_H
#include <QString>

class Client{
public:
    virtual void send(const QString &msg) = 0;
    virtual void setPacketSize(const int &size);
    virtual void setFrequency(const int& seconds);
    virtual ~Client(){}
};
#endif //SUMMER_PRACTICE_BASIC_CLIENT_H
