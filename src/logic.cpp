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

#include "logic.h"
#include <QVector>

//
// Функция для сортировки по времени
//
bool SortByTime(const Script::Line::Event* const s1, const Script::Line::Event* const s2)
{
    if (s1->start != s2->start)
    {
        return s1->start < s2->start;
    }
    else if (s1->end != s2->end)
    {
        return s1->end < s2->end;
    }
    else if (s1->layer != s2->layer)
    {
        return s1->layer < s2->layer;
    }
    else if (s1->style != s2->style)
    {
        return s1->style < s2->style;
    }
    else
    {
        return s1->actorName < s2->actorName;
    }
}

//
// Фильтры фраз
//
inline bool IsComment(const QString &text)
{
    const QStringList patterns = {
        "\\pos",

        "translated",
        "translator",
        "translation",
        "timed",
        "timer",
        "timing",
        "typesetted",
        "typesetter",
        "typesetting",
        "encoded",
        "encoder",
        "encoding",
        "styled",
        "styler",
        "styling",
        "karaoke",
        "qc",
        "note",

        "перевод",
        "тайминг",
        "стайлинг",
        "тайпсет",
        "энкод",
        "кодирование",
        "оформление",
        "редактор",
        "редактирование",
        "редактура",
        "редакция",
        "караоке",
        "коммент"
    };

    for (const QString& pattern : patterns)
    {
        if (text.contains(pattern, Qt::CaseInsensitive)) return true;
    }

    return false;
}

inline bool IsLyrics(const QString &style)
{
    const QStringList begins = {
        "op",
        "ed",
        "end"
    };
    const QStringList ends = {
        "op",
        "ed",
        "rom",
        "kar",
        "kan"
    };
    const QStringList middle = {
        "rus",
        "eng",
        "jap",
        "kara",
        "romaji",
        "kanji",
        "title",
        "comment",
        "sign",
        "note",
        "logo",
        "insert",
        "copyright",
        "name",
        "credit",
        "staff",
        "song",
        "lyric",
        "type"
    };

    for (const QString& begin : begins)
    {
        if (style.startsWith(begin, Qt::CaseInsensitive)) return true;
    }
    for (const QString& end : ends)
    {
        if (style.endsWith(end, Qt::CaseInsensitive)) return true;
    }
    for (const QString& mid : middle)
    {
        if (style.contains(mid, Qt::CaseInsensitive)) return true;
    }

    return false;
}

//
// Объединение фраз в группы
//
void GroupEvents(EventPtrList events, EventGroupList& groups, const int minDuration, const int maxOffset, const bool skipComments, const bool skipLyrics)
{
    // Сортировка по времени
    qSort(events.begin(), events.end(), SortByTime);

    EventPtrList curAccum, dropAccum;
    int firstDropOffset = 0;
    uint prevEnd = 0,
            curStart = 0,
            curEnd = 0;
    bool hasGroups = false;
    for (Script::Line::Event* const e : qAsConst(events))
    {
        // Уже есть отброшенные и новая фраза отстоит от предыдущей дальше первой
        if ( !dropAccum.isEmpty() && static_cast<int>(e->start) - static_cast<int>(prevEnd) > firstDropOffset && hasGroups )
        {
            // Добавить в текущую группу
            curAccum.append(dropAccum);
        }

        // Отбрасываем короткие фразы, комментарии или лирику
        if ( (static_cast<int>(e->end) - static_cast<int>(e->start) < minDuration) || (skipComments && IsComment(e->text)) || (skipLyrics && IsLyrics(e->style)) )
        {
            // У первой фразы нет отступа
            if ( 0 == prevEnd )
            {
                firstDropOffset = 0;
            }
            else
            {
                firstDropOffset = static_cast<int>(e->start) - static_cast<int>(prevEnd);
            }

            dropAccum.append(e);
        }
        else // Подходящая фраза
        {
            if ( static_cast<int>(e->start) - static_cast<int>(prevEnd) > maxOffset || !hasGroups )
            {
                if (hasGroups)
                {
                    groups.append( EventGroup(curStart, curEnd, curAccum) );
                    curAccum.clear();
                }

                curStart = e->start;
                hasGroups = true;
            }

            // Скинуть все накопленные, если есть
            if ( !dropAccum.isEmpty() )
            {
                curAccum.append(dropAccum);
            }

            curEnd = e->end;
            curAccum.append(e);
        }

        prevEnd = e->end;
    }
    // Скинуть оставшиеся
    if ( !dropAccum.isEmpty() )
    {
        curAccum.append(dropAccum);
    }
    if ( !curAccum.isEmpty() && hasGroups )
    {
        groups.append( EventGroup(curStart, curEnd, curAccum) );
    }
}

