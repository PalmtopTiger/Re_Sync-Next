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
