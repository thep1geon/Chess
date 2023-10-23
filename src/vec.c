#include "include/types.h"

vec2 Vec2(f32 x, f32 y) {
    vec2 v = (vec2){x, y};
    return v;
}

vec2 vec2_dot(vec2 a, vec2 b) {
    return (vec2){a.x * b.x, a.y * b.y};
}

vec2 vec2_sum(vec2 a, vec2 b) {
    return (vec2){a.x + b.x, a.y + b.y};
}

vec2 vec2_sub(vec2 a, vec2 b) {
    return (vec2){a.x - b.x, a.y - b.y};
}

vec2 vec2_scalar_mult(vec2 v, f32 scalar) {
    return (vec2){v.x * scalar, v.y * scalar};
}

f32 vec2_norm(vec2 v) {
    return (f32) sqrtf(v.x * v.x + v.y * v.y);
}

vec2 vec3_to_vec2(vec3 v) {
    return (vec2){v.x, v.y};
}

vec3 Vec3(f32 x, f32 y, f32 z) {
    return (vec3){x, y, z};
}

vec3 vec3_dot(vec3 a, vec3 b) {
    return (vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

vec3 vec3_sum(vec3 a, vec3 b) {
    return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3 vec3_sub(vec3 a, vec3 b) {
    return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

vec3 vec3_scalar_mult(vec3 v, f32 scalar) {
    return (vec3){v.x * scalar, v.y * scalar, v.z * scalar};
}

f32 vec3_norm(vec3 v) {
    return (f32) sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 vec2_to_vec3(vec2 v) {
    return (vec3){v.x, v.y, 0};
}
