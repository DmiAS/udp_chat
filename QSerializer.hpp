#ifndef QSERIALIZER_H
#define QSERIALIZER_H
#include <QDataStream>
#include "serializer.h"

class QSerializer: public Serializer{
public:
    QByteArray serialize(const Msg &msg) override;
    Msg deserialize(QByteArray msg) override;
    ~QSerializer() override{}
};

template <typename T>
T get(QDataStream & str) {
   T value;
   str >> value;
   return value;
}

#endif // QSERIALIZER_H
