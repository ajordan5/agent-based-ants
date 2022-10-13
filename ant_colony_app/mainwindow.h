#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <world.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void update_sim();

signals:
    void send_world(const World& world_state);

private:
    Ui::MainWindow *ui;
    World* ant_sim{nullptr};
    QTimer* timer{nullptr};
    void setup_sim();
};
#endif // MAINWINDOW_H
