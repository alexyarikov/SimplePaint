#pragma once

#include "BaseFigure.h"

// shape figure class
template <class TShapeParent>
class ShapeFigure : public BaseFigure, public TShapeParent
{
public:
    ShapeFigure(const QPen& pen);
    ~ShapeFigure() override {};

public:
    // add figure on scene
    void add(FigureScene& scene, const QPointF& point) override;

    // draw figure with mouse
    void draw(const QPointF& point) override;
};

// ctor
template <class TShapeParent>
ShapeFigure<TShapeParent>::ShapeFigure(const QPen& pen) : BaseFigure(pen)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    setPen(pen);
}

// add figure on scene
template <class TShapeParent>
void ShapeFigure<TShapeParent>::add(FigureScene& scene, const QPointF& point)
{
    BaseFigure::add(scene, point);
    setRect(point.x(), point.y(), 0, 0);
    scene.addItem(this);
}

// draw figure with mouse
template <class TShapeParent>
void ShapeFigure<TShapeParent>::draw(const QPointF& point)
{
    setRect(QRectF(drawStartPoint(), point).normalized());
}

// rectangle figure class
class RectangleFigure : public ShapeFigure<QGraphicsRectItem>
{
public:
    RectangleFigure(const QPen& pen) : ShapeFigure(pen) {};
    ~RectangleFigure() override {};
};

// ellipse figure class
class EllipseFigure : public ShapeFigure<QGraphicsEllipseItem>
{
public:
    EllipseFigure(const QPen& pen) : ShapeFigure(pen) {};
    ~EllipseFigure() override {};
};
