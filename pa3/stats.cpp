/**
 *  @file stats.cpp
 *  @description implementation of a stats class for rapid calculation of color averages
 *   and total color differences in CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "stats.h"

 /**
  *  Computes/retrieves the sum of a single color channel in a defined rectangular region
  *  @pre channel is a valid channel identifier
  *  @pre upper, left, lower, and right are valid image coordinates
  *  @param channel - one of 'r', 'g', or 'b'
  *  @param upper - y-coordinate of the upper edge of the rectangular region
  *  @param left - x-coordinate of the left side of the rectangular region
  *  @param lower - y-coordinate of the lower edge of the rectangular region
  *  @param right - x-coordinate of the right side of the rectangular region
  *  @return the sum of the appropriate color channel values in the defined rectangular area
  */
unsigned long Stats::GetColorSum(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned long sum;
  unsigned long lowerRight;
  if (channel == 'r') {
    lowerRight = sumR[lower][right];
    if (upper == 0 && left == 0) {
      sum = lowerRight;
    } else if (upper == 0 && left > 0) {
      // left != 0
      unsigned long oneLeft = sumR[lower][left - 1]; // !!! 
      //sum = lowerRight - oneUpFromLR + oneLeftAtTop;
      sum = lowerRight - oneLeft;
    } else if (left == 0 && upper > 0) {
      unsigned long oneUpAtRight = sumR[upper - 1][right];
      sum = lowerRight - oneUpAtRight;
    } else {
      unsigned long oneUpAtRight = sumR[upper - 1][right];
      unsigned long oneLeftFromLR = sumR[lower][left - 1];
      unsigned long oneURfromUR = sumR[upper - 1][left - 1];
      sum = lowerRight - oneUpAtRight - oneLeftFromLR + oneURfromUR;
    }
  } else if (channel == 'g') {
    lowerRight = sumG[lower][right];
    if (upper == 0 && left == 0) {
      sum = lowerRight;
    } else if (upper == 0 && left > 0) {
      unsigned long oneLeft = sumG[lower][left - 1]; // !!! 
      //sum = lowerRight - oneUpFromLR + oneLeftAtTop;
      sum = lowerRight - oneLeft;
    } else if (left == 0 && upper > 0) {
      unsigned long oneUpAtRight = sumG[upper - 1][right];
      sum = lowerRight - oneUpAtRight;
    } else {
      unsigned long oneLeft = sumB[lower][left - 1]; // !!! 
      unsigned long oneUpAtRight = sumG[upper - 1][right];
      unsigned long oneLeftFromLR = sumG[lower][left - 1];
      unsigned long oneURfromUR = sumG[upper - 1][left - 1];
      sum = lowerRight - oneUpAtRight - oneLeftFromLR + oneURfromUR;
    }
  } else {
    lowerRight = sumB[lower][right];
    if (upper == 0 && left == 0) {
      sum = lowerRight;
    } else if (upper == 0 && left > 0) {
      unsigned long oneLeft = sumB[lower][left - 1]; // !!! 
      //sum = lowerRight - oneUpFromLR + oneLeftAtTop;
      sum = lowerRight - oneLeft;
    } else if (left == 0 && upper > 0) {
      unsigned long oneUpAtRight = sumB[upper - 1][right];
      sum = lowerRight - oneUpAtRight;
    } else {
      unsigned long oneUpAtRight = sumB[upper - 1][right];
      unsigned long oneLeftFromLR = sumB[lower][left - 1];
      unsigned long oneURfromUR = sumB[upper - 1][left - 1];
      sum = lowerRight - oneUpAtRight - oneLeftFromLR + oneURfromUR;
    }
  }
  return sum;
}

/**
 *  Computes/retrieves the sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSum(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
    double lowerRight = sumA[lower][right];
    double sum;
    if (upper == 0 && left == 0) {
      sum = lowerRight;
    } else if (upper == 0 && left > 0) {
      double oneLeft = sumA[lower][left - 1]; // !!! 
      sum = lowerRight - oneLeft;
    } else if (left == 0 && upper > 0) {
      double oneUpAtRight = sumA[upper - 1][right];
      sum = lowerRight - oneUpAtRight;
    } else {
      double oneUpAtRight = sumA[upper - 1][right];
      double oneLeftFromLR = sumA[lower][left - 1];
      double oneURfromUR = sumA[upper - 1][left - 1];
      sum = lowerRight - oneUpAtRight - oneLeftFromLR + oneURfromUR;
    }
    return sum / 255.0;
}

/**
 *  Computes/retrieves the squared sum of a single color channel in a defined rectangular region
 *  @pre channel is a valid channel identifier
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param channel - one of 'r', 'g', or 'b'
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the appropriate color channel values in the defined rectangular area
 */
