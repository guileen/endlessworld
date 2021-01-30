#ifndef IMMERSION_RENDER_H
#define IMMERSION_RENDER_H
namespace immersion
{
    int setCamera(float x, float y, float z);
    int render(void* model, float x, float y, float z);
}
#endif