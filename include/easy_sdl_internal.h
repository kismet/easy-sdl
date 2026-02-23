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

#ifndef EASY_SDL_INTERNAL_H
#define EASY_SDL_INTERNAL_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "easy_sdl_defaults.h"
#include "easy_sdl_types.h"


/**
 * Tries to load a Font
 * This function relies on SDL_TTF libraries, and it's ment for internal to be used within the library
 * Developers using EDL as library should avoid to use this function
 * @since 0.1.0
 *
 * @param path the relative or absolute path to the Font to be loaded
 * @return a pointer to a valid Easy_Asset_t otherwise NULL on failure
 */
Easy_Asset_t* loadFont(char* path);

/**
 * Tries to load a Image
 * This function relies on SDL_Image libraries, and it's ment for internal to be used within the library
 * Developers using EDL as library should avoid to use this function
 * @since 0.1.0
 *
 * @param path the relative or absolute path to the Image to be loaded
 * @return a pointer to a valid Easy_Asset_t otherwise NULL on failure
 */
Easy_Asset_t* loadImage(char* path);


#endif //EASY_SDL_INTERNAL_H