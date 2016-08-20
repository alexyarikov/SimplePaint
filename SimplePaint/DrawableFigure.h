#pragma once

namespace SimplePaint
{
    class DrawableFigure
    {
    public:
        DrawableFigure(const QPointF& initialPos) : _initialPos(initialPos) {};
        virtual ~DrawableFigure() {};

    public:
        virtual void draw(const QPointF& pos) = 0;

    protected:
        const QPointF& initialPos() const { return _initialPos; }

    private:
        QPointF _initialPos;
    };
}
