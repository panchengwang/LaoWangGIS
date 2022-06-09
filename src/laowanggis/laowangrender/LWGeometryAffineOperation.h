#ifndef LWGEOMETRYAFFINEOPERATION_H
#define LWGEOMETRYAFFINEOPERATION_H

#include <geos/geomUtil.h>
#include <geos/geom.h>

class LWGeometryAffineOperation : public geos::geom::util::CoordinateOperation
{
public:
    LWGeometryAffineOperation();
    void setAffineMatrix(double a, double b, double xoff, double d, double e, double yoff);
    std::unique_ptr<CoordinateSequence> edit(
        const CoordinateSequence * 	coordinates,
        const Geometry* geometry
    );
protected:
    double _a, _b, _d, _e, _xoff, _yoff;
};

#endif // LWGEOMETRYAFFINEOPERATION_H
