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

std::unique_ptr<CoordinateSequence> LWGeometryAffineOperation::edit(const CoordinateSequence *coordinates, const Geometry *geometry)
{
    std::unique_ptr<CoordinateSequence> seq = coordinates->clone();

    Coordinate coord(0.0,0.0);
    double x,y;
    for(std::size_t i = 0; i < seq->size(); i++){
        coord = seq->getAt(i);
        x = coord.x;
        y = coord.y;
        coord.x = _a * x + _b * y + _xoff;
        coord.y = _d * x + _e * y + _yoff;
        seq->setAt(coord,i);
    }
    return seq;
}
