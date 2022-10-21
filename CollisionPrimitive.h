#pragma once
#include "Vector3.h"

struct Sphere
{
	Vector3 center{};
	float radius = 1.0f;
};

struct Plane
{
	Vector3 normal{};
	float distance = 0;
};