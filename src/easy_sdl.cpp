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
#include "../include/easy_sdl_internal.h"
#include <cstring>
#include <iostream>

using namespace std;

typedef struct Easy_SDL_Context {
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    bool subsystem_sdl_loaded = false;
    bool subsystem_image_loaded = false;
    bool subsystem_ttf_loaded = false;
    uint16_t n_assets = 0;
    uint16_t max_assets = 0;
    Easy_Asset_t* assets = NULL;
    TextStyle_t* text_style = NULL;
} Easy_SDL_Context_t;

static Easy_SDL_Context_t context;

static int findAssetByName(char* path);
static bool canLoadAsset();
static Easy_Asset_t * isAssetAlreadyLoaded(char* path);

SDL_Window* getSDLWindow(){
    return context.window;
}

SDL_Renderer* getSDLRender() {
    return context.renderer;
}

bool EDL_Destroy() {
    if (!(context.subsystem_sdl_loaded
        || context.subsystem_image_loaded
        || context.subsystem_ttf_loaded ) ) {
        return true;
    }
    if ( context.renderer != NULL ) {
        SDL_RenderClear( context.renderer );
        context.renderer = NULL;
    }
    if ( context.window != NULL ) {
        SDL_DestroyWindow( context.window );
        //Considering wherever we have to consume all the event from the event-pool
        //as describe by SDL_DestroyWindow docs. Hereafter the code to use:
        /*
            SDL_Event event;
            while (SDL_PollEvent(&event));
        */
        context.window = NULL;
    }
    //TODO delete all the loaded asssets

    if (context.subsystem_ttf_loaded) {
        //We have to use this call before the TTF_Quit
        //FIXME TTF_CloseFont();
        TTF_Quit();
        context.subsystem_ttf_loaded = false;
    }
    if (context.subsystem_image_loaded) {
        context.subsystem_image_loaded = false;
    }
    if (context.subsystem_sdl_loaded) {
        SDL_Quit();
        context.subsystem_sdl_loaded = false;
    }
    return true;
}

bool EDL_Init( ) {
    return EDL_Init((char *)"EasySDL",
                       (int) EASY_SDL_DEFAULT_WINDOW_HEIGHT,
                       (int) EASY_SDL_DEFAULT_WINDOW_WIDTH,
                       (uint32_t) EASY_SDL_DEFAULT_WINDOW_OPTIONS
    );
}


