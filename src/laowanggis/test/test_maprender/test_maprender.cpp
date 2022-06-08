#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../../laowangrender/LWMapRender.h"

int main(int argc, char** argv){

    LWMapRender render(800/72.0*25.4, 600/72.0*25.4,-180,-90,180,90, LWMapRender::RenderEngine::Image, 144/25.4);

    render.begin();
    render.save("/tmp/a.png") ;
    render.end();

    return EXIT_SUCCESS;
}
