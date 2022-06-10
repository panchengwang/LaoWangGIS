#include "LWGeometryAffineOperation.h"
#include <memory.h>
#include <geos/geom.h>

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
    if (geometry == nullptr) {
        return nullptr;
    }

    if(const LinearRing* ring = dynamic_cast<const LinearRing*>(geometry)) {
        const CoordinateSequence* coords = ring->getCoordinatesRO();
        auto newCoords = edit(coords, geometry);
        // LinearRing instance takes over ownership of newCoords instance
        return factory->createLinearRing(std::move(newCoords));
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

    CoordinateSequence *coords = (CoordinateSequence*)coordinates;
    Coordinate coord(0.0,0.0);
    double x,y;
    for(std::size_t i = 0; i < coords->size(); i++){
        coord = coords->getAt(i);
        x = coord.x;
        y = coord.y;
        coord.x = _a * x + _b * y + _xoff;
        coord.y = _d * x + _e * y + _yoff;
        coords->setAt(coord,i);
    }

    return CoordinateArraySequenceFactory::instance()->create(*coordinates);
}
