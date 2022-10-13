#include "antpainter.h"

AntPainter::AntPainter(QWidget* parent) : QWidget(parent)
{

}

void AntPainter::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    drawAnts(&painter);
    drawFood(&painter);
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

void AntPainter::drawFood(QPainter* painter)
{
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(5);
    painter->setPen(pen);

    auto food_locations = *world.food->get_locations();
    for (auto i = food_locations.begin();  i != food_locations.end(); i++)
    {
        int x = i->first;
        std::unordered_set<int> ys = i->second;
        for (auto j = ys.begin(); j != ys.end(); j++)
        {
            painter->drawPoint(x+this->width()/2, *j+this->height()/2);
        }
    }

}

void AntPainter::save_world(const World& world_state)
{
    world = world_state;
    this->update();
}
