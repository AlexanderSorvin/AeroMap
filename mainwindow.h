#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <programdata.h>
#include <csvreader.h>
#include <tablecontroller.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void ProgressBarIsChange(int value);
    void on_tableWidget_cellPressed(int row, int column);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    ProgramData * data;
    CSVReader * reader;
    TableController * table;

    struct ControlStruct
    {
        Point * data;
        QTableWidgetItem * item;
    };

    QVector<ControlStruct> info;
};

#endif // MAINWINDOW_H
