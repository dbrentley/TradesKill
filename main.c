#include "game.h"
#include "globals.h"
#include "logger.h"
#include "shader.h"
#include "timer.h"

game_t *game;

int main() {
    game_init("TradesKill");
    GLuint default_program =
            shader_program_create("assets/shaders/default.v.shader",
                                  "assets/shaders/default.f.shader");
    shader_program_bind_attribute_location(default_program, 0, "in_Position");
    shader_program_bind_attribute_location(default_program, 1, "in_Color");
    shader_program_link(default_program);
    GLint mvp_uniform =
            shader_program_get_uniform_location(default_program, "mvp");


    while (!game->window->should_close) {
        timer_start();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(default_program);

        for (int x = 0; x < game->current_scene->sprite_size; x++) {
            game->current_scene->sprites[x]->update(game->current_scene->sprites[x]);
        }

        // poll for events
        glfwPollEvents();

        // swap buffers
        glfwSwapBuffers(game->window->gl_window);

        glUseProgram(0);
        timer_end();
    }

    game_destroy();
    logline(INFO, "Exiting");

    return 0;
}
