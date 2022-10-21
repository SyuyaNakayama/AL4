#pragma once
#include "CollisionPrimitive.h"

class Collision
{
private:

public:
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter = nullptr);
};