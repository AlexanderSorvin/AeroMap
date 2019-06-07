#include "csvreader.h"
#include <QFile>
#include <QCoreApplication>

CSVReader::CSVReader(const QString& split, const char * codec, QObject * parent) :
    QObject(parent), split(split), codec(QTextCodec::codecForName(codec))
{

}

/* Прочитать файл */
void CSVReader::ReadNewFile(const QString &name)
{
    QFile file(name);
    int lineSize = 0;

    if (file.exists())
    {
        emit CurrentElementCount(0);
        emit StartReadFile();
        // Блок подсчета количества строк в файле
        {
            file.open(QIODevice::ReadOnly);
            while(!file.atEnd())
            {
                file.readLine();
                lineSize++;
            }
            file.close();
        }

        emit CountElementsIs(lineSize);
        // Блок считывания новых данных
        {
            int i = 0;
            file.open(QIODevice::ReadOnly);
            file.readLine();
            while(!file.atEnd())
            {
                QCoreApplication::processEvents();
                auto str = codec->toUnicode(file.readLine());
                emit CurrentElementCount(i * 100 / lineSize);
                i++;
                emit ParseWords(str.split(split));
            }
            emit CurrentElementCount(100);
        }
    }
}