unsigned long Stats::GetColorSumSq(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned long sum;
  unsigned long lowerRight;
  // std::cout << "upper = " << std::to_string(upper) << std::endl;
  // std::cout << "left = " << std::to_string(left) << std::endl;
  // std::cout << "lower = " << std::to_string(lower) << std::endl;
  // std::cout << "right = " << std::to_string(right) << std::endl;
  // std::cout << "array size: " << std::to_string(sumSqR.size()) << " x " << std::to_string(sumSqR[0].size()) << std::endl;
  if (channel == 'r') {
    lowerRight = sumSqR[lower][right];
    //lowerRight = sumSqR[right][lower];
    if (upper == 0 && left == 0) {
      sum = lowerRight;
    } else if (upper == 0 && left > 0) {
      unsigned long oneLeft = sumSqR[lower][left - 1]; // !!! 
      sum = lowerRight - oneLeft;
    } else if (left == 0 && upper > 0) {
      unsigned long oneUpAtRight = sumSqR[upper - 1][right];
      //unsigned long oneUpAtRight = sumSqR[right][upper - 1];
      sum = lowerRight - oneUpAtRight;
    } else {
      unsigned long oneUpAtRight = sumSqR[upper - 1][right];
      unsigned long oneLeftFromLR = sumSqR[lower][left - 1];
      unsigned long oneURfromUR = sumSqR[upper - 1][left - 1];
      sum = lowerRight - oneUpAtRight - oneLeftFromLR + oneURfromUR;
    }
  } else if (channel == 'g') {
    lowerRight = sumSqG[lower][right];
    if (upper == 0 && left == 0) {
      sum = lowerRight;
    } else if (upper == 0 && left > 0) {
      unsigned long oneLeft = sumSqG[lower][left - 1]; // !!! 
      // unsigned long oneUpFromLR = sumSqG[lower - 1][right];
      // unsigned long oneLeftAtTop = sumSqG[upper][right - 1];
      sum = lowerRight - oneLeft;
    } else if (left == 0 && upper > 0) {
      unsigned long oneUpAtRight = sumSqG[upper - 1][right];
      sum = lowerRight - oneUpAtRight;
    } else {
      unsigned long oneUpAtRight = sumSqG[upper - 1][right];
      unsigned long oneLeftFromLR = sumSqG[lower][left - 1];
      unsigned long oneURfromUR = sumSqG[upper - 1][left - 1];
      sum = lowerRight - oneUpAtRight - oneLeftFromLR + oneURfromUR;
    }
  } else {
    lowerRight = sumSqB[lower][right];
    if (upper == 0 && left == 0) {
      sum = lowerRight;
    } else if (upper == 0 && left > 0) {
      unsigned long oneLeft = sumSqB[lower][left - 1]; // !!! 
      sum = lowerRight - oneLeft;
    } else if (left == 0 && upper > 0) {
      unsigned long oneUpAtRight = sumSqB[upper - 1][right];
      sum = lowerRight - oneUpAtRight;
    } else {
      unsigned long oneUpAtRight = sumSqB[upper - 1][right];
      unsigned long oneLeftFromLR = sumSqB[lower][left - 1];
      unsigned long oneURfromUR = sumSqB[upper - 1][left - 1];
      sum = lowerRight - oneUpAtRight - oneLeftFromLR + oneURfromUR;
    }
  }
  return sum;
}

/**
 *  Computes/retrieves the squared sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSumSq(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
    double lowerRight = sumSqA[lower][right];
    double sum;
    if (upper == 0 && left == 0) {
      sum = lowerRight;
    } else if (upper == 0 && left > 0) {
      unsigned long oneLeft = sumSqA[lower][left - 1]; // !!! 
      sum = lowerRight - oneLeft;
    } else if (left == 0 && upper > 0) {
      double oneUpAtRight = sumSqA[upper - 1][right];
      sum = lowerRight - oneUpAtRight;
    } else {
      double oneUpAtRight = sumSqA[upper - 1][right];
      double oneLeftFromLR = sumSqA[lower][left - 1];
      double oneURfromUR = sumSqA[upper - 1][left - 1];
      sum = lowerRight - oneUpAtRight - oneLeftFromLR + oneURfromUR;
    }
    return sum / (255.0 * 255.0);
}

/**
 *  Simple function to compute the number of pixels in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the area of the defined rectangular area, in pixels
 */
