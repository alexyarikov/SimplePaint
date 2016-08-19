#pragma once

#include "Common.h"

namespace SimplePaint
{
    class MoveFigureCommand : public QUndoCommand
    {
    public:
        MoveFigureCommand(const FigureType figureType, QGraphicsItem* figure, const QPointF& oldPos);
        ~MoveFigureCommand() override;

        void undo() override;
        void redo() override;

    private:
        QGraphicsItem* _figure;
        QPointF _oldPos;
        QPointF _newPos;
    };
}
