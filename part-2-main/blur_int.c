//-------------------------------------------------------------------------------------------------
// 4190.308 Computer Architecture                                                       Spring 2023
//
/// @file
/// @brief Image blurring (int)
///        This module implements a function that blurs an image with a filter (integer version)
///
/// @author Your Name <your@email.com>
///
/// @section changelog Change Log
/// 2023/MM/DD Your Name Comment
///
//-------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include "blur.h"


struct Image blur_int(struct Image image, int kernel_size)
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
    int mid=(kernel_size/2);

    int fpnum1;
    int fpnum2;
    if(kernel_size==3){
        fpnum1 = 28;
        fpnum2=3;}
    else if(kernel_size==5){
        fpnum1 = 10;
        fpnum2=5;}
    else if(kernel_size==7){
        fpnum1 = 5;
        fpnum2=10;}
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int c = 0; c < channel; c++) {
                int temp=0;
                for (int k = 0; k < kernel_size; k++) {
                    for (int k2 = 0; k2 < kernel_size; k2++) {
                        temp += fpnum1*PIXEL(image, y+k,x+k2,c);
//                        printf("%d %d %d : %d \n",y+k,x+k2,c,temp);
                    }
                }
                temp += fpnum2*PIXEL(image, y+mid,x+mid,c);
//                printf("mid : %d %d\n",y+mid,x+mid);
//                printf("%d %d %d : %d \n",y,x,c,(uint8) (temp>> 8));
                PIXEL(output, y, x, c) = (uint8) (temp>> 8);

            }
        }
    }


  return output;

}
