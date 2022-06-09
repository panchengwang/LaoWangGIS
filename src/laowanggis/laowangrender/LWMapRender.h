#ifndef LWMAPRENDER_H
#define LWMAPRENDER_H

#include <string>
#include <cairo/cairo.h>
#include <geos/geom.h>
#include "LWGeometryAffineOperation.h"

using namespace geos::geom;

class LWMapRender
{
public:
    enum RenderEngine{
        Image,
        Pdf
    };

    LWMapRender(double width,
                double height,
                double minx, double miny, double maxx, double maxy,
                LWMapRender::RenderEngine engine = RenderEngine::Image,
                double pointPerMilliMeter = 72.0/25.4);
    ~LWMapRender();



public:

    void begin();
    void end();
    void save(const std::string& filename);
    std::string save();
    char *save(int& size);
    void recalculateExtent();

    void addGeometry(Geometry *g);
    void addPoint(Point* pt);
    void addLineString(LineString* g);
    void addPolygon(Polygon* g);
    void addCollection(GeometryCollection* g);

    std::unique_ptr<Geometry> affine(Geometry *g);

private:
    void init();

protected:
    double _width, _height;
    double _minX, _minY, _maxX, _maxY;
    double _centerX, _centerY;
    double _widthOfPoint, _heightOfPoint;               // for image surface
    double _pointPerMilliMeter;
    const std::string _fileName;
    RenderEngine _renderEngine;
    cairo_surface_t *_surface;
    cairo_t *_cairo;
    double _scale;
    LWGeometryAffineOperation _affineOperation;
    util::GeometryEditor _editor;


};

#endif // LWMAPRENDER_H
