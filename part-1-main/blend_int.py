"""
4190.308 Computer Architecture                                                          Spring 2023

Image blending (int)

This module implements a function that blends two images together (integer version)

@author:
    Your Name <your@email.com>

@changes:
    2023/MM/DD Your Name Comment

"""



def blend(img1, img2, height, width, channels, overlay, alpha):
    """
    Alpha-blends two images of size heightxwidth. The image data must contain an alpha
    channel, i.e., 'channels' must be four

    Args:
        img1:         image 1 data (multi-level list), BGRA
        img2:         image 2 data (multi-level list), BGRA
        height:       image height
        width:        image width
        channels:     number of channels (must be 4)
        overlay:      if 1, overlay the second image over the first
                      if 0, merge the two images
        alpha:        alpha blending factor (0-255)

    Returns:
        A tuple containing the following elements:
        - blended:    blended image data (multi-level list), BGRA
        - bheight:    blended image height (=height)
        - bwidth:     blended image width (=width)
        - bchannels:  blended image channels (=channels)

    """

    if channels != 4:
        raise ValueError('Invalid number of channels')


    # TODO
    # Your work goes here

    # For now, we simply copy the input parameters into the output parameters.
    # Fix/adjust once you have implemented your solution.
    bheight = height
    bwidth = width
    bchannels = channels
    blended = [[[0 for col in range(channels)] for row in range(bwidth)] for depth in range(bheight)]
    if (overlay == 0):
        for y in range(bheight):
            for x in range(bwidth):
                for c in range(channels - 1):
                    blended[y][x][c]+=(img1[y][x][c] * img1[y][x][3] * (256 - alpha))
                    blended[y][x][c]+= (img2[y][x][c] * img2[y][x][3] * alpha)
                    blended[y][x][c] = blended[y][x][c]>>16
                one = img1[y][x][3] * (256 - alpha)
                two = img2[y][x][3] * alpha
                blended[y][x][3] =(one + two) >> 8

    if (overlay == 1):
        for y in range(bheight):
            for x in range(bwidth):
                alpha_combined = (img2[y][x][3]) * alpha

                for c in range(channels - 1):
                    mul1 = (img1[y][x][c]) * ((1 << 16) - alpha_combined)
                    mul2 = (img2[y][x][c]) * alpha_combined
                    blended[y][x][c] =  (mul1 + mul2)>>16
                # print(f'blended[{y}][{x}][{c}] : {blended[y][x][c]}')
                blended[y][x][3] = img1[y][x][3]

    return blended, bheight, bwidth, bchannels



