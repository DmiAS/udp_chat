#include "QClient.h"


void QClient::setFrequency(const int &seconds){
    freq_ = seconds;
}

void QClient::setPacketSize(const int &size){
    dgramSize_ = size;
}

void QClient::send(const QString &msg, QHostAddress addr, quint16 port){
    int cnt = std::ceil(float(msg.length()) / float(dgramSize_));
    for (int i = 0; i < cnt; i++){
        auto chunk = msg.mid(i * dgramSize_, dgramSize_);
        Msg msg(STRING_TYPE, chunk.toUtf8(), i, i == cnt - 1 ? true : false);
        auto packet = serv->serialize(msg);
        socket->send(packet, addr, port);
    }
}

void QClient::sendFile(QFile &f, const QString &fileName, QHostAddress addr, quint16 port){
    bool isEnd = false;
    for (int i = 0; !isEnd; i++){
        auto chunk = f.read(dgramSize_);
        isEnd = chunk.isNull();
        Msg msg(FILE_TYPE, chunk, i, isEnd, fileName);
        auto packet = serv->serialize(msg);
        socket->send(packet, addr, port);
    }
    qDebug() << "sented file";
}
