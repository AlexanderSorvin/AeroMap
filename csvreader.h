#ifndef CSVREADER_H
#define CSVREADER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTextCodec>

/**
 * @brief The CSVReader class Модуль распаковки csv-файла.
 */
class CSVReader : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief CSVReader Конструктор распаковки csv-файла.
     * @param split Разделитель
     * @param codec Кодировка файла
     * @param parent Родитель модуля
     */
    explicit CSVReader(const QString& split = ";", const char *codec = "Windows-1251", QObject * parent = nullptr);

public slots:
    /**
     * @brief ReadNewFile Фукция чтения файла
     * @param name путь до файла
     */
    void ReadNewFile(const QString &name);

signals:
    /* Получить значение процента чтения */
    void CurrentElementCount(const int &count);
    /* Получить новую разобранную строку */
    void ParseWords(const QStringList &list);
    /* Событие начала чтения файла */
    void StartReadFile();
    /* Событие оповещения контейнеров о необоходимости подготовиться и выделить память */
    void CountElementsIs(int count);


private:
    QString split;
    QTextCodec * codec;
};

#endif // CSVREADER_H
