// Copyright 2026 Stefano Lenzi &lt;stefano@lenzi.pro&gt;
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "../../include/easy_sdl.h"

typedef struct Player {
    uint16_t x;
    uint16_t y;
    uint16_t orientation;
    Easy_Asset_t * avatar;
} Player_t;

Player_t player;

int main(int argc, char* argv[]) {
    EDL_Init();

    Easy_Asset_t * rocket = EDL_LoadAsset("assets/1.png");
    if(rocket == NULL ) {
        rocket = EDL_LoadAsset("../assets/1.png");
    }
    player.avatar = rocket;
    player.x = 0;
    player.y = 0;

    int const SPACESHIP_SPEED = 10;

    bool running = true;
    SDL_Event event;
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN ) {
                switch (event.key.scancode) {
                    case SDL_SCANCODE_A: case SDL_SCANCODE_LEFT:
                        player.x -= SPACESHIP_SPEED;
                        if (player.x < 0) player.x = 0;
                        break;

                    case SDL_SCANCODE_D: case SDL_SCANCODE_RIGHT:
                        player.x += SPACESHIP_SPEED;
                        break;

                    case SDL_SCANCODE_W: case SDL_SCANCODE_UP:
                        player.y -= SPACESHIP_SPEED;
                        if (player.y < 0) player.y = 0;
                        break;

                    case SDL_SCANCODE_S: case SDL_SCANCODE_DOWN:
                        player.y += SPACESHIP_SPEED;
                        break;
                }
            }
        }
        EDL_FrameClear();

        EDL_DrawAsset(player.x,player.y,rocket,0,0.1f);

        EDL_FramePresent();
    }

    EDL_Destroy();
    return 0;
}
