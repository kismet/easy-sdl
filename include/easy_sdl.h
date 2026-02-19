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

#ifndef EASY_SDL_H
#define EASY_SDL_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "easy_sdl_defaults.h"
#include "easy_sdl_types.h"


/**
 * This is the <b>FIRST</b> that must invoked by the developers
 * for creating a proper context, otherwise all the other function
 * will fail
 * By default this crate a FRAMED window with Hardware acceleration
 * enabled, moreover this function will load all the SDL most common
 * SDL subsystem (Core, Image, and Font)
 *
 * @param title The title to assign to the widow
 * @param width Width of the window
 * @param height Height of the window
 * @param options other options to pass to SDL please refers to #SDL_init()
 * @return TRUE if and only if the initialization succeeded
 */
bool EDL_init(char* title, int width, int height, uint32_t options );

/**
 * This load a 800x600 windows with "Easy SDL" as title
 * by invoking the initEasySDL function
 *
 */
bool EDL_init();

bool freeEasySDL();

// TODO lazy loading asset
// Easy_Asset_t* addAsset(char* path);

Easy_Asset_t* loadAsset(char* path);

/**
 * This function returns a loaded Asset (eventually it will try to load it)
 *
 * @param id the id that represents the asset to require
 * @return the Asset matching the id or NULL if none is found
 */
Easy_Asset_t* getAssetById(uint16_t id);

/**
 * Load a Font as Assets and return it, otherwise it will delete
 *
 *
 * @param path
 * @return
 */
Easy_Asset_t* loadFont(char* path);

Easy_Asset_t* loadImage(char* path);

void drawAsset(uint16_t x, uint16_t y, Easy_Asset_t* asset, uint16_t rotation, float scaling);

void drawAsset(uint16_t x, uint16_t y, Easy_Asset_t* asset, uint16_t rotation);

void drawAsset(uint16_t x, uint16_t y, Easy_Asset_t* asset);

/**
 * Assegna lo stile e ne effettua una copia interna
 *
 * @param style
 */
void setTextStyle(TextStyle_t* style);

/**
 * Restituisce lo stile corrente
 *
 * @return
 */
TextStyle_t* getTextStyle();


/**
 * Scrive il testo con lo stile corrente nella posizione (x,y)
 * @param x
 * @param y
 */
void drawText(uint16_t x, uint16_t y, char *);

/**
 * Scrive il testo con lo stile corrente nella posizione (x,y) all'interno
 * dello spazio (w,h)
 * @param x
 * @param y
 */
void drawText(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *, uint32_t options);

/**
 * The following section contains function that allows the developer
 * to access the SDL layer for using specific function that are not
 * exposed by the EasySDL layer
 */

/**
 *
 * @return
 */
SDL_Window* getSDLWindow();

SDL_Renderer* getSDLRender();


#endif //EASY_SDL_H