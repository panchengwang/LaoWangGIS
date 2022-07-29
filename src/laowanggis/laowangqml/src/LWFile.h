#ifndef LWFILE_H
#define LWFILE_H

#include <QtCore>

class LWFile: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(LWFile)
public:
    LWFile(QObject *parent = nullptr);

    Q_INVOKABLE QString readAll(const QString& filename);
};

#endif // LWFILE_H
