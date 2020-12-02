#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QVector>

template <typename T>
class FileParser
{
public:    
    FileParser(QString file);
    bool readFile(QVector<T>& x, QVector<T>& y);
    bool readFile(QVector<T>& x);
    int getErrorCode() const;
    QString getErrorFileParser() const;

    void setXcol(int value);

private:
    QString fileName;
    QString errorFileParser;
    int xcol, ycol;
    inline T convert(const QString &arg);
};

#endif // FILEPARSER_H
