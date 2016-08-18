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

void FigureScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    _figure = _figureFactory.create(_figureType, _figurePen);
    _figure->add(*this, mouseEvent->scenePos());

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (_figure)
        _figure->draw(mouseEvent->scenePos());
    else
        QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    _figure = Q_NULLPTR;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
