#include "antpainter.h"

AntPainter::AntPainter(QWidget* parent) : QWidget(parent)
{

}

void AntPainter::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    drawAnts(&painter);
}
void AntPainter::drawAnts(QPainter* painter)
{
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(5);
    painter->setPen(pen);

    for (auto ant : world.get_ants())
    {
         painter->drawPoint(ant->x+this->width()/2, ant->y+this->height()/2);
    }

}

void AntPainter::save_world(const World& world_state)
{
    world = world_state;
    this->update();
}
