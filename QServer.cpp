#include "QServer.h"
#include <algorithm>
#include <QFile>

QServer::QServer(std::shared_ptr<Socket> sock, std::shared_ptr<Serializer> serializer){
    socket = sock;
    serv = serializer;
    initConnections();
}

void QServer::initConnections(){
    QObject::connect(socket.get(), &Socket::dgramrecv, this, &QServer::recv);
    QObject::connect(this, &QServer::msgends, this, &QServer::buildMsg);
    QObject::connect(this, &QServer::fileEnds, this, &QServer::buildFile);
}

void QServer::start(){
}

void QServer::stop(){

}

void QServer::recv(QByteArray data, QHostAddress addr, quint16 port){
    qDebug() << "here";
    emit datarecved(addr, port, data.length()); // уведомление о приходе пакета любого вида
    auto msg = serv->deserialize(data);
    if (msg.msg_type == STRING_TYPE){
        strMu.lock();
        chunks_msg.push_back(msg);
        strMu.unlock();
        if (msg.is_last){
            emit msgends(addr);
        }
    } else if (msg.msg_type ==  FILE_TYPE){
        fileMu.lock();
        chunks_file.push_back(msg);
        fileMu.unlock();
        if (msg.is_last){
            emit fileEnds(addr, msg.fileName);
        }
    }
}

void QServer::buildMsg(QHostAddress addr){
    strMu.lock();
    auto vec = chunks_msg;
    chunks_msg.clear();
    strMu.unlock();
    // сортируем массив чанков, чтобы пакеты были в правильной последовательности
    std::sort(vec.begin(), vec.end(), [](const Msg &val1, const Msg &val2){
        return val1.index < val2.index;
    });
    QString res;
    // собираем итоговое сообщение
    for (auto &chunk: vec){
        res.append(chunk.buf);
    }
    qDebug() << "ends" << addr << res;
    emit msg(res, addr);
}

void QServer::buildFile(QHostAddress addr, const QString &fileName){
    strMu.lock();
    auto vec = chunks_file;
    chunks_file.clear();
    strMu.unlock();
    // сортируем массив чанков, чтобы пакеты были в правильной последовательности
    std::sort(vec.begin(), vec.end(), [](const Msg &val1, const Msg &val2){
        return val1.index < val2.index;
    });

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    // собираем итоговый файл
    for (auto &chunk: vec){
        file.write(chunk.buf);
    }
    file.close();
    qDebug() << "file written";
}
