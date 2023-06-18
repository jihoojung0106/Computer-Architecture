//-------------------------------------------------------------------------------------------------
// 4190.308 Computer Architecture                                                       Spring 2023
//
/// @file
/// @brief Image blending (float)
///        This module implements a function that blends two images together filter (floating-point
///        version). Note that CPython uses the 'double' data type for floating point numbers, 
///        so one may observe small differences in the output if the 'float' data type is used.
///
/// @author Your Name <your@email.com>
///
/// @section changelog Change Log
/// 2023/MM/DD Your Name Comment
///
//-------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include "blend.h"


struct Image blend_float(struct Image img1, struct Image img2, int overlay, double alpha)
{
  if (img1.channels != 4) abort();

  struct Image blended = {
    .height   = img1.height,
    .width    = img1.width,
    .channels = img1.channels
  };
  blended.data = malloc(blended.height*blended.width*blended.channels*sizeof(uint8));

double one=0;
double two=0;
double alpha_combined=0;
  if (blended.data == NULL) abort();
    if(overlay==0){
        for(int y=0;y<img1.height;y++){
            for(int x=0;x<img1.width;x++){
                for(int c=0;c<img1.channels-1;c++){
                    one=PIXEL(img1,y,x,c)/255.0 * PIXEL(img1,y,x,3)/255.0 * (1-alpha);
                    two=PIXEL(img2,y,x,c)/255.0 * PIXEL(img2,y,x,3)/255.0 * (alpha);
                    PIXEL(blended,y,x,c)=(int)(255.0*(one+two));
                }
                one=PIXEL(img1,y,x,3)/255.0* (1 - alpha);
                two=PIXEL(img2,y,x,3)/255.0* (alpha);
                PIXEL(blended,y,x,3)=(int)(255.0*(one+two));
            }
        }
    }else if(overlay==1){
        for(int y=0;y<img1.height;y++){
            for(int x=0;x<img1.width;x++){
                alpha_combined=PIXEL(img2,y,x,3)/255.0*alpha;
                for(int c=0;c<img1.channels-1;c++){
                    one=PIXEL(img1,y,x,c)/255.0 * (1-alpha_combined);
                    two=PIXEL(img2,y,x,c)/255.0 * (alpha_combined);
                    PIXEL(blended,y,x,c)=(int)(255.0*(one+two));
                }
                PIXEL(blended,y,x,3)=PIXEL(img1,y,x,3);
            }
        }
    }

  return blended;
}
