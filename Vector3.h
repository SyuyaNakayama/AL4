#pragma once
class Vector3
{
public:
	float x, y, z;
public:
	Vector3();
	Vector3(float x, float y, float z);

	float length() const; // ノルム(長さ)
	Vector3& normalize(); // 正規化
	float dot(const Vector3& v) const; // 内積値
	Vector3 cross(const Vector3& v) const; // 外積値

	// 単項演算子オーバーロード
	Vector3 operator+() const;
	Vector3 operator-() const;

	// 代入演算子オーバーロード
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

// 2項演算子オーバーロード
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);

const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);