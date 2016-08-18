#include "stdafx.h"
#include "simplepaint.h"
#include "figurescene.h"

SimplePaint::SimplePaint(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
}

SimplePaint::~SimplePaint()
{
}

void SimplePaint::setupUi()
{
    resize(800, 600);

    createActions();
    createMenu();
    createToolbar();
    createView();
    createStatusBar();
}

void SimplePaint::createActions()
{
    // new drawing action
    _actNew = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    _actNew->setShortcuts(QKeySequence::New);
    _actNew->setStatusTip(tr("New drawing"));
    connect(_actNew, &QAction::triggered, this, &SimplePaint::newDrawing);

    // exit action
    _actExit = new QAction(QIcon(":/images/exit.png"), tr("E&xit"), this);
    _actExit->setShortcuts(QKeySequence::Quit);
    _actExit->setStatusTip(tr("Exit the application"));
    connect(_actExit, &QAction::triggered, this, &SimplePaint::exit);

    // undo action
    _actUndo = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    _actUndo->setShortcuts(QKeySequence::Undo);
    _actUndo->setStatusTip(tr("Undo"));
    connect(_actUndo, &QAction::triggered, this, &SimplePaint::undo);

    // redo action
    _actRedo = new QAction(QIcon(":/images/redo.png"), tr("&Redo"), this);
    _actRedo->setShortcuts(QKeySequence::Redo);
    _actRedo->setStatusTip(tr("Redo"));
    connect(_actRedo, &QAction::triggered, this, &SimplePaint::redo);

    // about application action
    _actAbout = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
    _actAbout->setShortcuts(QKeySequence::HelpContents);
    _actAbout->setStatusTip(tr("About this application"));
    connect(_actAbout, &QAction::triggered, this, &SimplePaint::about);

    _actFigureColor = new QAction(QIcon(":/images/color.png"), tr("&Figure color"), this);
    _actFigureColor->setStatusTip(tr("Set figure color"));
    connect(_actFigureColor, &QAction::triggered, this, &SimplePaint::setFigureColor);

    // draw rectangle
    _actRectangle = new QAction(QIcon(":/images/rectangle.png"), tr("&Rectangle"), this);
    _actRectangle->setStatusTip(tr("Draw rectangle"));
    connect(_actRectangle, &QAction::triggered, this, &SimplePaint::drawRectangle);

    // draw ellipse
    _actEllipse = new QAction(QIcon(":/images/ellipse.png"), tr("&Ellipse"), this);
    _actEllipse->setStatusTip(tr("Draw rectangle"));
    connect(_actEllipse, &QAction::triggered, this, &SimplePaint::drawEllipse);
}

void SimplePaint::createMenu()
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

void SimplePaint::createToolbar()
{
    QToolBar* toolbar = addToolBar(qAppName());
    toolbar->addAction(_actNew);
    toolbar->addSeparator();

    // choose figure color
    toolbar->addAction(_actFigureColor);
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

void SimplePaint::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void SimplePaint::createView()
{
    _scene = new FigureScene(this);
    _scene->setSceneRect(QRectF(0, 0, 5000, 5000));

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    QGraphicsView* view = new QGraphicsView(_scene);
    layout->addWidget(view);

    QWidget* central_widget = new QWidget();
    central_widget->setLayout(layout);
    central_widget->setCursor(Qt::CrossCursor);
    setCentralWidget(central_widget);
}

QMenu* SimplePaint::createFiguresMenu()
{
    QMenu* mnuFigures = new QMenu(this);
    mnuFigures->addAction(_actRectangle);
    mnuFigures->addAction(_actEllipse);
    return mnuFigures;
}

void SimplePaint::newDrawing()
{
    _scene->clear();
}

void SimplePaint::about()
{
    QMessageBox::about(Q_NULLPTR, qAppName(), "");
}

void SimplePaint::exit()
{
    qApp->closeAllWindows();
}

void SimplePaint::undo()
{
    QMessageBox::information(Q_NULLPTR, qAppName(), "Not implemented yet");
}

void SimplePaint::redo()
{
    QMessageBox::information(Q_NULLPTR, qAppName(), "Not implemented yet");
}

void SimplePaint::drawRectangle()
{
    _scene->setFigureType(FigureFactory::FigureType::Rectangle);
    _btnFigures->setDefaultAction(_actRectangle);
}

void SimplePaint::drawEllipse()
{
    _scene->setFigureType(FigureFactory::FigureType::Ellipse);
    _btnFigures->setDefaultAction(_actEllipse);
}

void SimplePaint::setFigureColor()
{
    const QColor color = QColorDialog::getColor(Qt::black, this, "Select color");
    if (color.isValid())
        _scene->setFigureColor(color);
}
