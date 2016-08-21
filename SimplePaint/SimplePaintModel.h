#pragma once

namespace SimplePaint
{
    class FigureScene;
    class SimplePaintView;

    // application "model" class, intended to implement all business logic, separate data and logic from view
    class SimplePaintModel : public QObject
    {
        Q_OBJECT

    public:
        explicit SimplePaintModel(QObject* parent = Q_NULLPTR);
        ~SimplePaintModel();

        // scene and undo stack getters
        FigureScene* scene() const { return _scene; }
        QUndoStack* undoStack() const { return _undoStack; }

        // set view to this model
        void setView(SimplePaintView* view);

    private:
        SimplePaintView* _view;
        FigureScene* _scene;
        QPointer<QUndoStack> _undoStack;

        // create qobject connections
        void createConnections();

    private slots:
        void onNewDrawing();
        void onSetFigureTypeRectangle();
        void onSetFigureTypeEllipse();
        void onSetFigureColor(const QColor& color);
        void onSetSelectMode(const bool on);
        void onFigureCreated(QGraphicsItem& figure);
        void onFiguresMoved(QList<QGraphicsItem*>& figures, QList<QPointF>& figuresOldPos);
    };
}
