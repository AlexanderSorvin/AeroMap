#ifndef POINT_H
#define POINT_H

#include <QString>
#include <QVector>

struct Point
{
    Point() {}

    Point(const Point &p) :
        code(p.code), lat(p.lat),
        lon(p.lon), id(p.id), distance(p.distance)
    { }

    Point(Point &&p) :
        code(std::move(p.code)), lat(std::move(p.lat)),
        lon(std::move(p.lon)), id(std::move(p.id)),
        distance(std::move(p.distance))
    { }

    QString code;
    double lat;
    double lon;
    int id;

    QVector<double> distance;
};

#endif // POINT_H
