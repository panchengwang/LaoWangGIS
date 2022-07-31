#include "LWSQLConnection.h"

LWSQLConnection::LWSQLConnection(QObject *parent)
    :QObject(parent)
{

}

LWSQLConnection::~LWSQLConnection()
{
    close();
}


QJsonObject LWSQLConnection::execute(const QString& sql)
{
    QJsonObject obj;

    return obj;
}

QJsonObject LWSQLConnection::connectParameters() const
{
    return _connectParameters;
}

void LWSQLConnection::setConnectParameters(const QJsonObject& connectParameters)
{
    _connectParameters = connectParameters;
    open();
    close();
}


bool LWSQLConnection::open(){
    close();

    QString connectstr = QString("host=%1 port=%2 dbname=%3 user=%4 password=%5")
            .arg(_connectParameters.value("host").toString())
            .arg(_connectParameters.value("port").toString())
            .arg(_connectParameters.value("dbname").toString())
            .arg(_connectParameters.value("user").toString())
            .arg(_connectParameters.value("password").toString());
    _connection = PQconnectdb(connectstr.toStdString().c_str());
    if (PQstatus(_connection) != CONNECTION_OK ){
        _errorMessage = PQerrorMessage(_connection);
        emit error();
        close();
        return false;
    }
    return true;
}


void LWSQLConnection::close(){
    if(_result){
        PQclear(_result);
        _result = NULL;
    }
    if(_connection){
        PQfinish(_connection);
        _connection = NULL;
    }
}


QString LWSQLConnection::errorMessage() const {
    return _errorMessage;
}
