#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct color {
    float r;
    float g;
    float b;
} Color;

typedef struct ray {
    Vec3 orig; // origin of the ray vector
    Vec3 dir; // direction of the ray vector
} Ray;

float Q_rsqrt(float number);
void norm(Vec3* vec);
void plus(Vec3* vec, float n);
float mag(Vec3* vec);
void op_plus(Vec3* vec, Vec3* res, float n);
void scale(Vec3* vec, float n);
void op_scale(Vec3* vec, Vec3* res, float n);
Vec3 op_vecs(Vec3, Vec3, int);
float dot(Vec3, Vec3);
Vec3 get_norm(Vec3*);
void op_multiple(Vec3* a, Vec3* b, Vec3* c, Vec3* d, Vec3* res);
Vec3 ray_at(Ray, float);
Vec3 random_vec();
Vec3 random_in_unit_sphere();
Vec3 random_in_hemisphere(Vec3);
float len_sq(Vec3);