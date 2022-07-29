#include "LWFile.h"



LWFile::LWFile(QObject *parent) : QObject(parent)
{

}

QString LWFile::readAll(const QString &filename)
{
    return "read all from lwfile";
}
