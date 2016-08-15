#include "stdafx.h"
#include "figurescene.h"

FigureScene::FigureScene(QObject* parent) : QGraphicsScene(parent),
    _rectangle(Q_NULLPTR)
{
}

FigureScene::~FigureScene()
{
}

void FigureScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    Q_CHECK_PTR(mouseEvent);

    if (mouseEvent->button() != Qt::LeftButton)
        return;

    _rectangle = new QGraphicsRectItem();
    _rectangle->setBrush(Qt::red);
    _rectangle->setRect(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), 0, 0);
    addItem(_rectangle);

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    Q_CHECK_PTR(mouseEvent);

    if (_rectangle)
    {
        QPointF pos = mouseEvent->scenePos();           // current mouse position 
        QPointF last_pos = mouseEvent->lastScenePos();  // previous mouse position

        QRectF new_rect;

        if (last_pos.x() > pos.x())
        {
            new_rect.setWidth();
        }

        
        
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
