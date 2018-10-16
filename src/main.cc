#include "game_window.h"
#include "game.h"

int main(int argc, const char * argv[]) {
        //Start up SDL and create window
    GameWindow window("GameWindow", 800, 600, false);
    GameScean scean;
    window.changeScean(&scean);
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
    emscripten_set_main_loop_arg(window::loopFrame, NULL, 0, true);
#else
    window.runLoop();
#endif
}
