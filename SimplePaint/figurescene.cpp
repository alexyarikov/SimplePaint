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
    _rectangle->setRect(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), 0, 0);
    _draw_start_point = mouseEvent->scenePos();
    addItem(_rectangle);

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (_rectangle)
        _rectangle->setRect(QRectF(_draw_start_point, mouseEvent->scenePos()).normalized());
    else
        QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (_rectangle)
        _rectangle = Q_NULLPTR;

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
