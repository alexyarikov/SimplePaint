#include "stdafx.h"
#include "AddFigureCommand.h"
#include "FigureScene.h"

namespace SimplePaint
{
    AddFigureCommand::AddFigureCommand(FigureScene& scene,
                                       QGraphicsItem& figure,
                                       const FigureType figureType,
                                       const QPointF& initialPos) :
        _scene(scene),
        _figure(figure),
        _initialPos(initialPos)
    {
        /*setText(QObject::tr("Add %1 at (%2, %3)")
        .arg(figureName(figureType))
        .arg(pos.x()).arg(pos.y()));*/
    }

    void AddFigureCommand::undo()
    {
        _scene.removeItem(&_figure);
        _scene.update();
    }

    void AddFigureCommand::redo()
    {
        _scene.addItem(&_figure);
        //_figure.setPos(_initialPos);
        //_figure.setPos(0, 0);
        _scene.clearSelection();
        _scene.update();
    }
}
