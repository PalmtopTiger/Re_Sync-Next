/*******************************************************************************
 * This file is part of Re_Sync Next.
 *
 * Copyright (C) 2011-2019  Andrey Efremov <duxus@yandex.ru>
 *
 * Re_Sync is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Re_Sync is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Re_Sync.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#include "graphstruct.h"

//
// Класс графика
//
GraphStruct::GraphStruct() :
    position(0u),
    connected(false),
    graph(nullptr)
{}

void GraphStruct::clear()
{
    if (nullptr != this->graph)
    {
        for (QGraphicsItem *item : qAsConst(this->items))
        {
            this->graph->removeFromGroup(item);
            delete item;
        }
        this->items.clear();

        delete this->graph;
        this->graph = nullptr;
    }

    this->groups.clear();
}

//
// Класс файла
//
FileStruct::FileStruct() :
    scriptType(Script::SCR_UNKNOWN)
{}

void FileStruct::clear()
{
    GraphStruct::clear();

    this->script.clear();
    scriptType = Script::SCR_UNKNOWN;
}
