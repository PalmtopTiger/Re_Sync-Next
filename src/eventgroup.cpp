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

#include "eventgroup.h"

//
// Класс группы фраз
//
EventGroup::EventGroup(const uint start,
                       const uint end,
                       const EventPtrList& events) :
    _start(start),
    _end(end),
    _shift(0),
    _events(events)
{}

int EventGroup::shift()
{
    return _shift;
}

uint EventGroup::start() const
{
    int ret = static_cast<int>(_start) + _shift;
    if (ret < 0) ret = 0;
    return static_cast<uint>(ret);
}

uint EventGroup::end() const
{
    int ret = static_cast<int>(_end) + _shift;
    if (ret < 0) ret = 0;
    return static_cast<uint>(ret);
}

void EventGroup::shift(const int shift)
{
    _shift = shift;
}

void EventGroup::applyShift()
{
    int temp;

    for (Script::Line::Event* const e : qAsConst(_events))
    {
        temp = static_cast<int>(e->start) + _shift;
        if (temp < 0) temp = 0;
        e->start = static_cast<uint>(temp);

        temp = static_cast<int>(e->end) + _shift;
        if (temp < 0) temp = 0;
        e->end = static_cast<uint>(temp);
    }

    temp = static_cast<int>(_start) + _shift;
    if (temp < 0) temp = 0;
    _start = static_cast<uint>(temp);

    temp = static_cast<int>(_end) + _shift;
    if (temp < 0) temp = 0;
    _end = static_cast<uint>(temp);

    _shift = 0;
}

//
// Класс не совпавших групп фраз
//
DesyncGroup::DesyncGroup(const DesyncPositions& sync, const DesyncPositions& desync) :
    sync(sync),
    desync(desync)
{}
