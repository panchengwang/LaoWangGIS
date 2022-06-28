#include "LWMapRender.h"
#include <iostream>
#include <QtCore>
#include <ogrsf_frmts.h>





LWMapRender::LWMapRender(double width,
                         double height,
                         double minx, double miny, double maxx, double maxy,
                         LWMapRender::RenderEngine engine,
                         double pointPerMilliMeter)
{
    _width = width;
    _height = height;
    _minX = minx;
    _minY = miny;
    _maxX = maxx;
    _maxY = maxy;
    _renderEngine = engine;
    _pointPerMilliMeter = pointPerMilliMeter;

    if (_renderEngine == RenderEngine::Pdf){
        _pointPerMilliMeter = 72.0/25.4;
    }

    _pointWidth = _pointPerMilliMeter * _width;
    _pointHeight = _pointPerMilliMeter * _height;

}



LWMapRender::~LWMapRender()
{
    if (!_cairo){
        cairo_destroy(_cairo);
        _cairo= NULL;
    }
    if (!_surface){
        cairo_surface_destroy(_surface);
        _surface = NULL;
    }
}

/**
 * @brief LWMapRender::begin
 * @param width                             Unit must be millimeter
 * @param height                            Unit must be millimeter
 * @param engine                            Image -- draw a image in memory, Pdf -- create a pdf document
 * @param pointPerMilliMeter                If you create a image , the value of pointPerMilliMeter is the dpi/25.4 of the image.
 *                                          This value may be changed based on the device to output, such as screen(96/25.4,144/25.4,288/25.4), printer(300/25.4),etc.
 *                                          If you create a pdf, the value is always 72.0/25.4 .
 */
void LWMapRender::begin()
{
    recalculateExtent();
    if(_renderEngine == RenderEngine::Image){
        _surface = cairo_image_surface_create(
                    CAIRO_FORMAT_ARGB32,
                    _pointWidth,
                    _pointHeight
                    );
    }

    _cairo = cairo_create(_surface);
}



void LWMapRender::end()
{
    cairo_surface_finish(_surface);
}


/**
 * @brief LWMapRender::save
 * @param filename
 */
void LWMapRender::save(const std::string &filename)
{
    cairo_surface_write_to_png(_surface, filename.c_str());
}



/**
 * @brief LWMapRender::save
 *     save the map to a file.
 * @return The filename of the Map.
 */
std::string LWMapRender::save()
{
    std::string filename = (QDir::tempPath() + QDir::separator() + "map-" + QUuid::createUuid().toString(QUuid::WithoutBraces)+".png").toStdString();
    cairo_surface_write_to_png(_surface, filename.c_str());
    return filename;
}



/**
 * @brief LWMapRender::save
 *      Save map in memory buffer.
 *      The caller must release this buffer using free (Do not use delete).
 * @param size
 *      The buffer length.
 * @return
 */
char *LWMapRender::save(int &size)
{
    size = 0;
    return NULL;
}



void LWMapRender::recalculateExtent()
{
    double xscale, yscale;
    _centerX = (_minX + _maxX) * 0.5;
    _centerY = (_minY + _maxY) * 0.5;
    xscale = _pointWidth / (_maxX - _minX);
    yscale = _pointHeight / (_maxY - _minY);
    _scale = xscale < yscale ? xscale : yscale;
    _minX = _centerX - _pointWidth * 0.5 / _scale;
    _maxX = _centerX + _pointWidth * 0.5 / _scale;
    _minY = _centerY - _pointHeight * 0.5 / _scale;
    _maxY = _centerY + _pointHeight * 0.5 / _scale;

    double a = _scale;
    double b = 0.0;
    double xoff = _pointWidth * 0.5 - _centerX * _scale;
    double d = 0.0;
    double e = - _scale;
    double yoff = _pointHeight * 0.5 + _centerY * _scale;
    _affineOperation.setMatrix(a,b,xoff,
                               d,e,yoff);
}


void LWMapRender::addGeometry(OGRGeometry *g)
{
    OGRGeometry *g2 = affine(g);
//    std::cout << g2->exportToWkt() << std::endl;
    addGeometryInternal(g2);
    OGRGeometryFactory::destroyGeometry(g2);
}