unsigned int Stats::GetRectangleArea(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
	int numPixelsAcross = abs((int)(right - left + 1));
  int numPixelsHigh = abs((int)(lower - upper + 1));
  int totalNumPix = numPixelsAcross * numPixelsHigh;
  return totalNumPix;
}

/**
 *  Parameterized constructor
 *  Builds the channel sum and squared sum vectors from the supplied input image.
 *  Each channel sum vector's entry (x,y) will contain the sum of their respective
 *  color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *  Likewise, each channel squared sum vector's entry (x,y) will contain the squared sum of their
 *  respective color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *
 *  ***DON'T FORGET TO PRE-MULTIPLY THE ALPHA CHANNEL***
 * 
 *  @param img - input image from which the channel sum vectors will be populated
 */
Stats::Stats(const PNG& img) {
	// complete your implementation below
  // sumR, sumG, sumB, sumA
  // std::cout << "image dimensions: " << std::to_string(img.width()) << " x " << std::to_string(img.height()) << std::endl;
  // sumR.resize(img.width(), vector<unsigned long>(img.height()));
  // sumG.resize(img.width(), vector<unsigned long>(img.height()));
  // sumB.resize(img.width(), vector<unsigned long>(img.height()));
  // sumA.resize(img.width(), vector<double>(img.height()));
  // sumSqR.resize(img.width(), vector<unsigned long>(img.height()));
  // sumSqG.resize(img.width(), vector<unsigned long>(img.height()));
  // sumSqB.resize(img.width(), vector<unsigned long>(img.height()));
  // sumSqA.resize(img.width(), vector<double>(img.height()));
  sumR.resize(img.height(), vector<unsigned long>(img.width()));
  sumG.resize(img.height(), vector<unsigned long>(img.width()));
  sumB.resize(img.height(), vector<unsigned long>(img.width()));
  sumA.resize(img.height(), vector<double>(img.width()));
  sumSqR.resize(img.height(), vector<unsigned long>(img.width()));
  sumSqG.resize(img.height(), vector<unsigned long>(img.width()));
  sumSqB.resize(img.height(), vector<unsigned long>(img.width()));
  sumSqA.resize(img.height(), vector<double>(img.width()));

  for (unsigned i = 0; i < img.height(); i++) {
    for (unsigned j = 0; j < img.width(); j++) {
      RGBAPixel* px = img.getPixel(j, i);
      if (i == 0 && j == 0) {
        sumR[i][j] = px->r;
        sumG[i][j] = px->g;
        sumB[i][j] = px->b;
        sumA[i][j] = 255.0 * px->a;
        sumSqR[i][j] = (px->r) * (px->r);
        sumSqG[i][j] = (px->g) * (px->g);
        sumSqB[i][j] = (px->b) * (px->b);
        sumSqA[i][j] = (255.0 * px->a) * (255.0 * px->a);
        //sumA[i][j] = sumA[i][j] * 255.0;
        //sumSqA[i][j] = sumSqA[i][j] * 255.0;
      } else if (j == 0) {
        sumR[i][j] = sumR[i - 1][j] + px->r;
        sumG[i][j] = sumG[i - 1][j] + px->g;
        sumB[i][j] = sumB[i - 1][j] + px->b;
        sumA[i][j] = sumA[i - 1][j] + 255.0 * px->a;
        sumSqR[i][j] = sumSqR[i - 1][j] + (px->r) * (px->r);
        sumSqG[i][j] = sumSqG[i - 1][j] + (px->g) * (px->g);
        sumSqB[i][j] = sumSqB[i - 1][j] + (px->b) * (px->b);
        sumSqA[i][j] = sumSqA[i - 1][j] + (255.0 * px->a) * (255.0 * px->a);
        //sumA[i][j] = sumA[i][j] * 255.0;
        //sumSqA[i][j] = sumSqA[i][j] * 255.0;
      } else if (i == 0) {
        sumR[i][j] = sumR[i][j - 1] + px->r;
        sumG[i][j] = sumG[i][j - 1] + px->g;
        sumB[i][j] = sumB[i][j - 1] + px->b;
        sumA[i][j] = sumA[i][j - 1] + 255.0 * px->a;
        sumSqR[i][j] = sumSqR[i][j - 1] + (px->r) * (px->r);
        sumSqG[i][j] = sumSqG[i][j - 1] + (px->g) * (px->g);
        sumSqB[i][j] = sumSqB[i][j - 1] + (px->b) * (px->b);
        sumSqA[i][j] = sumSqA[i][j - 1] + (255.0 * px->a) * (255.0 * px->a);
        //sumA[i][j] = sumA[i][j] * 255.0;
        //sumSqA[i][j] = sumSqA[i][j] * 255.0;
      } else {
        sumR[i][j] = sumR[i - 1][j] + sumR[i][j - 1] - sumR[i - 1][j - 1] + px->r;
        sumG[i][j] = sumG[i - 1][j] + sumG[i][j - 1] - sumG[i - 1][j - 1] + px->g;
        sumB[i][j] = sumB[i - 1][j] + sumB[i][j - 1] - sumB[i - 1][j - 1] + px->b;
        sumA[i][j] = sumA[i - 1][j] + sumA[i][j - 1] - sumA[i - 1][j - 1] + 255.0 * px->a;
        sumSqR[i][j] = sumSqR[i - 1][j] + sumSqR[i][j - 1] - sumSqR[i - 1][j - 1] + (px->r) * (px->r);
        sumSqG[i][j] = sumSqG[i - 1][j] + sumSqG[i][j - 1] - sumSqG[i - 1][j - 1] + (px->g) * (px->g);
        sumSqB[i][j] = sumSqB[i - 1][j] + sumSqB[i][j - 1] - sumSqB[i - 1][j - 1] + (px->b) * (px->b);
        sumSqA[i][j] = sumSqA[i - 1][j] + sumSqA[i][j - 1] - sumSqA[i - 1][j - 1] + (255.0 * px->a) * (255.0 * px->a);
        //sumA[i][j] = sumA[i][j] * 255.0;
        //sumSqA[i][j] = sumSqA[i][j] * 255.0;
      }
    }
  }
  // double alphaSumSq = 0;
  // for (int j = 0; j < img.height(); j++) {
  //   vector<unsigned long> redRow;
  //   vector<unsigned long> greenRow;
  //   vector<unsigned long> blueRow;
  //   vector<double> alphaRow;
  //   vector<unsigned long> redRowSq;
  //   vector<unsigned long> greenRowSq;
  //   vector<unsigned long> blueRowSq;
  //   vector<double> alphaRowSq;
  //   int redSumRow = 0;
  //   int greenSumRow = 0;
  //   int blueSumRow = 0;
  //   double alphaSumRow = 0;
  //   int redSumSqRow = 0;
  //   int greenSumSqRow = 0;
  //   int blueSumSqRow = 0;
  //   double alphaSumSqRow = 0;
  //   for (int i = 0; i < img.width(); i++) {
  //     RGBAPixel* px = img.getPixel(i, j);
  //     redSumRow += px->r;
  //     redSumSqRow += px->r * px->r;
  //     redRow.push_back(redSumRow);
  //     redRowSq.push_back(redSumSqRow); // do we add and then square or square and then add??
  //     greenSumRow += px->g;
  //     greenSumSqRow += px->g * px->g;
  //     greenRow.push_back(greenSumRow);
  //     greenRowSq.push_back(greenSumSqRow);
  //     blueSumRow += px->b;
  //     blueSumSqRow += px->b * px->b;
  //     blueRow.push_back(blueSumRow);
  //     blueRowSq.push_back(blueSumSqRow);
  //     alphaSumRow += px->a * 255.0;
  //     alphaSumSqRow += px->a * px->a;
  //     alphaRow.push_back(alphaSumRow);
  //     alphaRowSq.push_back(alphaSumSqRow * 255.0);
  //   }
  //   sumR.push_back(redRow);
  //   sumG.push_back(greenRow);
  //   sumB.push_back(blueRow);
  //   sumA.push_back(alphaRow);
  //   sumSqR.push_back(redRowSq);
  //   sumSqG.push_back(greenRowSq);
  //   sumSqB.push_back(blueRowSq);
  //   sumSqA.push_back(alphaRowSq);
  // }
  // for (int i = 0; i < img.width(); i++) {
  //   unsigned long colSumR = 0;
  //   unsigned long colSumG = 0;
  //   unsigned long colSumB = 0;
  //   double colSumA = 0;
  //   unsigned long colSumRSq = 0;
  //   unsigned long colSumGSq = 0;
  //   unsigned long colSumBSq = 0;
  //   unsigned long colSumASq = 0;
  //   for (int j = 0; j < img.height(); j++) {
  //     colSumR += sumR[j][i];
  //     sumR[j][i] = colSumR;
  //     colSumRSq += sumSqR[j][i];
  //     sumSqR[j][i] = colSumRSq;
  //     colSumG += sumG[j][i];
  //     sumG[j][i] = colSumG;
  //     colSumGSq += sumSqG[j][i];
  //     sumSqG[j][i] = colSumGSq;
  //     colSumB += sumB[j][i];
  //     sumB[j][i] = colSumB;
  //     colSumBSq += sumSqB[j][i];
  //     sumSqB[j][i] = colSumBSq;
  //     colSumA += sumA[j][i];
  //     sumA[j][i] = colSumA;
  //     colSumASq += sumSqA[j][i];
  //     sumSqA[j][i] = colSumASq;
  //   }
  // }
  // std::cout << "sumR array size: " << std::to_string(sumR.size()) << " x " << std::to_string(sumSqR[0].size()) << std::endl;
  // std::cout << "sumG array size: " << std::to_string(sumG.size()) << " x " << std::to_string(sumSqR[0].size()) << std::endl;
  // std::cout << "sumB array size: " << std::to_string(sumB.size()) << " x " << std::to_string(sumSqR[0].size()) << std::endl;
  // std::cout << "sumA array size: " << std::to_string(sumA.size()) << " x " << std::to_string(sumSqR[0].size()) << std::endl;
  // std::cout << "sumSqR array size: " << std::to_string(sumSqR.size()) << " x " << std::to_string(sumSqR[0].size()) << std::endl;
  // std::cout << "sumSqG array size: " << std::to_string(sumSqG.size()) << " x " << std::to_string(sumSqR[0].size()) << std::endl;
  // std::cout << "sumSqB array size: " << std::to_string(sumSqB.size()) << " x " << std::to_string(sumSqR[0].size()) << std::endl;
  // std::cout << "sumSqA array size: " << std::to_string(sumSqA.size()) << " x " << std::to_string(sumSqR[0].size()) << std::endl;

}

