//-------------------------------------------------------------------------------------------------
// 4190.308 Computer Architecture                                                       Spring 2023
//
/// @file
/// @brief Image blending (int)
///        This module implements a function that blends two images together filter (integer
///        version)
///
/// @author Your Name <your@email.com>
///
/// @section changelog Change Log
/// 2023/MM/DD Your Name Comment
///
//-------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include "blend.h"

#include <stdio.h>

struct Image blend_int(struct Image img1, struct Image img2, int overlay, int alpha)
{
  if (img1.channels != 4) abort();
  struct Image blended = {
    .height   = img1.height,
    .width    = img1.width,
    .channels = img1.channels
  };
  blended.data = malloc(blended.height*blended.width*blended.channels*sizeof(uint8));
  if (blended.data == NULL) abort();

    int real=0;

    long one=0;
    long two=0;
    long alpha_combined=0;
    long hello;
    if (blended.data == NULL) abort();
    if(overlay==0){
        for(int y=0;y<img1.height;y++){
            for(int x=0;x<img1.width;x++){
                for(int c=0;c<img1.channels-1;c++){
                    one=PIXEL(img1,y,x,c)* PIXEL(img1,y,x,3) * (256-alpha);
                    two=PIXEL(img2,y,x,c) * PIXEL(img2,y,x,3) * (alpha);
                    PIXEL(blended,y,x,c)=(one+two)>>16;
                }
                one=PIXEL(img1,y,x,3)*(256 - alpha);
                two=PIXEL(img2,y,x,3)* (alpha);
                PIXEL(blended,y,x,3)=(one+two)>>8;
            }
        }
    }else if(overlay==1){
        int diff=0;
        for(int y=0;y<img1.height;y++){
            for(int x=0;x<img1.width;x++){
                alpha_combined=PIXEL(img2,y,x,3)*alpha;
                alpha_combined=alpha_combined>>8;
                for(int c=0;c<img1.channels-1;c++){
                    one=PIXEL(img1,y,x,c) * ((1<<8)-alpha_combined);
                    two=PIXEL(img2,y,x,c) * alpha_combined;
                    PIXEL(blended,y,x,c)=(one+two) >>8;
                }
                PIXEL(blended,y,x,3)=PIXEL(img1,y,x,3);

                }
        }
    }
    return blended;
}
