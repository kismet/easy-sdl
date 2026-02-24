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

    Easy_Asset_t * regular = EDL_LoadAsset("assets/fonts/CrayonLibre-Regular.ttf");
    if(regular == NULL ) {
        regular = EDL_LoadAsset("../assets/fonts/CrayonLibre-Regular.ttf");
    }

    Easy_Asset_t * space = EDL_LoadAsset("assets/fonts/SpaceNova-6Rpd1.otf");
    if(space == NULL ) {
        space = EDL_LoadAsset("../assets/fonts/SpaceNova-6Rpd1.otf");
    }

    //Definiamo un po' di colori
    SDL_Color red = { 255, 0, 0 };
    SDL_Color green = { 0, 255, 0 };
    SDL_Color blue = { 0, 0, 255 };
    SDL_Color yellow = { 255, 255, 0 };

    //Definisco un primo stile regular di grande e rosso
    TextStyle_t regularStyle;
    regularStyle.font = regular;
    regularStyle.size = 48;
    regularStyle.foreground = red;

    //Definisco uno stile space cambiando font, colore e dimensione
    TextStyle_t spaceStyle = regularStyle;
    spaceStyle.font = space;
    spaceStyle.size = 32;
    spaceStyle.foreground = green;

    bool running = true;
    SDL_Event event;
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                    running = false;
                }
        }
        EDL_FrameClear();
        EDL_SetTextStyle(&regularStyle);
        EDL_DrawText(50,50,"Writing with EDL!");
        EDL_SetTextStyle(&spaceStyle);
        EDL_DrawText(50,150,"Cambio il colore e la dimensione!");
        EDL_DrawText(50,250,"Ed il testo rimane del colore della penna...");
        EDL_FramePresent();
    }

    EDL_Destroy();
    return 0;
}