bool EDL_Init(char* title, int height, int width, uint32_t options ){
    if ( context.subsystem_sdl_loaded ){
        return context.subsystem_sdl_loaded;
    }
    if ( SDL_Init( SDL_INIT_EVENTS ) < 0 ) {
        SDL_Log("Error initializing SDL: %s", SDL_GetError());
        return false;
    } else {
        //FIXME us a local_cleanup() that cleans loaded subsystem;
        context.subsystem_sdl_loaded = true;
    }

    if ( TTF_Init() < 0 ){
        SDL_Log( "Error initializing TTF Failed: %s", SDL_GetError());
        return false;
    } else {
        //FIXME us a local_cleanup() that cleans loaded subsystem;
        context.subsystem_ttf_loaded = true;
    }

    //Since SDL3 IMG subsystem is loaded and unloaded by itself
    context.subsystem_image_loaded = true;

    SDL_Window* w = NULL;
    SDL_Renderer* r = NULL;

    bool result = SDL_CreateWindowAndRenderer( title, width, height, SDL_WINDOW_RESIZABLE, &w, &r);
    if ( result ) {
        SDL_SetWindowPosition(w, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        context.window = w;
        context.renderer = r;
    } else {
        SDL_Log ( "Error getting renderer: %s" ,SDL_GetError());
        return false;
    }

    if (context.subsystem_sdl_loaded
    && context.subsystem_image_loaded
    && context.subsystem_ttf_loaded ) {
        context.max_assets = EASY_SDL_DEFAULT_ASSET_SLOT;
        context.assets = (Easy_Asset_t*) malloc(sizeof(Easy_Asset_t)*context.max_assets);
        context.n_assets = 0;
        return true;
    }else{
        //FIXME us a local_cleanup() that cleans loaded subsystem;
        return false;
    }
}

Easy_Asset_t* EDL_GetAssetById(uint16_t id){
    if(id >= context.n_assets )
        return NULL;

    return &(context.assets[id]);
}

Easy_Asset_t* EDL_LoadAsset(char* path){
    Easy_Asset_t* t = isAssetAlreadyLoaded(path);
    if (t != NULL) return t;
    SDL_Log("The asset:%s is not part of the cache, loading it");


    t = loadImage(path);
    if (t != NULL) return t;
    SDL_Log("We failed to load as IMAGE the Asset at:%s, trying again as FONT");

    t = loadFont(path);
    return t;
}

Easy_Asset_t * isAssetAlreadyLoaded(char* path){
    int idx = findAssetByName(path);
    if( idx != -1){
        return &(context.assets[idx]);
    }
    return NULL;
}

bool canLoadAsset(){
    if ( context.renderer == NULL ) {
        SDL_Log("No valid render active. Assets cannot be loaded! Function EDL_init() must be invoked before this");
        return false;
    }

    if( context.n_assets == context.max_assets ){
        //TODO increase number of assets
        //TODO defining a policies for unloading assets
        SDL_Log("FATAL ERROR! No more space for loading assets. Assets loading/unloading planned for next releases");
        return false;
    }
    return true;
}

Easy_Asset_t* loadFont(char* path){
    Easy_Asset_t* asset = isAssetAlreadyLoaded(path);
    if( asset != NULL ){
        return asset;
    }
    if(!canLoadAsset()){
        return NULL;
    }

    TTF_Font* font = TTF_OpenFont(path, EASY_SDL_DEFAULT_FONT_SIZE);

    if(!font){
        SDL_Log(
            "We failed to load the FONT at: %s Please check that file exits. SDL says:%s",
            path, SDL_GetError());
        return NULL;
    }
    asset = &(context.assets[context.n_assets]);
    asset->detail.font.font = font;
    asset->detail.font.size = EASY_SDL_DEFAULT_FONT_SIZE;
    asset->detail.font.monospaced = TTF_FontIsFixedWidth(font);
    asset->type = ASSET_FONT;
    asset->loaded = true;
    asset->id = context.n_assets;
    //asset->origin = (char *) malloc(strlen(path)); this code generates segmentation fault
    asset->origin = (char *) malloc(strlen(path) + 1); //We need to add '+1' for storing '\0'
    //if the above code crashes please use strdup
    strcpy(asset->origin,path);
    context.n_assets++;

    //TODO init name
    return asset;

}

int findAssetByName(char* path){
    for(int i=0;i<context.n_assets;i++){
        if(strcmp(path,context.assets[i].origin) == 0)
            return i;

    }
    return -1;
}

Easy_Asset_t* loadImage(char* path){
    Easy_Asset_t* asset = isAssetAlreadyLoaded(path);
    if (asset != NULL) {
        return asset; // Asset already loaded
    }
    if (!canLoadAsset()) {
        SDL_Log("Cannot load asset: asset array is full or renderer is null.");
        return NULL;
    }
    SDL_Surface* image = IMG_Load(path);
    if (!image) {
        SDL_Log("Unable to load image %s. SDL says: ",path,  SDL_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(context.renderer, image);
    if (!texture) {
        SDL_Log("Unable to create texture from image. SDL says: %s" ,SDL_GetError());
        SDL_DestroySurface(image); // Free the surface to avoid memory leak
        return NULL;
    }
    asset = &context.assets[context.n_assets];
    asset->detail.image.surface = image;
    asset->detail.image.texture = texture;
    asset->detail.image.height = image->h;
    asset->detail.image.width = image->w;
    asset->type = ASSET_IMAGE;
    asset->loaded = true;
    asset->origin = strdup(path); // Use strdup to simplify memory management
    context.n_assets++;
    return asset;
}

void EDL_DrawAsset(uint16_t x, uint16_t y, Easy_Asset_t* asset,
               uint16_t rotation, float scaling) {
    if (context.renderer == NULL) {
        SDL_Log("FATAL ERROR: NULL Render we cannot perform EDL_DrawAsset(...) please inti the library wiht EDL_Init()");
    }

    if (asset == NULL) {
        SDL_Log("FATAL ERROR: NULL Asset, thus nothing to draw");
        return;
    }

    if (asset->type != ASSET_IMAGE){
        SDL_Log("FATAL ERROR: Asset is not a IMAGE, thus nothing to draw");
        return;
    }


    SDL_FRect rect;
    rect.w = ((float) asset->detail.image.width)*scaling;
    rect.h = ((float) asset->detail.image.height)*scaling;
    rect.x = x;
    rect.y = y;

    SDL_RenderTextureRotated(
        context.renderer,
        asset->detail.image.texture,
        NULL, &rect,
        rotation, NULL,
        SDL_FLIP_NONE);
}

void EDL_DrawAsset(uint16_t x, uint16_t y, Easy_Asset_t* asset, uint16_t rotation){
    EDL_DrawAsset(x,y,asset,rotation,1.0);
}

void EDL_DrawAsset(uint16_t x, uint16_t y, Easy_Asset_t* asset){
    EDL_DrawAsset(x,y,asset,0,1.0);
}


void EDL_DrawText(uint16_t x, uint16_t y, char* txt){
    EDL_DrawText(x, y, 0,0,txt,0);
}
const uint32_t N_BOXES = 1024*1024;
SDL_FRect boxes[N_BOXES];
uint32_t currentBox = 1;
void EDL_DrawText(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char* txt, uint32_t options){
    SDL_Surface* text;
    //TODO Set all the font style, at the moment only the color is set
    if ( context.text_style == NULL || context.text_style->font == NULL ){
        SDL_Log("FATAL ERROR: No valid TEXT_STYLE, please set it with EDL_SetTextStyle");
        return;
    }
    TTF_Font* font = context.text_style->font->detail.font.font;
    TTF_SetFontSize(font,context.text_style->size);
    text = TTF_RenderText_Solid(font, txt, 0, context.text_style->foreground );
    if ( !text ) {
        SDL_Log("FATAL ERROR: Failed to render text. SDL says: %s",SDL_GetError());
    }

    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface( context.renderer, text );

    //dst dichiarata in stack
    SDL_FRect dst = { (float)x, (float)y, (float)text->w, (float)text->h };
    if ( w != 0 || h !=0 ){
        dst.w = w;
        dst.h = h;
    }
    if (options & TEXT_CENTERED ){
        dst.x = (w-text->w)/2;
        dst.y = (h-text->h)/2+y;
        dst.w = text->w;
        dst.h = text->h;
    }
    boxes[currentBox] = dst;

    SDL_RenderTexture( context.renderer, texture, NULL, &(boxes[currentBox]) );
    currentBox = ( currentBox + 1 ) % N_BOXES;
    if( currentBox == 0 ){
        SDL_Log("WARNING: We are running out of bounding box...Behavior unexpteced!");
    }
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(text);
}

void EDL_SetTextStyle(TextStyle_t* style){
    if(context.text_style == NULL){
        context.text_style = (TextStyle_t *) malloc(sizeof(TextStyle_t));
    }
    memcpy(context.text_style,style,sizeof(TextStyle_t));
}

TextStyle_t* EDL_GetTextStyle(){
    return context.text_style;
}

bool EDL_FrameClear() {
    if(context.renderer != NULL && context.window != NULL) {
        return SDL_RenderClear(context.renderer);
    }
    return false;
}
bool EDL_FramePresent() {
    if(context.renderer != NULL && context.window != NULL) {
        return SDL_RenderPresent(context.renderer);
    }
    return false;
}