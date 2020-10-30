#include <stdint.h>
#include <videoDriver.h>
#include <font.h>
#include <lib.h>

#define BACKGROUND_COLOUR 0x000000

unsigned int bg_color = 0x0;
unsigned int f_color = 0xFFFFFF;

unsigned int SCREEN_WIDTH = 1024;
unsigned int SCREEN_HEIGHT = 768;
unsigned int SCREEN_bPP = 3; 

static unsigned int xPos = 0;
static unsigned int yPos = 0;

struct vbe_mode_info_structure{
    uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;      // deprecated
    uint8_t window_b;      // deprecated
    uint16_t granularity; // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;           // number of bytes per horizontal line
    uint16_t width;           // width in pixels
    uint16_t height;       // height in pixels
    uint8_t w_char;           // unused...
    uint8_t y_char;           // ...
    uint8_t planes;
    uint8_t bpp;   // bits per pixel in this mode
    uint8_t banks; // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer; // physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__((packed));

struct vbe_mode_info_structure * screen_data = (void*) 0x5C00; //VBEModeInfoBlock
/*
    uint16_t pitch;           // number of bytes per horizontal line
    uint16_t width;           // width in pixels
    uint16_t height;       // height in pixels
*/

void checkPosition();

void draw_char_from(int character, int row, int col, int color){
    while (row%CHAR_HEIGHT!=0){ //si la direccion que me paso el usuario no esta alineada con el tamano de caracteres que estamos utilizando
       row++;
    }
    while (col%CHAR_WIDTH!=0){
       col++;
    }
    unsigned char * bitMap = charBitmap(character);
    for(int i = 0; i < CHAR_HEIGHT; i++) {
        for(int j = 0; j < CHAR_WIDTH; j++) {
            unsigned int point = ((bitMap[i] >> j) & 0x01);
            if(point == 0) {
                drawPixel(row + i, col + CHAR_WIDTH - j, BACKGROUND_COLOUR);
            } else {
                //if (row + i > screen_data -> width) 
                //if ( col + CHAR_WIDTH - j > screen_data -> height)
                
                drawPixel(row + i, col + CHAR_WIDTH - j, color);
            }
        }
    }
}

  

void draw_char(int character, int color){
    draw_char_from(character, yPos, xPos, color);
    xPos += CHAR_WIDTH;

    checkPosition();
}

void checkPosition() {
    if(xPos >= screen_data->width) {
        xPos = 0;
        yPos += CHAR_HEIGHT;
    }
    if(yPos >= screen_data->height) {
        //Proximamente scrolleara... tal vez
        yPos = screen_data->height - CHAR_HEIGHT;
        int length = (screen_data->width * screen_data->height * 3) - (3 * screen_data->width); 
        memcpy((void *)(uint64_t)(screen_data->framebuffer), (void *)(uint64_t)(screen_data->framebuffer + 3 * screen_data->width), length);
        for(int i = 0; i < screen_data->width; i++) {
            for(int j = yPos; j < screen_data->height; j++) {
                drawPixel(j,i,BACKGROUND_COLOUR);
            }
        }
    }
}

void drawPixel(int row, int col, int color){
    char* current_position = (char*)(uint64_t)screen_data->framebuffer + 3 * (row * screen_data->width + col);

    int blue = color & 0xFF;
    int green = (color >> 8) & 0xFF;
    int red = (color >> 16) & 0xFF;

    *current_position = blue;
    current_position++;
    *current_position = green;
    current_position++;
    *current_position = red;
    //current_position++;
}