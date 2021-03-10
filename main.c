#include "game.h"
#include "globals.h"
#include "logger.h"
#include "shader.h"
#include "timer.h"
#include "utils.h"

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


    for (int a = 0; a < MAX_SPRITES; a++) {
        asset_create(float_rand(-20.0f, 20.0f), float_rand(-20.0f, 20.0f),
                     ORE_COPPER);
    }

    while (!game->window->should_close && game->running) {
        timer_start();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(default_program);
        glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE,
                           (const GLfloat *) game->window->mvp);
        if (game->window->update_aspect) {
            set_aspect(game->window->width, game->window->height);
            game->window->update_aspect = false;
        }
        game_render();

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
