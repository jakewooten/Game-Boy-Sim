#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>

#define COLOR0 0x0f380f 
#define COLOR1 0x306230 
#define COLOR2 0x8bac0f 
#define COLOR3 0x9bbc0f 

uint8_t miniPix[8];

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
uint32_t rmask = 0xff000000;
uint32_t gmask = 0x00ff0000;
uint32_t bmask = 0x0000ff00;
uint32_t amask = 0x000000ff;

void init();
void loadMedia();
uint8_t * intToRGB(uint8_t color);
uint8_t * getRowColor(uint16_t row);

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* stretchSurface = NULL;

void init(){
    // initialize sdl
    SDL_Init(SDL_INIT_VIDEO); 
    //create the window
    window = SDL_CreateWindow("PLEASE WORK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screenSurface = SDL_GetWindowSurface(window);
}

void loadMedia(){
    
}

int main(){
    uint8_t temp[8][8] = {0};
    // uint8_t ** temp;
    // uint32_t *pixels = (unsigned int *)stretchSurface->pixels;
	// convert bytearray to rgb values
	uint16_t smileyTile[8] = {0xFF00, 0xFF00,
                            0xFF24, 0xFF00, 
                            0xFF42, 0xFF7E, 
                            0xFF00, 0xFF00};
    
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            temp[i][j] = *getRowColor(smileyTile[i]);
            printf("%x ", temp[i][j]); 
        }
    
    // miniPix = intToRGB(&temp);

    // for (int i = 0; i < miniPix.size(); i++){
    //     printf("%d ",miniPix[i]);
    // }

}

uint8_t * intToRGB(uint8_t color){
    uint8_t temp[3] = {0};
	switch(color){
		case 0:
			temp[0] = 0x0f;
            temp[1] = 0x38;
            temp[2] = 0x0f;
			break;

		case 1:
			temp[0] = 0x30;
            temp[1] = 0x62;
            temp[2] = 0x30;
			break;
			
		case 2:
			temp[0] = 0x8b;
            temp[1] = 0xac;
            temp[2] = 0x0f;
			break;
			
		case 3:
			temp[0] = 0x9b;
            temp[1] = 0xbc;
            temp[2] = 0x0f;
			break;
			
		default:
			return {};
			break;
	}
    return temp;
}

uint8_t * getRowColor(uint16_t row){
    uint16_t byte1 = (row & 0xFF00) >> 8; // grab high order byte out of the 2
    uint16_t byte2 = (row & 0x00FF);      // grab low order byte
    uint16_t mask = 0x01;

    // std::cout << "our tile is: 0x" << std::hex << row << std::endl;
    // std::cout << "our byte1 is: 0x" << std::hex << byte1 << std::endl;
    // std::cout << "our byte2 is: 0x" << std::hex << byte2 << std::endl;

    for (int i = 0; i < 8; i++){
            if (byte1 & (mask << i)) miniPix[7-i] += 1; // if byte 1's bit is on
            if (byte2 & (mask << i)) miniPix[7-i] += 2; // if byte 2's bit is on
    }
    return miniPix;
}
