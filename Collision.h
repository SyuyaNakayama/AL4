#pragma once
#include "CollisionPrimitive.h"

class Collision
{
private:
	static void ClosestPtPoint2Triangle(const Vector3& point, const Triangle& triangle, Vector3* closest);
public:
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter = nullptr);
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, Vector3* inter = nullptr);
};