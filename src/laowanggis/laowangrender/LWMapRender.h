#ifndef LWMAPRENDER_H
#define LWMAPRENDER_H

#include <string>
#include <cairo/cairo.h>
#include <ogrsf_frmts.h>
#include "LWAffineOperator.h"



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

    void addGeometry( OGRGeometry *g);
    OGRGeometry* affine(OGRGeometry *g);

protected:
    void addPoint( OGRPoint* pt);
    void addLineString( OGRLineString* g);
    void addPolygon( OGRPolygon* g);
    void addCollection( OGRGeometryCollection* g);
    void addGeometryInternal(OGRGeometry *g);


private:
    void init();

protected:
    double _width, _height;
    double _minX, _minY, _maxX, _maxY;
    double _centerX, _centerY;
    double _pointWidth, _pointHeight;               // for image surface
    double _pointPerMilliMeter;
    const std::string _fileName;
    RenderEngine _renderEngine;
    cairo_surface_t *_surface;
    cairo_t *_cairo;
    double _scale;
    LWAffineOperator _affineOperation;



};

#endif // LWMAPRENDER_H
