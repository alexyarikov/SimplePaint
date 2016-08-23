#pragma once

namespace SimplePaint
{
    class SimplePaintModel;
    class FigureScene;

    // view class implementing all UI logic
    class SimplePaintView : public QMainWindow
    {
        Q_OBJECT
        friend class SimplePaintViewTest;

    public:
        SimplePaintView(SimplePaintModel& model);
        ~SimplePaintView();

    private:
        QPointer<QToolButton> _btnFigures;
        QPointer<QGraphicsView> _figuresView;
        QPointer<QAction> _actNew;
        QPointer<QAction> _actExit;
        QPointer<QAction> _actUndo;
        QPointer<QAction> _actRedo;
        QPointer<QAction> _actAbout;
        QPointer<QAction> _actRectangle;
        QPointer<QAction> _actEllipse;
        QPointer<QAction> _actFigureColor;
        QPointer<QAction> _actSelectMode;

        void createActions(QUndoStack* undoStack);
        void createMenu();
        void createToolbar();
        void createStatusBar();
        void createFiguresView(FigureScene* scene);
        QMenu* createFiguresMenu();

    private slots:
        void onAbout();
        void onSetFigureColor();
        void onSetFigureTypeRectangle();
        void onSetFigureTypeEllipse();
        void onToggleSelectMode();

    signals:
        void newDrawing();
        void setFigureTypeRectangle();
        void setFigureTypeEllipse();
        void setFigureColor(const QColor& color);
        void setSelectMode(const bool on);
    };
}
