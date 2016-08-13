#pragma once
#include <QtWidgets/QMainWindow>

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

    void setupUi();
    void createActions();
    void createMenu();
    void createToolbar();
    void createStatusBar();

private slots:
    void newDrawing();
    void about();
    void exit();
    void undo();
    void redo();
};
