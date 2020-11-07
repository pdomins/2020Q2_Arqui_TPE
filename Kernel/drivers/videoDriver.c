#include <stdint.h>
#include <videoDriver.h>
#include <font.h>
#include <lib.h>

#define BACKGROUND_COLOUR 0x000000
#define HEIGHT 768

unsigned int bg_color = 0x0;
unsigned int f_color = 0xFFFFFF;

unsigned int SCREEN_WIDTH = 1024;
unsigned int SCREEN_HEIGHT = 768;
unsigned int SCREEN_bPP = 3; 

static unsigned int xPos = 0;
static unsigned int yPos = (HEIGHT - CHAR_HEIGHT);

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
void shift();
void clearLine(int yPos);
void insertEnter();
void backspace();

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
}

int draw_char_from(int character, int row, int col, int color){
    switch(character) {
        case '\n': insertEnter();
        return 0;
        case '\b': backspace();
        return 0; 
    }
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
    return 1;
}

int draw_char(int character, int color){
    int ret = draw_char_from(character, yPos, xPos, color);
    if(ret) {
        xPos += CHAR_WIDTH;
    }
    checkPosition();
    return ret;
}

int drawMatrix(int * matrix, int row, int col, int rows, int columns) {
    if(row < 0 || col < 0 || row + rows > screen_data->height || col + columns > screen_data->width) {
        //Mostrar mensaje de error o algo parecido. Si la posición es invalida o se pasa de la pantalla.
        draw_char('E', 0xFF0000);
        return -1;
    }
    int x = col;
    int y = row;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(matrix[i * columns + j] >= 0 /*&& matrix[i][j] <= 0xFFFFFF*/) {
                drawPixel(y, x, matrix[i * columns + j]);
            }
            x++;
        }
        y++;
        x = col;

    }

    return 0; //Se debería retorna la cantidad de pixeles impresos o algo asi
}

void clearScreen() {
    for(int i = 0; i < screen_data->height; i++) {
        for(int j = 0; j < screen_data->width; j++) {
            drawPixel(i, j, BACKGROUND_COLOUR);
        }
    }
}

int screenHeight() {
    return screen_data->height;
}

int screenWidth() {
    return screen_data->width;
}

void checkPosition() {
    if(xPos >= screen_data->width) {
        xPos = 0;
        yPos += CHAR_HEIGHT;
    }
    if(yPos >= screen_data->height) {
        yPos = screen_data->height - CHAR_HEIGHT;
        shift();
    }
}

void shift() {
    int length = (screen_data->width * screen_data->height * 3) - ((3 * screen_data->width)*16);
    memcpy((void *)(uint64_t)(screen_data->framebuffer), (void *)(uint64_t)(screen_data->framebuffer + (3 * screen_data->width) * CHAR_HEIGHT), length);

    clearLine(yPos);
}

void clearLine(int yPos) {
    for(int i = yPos; i < yPos + CHAR_HEIGHT; i++) {
        for(int j = 0; j < screen_data->width; j++) {
            drawPixel(i, j, BACKGROUND_COLOUR);
        }
    }
}

void insertEnter(){
    xPos = 0;
    yPos += CHAR_HEIGHT;
    checkPosition();
    return;
}

void backspace(){
    if(xPos == 0 && yPos == 0) {
        return;
    }
    if(xPos == 0) {
        yPos -= CHAR_HEIGHT;
        xPos = screen_data->width;
    }
    xPos-= CHAR_WIDTH;
    for(int i = 0; i < CHAR_HEIGHT; i++) {
        for(int j = 0; j < CHAR_WIDTH; j++) {
            drawPixel(yPos + i,xPos + j,BACKGROUND_COLOUR);
        }
    }
    return;
}



