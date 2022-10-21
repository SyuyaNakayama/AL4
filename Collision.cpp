#include "Collision.h"
#include <math.h>

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter)
{
    // ���W�n�̌��_���狅�̒��S���W�ւ̋���
    float dist = sphere.center.dot(plane.normal);
    // ���ʂ̌��_���W�����Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
    dist -= plane.distance;
    // �����̐�Βl�����a���傫����Γ������Ă��Ȃ�
    if (fabsf(dist) > sphere.radius) { return false; }
    // �^����_���v�Z
    if (inter) { *inter = -dist * plane.normal + sphere.center; } // ���ʏ�̍ŋߐړ_���^����_�Ƃ���

    return true;
}
