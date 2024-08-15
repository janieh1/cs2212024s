/**
 * @file block.cpp
 * @author your name(s)
 *
 * Implements a rectangular image portion block for CPSC 221 PA1
 *
 * COMPLETE THE FUNCTION BODIES IN THIS FILE AND SUBMIT TO PRAIRIELEARN
 */

#include "block.h"

/**
 *  Sets the values in the data attribute, based on the w x h pixels rectangular region of sourceimg
 *  with the upper-left corner at (left, upper). The orientation of the pixels in the data vector
 *  must match with the orientation of the pixels in the PNG.
 *
 *  @param w - the width (in pixels) of the rectangular subimage region
 *  @param h - the height (in pixels) of the rectangular subimage region
 *  @param upper - the y-coordinate of the subimage region's upper-left corner
 *  @param left - the x-coordinate of the subimage regions's upper-left corner
 *  @param sourceimg - the input PNG image
 *
 *  @pre upper and left (and upper + h - 1, left + w - 1) are valid vector indices
 *  @post pixels contains sourceimg's pixel data starting from (left, upper)
 */
void Block::Build(unsigned int w, unsigned int h, unsigned int upper, unsigned int left, const PNG& sourceimg) {
    // COMPLETE YOUR IMPLEMENTATION BELOW
    for (unsigned y = upper; y < upper + h; y++) {
        vector<RGBAPixel> row;
        for (unsigned x = left; x < left + w; x++) {
            RGBAPixel* px = sourceimg.getPixel(x, y);
            row.push_back(*px);
        }
        pixels.push_back(row);
    }
    
}

/**
 *  Writes the pixel color data into the target PNG, starting from (left, upper)
 *
 *  @pre block's dimensions are even (multiples of 2)
 *  @pre upper, left are valid image indices
 *  @pre the rectangular region beginning at (left, upper) can completely receive all of the data attribute's color
 *  @post target PNG's subimage region has been filled with data attribute's pixel data
 *  @param scale - integer multiplier for dimensions. 0 = scale by 0.5.
 *                 For 0.5 scale, use an appropriate average color for each pixel.
 *                 For 1 and larger scale, scale each pixel using the original color with no blending.
 */
void Block::Render(unsigned int scale, unsigned int upper, unsigned int left, PNG& targetimg) const {
    // COMPLETE YOUR IMPLEMENTATION BELOW
    if (scale < 1) {
        for (unsigned i = 0; i < pixels.size() - 1; i += 2) {
            for (unsigned j = 0; j < pixels[i].size() - 1; j += 2) {
                RGBAPixel pixelOne = pixels[i][j];
                RGBAPixel pixelTwo = pixels[i + 1][j];
                RGBAPixel pixelThree = pixels[i][j + 1];
                RGBAPixel pixelFour = pixels[i + 1][j + 1];
                unsigned int startX1 = left + i / 2;
                unsigned int startY1 = upper + j / 2;
                unsigned int a = startY1;
                unsigned int b = startX1;
                while (a <= startY1) {
                    b = startX1;
                    while (b <= startX1) {
                        RGBAPixel* pxToChange = targetimg.getPixel(a, b);
                        pxToChange->r = (pixelOne.r + pixelTwo.r + pixelThree.r + pixelFour.r) / 4;
                        pxToChange->g = (pixelOne.g + pixelTwo.g + pixelThree.g + pixelFour.g) / 4;
                        pxToChange->b = (pixelOne.b + pixelTwo.b + pixelThree.b + pixelFour.b) / 4;
                        pxToChange->a = (pixelOne.a + pixelTwo.a + pixelThree.a + pixelFour.a) / 4;
                        b++;
                    }
                    a++;
                }
            }
        }
        return;
    }

    for (unsigned i = 0; i < pixels.size(); i++) {
        for (unsigned j = 0; j < pixels[i].size(); j++) {
            RGBAPixel blockPixel = pixels[i][j];
            unsigned int startX = left + i * scale;
            unsigned int startY = upper + j * scale;
            unsigned int a = startY;
            unsigned int b = startX;
            while (a < startY + scale) {
                b = startX;
                while (b < startX + scale) {
                    RGBAPixel* pxToChange = targetimg.getPixel(a, b);
                    pxToChange->r = blockPixel.r;
                    pxToChange->g = blockPixel.g;
                    pxToChange->b = blockPixel.b;
                    pxToChange->a = blockPixel.a;
                    b++;
                }
                a++;
            }
        }
    }
	
}

/**
 *  Mirror this block's pixel data horizontally (along a vertical axis)
 *
 *  @post pixel data in this Block has been mirrored horizontally
 */
void Block::FlipHorizontal() {
    // COMPLETE YOUR IMPLEMENTATION BELOW
    vector<vector<RGBAPixel>> temp(pixels.size());
    //temp.resize(pixels.size());
    for (unsigned i = 0; i < pixels.size(); i++) {
        temp[i].resize(pixels[i].size());
        for (int j = pixels[i].size() - 1; j >= 0; j--) { // [49, 0]
            temp[i][pixels[i].size() - j - 1] = pixels[i][j];
        }
    }
	pixels = temp;
}

/**
 *  Returns the width (in pixels) of this Block
 *
 *  @return rectangular Block's width
 */
unsigned int Block::GetWidth() const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    return pixels[0].size();
}

/**
 *  Returns the height (in pixels) of this Block
 *
 *  @return rectangular Block's height
 */
unsigned int Block::GetHeight() const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    return pixels.size();
}