//
// Нахождение наибольшей общей подпоследовательности
//
void LCS(const EventGroupList& sync, const EventGroupList& desync, DesyncGroupList& result, const int maxDesync)
{
    const int max_i = sync.length(), max_j = desync.length();
    int i, j, syncOffset, desyncOffset;

    // Построение таблицы
    QVector< QVector<int> > maxLen(sync.length() + 1);
    for (i = 0; i <= max_i; ++i)
    {
        maxLen[i].resize(desync.length() + 1);
        for (j = 0; j <= max_j; ++j)
        {
            maxLen[i][j] = 1;
        }
    }

    // Заполнение таблицы
    {
        int i, j;
        for (i = sync.length() - 1; i >= 0; --i)
        {
            for (j = desync.length() - 1; j >= 0; --j)
            {
                syncOffset = i > 0 ? static_cast<int>(sync[i].start()) - static_cast<int>(sync[i - 1].start()) : 0;
                if (syncOffset < 0) syncOffset = 0;
                desyncOffset = j > 0 ? static_cast<int>(desync[j].start()) - static_cast<int>(desync[j - 1].start()) : 0;
                if (desyncOffset < 0) desyncOffset = 0;

                if ( qAbs(syncOffset - desyncOffset) <= maxDesync )
                {
                    maxLen[i][j] = maxLen[i+1][j+1] + 1;
                }
                else
                {
                    maxLen[i][j] = qMax( maxLen[i+1][j], maxLen[i][j+1] );
                }
            }
        }
    }

    // Нахождение наибольшей общей подпоследовательности
    DesyncPositions syncAccum, desyncAccum;
    i = j = 0;
    while (maxLen[i][j] != 0 && i < max_i && j < max_j)
    {
        syncOffset = i > 0 ? static_cast<int>(sync[i].start()) - static_cast<int>(sync[i - 1].start()) : 0;
        if (syncOffset < 0) syncOffset = 0;
        desyncOffset = j > 0 ? static_cast<int>(desync[j].start()) - static_cast<int>(desync[j - 1].start()) : 0;
        if (desyncOffset < 0) desyncOffset = 0;

        if ( qAbs(syncOffset - desyncOffset) <= maxDesync )
        {
            if (!syncAccum.isEmpty() && !desyncAccum.isEmpty())
            {
                result.append( DesyncGroup(syncAccum, desyncAccum) );
            }
            syncAccum.clear();
            desyncAccum.clear();
            ++i;
            ++j;
        }
        else
        {
            if (maxLen[i][j] == maxLen[i+1][j])
            {
                syncAccum.append(i);
                ++i;
            }
            else
            {
                desyncAccum.append(j);
                ++j;
            }
        }
    }
}

//
// Подсчёт рассинхронизированных
//
int CountSyncronized(const EventGroupList& sync, const EventGroupList& desync, const int maxDesync)
{
    const int max_i = sync.length(), max_j = desync.length();
    int count = 0, i = 0, j = 0;
    while (i < max_i && j < max_j)
    {
        if ( qAbs(static_cast<int>(sync[i].start()) - static_cast<int>(desync[j].start())) <= maxDesync )
        {
            ++count;
            ++i;
            ++j;
        }
        else if ( sync[i].start() < desync[j].start() )
        {
            ++i;
        }
        else
        {
            ++j;
        }
    }

    return count;
}

//
// Синхронизация
//
void Syncronize(const EventGroupList& sync, const EventGroupList& desync, const DesyncGroupList& desyncPoints, EventGroupList& result, const int maxDesync, const int maxShift, const bool allowOverlap)
{
    // Полная синхронизация
    if (desyncPoints.isEmpty()) return;

    int i, j, k;
    // Первые синхронны
    if (desyncPoints[0].desync[0] > 0)
    {
        for (i = 0; i < desyncPoints[0].desync[0]; ++i)
        {
            result.append(desync[i]);
        }
    }

    int untilPosSync, untilPosDesync, pos, syncCount, bestSyncCount;
    int shift, bestShift;
    EventGroupList tempSync, tempDesync;
    uint prevEnd = 0;
    const int dpLen = desyncPoints.length();
    for (i = 0; i < dpLen; ++i)
    {
        const DesyncPositions& syncPos_i = desyncPoints[i].sync;
        const DesyncPositions& desyncPos_i = desyncPoints[i].desync;

        // Последняя группа или нет
        if (i < dpLen - 1)
        {
            untilPosSync = desyncPoints[i + 1].sync[0];
            untilPosDesync = desyncPoints[i + 1].desync[0];
        }
        else
        {
            untilPosSync = sync.length();
            untilPosDesync = desync.length();
        }

        bestSyncCount = 0;
        bestShift = 0;
        for (j = 0; j < syncPos_i.length(); ++j)
        {
            for (k = 0; k < desyncPos_i.length(); ++k)
            {
                shift = static_cast<int>(sync[syncPos_i[j]].start()) - static_cast<int>(desync[desyncPos_i[k]].start());
                if (qAbs(shift) > maxShift) continue;

                tempDesync.clear();
                for (pos = desyncPos_i[0]; pos < untilPosDesync; ++pos)
                {
                    tempDesync.append(desync[pos]);
                    tempDesync.back().shift(shift);
                }
                // Нельзя залезать на предыдущую группу
                if (!allowOverlap && tempDesync.first().start() < prevEnd) continue;

                tempSync.clear();
                for (pos = syncPos_i[0]; pos < untilPosSync; ++pos)
                {
                    tempSync.append(sync[pos]);
                }

                syncCount = CountSyncronized(tempSync, tempDesync, maxDesync);
                if (syncCount > bestSyncCount)
                {
                    bestSyncCount = syncCount;
                    bestShift = shift;
                }
            }
        }

        // Перекидываем лучший результат
        for (pos = desyncPos_i[0]; pos < untilPosDesync; ++pos)
        {
            result.append(desync[pos]);
            if (bestShift != 0)
            {
                result.last().shift(bestShift);
            }
        }
        prevEnd = result.last().end();
    }
}
