#pragma once
#include "SimplePaintView.h"
#include "Common.h"

namespace SimplePaint
{
    class SimplePaintModel;

    class SimplePaintViewTest : public SimplePaintView
    {
        Q_OBJECT

    public:
        SimplePaintViewTest(SimplePaintModel& model) : SimplePaintView(model) {};
        ~SimplePaintViewTest() override {};

        void testDrawRectangle();
        void testDrawEllipse();
        void testMoveFigures();
        void testUndo();
        void testRedo();
        void testNewDrawing();

    private:
        template<class TGraphicsItem> void testDrawShapeFigure(const FigureType figureType, const QColor& figureColor, const QRect& figureRect);

        // auxiliary functions
        template<class TGraphicsItem> TGraphicsItem* drawShapeFigure(const FigureType figureType, const QColor& figureColor, const QRect& figureRect);
        void moveSelectedFigures(const QPoint& posFrom, const QPoint& posTo);
        bool checkFigureSize(const QGraphicsItem& item, const QRect& expectedSize) const;
    };
}
