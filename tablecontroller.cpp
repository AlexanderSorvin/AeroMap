#include "tablecontroller.h"
#include <QDebug>
#include <ProjectMath.h>

TableController::TableController(QTableWidget *table, QLabel * label,
                                 QComboBox * box1, QComboBox * box2, QObject *parent) :
    QObject (parent), table(table), label(label), way(box1, box2)
{
    Reset();
}

void TableController::Reset()
{
    table->clear();
    sortlist.clear();
    table->setRowCount(0);
}

QTableWidgetItem *TableController::CreateTableItem(const QString& value)
{
    auto item = new QTableWidgetItem(value);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    return item;
}

void TableController::CreateTable_no_sort(QVector<Point> * data)
{
    Reset();

    table->setColumnCount(3);
    table->setShowGrid(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setHorizontalHeaderLabels(QStringList("Код аэродрома") << "Широта" << "Долгота");
    table->horizontalHeader()->setStretchLastSection(true);

    for (int i = 0; i < data->size(); i++)
    {
        table->insertRow(i);

        char sign[2] = {};
        int grad, min, sec;

        table->setItem(i, 0, CreateTableItem((*data)[i].code));

        std::tie<char, int, int, int>(sign[0], grad, min, sec) = GradMinSec((*data)[i].lat);
        table->setItem(i, 1, CreateTableItem(QString::asprintf("%1s%02d:%02d:%02d", sign, grad, min, sec)));

        std::tie<char, int, int, int>(sign[0], grad, min, sec) = GradMinSec((*data)[i].lon);
        table->setItem(i, 2, CreateTableItem(QString::asprintf("%1s%03d:%02d:%02d", sign, grad, min, sec)));

        sortlist.push_back(nullptr);
        sortlist.back() = &(data->data()[i]);
    }

    table->resizeColumnsToContents();
    way.CreateNewListPoints(*data);
}

void TableController::CreateTable_sort(QVector<Point> * data, int maxDistance)
{
    int row = sortlist[ActiveRow]->id;
    Reset();

    table->setColumnCount(4);
    table->setShowGrid(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setHorizontalHeaderLabels(QStringList("Код") << "Широта" << "Долгота" << "Расстояние");
    table->horizontalHeader()->setStretchLastSection(true);

    for (int i = 0; i < (*data).size(); i++)
    {
        sortlist.push_back(&(*data)[i]);
    }

    std::sort(sortlist.begin(), sortlist.end(),
              [row](const Point *&a, const Point *&b) -> bool { return a->distance[row] < b->distance[row]; });

    for (int i = 0; i < sortlist.size(); i++)
    {
        if (sortlist[i]->distance[row] / 1000 > maxDistance && maxDistance != 0)
            break;

        table->insertRow(i);

        char sign[2] = {};
        int grad, min, sec;

        table->setItem(i, 0, CreateTableItem(sortlist[i]->code));

        std::tie<char, int, int, int>(sign[0], grad, min, sec) = GradMinSec((*data)[i].lat);
        table->setItem(i, 1, CreateTableItem(QString::asprintf("%1s%02d:%02d:%02d", sign, grad, min, sec)));

        std::tie<char, int, int, int>(sign[0], grad, min, sec) = GradMinSec((*data)[i].lon);
        table->setItem(i, 2, CreateTableItem(QString::asprintf("%1s%03d:%02d:%02d", sign, grad, min, sec)));

        table->setItem(i, 3, CreateTableItem(QString::number(sortlist[i]->distance[row] / 1000)));
    }

    table->resizeColumnsToContents();
}

void TableController::SetActiveRow(int i)
{
    ActiveRow = i;
    label->setText(sortlist[i]->code);
}

void TableController::CalculateWay(QVector<Point> * data, double distance)
{
    QList<TWay> list(way.CalculateWay(*data, distance));

    Reset();

    table->setColumnCount(4);
    table->setShowGrid(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setHorizontalHeaderLabels(QStringList("Код") << "Широта" << "Долгота" << "Расстояние");
    table->horizontalHeader()->setStretchLastSection(true);

    int j = 0;
    for (auto i = list.rbegin(); i != list.rend(); i++)
    {
        sortlist.push_back(&(*data)[(*i).numberPoint]);

        table->insertRow(j);

        char sign[2] = {};
        int grad, min, sec;

        table->setItem(j, 0, CreateTableItem(sortlist[j]->code));

        std::tie<char, int, int, int>(sign[0], grad, min, sec) = GradMinSec((*data)[j].lat);
        table->setItem(j, 1, CreateTableItem(QString::asprintf("%1s%02d:%02d:%02d", sign, grad, min, sec)));

        std::tie<char, int, int, int>(sign[0], grad, min, sec) = GradMinSec((*data)[j].lon);
        table->setItem(j, 2, CreateTableItem(QString::asprintf("%1s%03d:%02d:%02d", sign, grad, min, sec)));

        table->setItem(j, 3, CreateTableItem(QString::number((*i).distance / 1000)));

        j++;
    }

    table->resizeColumnsToContents();
}
