#include "game.h"
#include "globals.h"
#include "logger.h"
#include "timer.h"

#include <stdio.h>

game_t *game;

int main() {
    game_init("TradesKill");


    while (!game->window->should_close) {
        timer_start();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // poll for events
        glfwPollEvents();

        // swap buffers
        glfwSwapBuffers(game->window->gl_window);

        timer_end();
    }

    game_destroy();
    logline(INFO, "Exiting");

    return 0;
}
