#version 450 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D imgOutput;

struct Color
{
    uint r;
    uint g;
    uint b;
    uint a;
};

layout(std430, binding = 4) buffer colorLayout
{
    Color color[];
};


uniform ivec2 u_image_size;

void main()
{
    ivec2 screen_coords = ivec2(
        gl_WorkGroupID.x,
        gl_WorkGroupID.y
    );

    uint screen_coords_idx = screen_coords.x * u_image_size.y + screen_coords.y;

    imageStore(
        imgOutput,
        screen_coords,
        vec4(
            float(color[screen_coords_idx].r) / color[screen_coords_idx].a,
            float(color[screen_coords_idx].g) / color[screen_coords_idx].a,
            float(color[screen_coords_idx].b) / color[screen_coords_idx].a,
            1.0f
        )
    );
}
