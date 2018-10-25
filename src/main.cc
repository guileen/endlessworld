#include "ew/ew.h"

int main(int argc, const char * argv[]) {
    //Start up SDL and create window
    EndlessWorld window(800, 600);
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
    emscripten_set_main_loop_arg(window::loopFrame, NULL, 0, true);
#else
    window.runLoop();
#endif
}
