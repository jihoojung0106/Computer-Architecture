//-------------------------------------------------------------------------------------------------
// 4190.308 Computer Architecture                                                       Spring 2023
//
/// @file
/// @brief Image blurring (float)
///        This module implements a function that blurs an image with a filter (floating-point 
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
#include "blur.h"
struct Image blur_float(struct Image image, int kernel_size)
{
  int h=image.height - kernel_size + 1;
  int w=image.width - kernel_size + 1;
  int channel=image.channels;
    struct Image output;
    output.height=h;
    output.width=w;
    output.channels=channel;
    output.data = (uint8*)calloc(h*w*channel, sizeof(uint8));
    if (output.data == NULL) abort();
    double fpnum=0;
    if(kernel_size==3){fpnum=1.0/9;}
    else if(kernel_size==5){fpnum=1.0/25;}
    else if(kernel_size==7){fpnum=1.0/49;}
//    printf("fpnum : %lf, kernel : %d",fpnum,kernel_size);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int c = 0; c < channel; c++) {
                double temp=0.0;
                for (int k = 0; k < kernel_size; k++) {
                    for (int k2 = 0; k2 < kernel_size; k2++) {
                        temp += fpnum*PIXEL(image, y+k,x+k2,c)/256;
                    }
                }
                PIXEL(output, y, x, c) = (uint8)(temp*256);
            }
        }
    }

    return output;
}
