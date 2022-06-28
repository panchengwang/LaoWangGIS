#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../../laowangrender/LWMapRender.h"
#include <QtSql>
#include <gdal.h>
#include <ogr_api.h>
#include <ogrsf_frmts.h>
#include <sstream>

int main(int argc, char** argv){
    GDALAllRegister();

    LWMapRender render(800/72.0*25.4, 600/72.0*25.4,108.7,24.5,114.3,30.2, LWMapRender::RenderEngine::Image, 72/25.4);

    QString host = "127.0.0.1";
    QString port = "5432";
    QString dbname = "laowangdb";
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
            << "hunan"
            << "county"
            << "railway"
            << "town"
               ;


    OGRGeometry *geo;
    render.begin();
    for(int i=0; i<layers.length(); i++){
        QSqlQuery query(QString("select st_astext(geom) from %1").arg(layers[i]), db);
        while(query.next()){
            OGRErr err = OGRGeometryFactory::createFromWkt(query.value(0).toString().toStdString().c_str(),NULL,&geo);
            if (err == OGRERR_NONE){
                render.addGeometry(geo);
                OGRGeometryFactory::destroyGeometry(geo);
            }
        }
    }


    render.save();
    render.end();

    db.close();

    return EXIT_SUCCESS;
}
