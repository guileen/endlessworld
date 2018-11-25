#include "ew/ew.h"
// Include the Emscripten library only if targetting WebAssembly
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#ifdef __EMSCRIPTEN__
EndlessWorld* ew;
void updateFrame() {
    ew->updateFrame();
}
#endif

int main(int argc, const char * argv[]) {
    //Start up SDL and create window
    EndlessWorld window(800, 600);
#ifdef __EMSCRIPTEN__
    ew = &window;
    emscripten_set_main_loop(updateFrame, 0, false);
#else
    window.runLoop();
#endif
}
