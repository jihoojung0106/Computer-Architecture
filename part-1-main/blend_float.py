"""
4190.308 Computer Architecture                                                          Spring 2023

Image blending (float)

This module implements a function that blends two images together (floating point version)

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
        alpha:        alpha blending factor (0.0-1.0)

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

    if(overlay==0):
        for y in range(bheight):
            for x in range(bwidth):
                for c in range(channels-1):
                    one=img1[y][x][c]/255.0 * img1[y][x][3]/255.0 * (1-alpha)
                    two=img2[y][x][c] / 255.0 * img2[y][x][3] / 255.0 * alpha
                    blended[y][x][c]=int(255.0*(one+two))
                one = img1[y][x][3] / 255.0 * (1 - alpha)
                two = img2[y][x][3] / 255.0 * alpha
                blended[y][x][3] = int(255.0 * (one + two))
    if (overlay == 1):
        for y in range(bheight):
            for x in range(bwidth):
                alpha_combined = (img2[y][x][3] / 255.0) * alpha
                for c in range(channels - 1):
                    blended[y][x][c]+=(img1[y][x][c]/255.0) * (1-alpha_combined)
                    blended[y][x][c]+=(img2[y][x][c]/255.0) * alpha_combined
                    blended[y][x][c] = int(blended[y][x][c] * 255.0)
                blended[y][x][3] = img1[y][x][3]

    return blended, bheight, bwidth, bchannels



