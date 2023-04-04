#include <iostream>

#include "PointCloudApplication.h"




int main()
{
    WindowSettings window_settings(
        1600, 900,
        "Rendering point clouds using GL_POINTS",
        false,
        true,
        4, 5
    );

    std::vector<PointCloudSetup> point_clouds = {
        { "Castle of chinchilla", "res/point_clouds/castle_of_chinchilla_4m.las", glm::vec3(0.1f, 0.0f, 1.7f) },
        { "Arc de triomphe", "res/point_clouds/arc_triomphe_15m.las", glm::vec3(0.0f, 0.5f, 3.2f) },
        { "Castle of loarre", "res/point_clouds/castle_of_loarre_42m.las", glm::vec3(0.5f, 2.0f, 7.5f) }
    };
    
    PointCloudApplication app(window_settings, point_clouds);
    app.run();

    return 0;
}

