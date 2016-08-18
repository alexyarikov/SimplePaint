#include "stdafx.h"
#include "FigureScene.h"
#include "ShapeFigure.h"

FigureScene::FigureScene(QObject* parent) : QGraphicsScene(parent)
{
    _figurePen.setColor(Qt::black);
    _figurePen.setWidthF(2);

    // register figure types
    _figureFactory.add<RectangleFigure>(FigureFactory::Rectangle);
    _figureFactory.add<EllipseFigure>(FigureFactory::Ellipse);
}

FigureScene::~FigureScene()
{
}

void FigureScene::setSelectMode(const bool on)
{
    _selectMode = on;

    for (QGraphicsItem* item : items())
    {
        item->setFlag(QGraphicsItem::ItemIsSelectable, on);
        item->setFlag(QGraphicsItem::ItemIsMovable, on);
    }
}

void FigureScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    // create figure and add it to the scene in draw mode
    // figure under cursor will be selected otherwise
    if (!_selectMode)
    {
        _figure = _figureFactory.create(_figureType, _figurePen);
        _figure->add(*this, mouseEvent->scenePos());
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (!_selectMode && _figure)
        _figure->draw(mouseEvent->scenePos());
    else
        QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    _figure = Q_NULLPTR;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
