#pragma once
#include <vector>

#include "PointData.h"



class PointRenderer
{
public:

	virtual void init(const std::vector<PointData>& point_data) = 0;

	virtual void render(const glm::mat4& mvp) = 0;

	virtual void onImGuiUpdate() {}

	virtual void cleanup() = 0;

};

