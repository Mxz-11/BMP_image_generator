/************************************************************************************************************/
/* File: BMPCreator.cpp                                                                                     */
/* Author: Mxz-11  alu.167442@usj.es                                                                        */
/* How to execute: g++ BMPCreator.cpp -o name_of_exe                                                        */
/*                 ./name_of_exe                                                                            */
/*                                                                                                          */
/* Content of this file:                                                                                    */
/* 1. User defined width and height.                                                                        */
/* 2. User defined number of black rows at the top.                                                         */
/* 3. User defined radius of a circle in the center.                                                        */
/* 4. User defined color for the circle.                                                                    */
/* 5. User defined background color.                                                                        */
/*                                                                                                          */
/************************************************************************************************************/

//#include "stdafx.h"

# include <cstdint>
# include <numeric>
# include <algorithm>
# include <vector>

# include <iostream>
# include <fstream>
# include <sstream>

using namespace std;

// BMP Header
# pragma pack (push, 1)
struct BMPHeader
{
  // Header
  std::uint16_t mType;
  std::uint32_t mFileSize;
  std::uint16_t mReserved1;
  std::uint16_t mReserved2;
  std::uint32_t mOffset;

  // Info Header
  std::uint32_t mInfoHeaderSize;
  std::int32_t  mWidth;
  std::int32_t  mHeight;
  std::uint16_t mPlanes;
  std::uint16_t mBitCount;
  std::uint32_t mCompression;
  std::uint32_t mImageSize;
  std::int32_t  mXPixelsPerMeter;
  std::int32_t  mYPixelsPerMeter;
  std::uint32_t mColoursUsed;
  std::uint32_t mColoursImportant;
};
static_assert(sizeof(BMPHeader) == 54);
# pragma pack (pop)




// RGB type
struct RGB
{
  std::uint8_t mR = 0;
  std::uint8_t mG = 0;
  std::uint8_t mB = 0;
};




// Image class
class Image
{
private:

  std::vector<RGB> mData;
  std::int32_t mWidth = 0;
  std::int32_t mHeight = 0;


public:

  Image() = default;

  // Constructor
  Image(std::int32_t width, std::int32_t height) :
    mData(width * height), mWidth(width), mHeight(height)
  {
  }

  // Colour assignment function
  void SetColour(std::int32_t x, std::int32_t y, const RGB &colour)
  {
    mData[y * mWidth + x] = colour;
  }

  // Width access function
  const int width() const
  {
    return mWidth;
  }

  // Height access function
  const int height() const
  {
    return mHeight;
  }

  bool SaveFile(const std::string &fileName)
  {
    const std::int32_t  rowSize = (mWidth * 3 + 3) & ~3; // 32-bit alignment
    const std::uint32_t bmpsize = rowSize * mHeight;
    const BMPHeader header =
    {
      0x4d42,
      54 + bmpsize, // File size
      0,
      0,
      54, // Offset to image data
      40,
      mWidth,
      mHeight,
      1,
      24, // Bits per pixel
      0,
      bmpsize,
      0,
      0,
      0,
      0
    };


    std::ofstream stream{ fileName, std::ios_base::binary };
    if ( stream )
    {

      stream.write( ( const char * ) &header, sizeof( header ) );
      std::vector<std::uint8_t> line( rowSize );

      for ( std::int32_t y = mHeight - 1; y >= 0; --y ) // Write the image data upside down
      {
        size_t position = 0;
        for ( std::int32_t x = 0; x < mWidth; ++x) // Write the image data
        {
          const RGB &colour = mData[y * mWidth + x];
          line[position++] = colour.mB; // Blue
          line[position++] = colour.mG; // Green
          line[position++] = colour.mR; // Red
        }
        stream.write( ( const char * ) line.data(), line.size() );
      }
      return true;
    }
    else
    {
      return false;
    }
  }
};

// Function to get user input for color
RGB GetUserColorInput(const std::string& prompt, RGB defaultColor) {
  char choice;
  std::cout << prompt << " (y/n) : ";
  std::cin >> choice;
  if (choice == 'y' || choice == 'Y') {
    int r, g, b;
    std::cout << "Enter Red (0-255): "; std::cin >> r;
    std::cout << "Enter Green (0-255): "; std::cin >> g;
    std::cout << "Enter Blue (0-255): "; std::cin >> b;
    return {static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)};
  }
  return defaultColor;
}

// Function to get user input for number of black rows
int GetBlackRowsInput(int imageHeight) {
  int blackRows;
  std::cout << "Number of black rows at top? : ";
  std::cin >> blackRows;
  return std::clamp(blackRows, 0, imageHeight);
}

// Function to get user input for circle radius
int GetCircleRadiusInput(int imageWidth, int imageHeight) {
  char drawCircle;
  int radius;
  std::cout << "Enter the radius of the circle: ";
  std::cin >> radius;
  return std::clamp(radius, 1, std::min(imageWidth, imageHeight) / 2);
}

int main()
{
  // Dimensions
  int imageWidth; // Width for the image
  std::cout << "Image Width? : ";
  std::cin >> imageWidth;
  imageWidth = std::clamp(imageWidth, 1, INT32_MAX);

  int imageHeight; // Height for the image
  std::cout << "Image Height? : ";
  std::cin >> imageHeight;
  imageHeight = std::clamp(imageHeight, 1, INT32_MAX);

  std::string fileName; // File name
  std::cout << "File Name? : ";
  std::cin >> fileName;

  //Number of black rows at top
  int blackRows = GetBlackRowsInput(imageHeight);

  //Circle radius
  int radius = 0;
  char drawCircle;
  std::cout << "Do you want to draw a circle in the center? (y/n) : ";
  std::cin >> drawCircle;
  if (drawCircle == 'y' || drawCircle == 'Y') {
    radius = GetCircleRadiusInput(imageWidth, imageHeight);
  }
  
  //Ask for circle color
  RGB circleColor;
  if (radius > 0) {
    circleColor = GetUserColorInput("Do you want to choose a color for the circle?", {0, 0, 0});
  }

  //Ask for background color
  RGB backgroundColor = GetUserColorInput("Do you want to choose a background color?", {255, 0, 0});

  // Image creation
  Image image(imageWidth, imageHeight);
  int centerX = imageWidth / 2; // Center of the image on X axis
  int centerY = imageHeight / 2; // Center of the image on Y axis
  RGB colour;
  for (int y = 0; y < imageHeight; ++y)
  {
    for (int x = 0; x < imageWidth; ++x)
    {
      if (y < blackRows)  // Black rows printer
      {
        colour = {0, 0, 0}; // Black color
      }
      else if ((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) <= radius * radius) // Circle printer
      {
        colour = circleColor; // Circle color
      }
      else
      {
        colour = backgroundColor; // Background color
      }
      image.SetColour(x, y, colour); // Set color
    }
  }

  image.SaveFile( fileName + ".bmp" ); // Save image

  return 0;
}
