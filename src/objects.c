#include "objects.h"

float hit_sphere(Ray* r, Vec3* center, float rad){
    Vec3 oc = {r->orig.x-center->x, r->orig.y-center->y, r->orig.x-center->z};
    op_vecs(r->orig, *center, 2);  
    float a = dot(r->dir, r->dir);
    float b = 2.0 * dot(oc, r->dir);
    float c = dot(oc, oc) - rad*rad;
    //printf("params: %f %f %f\n", oc.x,oc.y,oc.z);
    float disc = b*b-4*a*c;

    if (disc<0){
        return -1.0;
    } else {
        return (-b - sqrt(disc) ) / (2.0*a);
    }
}
