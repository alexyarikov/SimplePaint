#include "stdafx.h"
#include "MoveFigureCommand.h"

namespace SimplePaint
{
    MoveFigureCommand::MoveFigureCommand(QList<QGraphicsItem*> figures, QList<QPointF> oldPos) :
        _figures(figures),
        _oldPos(oldPos)
    {
        Q_ASSERT(_figures.size() == _oldPos.size());

        // save figures current positions to use in undo/redo logic
        for (QGraphicsItem* figure : figures)
            _newPos.push_back(figure->pos());
    }

    void MoveFigureCommand::undo()
    {
        // move figures to their old positions
        for (int i = 0; i < _figures.size(); i++)
            _figures[i]->setPos(_oldPos[i]);

        if (!_figures.isEmpty())
            _figures[0]->update();
    }

    void MoveFigureCommand::redo()
    {
        // move figures to their new positions
        for (int i = 0; i < _figures.size(); i++)
            _figures[i]->setPos(_newPos[i]);

        if (!_figures.isEmpty())
            _figures[0]->update();
    }
}
