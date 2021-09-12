#include "QSerializer.hpp"


Msg QSerializer::deserialize(QByteArray buf){
    QDataStream str(&buf, QIODevice::ReadOnly);
    Msg res;
    res.msg_type = get<quint8>(str);
    res.buf = get<QString>(str);
    res.index = get<qint32>(str);
    res.is_last = get<quint8>(str);
    return res;
}


QByteArray QSerializer::serialize(const Msg &msg){
    QByteArray buf;
    QDataStream s(&buf, QIODevice::WriteOnly);
    s << (quint8)msg.msg_type << msg.buf <<(qint32)msg.index << (quint8)msg.is_last;
    return buf;
}
