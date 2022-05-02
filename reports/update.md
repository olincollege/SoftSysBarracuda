# Raytracing Renderer
Mateos Norian, Krishna Suresh, Merwan Yeditha

## Project Goals
Our overall goal with this project is to explore rendering and specifically ray tracing algorithms. On the lower end of our project expectation we aim to mainly implement a basic form of ray tracing in C using a pre-existing visualization library such as OpenGL. Our next level primarily focuses on the GPU computing aspect of modern rendering engines. We hope to convert our C implementation to a Cuda C compatible version that is able to multithread the rendering on the GPU. Finally, our stretch goal is to incorporate this renderer into a webapp using WebAssembly.  

## Learning Goals
- Understand basics of ray tracing and rendering
- Gaining exposure to basic 3D graphics/rendering
- Explore GPU computing
- Explore WebAssembly

## Progress
So far we have mainly dedicated effort toward researching and understanding the tools and methods used for rendering. We also looked into Cuda C and explored how we might be able to eventually run the same C code on multiple GPU threads.

Resources we have found:
- https://cal.cs.umbc.edu/Courses/CMSC435-F15/Slides/raytrace.pdf
- https://github.com/RayTracing/raytracing.github.io
- https://www.nersc.gov/assets/pubs_presos/MattsonTutorialSC14.pdf

## Current Tasks
- Implement a vector collision detector to find intersections with a sphere - Merwan
- Use an existing visualization library to produce an image given a list of pixels - Mateos
- Implement diffuse component calculation - Mateos
- Implement ambient and specular component calculation - Krishna
- Integrate lighting calculations into pixel results - Krishna
