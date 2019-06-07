#include "programdata.h"
#include <ProjectMath.h>

#include <cmath>
#include <QDebug>

ProgramData::ProgramData(QObject *parent) : QObject(parent)
{

}

void ProgramData::AddNewPoint(const QStringList &list)
{
    Point p;

    p.code = list[0];
    p.lat = list[1].toDouble();
    p.lon = list[2].toDouble();


    for (auto i = elements.begin(); i != elements.end(); i++)
    {
        CalculateDistance(p, *i);
    }

    p.distance.push_back(0.0);
    p.id = elements.size();

    elements.push_back(std::move(p));
}

void ProgramData::ClearData()
{
    elements.clear();
}

void ProgramData::CountElementsIs(int count)
{
    elements.reserve(count);
}

QVector<Point> * ProgramData::getElements()
{
    return &elements;
}

void ProgramData::CalculateDistance(Point &point1, Point &point2)
{
    double distance = GetDistance(
                point1.lat / 180 * M_PI,
                point1.lon / 180 * M_PI,
                point2.lat / 180 * M_PI,
                point2.lon / 180 * M_PI
                );

    point1.distance.push_back(distance);
    point2.distance.push_back(distance);
}
