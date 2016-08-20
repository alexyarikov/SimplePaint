#include "stdafx.h"
#include "MoveFigureCommand.h"

namespace SimplePaint
{
    MoveFigureCommand::MoveFigureCommand(QList<QGraphicsItem*> figures, QList<QPointF> oldPos) :
        _figures(figures),
        _oldPos(oldPos)
    {
        Q_ASSERT(_figures.size() == _oldPos.size());
        for (QGraphicsItem* figure : figures)
            _newPos.push_back(figure->pos());
    }

    void MoveFigureCommand::undo()
    {
        for (int i = 0; i < _figures.size(); i++)
            _figures[i]->setPos(_oldPos[i]);
    }

    void MoveFigureCommand::redo()
    {
        for (int i = 0; i < _figures.size(); i++)
            _figures[i]->setPos(_newPos[i]);
    }
}
