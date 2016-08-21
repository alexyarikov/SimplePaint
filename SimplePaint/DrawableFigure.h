#pragma once

namespace SimplePaint
{
    // abstract class for all mouse-drawable figures
    // override draw virtual method in descendants to implement figure mouse drawing
    class DrawableFigure
    {
    public:
        DrawableFigure(const QPointF& initialPos) : _initialPos(initialPos) {};
        virtual ~DrawableFigure() {};

    public:
        // figure mouse draw interface method
        virtual void draw(const QPointF& pos) = 0;

    protected:
        // initial mouse position getter
        const QPointF& initialPos() const { return _initialPos; }

    private:
        // initial mouse position while creating a figure
        QPointF _initialPos;
    };
}
