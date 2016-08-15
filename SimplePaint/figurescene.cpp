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

    QGraphicsItem* item = Q_NULLPTR;

    switch (_figureType)
    {
        case FigureType::Rectangle:
        {
            item = _rectangle = new QGraphicsRectItem();
            _rectangle->setRect(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), 0, 0);
            _rectangle->setBrush(Qt::red);
            break;
        }
        case FigureType::Ellipse:
        {
            item = _ellipse = new QGraphicsEllipseItem();
            _ellipse->setRect(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), 0, 0);
            _ellipse->setBrush(Qt::red);
            break;
        }
    }

    if (item)
    {
        addItem(item);
        _draw_start_point = mouseEvent->scenePos();
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    switch (_figureType)
    {
        case FigureType::Rectangle:
        {
            _rectangle->setRect(QRectF(_draw_start_point, mouseEvent->scenePos()).normalized());
            break;
        }
        case FigureType::Ellipse:
        {
            _ellipse->setRect(QRectF(_draw_start_point, mouseEvent->scenePos()).normalized());
            break;
        }
        default:
            QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (_rectangle)
        _rectangle = Q_NULLPTR;

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
