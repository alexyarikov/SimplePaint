#pragma once

#include "Common.h"

namespace SimplePaint
{
    class MoveFigureCommand : public QUndoCommand
    {
    public:
        MoveFigureCommand(QList<QGraphicsItem*> figures, QList<QPointF> oldPos);
        ~MoveFigureCommand() override {};

        void undo() override;
        void redo() override;

    private:
        QList<QGraphicsItem*> _figures;
        QList<QPointF> _oldPos;
        QList<QPointF> _newPos;
    };
}
