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

void SimplePaint::createView()
{
    _scene = new FigureScene(this);
    _scene->setSceneRect(QRectF(0, 0, 5000, 5000));

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    QGraphicsView* view = new QGraphicsView(_scene);
    view->setBackgroundBrush(QBrush(Qt::white));
    layout->addWidget(view);

    QWidget* central_widget = new QWidget();
    central_widget->setLayout(layout);
    central_widget->setCursor(Qt::CrossCursor);
    setCentralWidget(central_widget);
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
    QMenu* mnuFigures = new QMenu(this);
    mnuFigures->addAction(_actRectangle);
    mnuFigures->addAction(_actEllipse);

    QToolBar *toolbar = addToolBar(tr("Simple paint"));
    toolbar->addAction(_actNew);
    toolbar->addSeparator();

    // choose figure color
    _cmbColors = new QComboBox(this);
    _cmbColors->addItem(QIcon(":/images/black.png"), tr("Black"), QVariant((int)Qt::black));
    _cmbColors->addItem(QIcon(":/images/red.png"), tr("Red"), QVariant((int)Qt::red));
    _cmbColors->addItem(QIcon(":/images/yellow.png"), tr("Yellow"), QVariant((int)Qt::yellow));
    _cmbColors->setCurrentIndex(0);
    QObject::connect(_cmbColors, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SimplePaint::colorChanged);
    toolbar->addWidget(_cmbColors);
    toolbar->addSeparator();

    // choose figure type
    _btnFigures = new QToolButton();
    _btnFigures->setPopupMode(QToolButton::InstantPopup);
    _btnFigures->setMenu(mnuFigures);
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

void SimplePaint::newDrawing()
{
    QMessageBox::information(Q_NULLPTR, qAppName(), "newDrawing");
}

void SimplePaint::about()
{
    QMessageBox::information(Q_NULLPTR, qAppName(), "about");
}

void SimplePaint::exit()
{
    qApp->closeAllWindows();
}

void SimplePaint::undo()
{
    QMessageBox::information(Q_NULLPTR, qAppName(), "undo");
}

void SimplePaint::redo()
{
    QMessageBox::information(Q_NULLPTR, qAppName(), "redo");
}

void SimplePaint::drawRectangle()
{
    _scene->setFigureType(FigureScene::FigureType::Rectangle);
    _btnFigures->setDefaultAction(_actRectangle);
}

void SimplePaint::drawEllipse()
{
    _scene->setFigureType(FigureScene::FigureType::Ellipse);
    _btnFigures->setDefaultAction(_actEllipse);
}

void SimplePaint::colorChanged(int index)
{
    QComboBox* combobox = qobject_cast<QComboBox*>(sender());
    if (combobox)
        _scene->setFigureColor(QColor((Qt::GlobalColor)combobox->itemData(index).toInt()));
}
