#include "fileparser.h"
#include <QFile>
#include <QTextStream>

template <typename T>
FileParser<T>::FileParser(QString file) :
    fileName(file),    
    errorFileParser(""),
    xcol(1),
    ycol(2)
{

}

template <typename T>
bool FileParser<T>::readFile(QVector<T> &x, QVector<T> &y)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        errorFileParser = "Cannot open file for reading: " + file.errorString();
        return false;
    } else {
        x.clear();
        y.clear();
        int xc = --xcol;
        int yc = --ycol;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.isEmpty()) continue;
            line = line.trimmed();
            if (line.at(0) == '#') continue;
            QStringList fields = line.split(QRegExp("\\s+"));            
            T xval = convert(fields[xc]);
            T yval = convert(fields[yc]);            
            x.push_back(xval);
            y.push_back(yval);
        }
    }    
    return true;
}

template<typename T>
bool FileParser<T>::readFile(QVector<T> &x)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        errorFileParser = "Cannot open file for reading: " + file.errorString();
        return false;
    } else {
        x.clear();
        int xc = --xcol;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.isEmpty()) continue;
            line = line.trimmed();
            if (line.at(0) == '#') continue;
            QStringList fields = line.split(QRegExp("\\s+"));
            T xval = convert(fields[xc]);
            x.push_back(xval);
        }
    }
    return true;
}

template <typename T>
QString FileParser<T>::getErrorFileParser() const
{
    return errorFileParser;
}

template <typename T>
void FileParser<T>::setXcol(int value)
{
    xcol = value;
}

template<typename T>
T FileParser<T>::convert(const QString& arg)
{
    return arg.toDouble();
}

template<>
float FileParser<float>::convert(const QString& arg)
{
    return arg.toFloat();
}

template<>
int FileParser<int>::convert(const QString& arg)
{
    return static_cast<int>(arg.toDouble());
}

template class FileParser<double>;
template class FileParser<float>;
template class FileParser<int>;
