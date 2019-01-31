/*
 * This file is part of Re_Sync Next.
 * Copyright (C) 2011-2019  Andrey Efremov <duxus@yandex.ru>
 *
 * Re_Sync Next is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Re_Sync Next is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Re_Sync Next.  If not, see <https://www.gnu.org/licenses/>.
 */

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
