#version 450 core

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

struct Point
{
    float x;
    float y;
    float z;

    float r;
    float g;
    float b;
};

struct Color
{
    uint r;
    uint g;
    uint b;
    uint a;
};

layout(std430, binding = 2) buffer depthLayout
{
    uint depth_buffer[];
};

layout(std430, binding = 3) buffer pointsLayout
{
    Point points[];
};

layout(std430, binding = 4) buffer colorLayout
{
    Color color[];
};

uniform mat4 u_MVP;
uniform ivec2 u_image_size;

void main()
{
    uint idx = gl_LocalInvocationIndex +
        gl_WorkGroupSize.x * gl_WorkGroupSize.y * (gl_WorkGroupID.x * gl_NumWorkGroups.x + gl_WorkGroupID.y);

    vec4 pos = u_MVP * vec4(points[idx].x, points[idx].y, points[idx].z, 1.0);
    pos.xyz = pos.xyz / pos.w;

    if (pos.x < -1.0 || pos.x > 1.0 || pos.y < -1.0 || pos.y > 1.0 || pos.w <= 0.0) {
        return;
    }

    ivec2 screen_coords = ivec2(
        (pos.x * 0.5 + 0.5) * u_image_size.x,
        (pos.y * 0.5 + 0.5) * u_image_size.y
    );

    uint screen_coords_idx = screen_coords.x * u_image_size.y + screen_coords.y;

    float depth = uintBitsToFloat(depth_buffer[screen_coords_idx]);

    if (pos.z <= depth * 1.0005f) {
        atomicAdd(color[screen_coords_idx].r, int(points[idx].r * 256));
        atomicAdd(color[screen_coords_idx].g, int(points[idx].g * 256));
        atomicAdd(color[screen_coords_idx].b, int(points[idx].b * 256));
        atomicAdd(color[screen_coords_idx].a, 256);
    }
}
