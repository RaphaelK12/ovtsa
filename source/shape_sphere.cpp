#include "shape_sphere.hpp"
#include "main.hpp"
#include "transform.hpp"
#include "material.hpp"
#include <glm/gtc/constants.hpp>
#include <glm/geometric.hpp>
#include <glm/exponential.hpp>

glm::vec3 sphere::computeNormal(const glm::vec3 & Position, const glm::vec3 & RayDirection) const
{
/*
	if(dot(Position, RayDirection) < 0)
		return glm::vec3(g_Perlin.Noise1(Position.x), g_Perlin.Noise1(Position.y), g_Perlin.Noise1(Position.z));
	else
		return glm::vec3(-g_Perlin.Noise1(-Position.x), -g_Perlin.Noise1(-Position.y), -g_Perlin.Noise1(-Position.z));
*/
	if (glm::dot(Position, RayDirection) < 0)
		return glm::vec3(Position.x, Position.y, Position.z);
	else
		return glm::vec3(-Position.x, -Position.y, -Position.z);
}

bool sphere::intersect
(
	ray const & Ray, 
	intersection & Intersection
) const
{
	bool bHit = false;

	float b = glm::dot(Ray.getPosition(), Ray.getDirection());
	float c = glm::dot(Ray.getPosition(), Ray.getPosition()) - 1.0f; // 1.0f => Radius
	float d = b * b - c;

	if(d > glm::epsilon<float>())
	{
		float e = glm::sqrt(d);
		float x1 = -b - e;
		float x2 = -b + e;
		if(x1 > glm::epsilon<float>())
		{
			Intersection.setLocalPosition(Ray.getPosition() + Ray.getDirection() * x1);
			bHit = true;
		}
		else if(x2 > glm::epsilon<float>())
		{
			Intersection.setLocalPosition(Ray.getPosition() + Ray.getDirection() * x2);
			bHit = true;
		}
	}

	return bHit;
}
