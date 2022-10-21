#include "Collision.h"
#include <math.h>

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter)
{
    // 座標系の原点から球の中心座標への距離
    float dist = sphere.center.dot(plane.normal);
    // 平面の原点座標を減算することで、平面と球の中心との距離が出る
    dist -= plane.distance;
    // 距離の絶対値が半径より大きければ当たっていない
    if (fabsf(dist) > sphere.radius) { return false; }
    // 疑似交点を計算
    if (inter) { *inter = -dist * plane.normal + sphere.center; } // 平面上の最近接点を疑似交点とする

    return true;
}