void LWMapRender::addPoint(OGRPoint* g)
{
    double x,y;

    x=g->getX();
    y=g->getY();

    cairo_set_source_rgba(_cairo,1.0,1.0,0.0,0.50);
    cairo_arc(_cairo,x,y,5,0,2*M_PI);
    cairo_fill(_cairo);
    cairo_set_source_rgba(_cairo,1.0,0.0,0.0,0.5);
    cairo_arc(_cairo,x,y,5,0,2*M_PI);
    cairo_set_line_width (_cairo, 1.0);
    cairo_stroke(_cairo);

}

void LWMapRender::addLineString(OGRLineString* g)
{
    int npoints = g->getNumPoints();
    OGRPoint pt;

    cairo_set_source_rgba(_cairo, 0.0,0.0,0.0,1);
    g->getPoint(0,&pt);
    cairo_move_to(_cairo,pt.getX(), pt.getY());
    for(int i=1; i<npoints; i++){
        g->getPoint(i,&pt);
        cairo_line_to(_cairo,pt.getX(), pt.getY());
    }
    cairo_set_line_width (_cairo, 1.0);
    cairo_stroke(_cairo);
}

void LWMapRender::addPolygon(OGRPolygon* g)
{
    int count = g->getExteriorRing()->getNumPoints();
    for(int i=0; i<g->getNumInteriorRings(); i++){
        count += g->getInteriorRing(i)->getNumPoints();
    }
    double *x = new double[count];
    double *y = new double[count];
    int k=0;

    OGRLinearRing *ring = g->getExteriorRing();
    for(int i=0; i<ring->getNumPoints(); i++){
        OGRPoint pt;
        ring->getPoint(i,&pt);
        x[k] = pt.getX();
        y[k] = pt.getY();
        k ++;
    }
    for(int i=0; i<g->getNumInteriorRings(); i++){
        ring = g->getInteriorRing(i);
        for (int j=0; j<ring->getNumPoints(); j++){
            OGRPoint pt;
            ring->getPoint(j,&pt);
            x[k] = pt.getX();
            y[k] = pt.getY();
            k++;
        }
    }

    cairo_set_source_rgba(_cairo,0.5,0.5,0.5,0.5);
    cairo_move_to(_cairo,x[0],y[0]);
    for(int i=1; i<count; i++){
        cairo_line_to(_cairo,x[i],y[i]);
    }
    cairo_fill(_cairo);


    addLineString(g->getExteriorRing());
    for(int i=0; i<g->getNumInteriorRings(); i++){
        addLineString(g->getInteriorRing(i));
    }
}

void LWMapRender::addCollection(OGRGeometryCollection* g)
{
    for(int i=0; i<g->getNumGeometries(); i++){
        OGRGeometry *mygeo = g->getGeometryRef(i);
        addGeometryInternal(mygeo);
    }
}

void LWMapRender::addGeometryInternal(OGRGeometry *g)
{
    OGRwkbGeometryType type = g->getGeometryType();
    switch(type){
    case OGRwkbGeometryType::wkbPoint:
        addPoint((OGRPoint*)g);
        break;
    case OGRwkbGeometryType::wkbLineString:
        addLineString((OGRLineString*)g);
        break;
    case OGRwkbGeometryType::wkbPolygon:
        addPolygon((OGRPolygon*)g);
        break;
    case OGRwkbGeometryType::wkbMultiPoint:
    case OGRwkbGeometryType::wkbMultiLineString:
    case OGRwkbGeometryType::wkbMultiPolygon:
    case OGRwkbGeometryType::wkbGeometryCollection:
        addCollection((OGRGeometryCollection*)g);
        break;
    default:
        break;
    }
}


OGRGeometry* LWMapRender::affine(OGRGeometry *g)
{
    return _affineOperation.affine(g);
}



void LWMapRender::init()
{
    _renderEngine = RenderEngine::Image;
    _surface = NULL;
    _cairo = NULL;
}


