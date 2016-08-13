#include "stdafx.h"
#include "simplepaint.h"

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
    createStatusBar();
}

void SimplePaint::createActions()
{
    // new drawing action
    _actNew = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    _actNew->setShortcuts(QKeySequence::New);
    _actNew->setStatusTip(tr("New drawing"));
    connect(_actNew, &QAction::triggered, this, &SimplePaint::newDrawing);

    // exit
    _actExit = new QAction(QIcon(":/images/exit.png"), tr("E&xit"), this);
    _actExit->setShortcuts(QKeySequence::Quit);
    _actExit->setStatusTip(tr("Exit the application"));
    connect(_actExit, &QAction::triggered, this, &SimplePaint::exit);

    // undo
    _actUndo = new QAction(QIcon(":/images/undo.png"), tr("&Undo"));
    _actUndo->setShortcuts(QKeySequence::Undo);
    _actUndo->setStatusTip(tr("Undo"));
    connect(_actUndo, &QAction::triggered, this, &SimplePaint::undo);

    // redo
    _actRedo = new QAction(QIcon(":/images/redo.png"), tr("&Redo"), this);
    _actRedo->setShortcuts(QKeySequence::Redo);
    _actRedo->setStatusTip(tr("Redo"));
    connect(_actRedo, &QAction::triggered, this, &SimplePaint::redo);

    // about application action
    _actAbout = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
    _actAbout->setShortcuts(QKeySequence::HelpContents);
    _actAbout->setStatusTip(tr("About this application"));
    connect(_actAbout, &QAction::triggered, this, &SimplePaint::about);
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
    QToolBar *toolbar = addToolBar(tr("File"));
    toolbar->addAction(_actNew);
    toolbar->addSeparator();

    QComboBox* cmbFigures = new QComboBox();
    cmbFigures->addItem(QIcon(":/images/rectangle.png"), tr("Rectangle"));
    cmbFigures->addItem(QIcon(":/images/ellipse.png"), tr("Ellipse"));
    toolbar->addWidget(cmbFigures);
    toolbar->addSeparator();

    toolbar->addAction(_actUndo);
    toolbar->addAction(_actRedo);

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
