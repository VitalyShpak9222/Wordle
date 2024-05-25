#include "readerandwriter.h"

ReaderAndWriter::ReaderAndWriter() {}

QString ReaderAndWriter::ReadRecord(QString str){
    QFile file(str);
    QByteArray data;
    if (file.open(QIODevice::ReadOnly)){
        data = file.readAll();
        file.close();
    }
    QString text = QString(data);
    return text;
}

void ReaderAndWriter::WriteRecord(QString string_in){
    QFile file("Record history.txt");
    QString text = (ReadRecord("Record history.txt") + "\n" + string_in);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&file);
        writeStream << text;
        file.close();
    }
}
