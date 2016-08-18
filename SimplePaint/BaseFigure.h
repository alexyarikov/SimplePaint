#pragma once

class FigureScene;

class BaseFigure
{
public:
    BaseFigure(const QPen& pen) {};
    virtual ~BaseFigure() {};

public:
    virtual void add(FigureScene& scene, const QPointF& point) { _draw_start_point = point; };
    virtual void draw(const QPointF& point) = 0;

protected:
    const QPointF& drawStartPoint() const { return _draw_start_point; }

private:
    QPointF _draw_start_point;
};
