#include "CollisionPrimitive.h"

void Triangle::ComputeNormal()
{
	Vector3 p0_p1 = p[1] - p[0];
	Vector3 p0_p2 = p[2] - p[0];
	// 外積により、2辺に垂直なベクトルを算出する
	normal = p0_p1.cross(p0_p2);
	normal.normalize();
}