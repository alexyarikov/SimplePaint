#include "stdafx.h"
#include "figurescene.h"

FigureScene::FigureScene(QObject* parent) : QGraphicsScene(parent)
{
}

FigureScene::~FigureScene()
{
}

void FigureScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    _draw_start_point = mouseEvent->scenePos();

    switch (_figureType)
    {
        case FigureType::Rectangle:
        {
            addRectangle(_draw_start_point);
            break;
        }
        case FigureType::Ellipse:
        {
            addEllipse(_draw_start_point);
            break;
        }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    bool res = false;

    switch (_figureType)
    {
        case FigureType::Rectangle:
        {
            res = drawRectangle(mouseEvent->scenePos());
            break;
        }
        case FigureType::Ellipse:
        {
            res = drawEllipse(mouseEvent->scenePos());
            break;
        }
    }

    if (res)
        QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    _ellipse = Q_NULLPTR;
    _rectangle = Q_NULLPTR;

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void FigureScene::addRectangle(const QPointF& point)
{
    _rectangle = new QGraphicsRectItem();
    _rectangle->setRect(point.x(), point.y(), 0, 0);
    _rectangle->setBrush(QBrush(_figureColor));
    _rectangle->setPen(QPen(_figureColor));
    addItem(_rectangle);
}

bool FigureScene::drawRectangle(const QPointF& point)
{
    if (_rectangle)
        _rectangle->setRect(QRectF(_draw_start_point, point).normalized());
    return _rectangle != Q_NULLPTR;
}

void FigureScene::addEllipse(const QPointF& point)
{
    _ellipse = new QGraphicsEllipseItem();
    _ellipse->setRect(point.x(), point.y(), 0, 0);
    _ellipse->setBrush(QBrush(_figureColor));
    _ellipse->setPen(QPen(_figureColor));
    addItem(_ellipse);
}

bool FigureScene::drawEllipse(const QPointF& point)
{
    if (_ellipse)
        _ellipse->setRect(QRectF(_draw_start_point, point).normalized());
    return _rectangle != Q_NULLPTR;
}
