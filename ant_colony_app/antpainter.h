#ifndef ANTPAINTER_H
#define ANTPAINTER_H

#include <QWidget>
#include <QPainter>
#include "world.h"

class AntPainter  : public QWidget
{
    Q_OBJECT

public:
    AntPainter(QWidget* parent = 0);

public slots:
    void save_world(const World& world_state);

protected:
    void paintEvent(QPaintEvent* event);
    void drawAnts(QPainter* painter);
    void drawFood(QPainter* painter);
    void drawHome(QPainter* painter);
    std::pair<double,double> world_to_pixel(double x, double y);
    World world;
};

#endif // ANTPAINTER_H
