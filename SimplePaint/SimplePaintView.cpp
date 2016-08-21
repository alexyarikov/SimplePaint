#include "stdafx.h"
#include "SimplePaintView.h"
#include "SimplePaintModel.h"
#include "FigureScene.h"

namespace SimplePaint
{
    SimplePaintView::SimplePaintView(SimplePaintModel& model)
    {
        resize(800, 600);

        createActions(model.undoStack());
        createMenu();
        createToolbar();
        createFiguresView(model.scene());
        createStatusBar();

        model.setView(this);
    }

    SimplePaintView::~SimplePaintView()
    {
    }

    void SimplePaintView::createActions(QUndoStack* undoStack)
    {
        Q_CHECK_PTR(undoStack);

        // new drawing action
        _actNew = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
        _actNew->setShortcuts(QKeySequence::New);
        _actNew->setStatusTip(tr("New drawing"));
        Q_ASSERT(QObject::connect(_actNew, &QAction::triggered, this, &SimplePaintView::newDrawing));

        // exit action
        _actExit = new QAction(QIcon(":/images/exit.png"), tr("E&xit"), this);
        _actExit->setShortcuts(QKeySequence::Quit);
        _actExit->setStatusTip(tr("Exit the application"));
        Q_ASSERT(QObject::connect(_actExit, &QAction::triggered, qApp, &QApplication::closeAllWindows));

        // undo action
        _actUndo = undoStack->createUndoAction(this, tr("&Undo"));
        _actUndo->setIcon(QIcon(":/images/undo.png"));
        _actUndo->setShortcuts(QKeySequence::Undo);
        _actUndo->setStatusTip(tr("Undo"));

        // redo action
        _actRedo = undoStack->createRedoAction(this, tr("&Redo"));
        _actRedo->setIcon(QIcon(":/images/redo.png"));
        _actRedo->setShortcuts(QKeySequence::Redo);
        _actRedo->setStatusTip(tr("Redo"));

        // about application action
        _actAbout = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
        _actAbout->setShortcuts(QKeySequence::HelpContents);
        _actAbout->setStatusTip(tr("About this application"));
        Q_ASSERT(QObject::connect(_actAbout, &QAction::triggered, this, &SimplePaintView::onAbout));

        _actFigureColor = new QAction(QIcon(":/images/color.png"), tr("&Figure color"), this);
        _actFigureColor->setStatusTip(tr("Set figure color"));
        Q_ASSERT(QObject::connect(_actFigureColor, &QAction::triggered, this, &SimplePaintView::onSetFigureColor));

        // draw rectangle
        _actRectangle = new QAction(QIcon(":/images/rectangle.png"), tr("&Rectangle"), this);
        _actRectangle->setStatusTip(tr("Draw rectangle"));
        Q_ASSERT(QObject::connect(_actRectangle, &QAction::triggered, this, &SimplePaintView::onSetFigureTypeRectangle));
        Q_ASSERT(QObject::connect(_actRectangle, &QAction::triggered, this, &SimplePaintView::setFigureTypeRectangle));

        // draw ellipse
        _actEllipse = new QAction(QIcon(":/images/ellipse.png"), tr("&Ellipse"), this);
        _actEllipse->setStatusTip(tr("Draw rectangle"));
        Q_ASSERT(QObject::connect(_actEllipse, &QAction::triggered, this, &SimplePaintView::onSetFigureTypeEllipse));
        Q_ASSERT(QObject::connect(_actEllipse, &QAction::triggered, this, &SimplePaintView::setFigureTypeEllipse));

        // toggle select mode
        _actSelectMode = new QAction(QIcon(":/images/select_mode.png"), tr("&Select mode"), this);
        _actSelectMode->setStatusTip(tr("Select mode"));
        _actSelectMode->setCheckable(true);
        Q_ASSERT(QObject::connect(_actSelectMode, &QAction::triggered, this, &SimplePaintView::onToggleSelectMode));
    }

    void SimplePaintView::createMenu()
    {
        QMenu *mnuFile = menuBar()->addMenu(tr("&File"));
        mnuFile->addAction(_actNew);
        mnuFile->addSeparator();
        mnuFile->addAction(_actExit);

        QMenu* mnuEdit = menuBar()->addMenu(tr("&Edit"));
        mnuEdit->addAction(_actUndo);
        mnuEdit->addAction(_actRedo);

        QMenu *mnuHelp = menuBar()->addMenu(tr("&Help"));
        mnuHelp->addAction(_actAbout);
    }

    void SimplePaintView::createToolbar()
    {
        QToolBar* toolbar = addToolBar(qAppName());
        toolbar->addAction(_actNew);
        toolbar->addSeparator();

        // choose figure color
        toolbar->addAction(_actFigureColor);
        toolbar->addSeparator();

        // toggle select mode
        toolbar->addAction(_actSelectMode);
        toolbar->addSeparator();

        // choose figure type
        _btnFigures = new QToolButton();
        _btnFigures->setPopupMode(QToolButton::InstantPopup);
        _btnFigures->setMenu(createFiguresMenu());
        _btnFigures->setDefaultAction(_actRectangle);
        toolbar->addWidget(_btnFigures);
        toolbar->addSeparator();

        // undo/redo
        toolbar->addAction(_actUndo);
        toolbar->addAction(_actRedo);

        // about
        toolbar->addSeparator();
        toolbar->addAction(_actAbout);
    }

    void SimplePaintView::createStatusBar()
    {
        statusBar()->showMessage(tr("Ready"));
    }

    void SimplePaintView::createFiguresView(FigureScene* scene)
    {
        QHBoxLayout* layout = new QHBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);

        _figuresView = new QGraphicsView(scene);
        layout->addWidget(_figuresView);

        QWidget* central_widget = new QWidget();
        central_widget->setLayout(layout);
        central_widget->setCursor(Qt::CrossCursor);
        setCentralWidget(central_widget);
    }

    QMenu* SimplePaintView::createFiguresMenu()
    {
        QMenu* menu = new QMenu(this);
        menu->addAction(_actRectangle);
        menu->addAction(_actEllipse);
        return menu;
    }

    void SimplePaintView::onAbout()
    {
        QMessageBox::about(Q_NULLPTR, "About " + qAppName(), "Simple graphical editor for drawing rectangles and ellipses with mouse and move them. Undo/redo operations are supported.");
    }

    void SimplePaintView::onSetFigureTypeRectangle()
    {
        _btnFigures->setDefaultAction(_actRectangle);
    }

    void SimplePaintView::onSetFigureTypeEllipse()
    {
        _btnFigures->setDefaultAction(_actEllipse);
    }

    void SimplePaintView::onSetFigureColor()
    {
        // get figure color from standard color selection dialog, inform the world about this
        const QColor color = QColorDialog::getColor(Qt::black, this, "Select figure color");
        if (color.isValid())
            emit setFigureColor(color);
    }

    void SimplePaintView::onToggleSelectMode()
    {
        bool on = _actSelectMode->isChecked();
        _figuresView->setCursor(on ? Qt::OpenHandCursor : Qt::CrossCursor);
        emit setSelectMode(on);
    }
}
