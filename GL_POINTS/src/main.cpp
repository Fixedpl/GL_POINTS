#include <iostream>

#include "BasicPointRenderer.h"




int main()
{
    WindowSettings window_settings(
        1600, 900,
        "Rendering point clouds using GL_POINTS",
        false,
        true,
        4, 5
    );

    /*
    { // Castle of chinchilla
        std::string path = "res/point_clouds/castle_of_chinchilla_4m.las";
        BasicPointRenderer basic_point_renderer(window_settings, path, glm::vec3(0.1f, 0.0f, 1.7f));
        basic_point_renderer.run();
    }
    */

    /*
    { // Arc triomphe
        std::string path = "res/point_clouds/arc_triomphe_15m.las";
        BasicPointRenderer basic_point_renderer(window_settings, path, glm::vec3(0.0f, 0.5f, 3.2f));
        basic_point_renderer.run();
    }
    */

    { // Castle of loarre
        std::string path = "res/point_clouds/castle_of_loarre_42m.las";
        BasicPointRenderer basic_point_renderer(window_settings, path, glm::vec3(0.5f, 2.0f, 7.5f));
        basic_point_renderer.run();
    }

    return 0;
}

