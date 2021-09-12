//
// Created by dimon on 27.08.2021.
//

#ifndef SUMMER_PRACTICE_DGRAMS_H
#define SUMMER_PRACTICE_DGRAMS_H

#include <QString>

#define STRING_TYPE 's'
#define FILE_TYPE  'f'
struct Msg{
    Msg() = default;
    Msg(char t, QString s, int i, bool last): msg_type{t}, buf{s}, index{i}, is_last{last}{}
    char msg_type = STRING_TYPE; // какое сообщение передается: часть строки или файла
    QString buf; // часть сообщения
    int index; // индекс пакета в общем сообщении
    bool is_last; // достигли ли конца
};

#endif //SUMMER_PRACTICE_DGRAMS_H
