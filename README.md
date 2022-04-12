# SilvermanChess_FPGA
4x4 Chess Game designed to run on the Intel De1-SoC FPGA Board

## How the Game Works
You start as white. 

The chess pieces can move in the same manner as traditional chess. 

The game ends not in checkmate, but when the king is 'taken'. 

## How it was built
Written using C language, with inline ARM assembly for accessing interrupts. 

Takes user input through mouse clicks, displays board onto the 320 X 240 VGA Output. 

Must be Compiled using the Intel Quartus Prime compiler. 
