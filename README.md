# RaytracerNJ_gl
real time ray tracing renderer based on opengl
### Features:   
- OpenGL4.6 based
- Path tracing
- Russian roulette
- Sample light source
- BVH acceleration structure
- PBR materials
- Spatial denoising using Joint Bilateral filtering (depth,normal,color) 
- Temporal denoising using back projection
- Detection of the reused pixel to reduce lagging 
- .obj model
### Control:
- **WASD** moving positon
- **mouse** change yaw and pitch
- **scroll** change FOV
### Examples:
#### Direct Illumination
<img width="962" alt="direct_illumination" src="https://github.com/niji127/RaytracerNJ_gl/assets/152270816/c05c3c7d-475c-4e4b-a29c-426ddbe6b4cc"><br>
#### 1 bounce
<img width="962" alt="1_bounce" src="https://github.com/niji127/RaytracerNJ_gl/assets/152270816/2f44e211-16c2-44d2-94f9-91953a1c47cb"><br>
#### Global Illumination
<img width="962" alt="global_illumination" src="https://github.com/niji127/RaytracerNJ_gl/assets/152270816/948d0bcf-3bb6-4e6b-a7ac-b483c1acdb4f"><br>
#### 15fps on RTX4060 laptop / 65.6k triangles / 720p / Russian_Roulette=0.8
![record](https://github.com/niji127/RaytracerNJ_gl/assets/152270816/6cbdc754-529a-4364-98ec-e20a481c7e8f)
