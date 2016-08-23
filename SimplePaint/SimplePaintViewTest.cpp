#include "stdafx.h"
#include "SimplePaintViewTest.h"

namespace SimplePaint
{
    // test drawing rectangle
    void SimplePaintViewTest::testDrawRectangle()
    {
        testDrawShapeFigure<QGraphicsRectItem>(FigureType::Rectangle, Qt::blue, QRect(100, 100, 300, 300));
    }

    // test drawing ellipse
    void SimplePaintViewTest::testDrawEllipse()
    {
        testDrawShapeFigure<QGraphicsEllipseItem>(FigureType::Ellipse, Qt::green, QRect(200, 200, 400, 400));
    }

    // test moving figures
    void SimplePaintViewTest::testMoveFigures()
    {
        // create 3 rectangles
        QPoint topLeft1(100, 100), topLeft2(100, 200), topLeft3(100, 300);
        QSize size(300, 100);

        QGraphicsRectItem* item1 = drawShapeFigure<QGraphicsRectItem>(FigureType::Rectangle, Qt::black, QRect(topLeft1, size));
        QGraphicsRectItem* item2 = drawShapeFigure<QGraphicsRectItem>(FigureType::Rectangle, Qt::red, QRect(topLeft2, size));
        QGraphicsRectItem* item3 = drawShapeFigure<QGraphicsRectItem>(FigureType::Rectangle, Qt::yellow, QRect(topLeft3, size));
        QVERIFY(item1 && item2 && item3);

        // turn select mode on and select all figures
        emit setSelectMode(true);
        item1->setSelected(true);
        item2->setSelected(true);
        item3->setSelected(true);

        // move them in south-east direction
        QPoint moveOffset(300, 500);
        QPoint topLeftNew1 = topLeft1 + moveOffset;
        QPoint topLeftNew2 = topLeft2 + moveOffset;
        QPoint topLeftNew3 = topLeft3 + moveOffset;

        moveSelectedFigures(topLeft1, topLeftNew1);

        // check figures new coordinates
        QVERIFY(checkFigureSize(*item1, QRect(topLeftNew1, size)));
        QVERIFY(checkFigureSize(*item2, QRect(topLeftNew2, size)));
        QVERIFY(checkFigureSize(*item3, QRect(topLeftNew3, size)));
    }

    // test undo
    void SimplePaintViewTest::testUndo()
    {
        // draw two figures
        QPoint topLeft1(100, 100), topLeft2(100, 200);
        QSize size(300, 100);

        QGraphicsEllipseItem* item1 = drawShapeFigure<QGraphicsEllipseItem>(FigureType::Ellipse, Qt::gray, QRect(topLeft1, size));
        QGraphicsEllipseItem* item2 = drawShapeFigure<QGraphicsEllipseItem>(FigureType::Ellipse, Qt::magenta, QRect(topLeft2, size));
        QVERIFY(item1 && item2);

        // turn select mode on and select all figures
        emit setSelectMode(true);
        item1->setSelected(true);
        item2->setSelected(true);

        // move them
        QPoint posFrom = QRect(topLeft1, size).center();
        QPoint posTo = QRect(topLeft1 + QPoint(200, 100), size).center();
        moveSelectedFigures(posFrom, posTo);

        // undo move, check figures coordinates
        _actUndo->activate(QAction::Trigger);
        QVERIFY(checkFigureSize(*_figuresView->scene()->items().at(0), QRect(topLeft2, size)));
        QVERIFY(checkFigureSize(*_figuresView->scene()->items().at(1), QRect(topLeft1, size)));

        // undo second figure creation, check figures number and coordinates
        _actUndo->activate(QAction::Trigger);
        QCOMPARE(_figuresView->scene()->items().size(), 1);
        QVERIFY(checkFigureSize(*_figuresView->scene()->items().at(0), QRect(topLeft1, size)));

        // undo first figure creation, check figures number
        _actUndo->activate(QAction::Trigger);
        QVERIFY(_figuresView->scene()->items().isEmpty());
    }

