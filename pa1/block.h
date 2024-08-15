/**
 * @file block.h
 * @author CPSC 221
 * 
 * Defines a rectangular image portion block for CPSC 221 PA1
 * 
 * DO NOT MODIFY THIS FILE
 * THIS FILE WILL NOT BE SUBMITTED FOR GRADING
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"

#include <vector>

using namespace cs221util;
using namespace std;

class Block {
	private:

		/** 2D container for pixel data
		 *  Be aware that a newly declared vector has a size of 0
		 *  Also be aware that your choice of row-major vs column-major order
		 *  affects how you will perform your horizontal or vertical flips.
		 */
		vector<vector<RGBAPixel>> pixels;

	public:

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
		void Build(unsigned int w, unsigned int h, unsigned int upper, unsigned int left, const PNG& sourceimg);

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
		void Render(unsigned int scale, unsigned int upper, unsigned int left, PNG& targetimg) const;

		/**
		 *  Mirror this block's pixel data horizontally (along a vertical axis)
		 * 
		 *  @post pixel data in this Block has been mirrored horizontally
		 */
		void FlipHorizontal();

		/**
		 *  Returns the width (in pixels) of this Block
		 * 
		 *  @return rectangular Block's width
		 */
		unsigned int GetWidth() const;

		/**
		 *  Returns the height (in pixels) of this Block
		 *
		 *  @return rectangular Block's height
		 */
		unsigned int GetHeight() const;
};

#endif
