#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "objects.h"
#include "vec3.h"

void calc_color(Ray r, Sphere s, Sphere gnd){
    // right now make a solid color
    //printf("%f %f %f\n",r.dir.x, r.dir.y, r.dir.z);
    Vec3 r_normd = get_norm(&(r.dir));
    Color color = {0,0,0};
    float t = 0.5*(r_normd.y + 1.0);
    color.r = (1.0-t)+t*0.5;
    color.g = (1.0-t)+t*0.7;
    color.b = (1.0-t)+t*1.0;
    t = hit_sphere(&r, gnd.center, gnd.rad);
    if (t>0.0) {
        Vec3 r_at = ray_at(r, t);
        r_at.z -= 1;
        norm(&r_at);
        color.r = 0;
        color.g = 1;
        color.b = 0;
    }
    t = hit_sphere(&r, s.center, s.rad);
    if (t>0.0) {
        Vec3 r_at = ray_at(r, t);
        r_at.z -= 1;
        norm(&r_at);
        color.r = 0.5*(r_at.x+1);
        color.g = 0.5*(r_at.y+1);
        color.b = 0.5*(r_at.z+1);
    }
    //printf("not circle\n");
    printf("%d %d %d\n", (int)(color.r*255.999), (int)(color.g*255.999), (int)(color.b*255.999));
}

int main(){
    // random ppm stuff
    printf("P3\n400 225\n255\n");
    // image params
    const float aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = 225;
    // camera params
    Vec3 origin = {0,0,0}; // not to be treated as a vector, just convenient
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0;
    Vec3 h = {viewport_width, 0, 0};
    Vec3 v = {0, viewport_height, 0};
    Vec3 foc_vec = {0, 0, focal_length};
    Vec3 lower_left = {origin.x-(h.x/2)-(v.x/2),
                            origin.y-(h.y/2)-(v.y/2),
                            origin.z-(h.z/2)-(v.z/2)-focal_length};

    //create the sphere
    Vec3 sphere_center = {0,0,-1};
    Sphere s = {&sphere_center, 0.5};
    Vec3 gnd_center = {0, -100, -1};
    Sphere gnd = {&gnd_center, 100};
    
    for (int j = image_height-1; j>=0; j--){
        for (int i = 0; i < image_width; i++){
            float u = (float)i / (image_width+1);
            float ve = (float)j / (image_height+1);
            Vec3 dir = {lower_left.x+(h.x*u)+(v.x*ve)-origin.x,
                        lower_left.y+(h.y*u)+(v.y*ve)-origin.y,
                        lower_left.z+(h.z*u)+(v.z*ve)-origin.z};
            //printf("%f %f %f\n", dir.x, dir.y, dir.z);
            Ray r = {origin, dir};
            calc_color(r, s, gnd);
        }
    }
}
