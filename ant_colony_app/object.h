#ifndef OBJECT_H
#define OBJECT_H

#define PI 3.14159

#include <unordered_map>
#include <unordered_set>

class Object
{
public:
    Object();
    virtual void add(int x, int y);
    void remove(int x, int y);
    std::unordered_map<int, std::unordered_set<int>> get_locations() const;
    int get_total() const;
    std::pair<int,int> search(double x, double y, double heading);
    bool contains(int x, int y);

protected:
    std::unordered_map<int, std::unordered_set<int>> locations;
    std::pair<int,int> search_quadrant(double xAnt, double yAnt, int xLeft, int yTop, int xRight, int yBottom);
    int sideSearchDistance;
    int forwardSearchDistance;
    int total{0};
};

#endif // OBJECT_H
