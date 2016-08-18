#pragma once

#include "FigureFactory.h"

class BaseFigure;

class FigureScene : public QGraphicsScene
{
    Q_OBJECT

public:
    FigureScene(QObject* parent = Q_NULLPTR);
    ~FigureScene();

    void setFigureType(const FigureFactory::FigureType figureType) { _figureType = figureType; };
    void setFigureColor(const QColor& color) { _figurePen.setColor(color); }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;

private:
    BaseFigure* _figure = Q_NULLPTR;
    FigureFactory::FigureType _figureType = FigureFactory::Rectangle;
    QPen _figurePen;
    FigureFactory _figureFactory;
};
