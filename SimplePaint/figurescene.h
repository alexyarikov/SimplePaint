#pragma once

class FigureScene : public QGraphicsScene
{
    Q_OBJECT

public:
    FigureScene(QObject* parent = Q_NULLPTR);
    ~FigureScene();

    enum class FigureType { Rectangle, Ellipse };

    void setFigureType(const FigureType figureType) { _figureType = figureType; };
    void setFigureColor(const QColor& color) { _figurePen.setColor(color); }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;

private:
    QGraphicsRectItem* _rectangle = Q_NULLPTR;
    QGraphicsEllipseItem* _ellipse = Q_NULLPTR;
    QPointF _draw_start_point;
    FigureType _figureType = FigureType::Rectangle;
    QPen _figurePen;

    void addRectangle(const QPointF& point);
    bool drawRectangle(const QPointF& point);

    void addEllipse(const QPointF& point);
    bool drawEllipse(const QPointF& point);
};
