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

#ifndef LOGIC_H
#define LOGIC_H

#include "script.h"
#include "eventgroup.h"

bool SortByTime(const Script::Line::Event* const s1, const Script::Line::Event* const s2);
void GroupEvents(EventPtrList events, EventGroupList& groups, const int minDuration = 500, const int maxOffset = 5000, const bool skipComments = true, const bool skipLyrics = false);
void LCS(const EventGroupList& sync, const EventGroupList& desync, DesyncGroupList& result, const int maxDesync = 200);
void Syncronize(const EventGroupList& sync, const EventGroupList& desync, const DesyncGroupList& desyncPoints, EventGroupList& result, const int maxDesync = 200, const int maxShift = 15000, const bool allowOverlap = false);

#endif // LOGIC_H
