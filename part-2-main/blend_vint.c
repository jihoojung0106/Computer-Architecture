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
#include "vector_math.h"
#include "vector_math.c"
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

    long one=0;
    long two=0;
    long alpha_combined=0;
    if (blended.data == NULL) abort();
    if(overlay==0){
        for(int y=0;y<img1.height;y++){
            for(int x=0;x<img1.width;x++){
                int first=(y*img1.width+x)*img1.channels;
                argb value1=img1.data[first+3]<<24 | img1.data[first+2]<<16 | img1.data[first+1]<<8 | img1.data[first];

                vrgb unpack_one=vunpack(value1);
                vrgb unpack_alpha_one=vbrdcst(img1.data[first+3]);
                vrgb unpack_one_mul=vmul(vmul(unpack_one,unpack_alpha_one), vbrdcst((256-alpha)));

                argb value2=img2.data[first+3]<<24 | img2.data[first+2]<<16 | img2.data[first+1]<<8 | img2.data[first];
                vrgb unpack_two=vunpack(value2);
                vrgb unpack_alpha_two=vbrdcst(img1.data[first+3]);
                vrgb unpack_two_mul=vmul(vmul(unpack_two,unpack_alpha_two), vbrdcst(alpha));

                vrgb added=vadd(unpack_one_mul,unpack_two_mul);

                one=img1.data[(y*img1.width+x)*img1.channels+3]*(256 - alpha);
                two=img2.data[(y*img1.width+x)*img1.channels+3]* (alpha);
                argb result=vpack(added,(one+two)>>8);
                blended.data[first]=result & 0xff;
                blended.data[first+1]=(result & 0xff00)>>8;
                blended.data[first+2]=(result & 0xff0000)>>16;
                blended.data[first+3]=(result & 0xff000000)>>24;
            }
        }
    }
    else if(overlay==1){
        for(int y=0;y<img1.height;y++){
            for(int x=0;x<img1.width;x++){
                int first=(y*img1.width+x)*img1.channels;
                alpha_combined=img2.data[first+3]*alpha;
                alpha_combined=alpha_combined>>8;
                argb value1=img1.data[first+3]<<24 | img1.data[first+2]<<16 | img1.data[first+1]<<8 | img1.data[first];

                vrgb unpack_one=vunpack(value1);
                vrgb unpack_alpha_one=vbrdcst(((1<<8)-alpha_combined));
                vrgb unpack_one_mul=vmul(unpack_one,unpack_alpha_one);

                argb value2=img2.data[first+3]<<24 | img2.data[first+2]<<16 | img2.data[first+1]<<8 | img2.data[first];
                vrgb unpack_two=vunpack(value2);
                vrgb unpack_alpha_two=vbrdcst(alpha_combined);
                vrgb unpack_two_mul=vmul(unpack_two,unpack_alpha_two);
                vrgb added=vadd(unpack_one_mul,unpack_two_mul);

                argb result=vpack(added,img1.data[first+3]);

                blended.data[first]=result & 0xff;
                blended.data[first+1]=(result & 0xff00)>>8;
                blended.data[first+2]=(result & 0xff0000)>>16;
                blended.data[first+3]=(result & 0xff000000)>>24;
            }
        }
    }
    return blended;
}
