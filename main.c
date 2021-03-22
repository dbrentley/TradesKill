#include "game.h"
#include "shader.h"

game_t *game;
asset_t *hero;

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

    hero = asset_create(HERO, "hero", 0, 0, 9, IDLE_E, false);
    hero->speed = 5.0f;
    asset_create(ORE_GOLD, NULL, -2.0f, 0, 0, NONE, false);
    asset_create(ORE_GOLD, NULL, -6.0f, 0, 4, NONE, false);
    asset_create(ORE_GOLD, NULL, -5.0f, 0, 3, NONE, false);
    asset_create(ORE_GOLD, NULL, -3.0f, 0, 1, NONE, false);
    asset_create(ORE_GOLD, NULL, -4.0f, 0, 2, NONE, false);


    while (!game->window->should_close && game->running) {
        timer_start();

        glBindTexture(GL_TEXTURE_2D, game->atlas->texture);
        glBindVertexArray(game->gle->vao);
        glBindBuffer(GL_ARRAY_BUFFER, game->gle->vbo);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(default_program);

        glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE,
                           (const GLfloat *) game->window->mvp);
        set_aspect(game->window->width, game->window->height);

        // update assets
        for (int x = 0; x < MAX_SPRITES; x++) {
            if (game->assets[x]->index != -1) {
                game->assets[x]->update(game->assets[x]);
            }
        }

        // render
        glBufferSubData(GL_ARRAY_BUFFER, 0,
                        game->assets_total * sizeof(float) * VERTEX_ELEMENTS,
                        game->gle->vertex_buffer);
        glDrawElements(GL_TRIANGLES, MAX_SPRITES, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(game->window->gl_window);
        glfwPollEvents();
        timer_end();
    }

    game_destroy();
    return 0;
}
