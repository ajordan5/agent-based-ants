#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_sim();
    connect(timer, SIGNAL(timeout()), this, SLOT(update_sim()));
    timer->start(5);
    connect(this, SIGNAL(send_world(const World&)), ui->PaintWidget, SLOT(save_world(const World&)));
}

void MainWindow::setup_sim()
{
    timer = new QTimer(this);
    ant_sim = new World;
    setup_food();
    ant_sim->add_many_ants(1000);
}

void MainWindow::setup_food()
{
    for (int i = 300; i < 700; i = i+5)
    {
        for (int j = 100; j < 300; j = j+5)
        {
            ant_sim->get_food()->add(i,j);
        }

    }

    for (int i = 700; i < 800; i = i+5)
    {
        for (int j = 700; j < 900; j = j+5)
        {
            ant_sim->get_food()->add(i,j);
        }

    }

    for (int i = 200; i < 300; i = i+5)
    {
        for (int j = 700; j < 900; j = j+5)
        {
            ant_sim->get_food()->add(i,j);
        }

    }
}

void MainWindow::update_sim()
{
    ant_sim->update();
    emit(send_world(*ant_sim));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ant_sim;
}

