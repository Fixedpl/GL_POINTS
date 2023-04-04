#pragma once
#include <glm/glm.hpp>


struct PointData
{
	PointData(const glm::vec3& _position, const glm::vec3& _color)
		: position(_position), color(_color) {}

	glm::vec3 position;
	glm::vec3 color;
};

