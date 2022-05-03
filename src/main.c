#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "objects.h"
#include "vec3.h"

Color calc_color(Ray r, Sphere s, Sphere gnd, int depth){
    // right now make a solid color
    //printf("%f %f %f\n",r.dir.x, r.dir.y, r.dir.z);

    Vec3 r_normd = get_norm(&(r.dir));
    Color color = {0,0,0};
    if (depth==0) return color;
    float obj_t;
    float gnd_t;
    float t;
    Vec3 center;
    float rad;
    gnd_t = hit_sphere(&r, gnd.center, gnd.rad);
    obj_t = hit_sphere(&r, s.center, s.rad);
    if (gnd_t > 0.0 && obj_t > 0.0){ //ray intersects both, go with object
        t = obj_t;
        center = *s.center;
        rad = s.rad;
    } else if (gnd_t > 0.0 && obj_t < 0.0){ //ray intersects gnd not obj, go with gnd
        t = gnd_t;
        center = *gnd.center;
        rad = gnd.rad;
    } else if (obj_t > 0.0 && gnd_t < 0.0){ // ray intersects obj not gnd, go with obj
        t = obj_t;
        center = *s.center;
        rad = s.rad;
    } else{ // ray intersects nothing
        float t = 0.5*(r_normd.y + 1.0);
        color.r = (1.0-t)+t*0.5;
        color.g = (1.0-t)+t*0.7;
        color.b = (1.0-t)+t*1.0;
        return color;
    }
    
    Vec3 r_at = ray_at(r, t);
    //r_at.z -= -1;
    //norm(&r_at);
    Vec3 normal = {(r_at.x-center.x)/rad,(r_at.y-center.y)/rad,(r_at.z-center.z)/rad};
    //printf("%f %f %f\n", normal.x, normal.y, normal.z);
    //norm(&normal);
    //printf("%f %f %f\n", normal.x, normal.y, normal.z);
    color.r = (normal.x+1.0)*.5;
    color.g = (normal.y+1.0)*.5;
    color.b = (normal.z+1.0)*.5;
    //scale(&normal, 1/rad);
    Vec3 rand_hem = random_in_hemisphere(normal);
    Vec3 target = {r_at.x+rand_hem.x, r_at.y+rand_hem.y, r_at.z+rand_hem.z};
    Vec3 new_ = {target.x-r_at.x,target.y-r_at.y,target.z-r_at.z};
    Ray new = {r_at, new_};
    color = calc_color(new, s, gnd, depth-1); 
    ////printf("not circle\n");
    color.r = 0.5*color.r;
    color.g = 0.5*color.g;
    color.b = 0.5*color.b;

    return color;
}

float rand_float(){
    return (float)rand()/(float)(RAND_MAX/1);
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
    Vec3 sphere_center = {0,0.05,-1};
    Sphere s = {&sphere_center, 0.5};
    Vec3 gnd_center = {0, -100.5, -1};
    Sphere gnd = {&gnd_center, 100};
    Color color;
    Color temp_col;
    int num_samples = 50;
    float scale = 1.0/(float)num_samples;
    for (int j = image_height-1; j>=0; j--){
        for (int i = 0; i < image_width; i++){
            color.r = 0;
            color.g = 0;
            color.b = 0;
            for (int s_ = 0; s_ < num_samples; s_++){
                float u = ((float)i + rand_float()) / (image_width+1);
                float ve = ((float)j + rand_float()) / (image_height+1);
                //printf("%f\n", rand_float());
                Vec3 dir = {lower_left.x+(h.x*u)+(v.x*ve)-origin.x,
                            lower_left.y+(h.y*u)+(v.y*ve)-origin.y,
                            lower_left.z+(h.z*u)+(v.z*ve)-origin.z};
                //printf("%f %f %f\n", dir.x, dir.y, dir.z);
                Ray r = {origin, dir};
                temp_col = calc_color(r, s, gnd, 1000);
                //printf("%d %d %d\n", (int)(temp_col.r*255.999), (int)(temp_col.g*255.999), (int)(temp_col.b*255.999));
                color.r += temp_col.r;
                color.g += temp_col.g;
                color.b += temp_col.b;
            }
            color.r *= scale;
            color.g *= scale;
            color.b *= scale;
            printf("%d %d %d\n", (int)(color.r*255.999), (int)(color.g*255.999), (int)(color.b*255.999));
        }
    }
}

