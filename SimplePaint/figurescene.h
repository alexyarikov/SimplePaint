#pragma once

#include "Common.h"
#include "FigureFactory.h"

namespace SimplePaint
{
    class FigureScene : public QGraphicsScene
    {
        Q_OBJECT

    public:
        FigureScene(QObject* parent = Q_NULLPTR);
        ~FigureScene();

        void setSelectMode(const bool on);
        void setFigureType(const FigureType figureType) { _figureType = figureType;   }
        void setFigureColor(const QColor& color)        { _figurePen.setColor(color); }

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

    private:
        FigureType _figureType = FigureType::Rectangle;
        QPen _figurePen;
        FigureFactory _figureFactory;
        bool _selectMode = false;
        QList<QGraphicsItem*> _figures;
        QList<QPointF> _movedFiguresOldPos;

    signals:
        void figureCreated(QGraphicsItem& figure);
        void figuresMoved(QList<QGraphicsItem*>& figures, QList<QPointF>& figuresOldPos);
    };
}
