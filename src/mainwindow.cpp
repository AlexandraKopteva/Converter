#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gui_form = new GUIForm(this);
    setWindowTitle("Converter FB2 to TXT");
    setMinimumSize(200,140);
    setCentralWidget(gui_form);
}

MainWindow::~MainWindow()
{
    delete ui;
}
