#include "stdafx.h"
#include "SimplePaintModel.h"
#include "SimplePaintView.h"
#include "FigureScene.h"
#include "AddFigureCommand.h"
#include "MoveFigureCommand.h"

namespace SimplePaint
{
    SimplePaintModel::SimplePaintModel(QObject* parent/* = Q_NULLPTR*/) :
        QObject(parent),
        _view(Q_NULLPTR)
    {
        _scene = new FigureScene(this);
        _undoStack = new QUndoStack(this);
    }

    SimplePaintModel::~SimplePaintModel()
    {
    }

    void SimplePaintModel::setView(SimplePaintView* view)
    {
        Q_CHECK_PTR(view);

        if (_view) // disconnect all previous view <-> model connections
            QObject::disconnect(_view, 0, this, 0);

        _view = view;

        createConnections();
    }

    void SimplePaintModel::createConnections()
    {
        // create view <---> model connections
        QObject::connect(_view, &SimplePaintView::newDrawing, this, &SimplePaintModel::onNewDrawing);
        QObject::connect(_view, &SimplePaintView::setFigureTypeRectangle, this, &SimplePaintModel::onSetFigureTypeRectangle);
        QObject::connect(_view, &SimplePaintView::setFigureTypeEllipse, this, &SimplePaintModel::onSetFigureTypeEllipse);
        QObject::connect(_view, &SimplePaintView::setFigureColor, this, &SimplePaintModel::onSetFigureColor);
        QObject::connect(_view, &SimplePaintView::setSelectMode, this, &SimplePaintModel::onSetSelectMode);

        // create figure scene <---> model connections
        QObject::connect(_scene, &FigureScene::figureCreated, this, &SimplePaintModel::onFigureCreated);
        QObject::connect(_scene, &FigureScene::figuresMoved, this, &SimplePaintModel::onFiguresMoved);
    }

    void SimplePaintModel::onNewDrawing()
    {
        // clear everything
        _scene->clear();
        _undoStack->clear();
    }

    void SimplePaintModel::onSetFigureTypeRectangle()
    {
        _scene->setFigureType(FigureType::Rectangle);
    }

    void SimplePaintModel::onSetFigureTypeEllipse()
    {
        _scene->setFigureType(FigureType::Ellipse);
    }

    void SimplePaintModel::onSetFigureColor(const QColor& color)
    {
        _scene->setFigureColor(color);
    }

    void SimplePaintModel::onSetSelectMode(const bool on)
    {
        _scene->setSelectMode(on);
    }

    void SimplePaintModel::onFigureCreated(QGraphicsItem& figure)
    {
        _undoStack->push(new AddFigureCommand(*_scene, figure));
    }

    void SimplePaintModel::onFiguresMoved(QList<QGraphicsItem*>& figures, QList<QPointF>& figuresOldPos)
    {
        _undoStack->push(new MoveFigureCommand(figures, figuresOldPos));
    }
}
