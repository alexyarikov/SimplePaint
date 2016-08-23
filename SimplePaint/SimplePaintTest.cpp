#include "stdafx.h"
#include "SimplePaintTest.h"
#include "SimplePaintModel.h"
#include "SimplePaintViewTest.h"

#define doTest(testFunc)                                                            \
    SimplePaint::SimplePaintModel* model = new SimplePaint::SimplePaintModel(this); \
    SimplePaint::SimplePaintViewTest view(*model);                                  \
    view.testFunc();                                                                \

void SimplePaintTest::testDrawingRectangle()
{
    doTest(testDrawRectangle);
}

void SimplePaintTest::testDrawingEllipse()
{
    doTest(testDrawEllipse);
}

void SimplePaintTest::testMoveFigures()
{
    doTest(testMoveFigures);
}

void SimplePaintTest::testUndo()
{
    doTest(testUndo);
}

void SimplePaintTest::testRedo()
{
    doTest(testRedo);
}

void SimplePaintTest::testNewDrawing()
{
    doTest(testNewDrawing);
}
