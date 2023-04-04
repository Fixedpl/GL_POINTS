#pragma once

#include "PointRenderer.h"


class EmptyPointRenderer : public PointRenderer
{
public:

	void init(const std::vector<PointData>& point_data) {}

	void render(const glm::mat4& mvp) {}

	void cleanup() {}

};

