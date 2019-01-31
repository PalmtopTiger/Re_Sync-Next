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

#ifndef QGRAPHICSEVENTGROUP_H
#define QGRAPHICSEVENTGROUP_H

#include "eventgroup.h"
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class QGraphicsEventGroup : public QGraphicsItemGroup
{
public:
    explicit QGraphicsEventGroup();
    ~QGraphicsEventGroup();

    void setPrev(QGraphicsEventGroup * const prev);
    void setNext(QGraphicsEventGroup * const next);
    void setEventGroup(EventGroup * const eventGroup);
    QGraphicsRectItem * rect();
    QGraphicsTextItem * text();
    EventGroup * eventGroup();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setToolTip(const QString &toolTip);
    void setCursor(const QCursor &cursor);
    void setMovable(const bool enabled);
    void moveByX(const qreal dx, const bool moveNext = false);

private:
    QGraphicsEventGroup *_prev, *_next;
    EventGroup *_eventGroup;
    QGraphicsRectItem _rect;
    QGraphicsTextItem _text;
    qreal _corX, _minX, _maxX;

    void init();
};

#endif // QGRAPHICSEVENTGROUP_H
