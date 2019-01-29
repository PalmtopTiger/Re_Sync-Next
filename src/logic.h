#ifndef LOGIC_H
#define LOGIC_H

#include "script.h"
#include "eventgroup.h"

bool SortByTime(const Script::Line::Event* const s1, const Script::Line::Event* const s2);
void GroupEvents(EventPtrList events, EventGroupList& groups, const int minDuration = 500, const int maxOffset = 5000, const bool skipComments = true, const bool skipLyrics = false);
void LCS(const EventGroupList& sync, const EventGroupList& desync, DesyncGroupList& result, const int maxDesync = 200);
void Syncronize(const EventGroupList& sync, const EventGroupList& desync, const DesyncGroupList& desyncPoints, EventGroupList& result, const int maxDesync = 200, const int maxShift = 15000, const bool allowOverlap = false);

#endif // LOGIC_H
