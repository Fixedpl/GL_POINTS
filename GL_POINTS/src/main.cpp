#include <iostream>

#include "BasicPointRenderer.h"




int main()
{
    WindowSettings window_settings(
        1280, 720,
        "Rendering point clouds using GL_POINTS",
        false,
        true,
        4, 5
    );

    BasicPointRenderer basic_point_renderer(window_settings);
    basic_point_renderer.run();
  
    return 0;
}

