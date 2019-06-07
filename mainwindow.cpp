#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    data = new ProgramData(this);
    reader = new CSVReader("	", "UTF-8", this);
    table = new TableController(ui->tableWidget, ui->label_5, ui->comboBox, ui->comboBox_2, this);

    ui->stackedWidget->setCurrentIndex(1);
//    QGraphicsScene * scene = new QGraphicsScene();
//    QGraphicsPixmapItem * item = scene->addPixmap(QPixmap(":/map.jpeg"));
//    item->show();
//    ui->graphicsView->setScene(scene);

    connect(reader, SIGNAL(StartReadFile()), data, SLOT(ClearData()));
    connect(reader, SIGNAL(ParseWords(const QStringList &)), data, SLOT(AddNewPoint(const QStringList &)));
    connect(reader, SIGNAL(CurrentElementCount(int)), this, SLOT(ProgressBarIsChange(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "CSV (*.csv);;Все файлы (*.*)");
    if (fileName == "")
        return;

    ui->stackedWidget->setCurrentIndex(0);
    reader->ReadNewFile(fileName);

    ui->stackedWidget->setCurrentIndex(1);
    table->CreateTable_no_sort(data->getElements());
}

void MainWindow::ProgressBarIsChange(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::on_tableWidget_cellPressed(int row, int )
{
    table->SetActiveRow(row);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (!data->getElements()->empty())
        table->CreateTable_sort(data->getElements(), ui->spinBox->value());
}

void MainWindow::on_pushButton_3_clicked()
{
    if (!data->getElements()->empty())
        table->CalculateWay(data->getElements(), ui->spinBox_2->value() * 1000);
}
