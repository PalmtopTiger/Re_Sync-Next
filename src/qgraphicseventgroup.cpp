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

#include "qgraphicseventgroup.h"

QGraphicsEventGroup::QGraphicsEventGroup() :
    QGraphicsItemGroup(),
    _prev(nullptr),
    _next(nullptr),
    _eventGroup(nullptr),
    _rect(this),
    _text(this)
{
    this->init();
}

QGraphicsEventGroup::~QGraphicsEventGroup() {}

void QGraphicsEventGroup::setPrev(QGraphicsEventGroup * const prev)
{
    _prev = prev;
}

void QGraphicsEventGroup::setNext(QGraphicsEventGroup * const next)
{
    _next = next;
}

void QGraphicsEventGroup::setEventGroup(EventGroup * const eventGroup)
{
    _eventGroup = eventGroup;
}

QGraphicsRectItem * QGraphicsEventGroup::rect()
{
    return &_rect;
}

QGraphicsTextItem * QGraphicsEventGroup::text()
{
    return &_text;
}

EventGroup * QGraphicsEventGroup::eventGroup()
{
    return _eventGroup;
}

void QGraphicsEventGroup::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _corX = QGraphicsItem::mapToItem(this, event->pos()).x();
    _minX = nullptr != _prev ? _prev->x() + _prev->rect()->rect().width() : 0.0;
    _maxX = (nullptr != _next ? _next->x() : this->scene()->width()) - this->rect()->rect().width();

    QGraphicsItemGroup::mousePressEvent(event);
}

void QGraphicsEventGroup::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static qreal dx;
    dx = qMax(_minX - this->x(), QGraphicsItem::mapToItem(this, event->pos()).x() - _corX);
    if (event->buttons() & Qt::LeftButton)
    {
        this->moveByX(dx, true);
    }
    else
    {
        dx = qMin(_maxX - this->x(), dx);
        this->moveByX(dx, false);
    }
}

void QGraphicsEventGroup::setToolTip(const QString &toolTip)
{
    _rect.setToolTip(toolTip);
    _text.setToolTip(toolTip);
}

void QGraphicsEventGroup::setCursor(const QCursor &cursor)
{
    _rect.setCursor(cursor);
    _text.setCursor(cursor);
}

void QGraphicsEventGroup::setMovable(const bool enabled)
{
    //QGraphicsItem::ItemIsSelectable
    if (enabled) this->setFlags(this->flags() | QGraphicsItem::ItemIsMovable);
    else this->setFlags(this->flags() & ~QGraphicsItem::ItemIsMovable);
}

void QGraphicsEventGroup::moveByX(const qreal dx, const bool moveNext)
{
    this->moveBy(dx, 0.0);
    if (moveNext && nullptr != _next) _next->moveByX(dx, moveNext);
}

void QGraphicsEventGroup::init()
{
    this->addToGroup(&_rect);
    this->addToGroup(&_text);
}
