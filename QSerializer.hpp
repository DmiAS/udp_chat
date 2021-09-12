#ifndef QSERIALIZER_H
#define QSERIALIZER_H
#include <QDataStream>
#include "dgrams.h"

class QSerializer{
public:
    QByteArray serialize(const Msg &msg);
    Msg deserialize(QByteArray msg);
    ~QSerializer(){}
};

template <typename T> T get(QDataStream & str) {
   T value;
   str >> value;
   return value;
}

#endif // QSERIALIZER_H
