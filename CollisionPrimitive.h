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

struct Triangle
{
	Vector3 p[3]{}, normal{};
	void ComputeNormal();
};

struct Ray
{
	Vector3 start, dir = { 1,0,0 };
};