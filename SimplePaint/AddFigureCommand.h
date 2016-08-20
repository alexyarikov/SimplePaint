#pragma once

#include "Common.h"

namespace SimplePaint
{
    class FigureScene;

    class AddFigureCommand : public QUndoCommand
    {
    public:
        AddFigureCommand(FigureScene& scene, QGraphicsItem& figure);
        ~AddFigureCommand() override {};

        void undo() override;
        void redo() override;

    private:
        FigureScene& _scene;
        QGraphicsItem& _figure;
    };
}
