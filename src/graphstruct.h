#ifndef GRAPHSTRUCT_H
#define GRAPHSTRUCT_H

#include "script.h"
#include "eventgroup.h"
#include <QFileInfo>
#include <QGraphicsItem>

//
// Класс графика
//
class GraphStruct
{
public:
    GraphStruct();

    uint position;
    bool connected;
    QString title;
    QColor borderColor;
    QColor bgColor;
    QColor hlColor;

    EventGroupList groups;
    QList<QGraphicsItem *> items;
    QGraphicsItemGroup *graph;

    void clear();
};

//
// Класс файла
//
class FileStruct : public GraphStruct
{
public:
    FileStruct();

    QFileInfo fileInfo;
    Script::Script script;
    Script::ScriptType scriptType;

    void clear();
};

#endif // GRAPHSTRUCT_H
