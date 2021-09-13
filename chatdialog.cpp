#include <QtGui>

#include "chatdialog.h"
#include <QScrollBar>

ChatDialog::ChatDialog(const User &client, const User &srv, QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    msg_line->setFocusPolicy(Qt::StrongFocus);
    win->setFocusPolicy(Qt::NoFocus);
    win->setReadOnly(true);
//    listWidget->setFocusPolicy(Qt::NoFocus);

    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << "Время" << "Отправитель" << "Размер");

    QDir dir(".");
    lineEdit->setText(dir.absolutePath());
    lineEdit->setCursorPosition(0);
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignLeft);

    packet->setValue(DEFAULT_SIZE);
    latency->setValue(DEFAULT_FREQ);

    connect(&client, &User::chunkrecv, this, &ChatDialog::updateTable);
    connect(&srv, &User::chunkrecv, this, &ChatDialog::updateTable);

    connect(&client, &User::msgrcv, this, &ChatDialog::on_msg_recv);
    connect(&srv, &User::msgrcv, this, &ChatDialog::on_msg_recv);

//    connect(msg_line, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
//    connect(msg_line, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
//    connect(&client, SIGNAL(newMessage(QString,QString)),
//            this, SLOT(appendMessage(QString,QString)));
//    connect(&client, SIGNAL(newParticipant(QString)),
//            this, SLOT(newParticipant(QString)));
//    connect(&client, SIGNAL(participantLeft(QString)),
//            this, SLOT(participantLeft(QString)));

    myNickName = "client.nickName()";
//    newParticipant(myNickName);
    tableFormat.setBorder(0);
    QTimer::singleShot(10 * 1000, this, SLOT(showInformation()));
}

void ChatDialog::updateTable(QString date, QString name, int len){
    table->insertRow(table->rowCount());
    table->setItem(table->rowCount(), 0, new QTableWidgetItem(date));
    table->setItem(table->rowCount(), 1, new QTableWidgetItem(name));
    table->setItem(table->rowCount(), 2, new QTableWidgetItem(len));
}


void ChatDialog::on_msg_recv(QString sender, QString msg){
    auto time = QDateTime::currentDateTime().toString();

    QTextCursor cursor(win->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + time + ":" + sender + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(msg);
    QScrollBar *bar = win->verticalScrollBar();
    bar->setValue(bar->maximum());
}

//void ChatDialog::newParticipant(const QString &nick)
//{
//    if (nick.isEmpty())
//        return;

//    QColor color = textEdit->textColor();
//    textEdit->setTextColor(Qt::gray);
//    textEdit->append(tr("* %1 has joined").arg(nick));
//    textEdit->setTextColor(color);
//    listWidget->addItem(nick);
//}

//void ChatDialog::participantLeft(const QString &nick)
//{
//    if (nick.isEmpty())
//        return;

//    QList<QListWidgetItem *> items = listWidget->findItems(nick,
//                                                           Qt::MatchExactly);
//    if (items.isEmpty())
//        return;

//    delete items.at(0);
//    QColor color = textEdit->textColor();
//    textEdit->setTextColor(Qt::gray);
//    textEdit->append(tr("* %1 has left").arg(nick));
//    textEdit->setTextColor(color);
//}

//void ChatDialog::showInformation()
//{
//    if (listWidget->count() == 1) {
//        QMessageBox::information(this, tr("Chat"),
//                                 tr("Launch several instances of this "
//                                    "program on your local network and "
//                                    "start chatting!"));
//    }
//}


void ChatDialog::on_send_msg_clicked()
{
    QString text = msg_line->toPlainText();
    if (text.isEmpty())
        return;
    on_msg_recv("i", text);
//    auto data = srv.srv->getAddrPort();
//    client.cli->send(text, data.first, data.second);
    msg_line->clear();
}

void ChatDialog::on_send_file_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Выберите файл", "C:\\");
    QFile f(file_path);
    f.open(QIODevice::ReadOnly);
    if (!f.isOpen()){
        QMessageBox::warning(this, "Ошибка",
                                         "Файл не может быть открыт");
        return;
    }
    //    auto data = srv.srv->getAddrPort();
//    client.cli->sendFile(f, data.first, data.second);
    f.close();
}

void ChatDialog::on_pushButton_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Выберите новый путь", "C:\\");
    if (!file_path.isNull())
        directory = file_path;
}

void ChatDialog::on_latency_editingFinished()
{
    qDebug() << "finished";
}

void ChatDialog::on_packet_editingFinished()
{

}
