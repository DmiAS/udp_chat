#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QFileDialog>
#include "ui_chatdialog.h"
#include <QTextTableFormat>
#include <QMessageBox>
#include "user.h"

class ChatDialog : public QDialog, private Ui::ChatDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);
    ChatDialog(const User &client, const User &srv, QWidget *parent = 0);

//public slots:
//    void appendMessage(const QString &from, const QString &message);

private slots:
//    void returnPressed();
//    void newParticipant(const QString &nick);
//    void participantLeft(const QString &nick);
//    void showInformation();

    void updateTable(QString, QString, int);

    void on_msg_recv(QString sender, QString msg);

    void on_send_msg_clicked();

    void on_send_file_clicked();

    void on_pushButton_clicked();

    void on_latency_editingFinished();

    void on_packet_editingFinished();

private:
    QString directory;
    User client, srv;
    QString myNickName;
    QTextTableFormat tableFormat;
};

#endif // CHATDIALOG_H
