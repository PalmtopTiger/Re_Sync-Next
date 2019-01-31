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

#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include "script.h"

//
// Класс группы фраз
//
typedef QList<Script::Line::Event*> EventPtrList;

class EventGroup
{
    uint         _start;
    uint         _end;
    int          _shift;
    EventPtrList _events;

public:
    EventGroup(const uint start,
               const uint end,
               const EventPtrList& events);

    uint start() const;
    uint end() const;
    void shift(const int shift);
    int shift();
    void applyShift();
};
typedef QList<EventGroup> EventGroupList;

//
// Класс не совпавших групп фраз
//
typedef QList<int> DesyncPositions;

class DesyncGroup
{
public:
    DesyncGroup(const DesyncPositions& sync, const DesyncPositions& desync);

    //! @todo: сделать приватными?
    DesyncPositions sync, desync;
};
typedef QList<DesyncGroup> DesyncGroupList;

#endif // EVENTGROUP_H
