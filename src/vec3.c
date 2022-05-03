#include "vec3.h"


float Q_rsqrt( float number )
{
    // shamelessly stolen from the quake 3 algo
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;
	i  = 0x5f3759df - ( i >> 1 ); 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );

	return y;
}

void norm(Vec3* vec) {
    float old_sqrt = 1/(sqrt(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z));
    float inv_sqrt = Q_rsqrt(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z);
    vec->x = (vec->x)*old_sqrt;
    vec->y = (vec->y)*old_sqrt;
    vec->z = (vec->z)*old_sqrt;
}

Vec3 get_norm(Vec3* vec){
    float old_sqrt = 1/(sqrt(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z));
    Vec3 res = {vec->x*old_sqrt, vec->y*old_sqrt, vec->z*old_sqrt};
    return res;
}

void plus(Vec3* vec, float n) {
    vec->x = vec->x+n;
    vec->y = vec->y+n;
    vec->z = vec->z+n;
}

float mag(Vec3* vec){
    return sqrt(vec->x*vec->x+vec->y*vec->y+vec->z*vec->z);
}

void op_plus (Vec3* vec, Vec3* res, float n){
    res->x = vec->x+n;
    res->y = vec->y+n;
    res->z = vec->z+n; 
}

void scale(Vec3* vec, float n){
    vec->x = vec->x*n;
    vec->y = vec->y*n;
    vec->z = vec->z*n;
}

void op_scale(Vec3* vec, Vec3* res, float n){
    res->x = vec->x*n;
    res->y = vec->y*n;
    res->z = vec->z*n;
}

Vec3 op_vecs(Vec3 vec, Vec3 vec2, int op){
    Vec3 res;
    switch(op){
        case 1: //addition
            res.x = vec.x+vec2.x;
            res.y = vec.y+vec2.y;
            res.z = vec.z+vec2.z;
        case 2: //subtraction
            res.x = vec.x-vec2.x;
            res.y = vec.y-vec2.y;
            res.z = vec.z-vec2.z;
        case 3: //mult
            res.x = vec.x*vec2.x;
            res.y = vec.y*vec2.y;
            res.z = vec.z*vec2.z;
        case 4: //division
            res.x = vec.x/vec2.x;
            res.y = vec.y/vec2.y;
            res.z = vec.z/vec2.z;
    }
    return res;
}

float dot(Vec3 a, Vec3 b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

void op_multiple(Vec3* a, Vec3* b, Vec3* c, Vec3* d, Vec3* res){
    res->x = a->x+b->x+c->x+d->x;
    res->x = a->y+b->y+c->y+d->y;
    res->z = a->z+b->z+c->z+d->z;
}

Vec3 ray_at(Ray r, float t){
    Vec3 res = {r.orig.x + r.dir.x*t, r.orig.y + r.dir.y, r.orig.z + r.dir.z};
    return res;
}

Vec3 random_vec(){
    float x = 2*((float)rand()/(float)(RAND_MAX/1)-0.5);
    float y = 2*((float)rand()/(float)(RAND_MAX/1)-0.5);
    float z = 2*((float)rand()/(float)(RAND_MAX/1)-0.5);
    Vec3 res = {x,y,z};
    return res;
}

Vec3 random_in_unit_sphere() {
    while (1) {
        Vec3 p = random_vec();
        if (len_sq(p) >= 1) continue;
        return p;
    }
}

Vec3 random_in_hemisphere(Vec3 normal) {
    Vec3 in_unit_sphere = random_in_unit_sphere();
    //printf("%f %f %f\n", in_unit_sphere.x, in_unit_sphere.y, in_unit_sphere.z);
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        scale(&in_unit_sphere, -1);
        return in_unit_sphere;
}


float len_sq(Vec3 vec){
    return vec.x*vec.x+vec.y*vec.y+vec.z*vec.z;
}