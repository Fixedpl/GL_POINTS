#version 450 core

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D imgOutput;

struct Point
{
    float x, y, z;
    float r, g, b;
};

layout(std430, binding = 2) buffer depthLayout
{
    uint depth_buffer[];
};

layout(std430, binding = 3) buffer pointsLayout
{
    Point points[];
};

uniform mat4 u_MVP;
uniform ivec2 u_image_size;

void main()
{
    uint idx = gl_LocalInvocationIndex +
        gl_WorkGroupSize.x * gl_WorkGroupSize.y * 
        (gl_WorkGroupID.x * gl_NumWorkGroups.x + gl_WorkGroupID.y);

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

    uint point_depth = floatBitsToUint(pos.z);

    atomicMin(depth_buffer[screen_coords_idx], point_depth);

    if (point_depth > depth_buffer[screen_coords_idx]) {
        return;
    }

    imageStore(
        imgOutput,
        screen_coords,
        vec4(points[idx].r, points[idx].g, points[idx].b, 1.0)
    );
}
