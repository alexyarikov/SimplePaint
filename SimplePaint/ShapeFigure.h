#pragma once

namespace SimplePaint
{
    template <class TParentClass>
    class ShapeFigure : public TParentClass
    {
    public:
        ShapeFigure(const QPointF& initial_pos, QPen& pen) : _initial_pos(initial_pos)
        {
            setPen(pen);
        };
        ~ShapeFigure() override {};

    protected:
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override
        {
            setRect(QRectF(_initial_pos, event->scenePos()).normalized());
        }

    private:
        QPointF _initial_pos;
    };

    // rectangle figure class
    class RectangleFigure : public ShapeFigure<QGraphicsRectItem>
    {
    public:
        RectangleFigure(const QPointF& initial_pos, QPen& pen) : ShapeFigure(initial_pos, pen) {};
        ~RectangleFigure() override {};
    };

    // ellipse figure class
    class EllipseFigure : public ShapeFigure<QGraphicsEllipseItem>
    {
    public:
        EllipseFigure(const QPointF& initial_pos, QPen& pen) : ShapeFigure(initial_pos, pen) {};
        ~EllipseFigure() override {};
    };
}
