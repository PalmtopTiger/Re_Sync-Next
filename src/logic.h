#ifndef LOGIC_H
#define LOGIC_H

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
               const EventPtrList& events) :
        _start(start),
        _end(end),
        _shift(0),
        _events(events)
    {}

    uint start() const;
    uint end() const;
    void shift(const int shift);
    int shift() { return _shift; }
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
    DesyncGroup(const DesyncPositions& sync, const DesyncPositions& desync) :
        sync(sync),
        desync(desync)
    {}
    //! @todo: сделать приватными?
    DesyncPositions sync, desync;
};
typedef QList<DesyncGroup> DesyncGroupList;


bool SortByTime(const Script::Line::Event* const s1, const Script::Line::Event* const s2);
void GroupEvents(EventPtrList events, EventGroupList& groups, const int minDuration = 500, const int maxOffset = 5000, const bool skipComments = true, const bool skipLyrics = false);
void LCS(const EventGroupList& sync, const EventGroupList& desync, DesyncGroupList& result, const int maxDesync = 200);
void Syncronize(const EventGroupList& sync, const EventGroupList& desync, const DesyncGroupList& desyncPoints, EventGroupList& result, const int maxDesync = 200, const int maxShift = 15000, const bool allowOverlap = false);

#endif // LOGIC_H
