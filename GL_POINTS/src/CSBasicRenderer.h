#pragma once
#include "ComputeShaderPointRenderer.h"


class CSBasicRenderer : public ComputeShaderPointRenderer
{
public:

	CSBasicRenderer(const uint32_t& screen_width, const uint32_t& screen_height);

	void init(const std::vector<PointData>& point_data);

	void render(const glm::mat4& mvp);

	void cleanup();

	void prepareComputeShader();

};

