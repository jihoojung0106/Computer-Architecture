"""
4190.308 Computer Architecture                                                          Spring 2023

Image blurring (int)

This module implements a function that blurs an image with a filter (integer version)

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

    # For now, we simply copy the input parameters into the output parameters.
    # Fix/adjust once you have implemented your solution.
    bheight = height - kernel_size + 1
    bwidth = width - kernel_size + 1
    bchannels = channels
    blurred=[[[0 for col in range(channels)] for row in range(bwidth)] for depth in range(bheight)]

    mid=int(kernel_size/2)
    if (kernel_size == 3):
        fpnum1 = 28
        fpnum2=3
    elif (kernel_size == 5):
        fpnum1 = 10
        fpnum2 = 5
    elif (kernel_size == 7):
        fpnum1 = 5
        fpnum2 = 10

    for y in range(bheight):
        for x in range(bwidth):
            for c in range(channels):
                for k in range(kernel_size):
                    for k2 in range(kernel_size):
                        blurred[y][x][c] += (fpnum1 * (image[y + k][x + k2][c]) )
                blurred[y][x][c] += image[y + mid][x + mid][c] * fpnum2
                blurred[y][x][c] = blurred[y][x][c] >> 8
                # print(f'blurred[{y}][{x}][{c}] : {blurred[y][x][c]}')

    return blurred, bheight, bwidth, bchannels



