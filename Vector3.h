#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

struct Vector3 {
    float x, y, z;

    float distanceTo(const Vector3& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 normalize() const {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length == 0.0f) return {0.0f, 0.0f, 0.0f};
        return {x / length, y / length, z / length};
    }
};

#endif
