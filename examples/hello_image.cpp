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

#include "../include/easy_sdl.h"

int main(int argc, char* argv[]) {
    EDL_Init();

    Easy_Asset_t * img = EDL_LoadAsset("assets/1.png");
    if(img == NULL ) {
        img = EDL_LoadAsset("../assets/1.png");
    }

    Easy_Asset_t * img2 = EDL_LoadAsset("assets/2.png");
    if(img2 == NULL ) {
        img2 = EDL_LoadAsset("../assets/2.png");
    }


    bool running = true;
    SDL_Event event;
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                running = false;
                }
        }
        SDL_RenderClear(getSDLRender());
        drawAsset(100,100,img,0,0.1f);
        drawAsset(200,200,img2,0,0.1f);
        SDL_RenderPresent(getSDLRender());
    }

    EDL_Destroy();
    return 0;
}
