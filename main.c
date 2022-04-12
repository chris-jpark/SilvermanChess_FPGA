#include "address_map_arm.h"
#include  "tools.h"

Piece basemap[4][4];

//draw pixel by pixelxww
void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

//swap two integers
void swap(int* x, int* y){
    int temp = *x;
    *x= *y;
    *y = temp;
}

//refresh the screen
void clear_screen(){
    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 240; y++) {
            plot_pixel (x, y, 0);
        }
    }
}

//swap between the back buffer and the front buffer
void wait_for_vsync(){
  volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
  register int status;

  *pixel_ctrl_ptr = 1;

  status = *(pixel_ctrl_ptr + 3);
  while ((status &0x01)!= 0){
    status = *(pixel_ctrl_ptr + 3);
  }
}

//draw the chessboard
void draw_board(){
    for(int x  = 0; x < 320; x++ ){
        for(int y = 0; y < 240; y++){
            plot_pixel(x, y, board[y][x]); 
        }
    }
}


void draw_piece(Piece currPiece, int a, int b){
    for(int x  = 0; x < 60; x++){
        for(int y = 0; y < 60; y++){
            if(strcmp(currPiece.name, "wP")==0) {
                if(wPawn[x][y] != 65535)
                    plot_pixel(a*60+y+OFFSET, b*60+x, wPawn[x][y]);
            }
            else if(strcmp(currPiece.name, "wR")==0) {
                if(wRook[x][y] != 65535)
                plot_pixel(a*60+y+OFFSET, b*60+x, wRook[x][y]);
            }
            else if(strcmp(currPiece.name, "wQ")==0) {
                if(wQueen[x][y] != 65535)
                plot_pixel(a*60+y+OFFSET, b*60+x, wQueen[x][y]);
            }else if(strcmp(currPiece.name, "wK")==0) {
                if(wKing[x][y] != 65535)
                plot_pixel(a*60+y+OFFSET, b*60+x, wKing[x][y]);
            }else if(strcmp(currPiece.name, "bP")==0) {
                if(bPawn[x][y] != 65535)
                plot_pixel(a*60+y+OFFSET, b*60+x, bPawn[x][y]);
            }else if(strcmp(currPiece.name, "bR")==0) {
                if(bRook[x][y] != 65535)
                plot_pixel(a*60+y+OFFSET, b*60+x, bRook[x][y]);
            }else if(strcmp(currPiece.name, "bQ")==0) {
                if(bQueen[x][y] != 65535)
                plot_pixel(a*60+y+OFFSET, b*60+x, bQueen[x][y]);
            }else if(strcmp(currPiece.name, "bK")==0) {
                if(bKing[x][y] != 65535)
                plot_pixel(a*60+y+OFFSET, b*60+x, bKing[x][y]);
            }
            
        }
    }
}

int main(){
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

    makeBoard(); 

    while(1){
        //insert what to draw on the screen here
		clear_screen();
        draw_board();
        for(int x = 0; x < 4; x++){
            for(int y = 0; y < 4; y++){
            draw_piece(basemap[x][y], x, y); 
            }
        }
		wait_for_vsync(); // swap front and back buffers on VGA vertical sync

        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
}

