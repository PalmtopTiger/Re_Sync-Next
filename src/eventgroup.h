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
