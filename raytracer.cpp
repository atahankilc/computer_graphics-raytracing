#include <iostream>

#include "Scene.h"

int main(int argc, char* argv[])
{
    auto scene = new Scene(argv[1]);
    scene->renderCameras();
    delete scene;
    return 0;
}