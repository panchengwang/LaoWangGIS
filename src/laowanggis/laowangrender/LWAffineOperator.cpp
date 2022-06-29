#include "LWAffineOperator.h"
#include <iostream>


LWAffineOperator::LWAffineOperator()
{

}




void LWAffineOperator::setMatrix(double a, double b, double xoff, double d, double e, double yoff)
{
    _a = a;
    _b = b;
    _xoff = xoff;
    _d = d;
    _e = e;
    _yoff = yoff;
}




OGRGeometry *LWAffineOperator::affine(OGRGeometry *geo)
{
    OGRGeometry *g = NULL;
    OGRwkbGeometryType type = geo->getGeometryType();
    switch(type){
    case OGRwkbGeometryType::wkbPoint:
        g = affine((OGRPoint*)geo);
        break;
    case OGRwkbGeometryType::wkbLineString:
        g = affine((OGRLineString*)geo);
        break;
    case OGRwkbGeometryType::wkbLinearRing:
        g = (OGRLinearRing*)affine((OGRLineString*)geo);
        break;
    case OGRwkbGeometryType::wkbPolygon:
        g = affine((OGRPolygon*)geo);
        break;
    case OGRwkbGeometryType::wkbMultiPoint:
    case OGRwkbGeometryType::wkbMultiLineString:
    case OGRwkbGeometryType::wkbMultiPolygon:
    case OGRwkbGeometryType::wkbGeometryCollection:
        g = affine((OGRGeometryCollection*)geo);
        break;
    default:
        break;
    }
    return g;
}



OGRPoint *LWAffineOperator::affine(OGRPoint *pt)
{
    OGRPoint *mypt = pt->clone();
    double x, y;
    x = mypt->getX();
    y = mypt->getY();
    mypt->setX(_a * x + _b * y + _xoff);
    mypt->setY(_d * x + _e * y + _yoff);

    return mypt;
}



OGRLineString *LWAffineOperator::affine(OGRLineString *ls)
{
    OGRLineString* myls = ls->clone();
    int npoints = ls->getNumPoints();
    OGRRawPoint* points = new OGRRawPoint[npoints];
    ls->getPoints(points);
    for(int i=0; i<npoints; i++){
        affine(&points[i]);
    }
    myls->setPoints(npoints,points);
    delete [] points;
    return myls;
}



OGRPolygon *LWAffineOperator::affine(OGRPolygon *pg)
{
    OGRPolygon *mypg =(OGRPolygon*) OGRGeometryFactory::createGeometry(OGRwkbGeometryType::wkbPolygon);
    OGRLinearRing *lr = (OGRLinearRing*) affine(pg->getExteriorRing());
    mypg->addRing(lr);
    OGRGeometryFactory::destroyGeometry(lr);
    for(int i=0; i<pg->getNumInteriorRings(); i++){
        lr = (OGRLinearRing*) affine(pg->getInteriorRing(i));
        mypg->addRing(lr);
        OGRGeometryFactory::destroyGeometry(lr);
    }
    return mypg;
}



OGRGeometryCollection *LWAffineOperator::affine(OGRGeometryCollection *coll)
{
    OGRGeometryCollection *mycoll =(OGRGeometryCollection*) OGRGeometryFactory::createGeometry(OGRwkbGeometryType::wkbGeometryCollection);
    int ngeos = coll->getNumGeometries();
    for(int i=0; i<ngeos; i++){
        OGRGeometry *mygeo = affine(coll->getGeometryRef(i));
        mycoll->addGeometry(mygeo);
        OGRGeometryFactory::destroyGeometry(mygeo);
    }
    return mycoll;
}


void LWAffineOperator::affine(OGRRawPoint *pt)
{
    double x, y;
    x = pt->x;
    y = pt->y;
    pt->x = _a * x + _b * y + _xoff;
    pt->y = _d * x + _e * y + _yoff;
}
