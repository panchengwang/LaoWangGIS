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
    recalculateExtent();
    if(_renderEngine == RenderEngine::Image){
        _surface = cairo_image_surface_create(
                    CAIRO_FORMAT_ARGB32,
                    _widthOfPoint,
                    _heightOfPoint
                    );
    }

    _cairo = cairo_create(_surface);
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

    double a = _scale;
    double b = 0.0;
    double xoff = _widthOfPoint * 0.5 - _centerX * _scale;
    double d = 0.0;
    double e = - _scale;
    double yoff = _heightOfPoint * 0.5 + _centerY * _scale;
    _affineOperation.setAffineMatrix(a,b,xoff,
                                     d,e,yoff);
}


void LWMapRender::addGeometry(Geometry *g)
{
    std::unique_ptr<Geometry> geo2 = _editor.edit(g, &_affineOperation);
    Geometry* g2 = geo2.get();
    Point* pt = dynamic_cast<Point*>(g2);
    if( pt ){
        addPoint(pt);
        return;
    }

    LineString* ls = dynamic_cast<LineString*>(g2);
    if(ls){
        addLineString(ls);
        return;
    }

    Polygon* pg = dynamic_cast<Polygon*>(g2);
    if(pg){
        addPolygon(pg);
        return;
    }

    GeometryCollection* collection = dynamic_cast<GeometryCollection*>(g2);
    if(collection){
        addCollection(collection);
        return;
    }

}

void LWMapRender::addPoint(Point* g)
{
    double x,y;

    x=g->getX();
    y=g->getY();

    cairo_set_source_rgba(_cairo,1.0,1.0,0.0,0.50);
    cairo_arc(_cairo,x,y,5,0,2*M_PI);
    cairo_fill(_cairo);
    cairo_set_source_rgba(_cairo,1.0,0.0,0.0,0.5);
    cairo_arc(_cairo,x,y,5,0,2*M_PI);
    cairo_stroke(_cairo);

}

void LWMapRender::addLineString(LineString* g)
{
    const CoordinateSequence *seq = g->getCoordinatesRO();
    const Coordinate& coord = seq->getAt(0);
    cairo_set_source_rgba(_cairo, 0.0,0.0,0.0,0.5);
    cairo_move_to(_cairo,coord.x,coord.y);
    for(int i=1; i<seq->size(); i++){
        const Coordinate& coord = seq->getAt(i);
        cairo_move_to(_cairo,coord.x, coord.y);
    }
    cairo_stroke(_cairo);
}

void LWMapRender::addPolygon(Polygon* g)
{
    std::unique_ptr<CoordinateSequence> myseq = g->getCoordinates();
    const CoordinateSequence *seq = myseq.get();
    const Coordinate& coord = seq->getAt(0);
    cairo_set_source_rgba(_cairo, 0.0,0.0,0.0,0.5);
    cairo_move_to(_cairo,coord.x,coord.y);
    for(int i=1; i<seq->size(); i++){
        const Coordinate& coord = seq->getAt(i);
        cairo_move_to(_cairo,coord.x, coord.y);
    }
    cairo_fill(_cairo);
}

void LWMapRender::addCollection(GeometryCollection* g)
{

}


std::unique_ptr<Geometry> LWMapRender::affine(Geometry *g)
{
    return _editor.edit(g, &_affineOperation);
}



void LWMapRender::init()
{
    _renderEngine = RenderEngine::Image;
    _surface = NULL;
    _cairo = NULL;
}


