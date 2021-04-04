#include "game.h"
#include "shader.h"
#include "utils.h"

#include <stdlib.h>

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

    float min = -45.0f;
    float max = 45.0f;

    for (int i = 0; i < 50; i++) {
        asset_create(ORE_GOLD, NULL, float_rand(min, max), float_rand(min, max),
                     NONE, false);
    }
    hero = asset_create(HERO, "hero", 0, 0, IDLE_E, false);
    hero->speed = 5.0f;


    glBindTexture(GL_TEXTURE_2D, game->atlas->texture);
    glBindVertexArray(game->gle->vao);
    glBindBuffer(GL_ARRAY_BUFFER, game->gle->vbo);

    while (!game->window->should_close && game->running) {
        timer_start();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(default_program);
        glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE,
                           (const GLfloat *) game->window->mvp);
        set_aspect(game->window->width, game->window->height);

        for (int x = 0; x < game->assets_count; x++) {
            if (game->assets[x]->index != -1) {
                game->assets[x]->update(game->assets[x]);
            }
        }

        float asset_index[game->assets_count][2];
        int asset_index_cnt = 0;
        for (int x = 0; x < game->assets_count; x++) {
            if (game->assets[x]->index != -1) {
                asset_index[asset_index_cnt][0] =
                        (float) game->assets[x]->index;
                //asset_index[asset_index_cnt][1] = game->assets[x]->col_height;
                asset_index[asset_index_cnt][1] = game->assets[x]->position.y;
                asset_index_cnt++;
            }
        }
        // bubble sort - inefficient - replace with selection or quick
        bool sorted = false;
        bool did_sort = false;
        while (sorted == false) {
            for (int i = 0; i < game->assets_count - 1; i++) {
                if (asset_index[i][1] < asset_index[i + 1][1]) {
                    float t0 = asset_index[i][0];
                    float t1 = asset_index[i][1];
                    asset_index[i][0] = asset_index[i + 1][0];
                    asset_index[i][1] = asset_index[i + 1][1];
                    asset_index[i + 1][0] = t0;
                    asset_index[i + 1][1] = t1;
                    did_sort = true;
                }
            }
            if (did_sort == true) {
                sorted = false;
                did_sort = false;
            } else {
                sorted = true;
            }
        }

        for (int i = 0; i < game->assets_count; i++) {
            int offset = (int) asset_index[i][0] * VERTEX_ELEMENTS;
            memcpy(game->gle->vertex_buffer + (i * VERTEX_ELEMENTS),
                   game->asset_array + offset, VERTEX_ELEMENTS * sizeof(float));
        }

        // render
        glBufferSubData(GL_ARRAY_BUFFER, 0,
                        game->assets_total * sizeof(float) * VERTEX_ELEMENTS,
                        game->gle->vertex_buffer);
        glDrawElements(GL_TRIANGLES, game->assets_count * 6, GL_UNSIGNED_INT,
                       0);
        //        free(vertex_buffer);
        glfwSwapBuffers(game->window->gl_window);
        glfwPollEvents();
        timer_end();
    }

    game_destroy();
    return 0;
}
