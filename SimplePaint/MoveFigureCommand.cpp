#include "stdafx.h"
#include "MoveFigureCommand.h"

namespace SimplePaint
{
    MoveFigureCommand::MoveFigureCommand(const FigureType figureType, QGraphicsItem* figure, const QPointF& oldPos) :
        _figure(figure),
        _oldPos(oldPos)
    {
        _newPos = figure->pos();
        /*setText(QObject::tr("Move %1 from (%2, %3) to (%3, %4)")
                .arg(figureName(figureType))
                .arg(oldPos.x()).arg(oldPos.y())
                .arg(newPos.x()).arg(newPos.y()));*/
    }

    MoveFigureCommand::~MoveFigureCommand()
    {
        _figure = Q_NULLPTR;
    }

    void MoveFigureCommand::undo()
    {
        _figure->setPos(_oldPos);
        _figure->scene()->update();
    }

    void MoveFigureCommand::redo()
    {
        _figure->setPos(_newPos);
    }
}
