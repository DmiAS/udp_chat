//
// Created by dimon on 26.08.2021.
//
#ifndef SUMMER_PRACTICE_BASIC_SERVER_H
#define SUMMER_PRACTICE_BASIC_SERVER_H

class BasicServer {
public:
    virtual void start() = 0;
    virtual void stop();
    virtual ~BasicServer(){}
};

#endif //SUMMER_PRACTICE_BASIC_SERVER_H
