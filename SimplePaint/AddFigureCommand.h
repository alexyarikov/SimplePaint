#pragma once

#include "Common.h"

namespace SimplePaint
{
    class FigureScene;

    class AddFigureCommand : public QUndoCommand
    {
    public:
        AddFigureCommand(FigureScene& scene,
                         QGraphicsItem& figure,
                         const FigureType figureType,
                         const QPointF& initialPos);
        ~AddFigureCommand() override {};

        void undo() override;
        void redo() override;

    private:
        FigureScene& _scene;
        QGraphicsItem& _figure;
        QPointF _initialPos;
    };
}
