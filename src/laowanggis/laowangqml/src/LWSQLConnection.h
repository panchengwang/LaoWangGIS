#ifndef LWSQLCONNECTION_H
#define LWSQLCONNECTION_H

#include <QtCore>
#include <libpq-fe.h>


class LWSQLConnection: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(LWSQLConnection)

    Q_PROPERTY(QJsonObject connectParameters READ connectParameters WRITE setConnectParameters NOTIFY connectParametersChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage)

public:
    LWSQLConnection(QObject *parent = nullptr);
    ~LWSQLConnection();

    Q_INVOKABLE QJsonObject execute(const QString& sql);

    Q_INVOKABLE QJsonObject connectParameters() const;
    Q_INVOKABLE void setConnectParameters(const QJsonObject& connectParameters);

    Q_INVOKABLE QString errorMessage() const;
private:
    bool open();
    void close();

signals:
    void connectParametersChanged();
    void error();

protected:
    PGconn     *_connection=NULL;
    PGresult   *_result=NULL;
    QJsonObject _connectParameters;
    QString     _errorMessage;
};

#endif // LWSQLCONNECTION_H
