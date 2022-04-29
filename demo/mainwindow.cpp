#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	timer = new QTimer(this);
	connect( timer, &QTimer::timeout, this, &MainWindow::update );
	timer->start(100);
}

void MainWindow::update(){
}

MainWindow::~MainWindow()
{
    delete ui;
}

