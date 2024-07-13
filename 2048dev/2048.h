

#include "graphics.h"
#include <stdlib.h>
#include "platdefs.h"

/* The fundamental trick: the 4x4 board is represented as a 64-bit word,
 * with each board square packed into a single 4-bit nibble.
 *
 * The maximum possible board value that can be supported is 32768 (2^30), but
 * this is a minor limitation as achieving 65536 is highly unlikely under normal circumstances.
 *
 * The space and computation savings from using this representation should be significant.
 *
 * The nibble shift can be computed as (r,c) -> shift (4*r + c). That is, (0,0) is the LSB.
 */

typedef uint64_t board_t;
typedef uint16_t row_t;

//store the depth at which the heuristic was recorded as well as the actual heuristic
struct trans_table_entry_t{
    uint8_t depth;
    float heuristic;
};

static const board_t ROW_MASK = 0xFFFFULL;
static const board_t COL_MASK = 0x000F000F000F000FULL;


static inline void print_board(board_t board) {
    int i,j,tile;
    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
            uint8_t powerVal = (board) & 0xf;//get the power value of 2
            if(powerVal == 0)
            	tile=0;
            else
            	tile=1 << powerVal;
            
            board >>= 4;
            PIMAGE img; //Declare an img image object
            img = newimage();//create an object
            switch (tile)
            {
            case 0:
            {
                
				
				
				getimage(img, "2048\\20.jpg");//get the image from file
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);//put the image on the specified location
                
                break;
            }
            case 2:
            {
                getimage(img, "2048\\21.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 4:
            {
                getimage(img, "2048\\22.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 8:
            {
                getimage(img, "2048\\23.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 16:
            {
                getimage(img, "2048\\24.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 32:
            {
                getimage(img, "2048\\25.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 64:
            {
                getimage(img, "2048\\26.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 128:
            {
                getimage(img, "2048\\27.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 256:
            {
                getimage(img, "2048\\28.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 512:
            {
                getimage(img, "2048\\29.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 1024:
            {
                getimage(img, "2048\\210.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 2048:
            {
                getimage(img, "2048\\211.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 4096:
            {
                getimage(img, "2048\\212.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
                
            }
            case 8192:
            {
                getimage(img, "2048\\213.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 16384:
            {
                getimage(img, "2048\\214.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            case 32768:
            {
                getimage(img, "2048\\215.jpg");
                putimage( 100*j+30,205+100*i,90,90,img,0,0,90,90);
                
                break;
            }
            }
            delimage(img);//delete the object created earlier to release memory space
        }
        
    }
    
}


static inline board_t unpack_col(row_t row) {
    board_t tmp = row;
    return (tmp | (tmp << 12ULL) | (tmp << 24ULL) | (tmp << 36ULL)) & COL_MASK;
}

static inline row_t reverse_row(row_t row) {
    return (row >> 12) | ((row >> 4) & 0x00F0)  | ((row << 4) & 0x0F00) | (row << 12);
}


