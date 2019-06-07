#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include <QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <point.h>
#include <QLabel>
#include <ProjectMath.h>
#include <way.h>

class TableController : QObject
{
    Q_OBJECT
public:
    TableController(QTableWidget * table, QLabel * label, QComboBox * box1, QComboBox * box2, QObject * parent = nullptr);

    void CreateTable_no_sort(QVector<Point> * data);
    void CreateTable_sort(QVector<Point> *data, int maxDistance);

    void SetActiveRow(int i);
    void CalculateWay(QVector<Point> * data, double distance);

public slots:
    void Reset();

private:
    QTableWidget * table;
    // Текст, меняющийся на вкладке "Опции ближайших точек"
    QLabel * label;

    QTableWidgetItem * CreateTableItem(const QString &value);

    QVector<const Point *> sortlist;

    int ActiveRow = 0;
    Way way;

};

#endif // TABLECONTROLLER_H
