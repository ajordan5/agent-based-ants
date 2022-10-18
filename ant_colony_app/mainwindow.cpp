#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_sim();
    connect(timer, SIGNAL(timeout()), this, SLOT(update_sim()));
    timer->start(50);
    connect(this, SIGNAL(send_world(const World&)), ui->PaintWidget, SLOT(save_world(const World&)));
}

void MainWindow::setup_sim()
{
    timer = new QTimer(this);
    ant_sim = new World;
    for (int i = 200; i < 400; i = i+10)
    {
        for (int j = 100; j < 300; j = j+10)
        {
            ant_sim->food->add_food(i,j);
        }

    }
    ant_sim->add_many_ants(2000);

//    ant_sim->food->add_food(10,10);
//    ant_sim->food->add_food(70,40);
//    ant_sim->food->add_food(100,0);
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

