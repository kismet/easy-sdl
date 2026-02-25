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

#include <cstdio>

#include "../../include/easy_sdl.h"


const SDL_Color red = { 255, 0, 0 };
const SDL_Color green = { 0, 255, 0 };
const SDL_Color blue = { 0, 0, 255 };

const SDL_Color white = { 255, 255, 0 };
const SDL_Color black = { 0, 0, 0 };

const SDL_Color yellow = { 255, 255, 0 };
const SDL_Color purple = { 255, 0, 255 };
const SDL_Color cyan = { 0, 255, 255 };

double mean(int* values, int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum+=values[i];
    }
    sum /= n;
    return sum;
}

int main(int argc, char* argv[]) {
    int countFrames = 0;
    int countMeasures = 0;
    int index = 0;
    long lastTime = 0;
    const int MEASURES_LENGTH = 7;
    int measures[MEASURES_LENGTH];

    EDL_Init();

    Easy_Asset_t * font = EDL_LoadAsset("assets/fonts/CrayonLibre-Regular.ttf");
    if(font == NULL ) {
        font = EDL_LoadAsset("../assets/fonts/CrayonLibre-Regular.ttf");
    }

    //Definisco un primo stile rosso e grande
    TextStyle_t titleStyle;
    titleStyle.font = font;
    titleStyle.size = 48;
    titleStyle.foreground = red;

    TextStyle_t valueStyle = titleStyle;

    bool running = true;
    SDL_Event event;
    lastTime = SDL_GetTicks();

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                    running = false;
                }
        }
        EDL_FrameClear();
        EDL_SetTextStyle(&titleStyle);
        EDL_DrawText(50,50,"FPS:");
        countFrames++;
        if ( lastTime + 100 < SDL_GetTicks() ) {
            measures[index] = countFrames;
            countFrames = 0;
            countMeasures++;
            countMeasures = countMeasures > MEASURES_LENGTH ? MEASURES_LENGTH : countMeasures;
            lastTime = SDL_GetTicks();
            index = (index + 1) % MEASURES_LENGTH;
        };
        double meanValue = mean(measures, countMeasures );
        if (meanValue < 20) {
            valueStyle.foreground = red;
        }else if ( meanValue < 60 ) {
            valueStyle.foreground = yellow;
        }else {
            valueStyle.foreground = green;
        }
        EDL_SetTextStyle(&valueStyle);
        char text[100];
        snprintf(text, 100, "%4.2f", meanValue);
        EDL_DrawText(150,50,text);
        EDL_FramePresent();
    }

    EDL_Destroy();
    return 0;
}