    // test redo
    void SimplePaintViewTest::testRedo()
    {
        // draw two figures
        QPoint topLeft1(100, 100), topLeft2(100, 200);
        QSize size(300, 100);

        QGraphicsRectItem* item1 = drawShapeFigure<QGraphicsRectItem>(FigureType::Rectangle, Qt::cyan, QRect(topLeft1, size));
        QGraphicsRectItem* item2 = drawShapeFigure<QGraphicsRectItem>(FigureType::Rectangle, Qt::white, QRect(topLeft2, size));
        QVERIFY(item1 && item2);

        // turn select mode on and select all figures
        emit setSelectMode(true);
        item1->setSelected(true);
        item2->setSelected(true);

        // move them
        QPoint moveOffset(-100, -200);
        moveSelectedFigures(topLeft1, topLeft1 + moveOffset);

        // undo all, then redo, check figures number and their coordinates
        _actUndo->activate(QAction::Trigger);
        _actUndo->activate(QAction::Trigger);
        _actUndo->activate(QAction::Trigger);
        _actRedo->activate(QAction::Trigger);
        QCOMPARE(_figuresView->scene()->items().size(), 1);
        QVERIFY(checkFigureSize(*_figuresView->scene()->items().at(0), QRect(topLeft1, size)));

        // redo, check figures number and their coordinates
        _actRedo->activate(QAction::Trigger);
        QCOMPARE(_figuresView->scene()->items().size(), 2);
        QVERIFY(checkFigureSize(*_figuresView->scene()->items().at(0), QRect(topLeft2, size)));
        QVERIFY(checkFigureSize(*_figuresView->scene()->items().at(1), QRect(topLeft1, size)));

        // redo, check figures number and their coordinates
        _actRedo->activate(QAction::Trigger);
        QCOMPARE(_figuresView->scene()->items().size(), 2);
        QVERIFY(checkFigureSize(*_figuresView->scene()->items().at(0), QRect(topLeft2 + moveOffset, size)));
        QVERIFY(checkFigureSize(*_figuresView->scene()->items().at(1), QRect(topLeft1 + moveOffset, size)));
    }

    // test clear
    void SimplePaintViewTest::testNewDrawing()
    {
        // draw figure
        QPoint topLeft(100, 100);
        QSize size(300, 100);

        QGraphicsRectItem* item = drawShapeFigure<QGraphicsRectItem>(FigureType::Rectangle, Qt::blue, QRect(topLeft, size));
        moveSelectedFigures(topLeft, topLeft + QPoint(-100, 100));

        // turn select mode on and select figure
        emit setSelectMode(true);
        item->setSelected(true);

        // new drawing (clear everything), check figures number
        emit newDrawing();
        QVERIFY(_figuresView->scene()->items().isEmpty());
    }

    // test drawing shaped figure
    template<class TGraphicsItem> void SimplePaintViewTest::testDrawShapeFigure(const FigureType figureType, const QColor& figureColor, const QRect& figureRect)
    {
        TGraphicsItem* item = drawShapeFigure<TGraphicsItem>(figureType, figureColor, figureRect);
        QVERIFY(item);
        QVERIFY(checkFigureSize(*item, figureRect));
        QCOMPARE(item->pen().color(), figureColor);
    }

    // draw shaped (rectangle-based) figure
    template<class TGraphicsItem> TGraphicsItem* SimplePaintViewTest::drawShapeFigure(const FigureType figureType, const QColor& figureColor, const QRect& figureRect)
    {
        // set figure type
        switch (figureType)
        {
            case Rectangle:
                emit setFigureTypeRectangle();
                break;
            case Ellipse:
                emit setFigureTypeEllipse();
                break;
            default:
                return Q_NULLPTR;
        }

        // set figure color
        emit setFigureColor(figureColor);

        // emulate figure mouse drawing
        QWidget* w = _figuresView->viewport();

        QPoint topLeft = figureRect.topLeft();
        QPoint bottomRight(figureRect.x() + figureRect.width(), figureRect.y() + figureRect.height());

        QTest::mouseMove(w, topLeft);
        QTest::mousePress(w, Qt::LeftButton, Qt::KeyboardModifiers(), topLeft);

        QMouseEvent* event = new QMouseEvent(QEvent::MouseMove,
                                             bottomRight,
                                             w->mapToGlobal(bottomRight),
                                             Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::postEvent(w, event);
        QTest::qWait(10);

        QTest::mouseRelease(w, Qt::LeftButton, Qt::KeyboardModifiers(), bottomRight);

        // check newly created figure coordinates
        QGraphicsScene* scene = _figuresView->scene();
        if (!scene)
            return Q_NULLPTR;

        QList<QGraphicsItem*> items = scene->items();
        if (items.isEmpty())
            return Q_NULLPTR;

        return qgraphicsitem_cast<TGraphicsItem*>(items.at(0));
    }

    // move selected figures to the specified point
    void SimplePaintViewTest::moveSelectedFigures(const QPoint& posFrom, const QPoint& posTo)
    {
        // emulate figure mouse moving
        QWidget* w = _figuresView->viewport();

        QTest::mouseMove(w, posFrom);
        QTest::mousePress(w, Qt::LeftButton, Qt::KeyboardModifiers(), posFrom);

        QMouseEvent* event = new QMouseEvent(QEvent::MouseMove,
                                             posTo,
                                             w->mapToGlobal(posTo),
                                             Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::postEvent(w, event);
        QTest::qWait(10);

        QTest::mouseRelease(w, Qt::LeftButton, Qt::KeyboardModifiers(), posTo);
    }

    bool SimplePaintViewTest::checkFigureSize(const QGraphicsItem& item, const QRect& expectedSize) const
    {
        int margin = 0 - SimplePaint::figurePenWidth / 2;

        QRectF ttt = item.sceneBoundingRect();

        QRectF actualSceneSize = item.sceneBoundingRect().marginsAdded(QMargins(margin, margin, margin, margin));
        QRectF expectedSceneSize = _figuresView->mapToScene(expectedSize).boundingRect();
        return actualSceneSize == expectedSceneSize;
    }
}
