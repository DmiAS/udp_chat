#include "QClient.h"


void QClient::setFrequency(const int &seconds){
    freq_ = seconds;
}

void QClient::setPacketSize(const int &size){
    dgramSize_ = size;
}

void QClient::send(const QString &msg){
    int cnt = std::ceil(float(msg.length()) / float(dgramSize_));
    for (int i = 0; i < cnt; i++){
        auto chunk = msg.mid(i * dgramSize_, dgramSize_);
        Msg msg(STRING_TYPE, chunk, i, i == cnt - 1 ? true : false);
        auto packet = serv->serialize(msg);
        socket->send(packet, recv_, recvp_);
    }
}

void QClient::sendFile(QFile f, const QString &fileName){
    QTextStream stream(&f);

    bool isEnd = false;
    for (int i = 0; !isEnd; i++){
        isEnd = stream.atEnd();
        auto chunk = stream.read(dgramSize_);
        Msg msg(FILE_TYPE, chunk, i, isEnd);
        auto packet = serv->serialize(msg);
        socket->send(packet, recv_, recvp_);
    }
}
