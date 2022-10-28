#include "antpainter.h"

AntPainter::AntPainter(QWidget* parent) : QWidget(parent)
{

}

void AntPainter::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawAnts(&painter);
    drawFood(&painter);
    drawHome(&painter);
    drawPheromones(&painter);
}

void AntPainter::drawPheromones(QPainter* painter)
{
    const uchar* foodData = world.get_food_pheromones()->get_strengths();
    const uchar* homeData = world.get_home_pheromones()->get_strengths();
    std::pair<double,double> bounds = world.get_bounds();
    int width= bounds.first;
    int height = bounds.second;
    int intSize = sizeof(int);
    int numberOfBytesPerWidth{width*intSize};
    QImage foodPheromoneImage{foodData,width,height,numberOfBytesPerWidth,QImage::Format_ARGB32};
    QImage homePheromoneImage{homeData,width,height,numberOfBytesPerWidth,QImage::Format_ARGB32};

    painter->drawImage(QRect{0,0,this->width(),this->height()},foodPheromoneImage);
    painter->drawImage(QRect{0,0,this->width(),this->height()},homePheromoneImage);

}

void AntPainter::drawAnts(QPainter* painter)
{
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(5);
    painter->setPen(pen);

    for (auto ant : world.get_ants())
    {
        std::pair<double, double> antPixels = world_to_pixel(ant->x, ant->y);
        painter->drawPoint(antPixels.first, antPixels.second);
    }

}

void AntPainter::drawHome(QPainter* painter)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(10);
    painter->setPen(pen);

    auto home = world.get_home();
    auto homePixels = world_to_pixel(home->x, home->y);

    painter->drawEllipse(homePixels.first, homePixels.second, 20, 20);


}

void AntPainter::drawFood(QPainter* painter)
{
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(5);
    painter->setPen(pen);

    auto food_locations = world.get_food()->get_locations();
    for (auto i = food_locations.begin();  i != food_locations.end(); i++)
    {
        int x = i->first;
        std::unordered_set<int> ys = i->second;
        for (auto j = ys.begin(); j != ys.end(); j++)
        {
            std::pair<double, double> foodPixels = world_to_pixel(x, *j);
            painter->drawPoint(foodPixels.first, foodPixels.second);
        }
    }

}

std::pair<double,double> AntPainter::world_to_pixel(double x, double y)
{
    std::pair<double,double> boundary = world.get_bounds();
    double pixel_x = this->width()*x/boundary.first;
    double pixel_y = this->height()*y/boundary.second;
    return {pixel_x, pixel_y};

}

void AntPainter::save_world(const World& world_state)
{
    world = world_state;
    this->update();
}
