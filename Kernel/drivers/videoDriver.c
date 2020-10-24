#include <stdint.h>
#include <videoDriver.h>


unsigned int bg_color = 0x0;
unsigned int f_color = 0xFFFFFF;

unsigned int SCREEN_WIDTH = 1024;
unsigned int SCREEN_HEIGHT = 768;
unsigned int SCREEN_bPP = 3; 

struct vbe_mode_info_structure
{
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

struct vbe_mode_info_structure * screen_data = 0x0000000000005C00; //VBEModeInfoBlock //(void*) 0x5C00 Por que? No hay pol que

void draw_pixel(int row, int col){
    char* current_position = screen_data->framebuffer + 3 * (row * screen_data->width + col);
    for (int i = 0; i < 1000; i++)
    {
    *current_position = 200;
    current_position++;
    *current_position = 0;
    current_position++;
    *current_position = 200;
    current_position++;
    }

}