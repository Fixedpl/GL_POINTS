#pragma once
#include "ComputeShaderPointRenderer.h"


class CSEarlyZRenderer : public ComputeShaderPointRenderer
{
public:

	CSEarlyZRenderer(const uint32_t& screen_width, const uint32_t& screen_height);

	void init(const std::vector<PointData>& point_data);

	void render(const glm::mat4& mvp);

	void cleanup();

	void prepareComputeShader();
};

