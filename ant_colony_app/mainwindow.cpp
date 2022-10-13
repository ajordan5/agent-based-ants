#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_sim();
    connect(timer, SIGNAL(timeout()), this, SLOT(update_sim()));
    timer->start(1000);
}

void MainWindow::setup_sim()
{
    timer = new QTimer(this);
    ant_sim = new World;
    ant_sim->add_many_ants(1);
}

void MainWindow::update_sim()
{
    ant_sim->update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ant_sim;
}

