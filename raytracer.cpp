#include <iostream>
#include "default_files/parser.h"
#include "default_files/ppm.h"

#include "additional_files/math.h"

typedef unsigned char RGB[3];

int main(int argc, char* argv[])
{
    parser::Scene scene;

    scene.loadFromXml("simple.xml");

    for(auto camera : scene.cameras){
        Vec3f e = math::Vec3fCopy(camera.position);
        Vec3f v = math::Vec3fCopy(camera.up);
        Vec3f w = math::Vec3fScalarMultiplication(camera.gaze, -1);
        Vec3f u = math::Vec3fCrossProduct(v, w);
        
        float d = camera.near_distance;
        int width = camera.image_width;
        int height = camera.image_height;

        double pixelWidth = (camera.near_plane.y-camera.near_plane.x) / width;
        double pixelWidthOffset = pixelWidth / 2;
        double pixelHeight = (camera.near_plane.w-camera.near_plane.z) / height;
        double pixelHeightOffset = pixelHeight / 2;

        Vec3f m = math::Vec3fAddition(e, math::Vec3fScalarMultiplication(w, -d));
        Vec3f lu = math::Vec3fScalarMultiplication(u, camera.near_plane.x);
        Vec3f tv = math::Vec3fScalarMultiplication(v, camera.near_plane.w);
        Vec3f q = math::Vec3fAddition(m, math::Vec3fAddition(lu, tv));

        unsigned char* image = new unsigned char [width * height * 3];

        int i = 0;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                Vec3f su = math::Vec3fScalarMultiplication(u,x * pixelWidth + pixelWidthOffset);
                Vec3f sv = math::Vec3fScalarMultiplication(v,y * pixelHeight + pixelHeightOffset);
                Vec3f s = math::Vec3fAddition(q, math::Vec3fAddition(su, math::Vec3fScalarMultiplication(sv, -1)));
                
                float d;
                bool isBreak = false;
                for(d = 0; d < 1; d += 0.1){
                    for(auto sphere : scene.spheres) {
                        if(x < 100 && x > 10 && y < 100 && y > 10)
                            isBreak = true;
                            break;
                    }
                    if(isBreak)
                        break;
                }
        
                image[i++] = d < 1 ? 255 : scene.background_color.x;
                image[i++] = d < 1 ? 255 : scene.background_color.y;
                image[i++] = d < 1 ? 255 : scene.background_color.z;
            }
        }

        write_ppm(camera.image_name.c_str(), image, width, height);
    }
    
}