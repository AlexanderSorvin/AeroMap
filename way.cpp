#include "way.h"
#include <algorithm>

struct dataAlgorithm
{
    dataAlgorithm() :
        visited(false),
        numberPrev(-1),
        distance(std::numeric_limits<double>::max())
    {

    }

    /* Была ли уже пересчитанна данная точка */
    bool visited;
    /* Номер аэродрома, из которого прилет осуществлялся быстрее */
    int numberPrev;
    /* Минимальное расстояние от начальной точки */
    double distance;
};

Way::Way(QComboBox * box1, QComboBox * box2) : boxPoint1(box1), boxPoint2(box2)
{

}

QList<TWay> Way::CalculateWay(const QVector<Point> &data, double maxDistance)
{
    // Ищем путь из начальной точки в конечную
    int startPoint = boxPoint1->currentIndex();
    int finishPoint = boxPoint2->currentIndex();

    QVector<dataAlgorithm> d;
    d.resize(data.size());
    d[startPoint].distance = 0;

    int NextPoint = startPoint;
    for (int j = 0; j < data.size(); j++)
    {
        if (NextPoint == finishPoint)
            break;

        startPoint = NextPoint;
        d[startPoint].visited = true;
        for (int i = 0; i < data.size(); i++)
        {
            if (d[i].visited)
                continue;

            if (data[startPoint].distance[i] > maxDistance)
                continue;

            if (data[startPoint].distance[i] + d[startPoint].distance < d[i].distance)
            {
                d[i].distance = data[startPoint].distance[i] + d[startPoint].distance;
                d[i].numberPrev = startPoint;
            }
        }

        // Можно внести в общий цикл, через добавление функции
        double currentMinDistance = std::numeric_limits<double>::max();
        for (int i = 0; i < data.size(); i++)
        {
            if (d[i].visited)
                continue;

            if (d[i].distance < currentMinDistance)
            {
                currentMinDistance = d[i].distance;
                NextPoint = i;
                if (i == finishPoint)
                {
                    break;
                }
            }
        }
    }

    // Собираем маршрут (Он будет в обратном порядке)
    int currentPoint = finishPoint;
    QList<TWay> way;
    way.push_back({currentPoint, currentPoint != -1 ? d[currentPoint].distance : 0.0});
    while (d[currentPoint].numberPrev != -1)
    {
        currentPoint = d[currentPoint].numberPrev;
        way.push_back({currentPoint, currentPoint != -1 ? d[currentPoint].distance : 0.0});
    }

    return way;
}

void Way::CreateNewListPoints(const QVector<Point> &data)
{
    boxPoint1->clear();
    boxPoint2->clear();

    for (auto i : data)
    {
        boxPoint1->addItem(i.code);
        boxPoint2->addItem(i.code);
    }
}
