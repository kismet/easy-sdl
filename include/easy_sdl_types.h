/*
 * Copyright 2026 Stefano Lenzi &lt;stefano@lenzi.pro&gt;
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef EASY_SDL_TYPE_H
#define EASY_SDL_TYPE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>


typedef struct Image_Asset {
    uint16_t height;
    uint16_t width;
    SDL_Texture* texture;
    SDL_Surface* surface;
} Image_Asset_t;

typedef struct Font_Asset {
    int size;
    bool monospaced;
    TTF_Font* font;
} Font_Asset_t;

typedef enum Text_Options{
    TEXT_LEFT = 0,
    TEXT_CENTERED = 1,
    TEXT_RIGHT = 2
} Text_Options_t;

typedef enum Asset_Type{
    ASSET_IMAGE, ASSET_FONT
} Asset_Type_t;

typedef union Easy_Asset_Union {
    Image_Asset_t image;
    Font_Asset_t font;
} Easy_Asset_Union_t;


typedef struct Easy_Asset {
    Asset_Type_t type;
    uint32_t id;
    bool loaded;
    char* origin;
    char* name;
    Easy_Asset_Union_t detail;
} Easy_Asset_t;

typedef struct TextStyle {
    bool solid;
    uint8_t size;
    bool italic;
    bool underline;
    bool bold;
    bool strikethrough;
    Easy_Asset_t* font;
    SDL_Color foreground = {255, 255, 255, 255};
} TextStyle_t;



#endif //EASY_SDL_TYPE_H