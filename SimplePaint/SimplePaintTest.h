#pragma once

class SimplePaintTest : public QObject
{
    Q_OBJECT

public:
    SimplePaintTest(QObject *parent = Q_NULLPTR) {};
    ~SimplePaintTest() {};

private slots:
    void testDrawingRectangle();
    void testDrawingEllipse();
    void testMoveFigure();
};
