#pragma once

class FigureScene : public QGraphicsScene
{
    Q_OBJECT

public:
    FigureScene(QObject* parent = Q_NULLPTR);
    ~FigureScene();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;

private:
    QGraphicsRectItem* _rectangle;
};
