#pragma once

#include "Common.h"
#include "FigureFactory.h"

namespace SimplePaint
{
    // figure scene class, implements figures drawing logic
    class FigureScene : public QGraphicsScene
    {
        Q_OBJECT

    public:
        explicit FigureScene(QObject* parent = Q_NULLPTR);
        ~FigureScene() override;

        // set figures drawing parameters
        void setSelectMode(const bool on);
        void setFigureType(const FigureType figureType) { _figureType = figureType;   }
        void setFigureColor(const QColor& color)        { _figurePen.setColor(color); }

    protected:
        // mouse event handlers
        void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

    private:
        FigureType _figureType = FigureType::Rectangle;
        QPen _figurePen;
        FigureFactory _figureFactory;
        bool _selectMode = false;
        QList<QGraphicsItem*> _figures;         // newly created figure to be drawn in mousemove, or selected figures to be moved in mousemove
        QList<QPointF> _movedFiguresOldPos;     // moved figures initial positions

    signals:
        void figureCreated(QGraphicsItem& figure);
        void figuresMoved(QList<QGraphicsItem*>& figures, QList<QPointF>& figuresOldPos);
    };
}
