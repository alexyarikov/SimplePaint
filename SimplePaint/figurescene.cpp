#include "stdafx.h"
#include "FigureScene.h"
#include "ShapeFigure.h"

namespace SimplePaint
{
    FigureScene::FigureScene(QObject* parent) : QGraphicsScene(parent)
    {
        _figurePen.setColor(Qt::black);
        _figurePen.setWidthF(2);

        // register figure types
        _figureFactory.add<RectangleFigure>(FigureType::Rectangle);
        _figureFactory.add<EllipseFigure>(FigureType::Ellipse);
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
            _figure = _figureFactory.create(_figureType, mouseEvent->scenePos(), _figurePen);
            emit figureCreated(*_figure, _figureType, mouseEvent->scenePos());
        }

        QGraphicsScene::mousePressEvent(mouseEvent);
    }

    void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
    {
        if (!_selectMode && _figure)
            //_figure->draw(mouseEvent->scenePos());
            sendEvent(_figure, mouseEvent);
        else
            QGraphicsScene::mouseMoveEvent(mouseEvent);
    }

    void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
    {
        _figure = Q_NULLPTR;
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
    }
}
