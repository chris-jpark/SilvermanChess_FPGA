#include "address_map_arm.h"
#include "tools.h"
#include "images.c"

Piece basemap[4][4];

 void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void swap(int* x, int* y){
    int temp = *x;
    *x= *y;
    *y = temp;
}

void clear_screen(){
    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 240; y++) {
            plot_pixel (x, y, 0);
        }
    }
}

void wait_for_vsync(){
  volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
  register int status;

  *pixel_ctrl_ptr = 1;

  status = *(pixel_ctrl_ptr + 3);
  while ((status &0x01)!= 0){
    status = *(pixel_ctrl_ptr + 3);
  }
}

void draw_board(){
    for(int x  = 0; x < 320; x++ ){
        for(int y = 0; y < 240; y++){
            plot_pixel(x, y, board[y][x]); 
        }
    }
}

main(){
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
     *(pixel_ctrl_ptr + 1) = 0xC8000000; // first store the address in the
                                        // back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer
    /* set back pixel buffer to start of SDRAM memory */
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    while(1){
        //insert what to draw on the screen here
		clear_screen();
        draw_board();
		wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
}

