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

#include <cmath>
#include <math.h>

#include "../../include/easy_sdl.h"

typedef struct Player {
    int16_t x = EDL_DEFAULT_WINDOW_WIDTH/2;
    int16_t y = EDL_DEFAULT_WINDOW_HEIGHT/2;
    int16_t orientation = 0;
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


    bool running = true;
    SDL_Event event;
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN ) {
                SDL_Log("Player: %d %d %d",player.x,player.y, player.orientation);
                double offset_x = 10.0f*sin(player.orientation/180.0f*3.14f);
                double offset_y = 10.0f*cos(player.orientation/180.0f*3.14f);
                SDL_Log("Delta: %.2f %2.f",offset_x, offset_y);
                switch (event.key.scancode) {
                    case SDL_SCANCODE_A: case SDL_SCANCODE_LEFT:
                        player.orientation -=1;
                        player.orientation %= 360;
                        break;
                    case SDL_SCANCODE_D: case SDL_SCANCODE_RIGHT:
                        player.orientation +=1;
                        player.orientation %= 360;
                        break;
                    case SDL_SCANCODE_S: case SDL_SCANCODE_DOWN:
                        player.x -= offset_x;
                        player.y += offset_y;
                        break;
                    case SDL_SCANCODE_W: case SDL_SCANCODE_UP:
                        player.x += offset_x;
                        player.y -= offset_y;
                        if (player.x < 0) player.x = 0;
                        if (player.y < 0) player.y = 0;
                        break;
                }
            }
        }
        EDL_FrameClear();
        uint16_t angle = player.orientation + 360;
        EDL_DrawAsset(player.x,player.y,rocket,angle,0.1f);

        EDL_FramePresent();
    }

    EDL_Destroy();
    return 0;
}
