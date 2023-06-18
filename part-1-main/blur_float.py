"""
4190.308 Computer Architecture                                                          Spring 2023

Image blurring (float)

This module implements a function that blurs an image with a 3x3 filter (floating point version)

@author:
    Your Name <your@email.com>

@changes:
    2023/MM/DD Your Name Comment

"""



def blur(image, height, width, channels, kernel_size=5):
    """
    Blurs an image with a kernel and returns the blurred image.

    Args:
        image:        image data (multi-level list)
        height:       image height
        width:        image width
        channels:     number of channels (BGR or BGRA)
        kernel_size:  size of blurring kernel

    Returns:
        A tuple containing the following elements:
        - blurred:    blurred image data
        - bheight:    blurred image height
        - bwidth:     blurred image width
        - bchannels:  blurred image channels

    """

    # TODO
    # Your work goes here
    bheight = height - kernel_size + 1
    bwidth = width - kernel_size + 1
    bchannels = channels
    fpnum = 0
    # For now, we simply copy the input parameters into the output parameters.
    # Fix/adjust once you have implemented your solution.
    # print(f'height : {height}\t width : {width}\tchannels : {channels}\t kernel_size : {kernel_size}')
    # print(f'bheight : {bheight}\t bwidth : {bwidth}\tchannels : {channels}\t kernel_size : {kernel_size}')


    blurred=[[[0 for col in range(channels)] for row in range(bwidth)] for depth in range(bheight)]

    if(kernel_size==3):
        fpnum=1/9
    elif(kernel_size==5):
        fpnum=1/25
    elif(kernel_size==7):
        fpnum=1/49

    for y in range(bheight):
        for x in range(bwidth):
            for c in range(channels):
                for k in range(kernel_size):
                    for k2 in range(kernel_size):
                        blurred[y][x][c] += fpnum*(image[y+k][x+k2][c]/256)
                        # print(f'blurred[{y}][{x}][{c}]= {fpnum*(image[y+k][x+k2][c]/256)} ')

                blurred[y][x][c]=int(blurred[y][x][c]*256)
                # print(f' total : blurred[{y}][{x}][{c}]= {blurred[y][x][c]} ')

    return blurred, bheight, bwidth, bchannels



