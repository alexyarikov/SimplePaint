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

        QGraphicsScene::mousePressEvent(mouseEvent);

        _figures.clear();
        _movedFiguresOldPos.clear();

        // create figure and add it to the scene in draw mode
        if (!_selectMode)
        {
            _figures.push_back(_figureFactory.create(_figureType, mouseEvent->scenePos(), _figurePen));
            emit figureCreated(*_figures[0]);
        }
        else
        {
            // save initial positions of figures to be moved
            _figures = selectedItems();
            for (QGraphicsItem* figure : _figures)
                _movedFiguresOldPos.push_back(figure->pos());
        }
    }

    void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
    {
        if (!_selectMode && !_figures.isEmpty())
        {
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

        if (_selectMode && !_figures.isEmpty() && !_movedFiguresOldPos.isEmpty() && _figures[0]->pos() != _movedFiguresOldPos[0])
            emit figuresMoved(_figures, _movedFiguresOldPos);

        _figures.clear();
        _movedFiguresOldPos.clear();

        QGraphicsScene::mouseReleaseEvent(mouseEvent);
    }
}
