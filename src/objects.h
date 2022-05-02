#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "vec3.h"

typedef struct {
    Vec3* center;
    float rad;
    // 0 for no collision, 1 for single root, 2 for two roots
} Sphere;

typedef struct{
    void* obj;
    Color (*get_col)(Ray*, Vec3*, float);
} Object;

float hit_sphere(Ray*, Vec3*, float);
Color get_sphere_col(Ray*, Vec3*, float);