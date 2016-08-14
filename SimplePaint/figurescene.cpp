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
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    _rectangle = new QGraphicsRectItem();
    _rectangle->setBrush(Qt::red);
    _rectangle->setPos(mouseEvent->scenePos());
    addItem(_rectangle);

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (_rectangle)
    {
        QRectF rect = _rectangle->rect();
        //TODO...
        _rectangle->setRect(rect);
    }

    //QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
