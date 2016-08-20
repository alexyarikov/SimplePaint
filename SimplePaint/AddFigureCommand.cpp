#include "stdafx.h"
#include "AddFigureCommand.h"
#include "FigureScene.h"

namespace SimplePaint
{
    AddFigureCommand::AddFigureCommand(FigureScene& scene, QGraphicsItem& figure) :
        _scene(scene),
        _figure(figure)
    {
    }

    void AddFigureCommand::undo()
    {
        _scene.removeItem(&_figure);
    }

    void AddFigureCommand::redo()
    {
        _scene.addItem(&_figure);
        _scene.clearSelection();
    }
}
