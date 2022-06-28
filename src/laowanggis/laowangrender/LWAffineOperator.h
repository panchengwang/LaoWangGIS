#ifndef LWAFFINEOPERATOR_H
#define LWAFFINEOPERATOR_H

#include <ogrsf_frmts.h>

class LWAffineOperator
{
public:
    LWAffineOperator();
    void setMatrix(double a, double b, double xoff,
                     double d, double e, double yoff);

    OGRGeometry *affine(OGRGeometry* geo);

    OGRPoint* affine(OGRPoint *pt);
    OGRLineString* affine(OGRLineString *ls);
    OGRPolygon* affine(OGRPolygon *pg);
    OGRGeometryCollection* affine(OGRGeometryCollection* coll);

    void affine(OGRRawPoint *pt);

protected:
    double _a, _b, _c, _d, _e, _f, _g, _h, _i;
    double _xoff, _yoff, _zoff;
};

#endif // LWAFFINEOPERATOR_H
