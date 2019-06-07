#ifndef PROGRAMDATA_H
#define PROGRAMDATA_H

#include <QObject>
#include <point.h>

class ProgramData : public QObject
{
    Q_OBJECT
public:
    explicit ProgramData(QObject *parent = nullptr);

    QVector<Point> *getElements();

signals:
    void DataIsReady();

public slots:
    void AddNewPoint(const QStringList &list);
    void ClearData();
    void CountElementsIs(int count);

private:
    QVector<Point> elements;

    void CalculateDistance(Point &point1, Point &point2);
};

#endif // PROGRAMDATA_H
