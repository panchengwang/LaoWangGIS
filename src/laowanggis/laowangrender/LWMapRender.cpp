#include "LWMapRender.h"
#include <iostream>
#include <QtCore>

using namespace geos::geom;

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

    _widthOfPoint = _pointPerMilliMeter * _width;
    _heightOfPoint = _pointPerMilliMeter * _height;


    recalculateExtent();
}



LWMapRender::~LWMapRender()
{
    end();
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
    if(_renderEngine == RenderEngine::Image){
        _surface = cairo_image_surface_create(
                    CAIRO_FORMAT_ARGB32,
                    _widthOfPoint,
                    _heightOfPoint
                    );
    }
}



void LWMapRender::end()
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
    xscale = _widthOfPoint / (_maxX - _minX);
    yscale = _heightOfPoint / (_maxY - _minY);
    _scale = xscale < yscale ? xscale : yscale;
    _minX = _centerX - _widthOfPoint * 0.5 / _scale;
    _maxX = _centerX + _widthOfPoint * 0.5 / _scale;
    _minY = _centerY - _heightOfPoint * 0.5 / _scale;
    _maxY = _centerY + _heightOfPoint * 0.5 / _scale;
}

void LWMapRender::addGeometry(Geometry *g)
{
    switch(g->getGeometryTypeId()){
    case geos::geom::GEOS_POINT:
        addPoint((Point*)g);
        break;
    case geos::geom::GEOS_LINESTRING:
        addLineString((LineString*)g);
        break;
    case geos::geom::GEOS_POLYGON:
        addPolygon((Polygon*)g);
        break;
    default:
        addCollection((GeometryCollection*)g);
        break;
    }
}

void LWMapRender::addPoint(Point *pt)
{
    double x,y;
    x=pt->getX();
    y=pt->getY();

}

void LWMapRender::addLineString(LineString *ls)
{

}

void LWMapRender::addPolygon(Polygon *pg)
{

}

void LWMapRender::addCollection(GeometryCollection *cl)
{

}


Geometry *LWMapRender::affine(Geometry *g)
{

}



Point *LWMapRender::affine(Point *pt)
{

}

LineString *LWMapRender::affine(LineString *ls)
{

}

Polygon *LWMapRender::affine(Polygon *pg)
{

}

GeometryCollection *LWMapRender::affine(GeometryCollection *cl)
{

}


void LWMapRender::init()
{
    _renderEngine = RenderEngine::Image;
    _surface = NULL;
    _cairo = NULL;
}


