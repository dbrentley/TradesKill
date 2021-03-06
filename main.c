#include "game.h"
#include "globals.h"
#include "shader.h"
#include "timer.h"

game_t *game;
asset_t *hero;

int main() {
    game_init("TradesKill");
    pthread_t queue_processing_add_thread;
    pthread_create(&queue_processing_add_thread, NULL, asset_process_add_queue,
                   NULL);

    pthread_t queue_processing_rem_thread;
    pthread_create(&queue_processing_rem_thread, NULL, asset_process_rem_queue,
                   NULL);

    GLuint default_program =
            shader_program_create("assets/shaders/default.v.shader",
                                  "assets/shaders/default.f.shader");
    shader_program_bind_attribute_location(default_program, 0, "in_Position");
    shader_program_bind_attribute_location(default_program, 1, "in_Color");
    shader_program_link(default_program);
    GLint mvp_uniform =
            shader_program_get_uniform_location(default_program, "mvp");

    asset_add(ORE_GOLD, NULL, -2.0f, 0, NONE, false);
    hero = asset_create(HERO, "hero", 0, 0, IDLE_E, false);
    hero->velocity = 5.0f;


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

        for (int x = 0; x < game->assets_count; x++) {
            if (game->assets[x]->index != -1) {
                game->assets[x]->update(game->assets[x]);
            }
        }

        glBufferSubData(GL_ARRAY_BUFFER, 0, MAX_SPRITES * sizeof(float) * 16,
                        game->gle->vertex_buffer);

        glDrawElements(GL_TRIANGLES, MAX_SPRITES, GL_UNSIGNED_INT, 0);


        // swap buffers
        glfwSwapBuffers(game->window->gl_window);
        glfwPollEvents();
        timer_end();
    }

    pthread_join(queue_processing_add_thread, NULL);
    pthread_join(queue_processing_rem_thread, NULL);
    game_destroy();

    return 0;
}
