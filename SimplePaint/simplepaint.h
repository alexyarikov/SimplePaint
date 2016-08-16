#pragma once
#include <QtWidgets/QMainWindow>

class FigureScene;

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
    QPointer<QToolButton> _btnFigures;
    QPointer<QComboBox> _cmbColors;
    QPointer<FigureScene> _scene;

    void setupUi();
    void createActions();
    void createMenu();
    void createToolbar();
    void createStatusBar();
    void createView();

private slots:
    void newDrawing();
    void about();
    void exit();
    void undo();
    void redo();
    void drawRectangle();
    void drawEllipse();
    void colorChanged(int index);
};
