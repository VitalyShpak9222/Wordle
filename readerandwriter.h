#ifndef READERANDWRITER_H
#define READERANDWRITER_H

#include <QFile>
#include <QDebug>
#include <QString>

class ReaderAndWriter
{
public:
    ReaderAndWriter();
    static QString ReadRecord(QString str);
    static void WriteRecord(QString str);
};

#endif // READERANDWRITER_H
