#include "QServer.h"
#include <algorithm>

QServer::QServer(const QHostAddress &address, const quint16 &port){
    socket = new QtSocket;
    socket->bind(address, port);
    serv = new QSerializer;
    QObject::connect(socket, &Socket::dgramrecv, this, &QServer::recv);
    QObject::connect(this, &QServer::msgends, this, &QServer::buildMsg);
}


void QServer::start(){
}

void QServer::stop(){

}

void QServer::recv(QByteArray data, QHostAddress addr, quint16 port){
    auto msg = serv->deserialize(data);
    qDebug() << addr << port << msg.buf;
    strMu.lock();
    chunks_msg.push_back(msg);
    strMu.unlock();
    if (msg.is_last){
        emit msgends(addr);
    }
}

void QServer::buildMsg(QHostAddress addr){
    strMu.lock();
    auto vec = chunks_msg;
    chunks_msg.clear();
    strMu.unlock();
    std::sort(vec.begin(), vec.end(), [](const Msg &val1, const Msg &val2){
        return val1.index < val2.index;
    });
    QString res;
    for (auto &chunk: vec){
        res.append(chunk.buf);
    }
    qDebug() << "ends" << addr << res;
    emit msg(res, addr);
}
