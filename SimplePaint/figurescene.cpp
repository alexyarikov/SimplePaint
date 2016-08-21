#include "stdafx.h"
#include "FigureScene.h"
#include "ShapeFigure.h"

namespace SimplePaint
{
    FigureScene::FigureScene(QObject* parent) : QGraphicsScene(parent)
    {
        setSceneRect(0, 0, 5000, 5000);

        // setup figures pen
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
        // there are two modes - figure selection mode (on == true) to select figures
        // and draw mode (on == false)
        // set current mode and change figures corresponding flags
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

        _figures.clear();
        _movedFiguresOldPos.clear();

        if (!_selectMode)
        {
            // draw mode, create figure and inform the world about it
            _figures.push_back(_figureFactory.create(_figureType, mouseEvent->scenePos(), _figurePen));
            emit figureCreated(*_figures[0]);
        }
        else
        {
            // select mode, save initial positions of figures to be moved
            _figures = selectedItems();
            for (QGraphicsItem* figure : _figures)
                _movedFiguresOldPos.push_back(figure->pos());
        }

        QGraphicsScene::mousePressEvent(mouseEvent);
    }

    void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
    {
        if (!_selectMode && !_figures.isEmpty())
        {
            // draw mode, only the DrawableFigure-subclass knows how to draw itself with mouse, do it here
            DrawableFigure* drawableFigure = dynamic_cast<DrawableFigure*>(_figures[0]);
            if (drawableFigure)
                drawableFigure->draw(mouseEvent->scenePos());
        }
        else
            QGraphicsScene::mouseMoveEvent(mouseEvent);
    }

    void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
    {
        if (mouseEvent->button() != Qt::LeftButton)
            return;

        // selection mode, if figure(-s) were really moved, inform the world about it
        if (_selectMode && !_figures.isEmpty() && !_movedFiguresOldPos.isEmpty() && _figures[0]->pos() != _movedFiguresOldPos[0])
            emit figuresMoved(_figures, _movedFiguresOldPos);

        _figures.clear();
        _movedFiguresOldPos.clear();

        QGraphicsScene::mouseReleaseEvent(mouseEvent);
    }
}
