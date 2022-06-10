#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../../laowangrender/LWMapRender.h"
#include <QtSql>
#include <geos/io.h>
#include <sstream>

int main(int argc, char** argv){

    LWMapRender render(800/72.0*25.4, 600/72.0*25.4,-180,-90,180,90, LWMapRender::RenderEngine::Image, 144/25.4);

    QString host = "127.0.0.1";
    QString port = "5432";
    QString dbname = "gisdb";
    QString username = "pcwang";
    QString password = "123456";
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);
    bool ok = db.open();
    if( !ok){
        qInfo() << "can not connect to database server " ;
        return EXIT_FAILURE;
    }
    QStringList layers;
    layers
            << "province"
            << "town";

    geos::io::WKBReader reader;
    render.begin();
    for(int i=0; i<layers.length(); i++){
        QSqlQuery query(QString("select geo from %1").arg(layers[i]), db);
        while(query.next()){
            std::istringstream is(query.value(0).toString().toStdString());
            Geometry* geo = reader.readHEX(is).release();
            render.addGeometry(geo);
            delete geo;
        }
    }

    render.save("/tmp/a.png");
    render.end();

    db.close();

    return EXIT_SUCCESS;
}
