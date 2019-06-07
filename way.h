#ifndef WAY_H
#define WAY_H

#include <point.h>
#include <QComboBox>

/* Структура кратчайшего пути */
struct TWay
{
    TWay(int numberPoint, double distance) :
        numberPoint(numberPoint), distance(distance)
    { }

    int numberPoint;
    double distance;
};

class Way : public QObject
{
public:
    Way(QComboBox * box1, QComboBox * box2);

    /* Рассчитать ближайший маршрут */
    QList<TWay> CalculateWay(const QVector<Point> &data, double maxDistance);

    /* Создать или обновить списки */
    void CreateNewListPoints(const QVector<Point> &data);

protected:
    QComboBox * boxPoint1;
    QComboBox * boxPoint2;
};

#endif // WAY_H
