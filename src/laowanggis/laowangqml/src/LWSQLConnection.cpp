#include "LWSQLConnection.h"


#define PQ_CLEAR(result)        \
    if(result){                 \
        PQclear(result);        \
        result = NULL;          \
    }

#define PQ_FINISH(conn)         \
    if(conn){                   \
        PQfinish(conn);         \
        conn = NULL;            \
    }

LWSQLConnection::LWSQLConnection(QObject *parent)
    :QObject(parent)
{

}

LWSQLConnection::~LWSQLConnection()
{
    close();
}


QJsonObject LWSQLConnection::executeQuery(const QString& sql)
{

    QJsonObject obj;
    if(!open()){
        return obj;
    }

    _result = PQexec(_connection,sql.toStdString().c_str());
    if(PQresultStatus(_result) != PGRES_TUPLES_OK ){
        _errorMessage = PQerrorMessage(_connection);
        PQ_CLEAR(_result);
        close();
        return obj;
    }

    //Get meta data of the result
    QJsonArray fields;
    for(int i=0; i< PQnfields(_result); i++ ){
        QJsonObject field;

        field.insert("name",PQfname(_result,i));

        QString mysql = QString("select typname from pg_type where oid=%1").arg(PQftype(_result,i));
        PGresult *myresult = PQexec(_connection,mysql.toStdString().c_str());
        field.insert("type",PQgetvalue(myresult,0,0));
        PQ_CLEAR(myresult);

        field.insert("size", PQfsize(_result,i));
        field.insert("modifier", PQfmod(_result,i));
        fields.append(field);
    }
    obj.insert("fields",fields);

    QJsonArray data;
    for(int i=0; i<PQntuples(_result); i++){
        QJsonObject d;
        for(int j=0; j<PQnfields(_result); j++){
            d.insert(PQfname(_result,j),PQgetvalue(_result,i,j));
        }
        data.append(d);
    }

    obj.insert("rows",data);

    close();
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
    PQ_CLEAR(_result);
    PQ_FINISH(_connection);
}


QString LWSQLConnection::errorMessage() const {
    return _errorMessage;
}
