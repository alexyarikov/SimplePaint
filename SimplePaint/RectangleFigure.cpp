#include "stdafx.h"
#include "RectangleFigure.h"

RectangleFigure::RectangleFigure(QGraphicsItem* parent /*= Q_NULLPTR*/) : QGraphicsRectItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

RectangleFigure::~RectangleFigure()
{
}
