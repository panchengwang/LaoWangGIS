#include "LWGeometryAffineOperation.h"
#include <memory.h>
#include <geos/geom.h>
#include <QtCore>

LWGeometryAffineOperation::LWGeometryAffineOperation()
{
    setAffineMatrix(
                1.0,0.0,0.0,
                0.0,1.0,0.0
                );
}

void LWGeometryAffineOperation::setAffineMatrix(double a, double b, double xoff, double d, double e,  double yoff)
{
    _a = a;
    _b = b;
    _d = d;
    _e = e;
    _xoff = xoff;
    _yoff = yoff;
}




std::unique_ptr<Geometry>
LWGeometryAffineOperation::edit(const Geometry* geometry,
                          const GeometryFactory* factory)
{
    std::unique_ptr<Geometry> ret = nullptr;
//    ret = CoordinateOperation::edit(geometry,factory);

//    if (ret == nullptr) {
//        return nullptr;
//    }
    if(geometry->isEmpty()){
        qInfo() << "empty";
    }
    if(const Polygon* pg = dynamic_cast<const Polygon*>(geometry)) {
        qInfo() << ((Polygon*)geometry)->getArea();
        std::unique_ptr<LinearRing>  shell = pg->getExteriorRing()->clone();
        shell.reset((LinearRing*)edit(shell.get(),factory).release());
        ret = factory->createPolygon(std::move(shell));
        return ret;
    }
    if(const LineString* line = dynamic_cast<const LineString*>(geometry)) {
        const CoordinateSequence* coords = line->getCoordinatesRO();
        auto newCoords = edit(coords, geometry);
        return factory->createLineString(std::move(newCoords));
    }
    if(const Point* point = dynamic_cast<const Point*>(geometry)) {
        auto coords = point->getCoordinatesRO();
        auto newCoords = edit(coords, geometry);
        return std::unique_ptr<Geometry>(factory->createPoint(newCoords.release()));
    }

    return geometry->clone();
}


std::unique_ptr<CoordinateSequence> LWGeometryAffineOperation::edit(
        const CoordinateSequence *coordinates,
        const Geometry *geometry)
{
    std::unique_ptr<CoordinateSequence> mycoords = coordinates->clone();

    Coordinate coord(0.0,0.0);
    double x,y;
    for(std::size_t i = 0; i < mycoords->size(); i++){
        coord = mycoords->getAt(i);
        x = coord.x;
        y = coord.y;
        coord.x = _a * x + _b * y + _xoff;
        coord.y = _d * x + _e * y + _yoff;
        mycoords->setAt(coord,i);
    }

    return mycoords;
}
