﻿#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "dgrams.h"
#include <QByteArray>

class Serializer{
public:
    virtual QByteArray serialize(const Msg &msg) = 0;
    virtual Msg deserialize(QByteArray msg);
    virtual ~Serializer(){}
};

#endif // SERIALIZER_H