/**
 *  Computes/retrieves the average color of all pixels contained in the rectangle
 *  bounded by upper, left, lower, and right. Fractional values should be
 *  truncated/rounded down for assignment into integer variables.
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return pixel containing the average color of the pixels in the defined rectangle
 */
RGBAPixel Stats::GetAvg(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned int area = GetRectangleArea(upper, left, lower, right);
  unsigned int avgRed = GetColorSum('r', upper, left, lower, right) / area;
  unsigned int avgGreen = GetColorSum('g', upper, left, lower, right)  / area;
  unsigned int avgBlue = GetColorSum('b', upper, left, lower, right)  / area;
  double avgAlpha = GetAlphaSum(upper, left, lower, right) / area;
	return RGBAPixel(avgRed, avgGreen, avgBlue, avgAlpha);
}

/**
 *  Computes the total sum squared difference from the mean, for the specified rectangle.
 *  Each channel's sum squared difference is computed separately, and then added to form the total.
 *
 *  Note that using the GetAvg function in computing the sum squared difference will result in
 *  accumulation of error especially with larger rectangles.
 *  You should use more precise computation of the average color for this function's intermediate steps.
 * 
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return total sum of squared deviations from the mean, over all color channels.
 */
double Stats::GetSumSqDev(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  double area = (double)GetRectangleArea(upper, left, lower, right);
  double redSq = (double)GetColorSumSq('r', upper, left, lower, right);
  double red = (double)GetColorSum('r', upper, left, lower, right);
  double greenSq = (double)GetColorSumSq('g', upper, left, lower, right);
  double green = (double)GetColorSum('g', upper, left, lower, right);
  double blueSq = (double)GetColorSumSq('b', upper, left, lower, right);
  double blue = (double)GetColorSum('b', upper, left, lower, right);
  double alphaSq = GetAlphaSumSq(upper, left, lower, right);
  double alpha = (double)GetAlphaSum(upper, left, lower, right);

  // unsigned int area = GetRectangleArea(upper, left, lower, right);
  // unsigned int redSq = GetColorSumSq('r', upper, left, lower, right);
  // unsigned int red = GetColorSum('r', upper, left, lower, right);
  // unsigned int greenSq = GetColorSumSq('g', upper, left, lower, right);
  // unsigned int green = GetColorSum('g', upper, left, lower, right);
  // unsigned int blueSq = GetColorSumSq('b', upper, left, lower, right);
  // unsigned int blue = GetColorSum('b', upper, left, lower, right);
  // double alphaSq = GetAlphaSumSq(upper, left, lower, right);
  // double alpha = GetAlphaSum(upper, left, lower, right);
  return (redSq + greenSq + blueSq + alphaSq) - ((red*red + green*green + blue*blue + alpha*alpha) / area);
  //return (redSq + greenSq + blueSq) - ((red*red + green*green + blue*blue) / area);

  //return ((double)redSq + (double)greenSq + (double)blueSq) - (((double)red*(double)red + (double)green*(double)green + (double)blue*(double)blue) / (double)area);
}