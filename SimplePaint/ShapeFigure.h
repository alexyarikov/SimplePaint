#pragma once

#include "DrawableFigure.h"

namespace SimplePaint
{
    template <class GraphicsItemClass>
    class ShapeFigure : public GraphicsItemClass, public DrawableFigure
    {
    public:
        ShapeFigure(const QPointF& initialPos, QPen& pen) : DrawableFigure(initialPos)
        {
            setPen(pen);
        };
        ~ShapeFigure() override {};

    protected:
        void draw(const QPointF& pos) override
        {
            setRect(QRectF(initialPos(), pos).normalized());
        }
    };

    // rectangle figure class
    class RectangleFigure : public ShapeFigure<QGraphicsRectItem>
    {
    public:
        RectangleFigure(const QPointF& initialPos, QPen& pen) : ShapeFigure(initialPos, pen) {};
        ~RectangleFigure() override {};
    };

    // ellipse figure class
    class EllipseFigure : public ShapeFigure<QGraphicsEllipseItem>
    {
    public:
        EllipseFigure(const QPointF& initialPos, QPen& pen) : ShapeFigure(initialPos, pen) {};
        ~EllipseFigure() override {};
    };
}
