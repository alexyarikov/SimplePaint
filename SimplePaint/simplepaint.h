#pragma once

#include "FigureScene.h"

namespace SimplePaint
{
    class SimplePaint : public QMainWindow
    {
        Q_OBJECT

    public:
        SimplePaint(QWidget* parent = Q_NULLPTR);
        ~SimplePaint();

    private:
        QPointer<QAction> _actNew;
        QPointer<QAction> _actExit;
        QPointer<QAction> _actUndo;
        QPointer<QAction> _actRedo;
        QPointer<QAction> _actAbout;
        QPointer<QAction> _actRectangle;
        QPointer<QAction> _actEllipse;
        QPointer<QAction> _actFigureColor;
        QPointer<QAction> _actSelectMode;
        QPointer<QToolButton> _btnFigures;
        QPointer<QGraphicsView> _view;
        QPointer<FigureScene> _scene;
        QPointer<QUndoStack> _undoStack;

        void setupUi();
        void createActions();
        void createMenu();
        void createToolbar();
        void createStatusBar();
        void createView();
        void createConnections();
        QMenu* createFiguresMenu();

        private slots:
        void newDrawing();
        void about();
        void exit();
        void drawRectangle();
        void drawEllipse();
        void setFigureColor();
        void toggleSelectMode();

    private slots:
        void figureCreated(QGraphicsItem& figure);
        void figuresMoved(QList<QGraphicsItem*>& figures, QList<QPointF>& figuresOldPos);
    };
}
