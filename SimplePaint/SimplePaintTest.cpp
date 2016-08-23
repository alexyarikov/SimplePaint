#include "stdafx.h"
#include "SimplePaintTest.h"
#include "SimplePaintModel.h"
#include "SimplePaintViewTest.h"

void SimplePaintTest::testDrawingRectangle()
{
    SimplePaint::SimplePaintModel* model = new SimplePaint::SimplePaintModel(this);
    SimplePaint::SimplePaintViewTest view(*model);
    view.testDrawRectangle();
}

void SimplePaintTest::testDrawingEllipse()
{
    SimplePaint::SimplePaintModel* model = new SimplePaint::SimplePaintModel(this);
    SimplePaint::SimplePaintViewTest view(*model);
    view.testDrawEllipse();
}

void SimplePaintTest::testMoveFigure()
{
    SimplePaint::SimplePaintModel* model = new SimplePaint::SimplePaintModel(this);
    SimplePaint::SimplePaintViewTest view(*model);
    view.testMoveFigure();
}
