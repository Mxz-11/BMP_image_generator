# BMP Creator - README
## Description

####  This program allows users to generate a BMP (bitmap) image with customizable features such as:

    Selecting the image dimensions (width & height).

    Choosing a background color.

    Drawing a black region at the top with a user-defined number of rows.

    Optionally drawing a circle in the center with a user-defined radius and color.

## Features

    Custom Image Dimensions: The user inputs the width and height of the BMP.

    Background Color Selection: The user can choose a custom background color or default to red.

    Top Black Rows: The user specifies how many rows at the top should be black.

    Optional Circle: The user can decide whether to draw a circle, specify its radius, and set its color.

    BMP File Generation: The final image is saved as a BMP file.

##  How to Compile and Run
### Compilation (Linux/Mac)
 g++ BMPCreator.cpp -o BMPCreator
### Run the program
 ./BMPCreator
### How to Use the Program

    Enter Image Width & Height

    Enter the number of black rows for the top section

    Choose if you want a circle (y/n)

        If yes, specify the circle radius.

        Choose a custom color for the circle (optional).

    Choose a custom background color (y/n)

    Enter a file name for the BMP

    The BMP file is generated and saved in the current directory.

### Example Input & Output
Image Width? : 400
Image Height? : 300
Number of black rows at top? : 50
Do you want to draw a circle in the center? (y/n) : y
Enter the radius of the circle: 80
Do you want to choose a color for the circle? (y/n) : y
Enter Red (0-255): 0
Enter Green (0-255): 255
Enter Blue (0-255): 0
Do you want to choose a background color? (y/n) : y
Enter Red (0-255): 255
Enter Green (0-255): 255
Enter Blue (0-255): 0
File Name? : test_image
Output

A BMP file named test_image.bmp will be generated with the specified parameters.
### Dependencies

    Standard C++ Libraries (iostream, fstream, vector, cmath, etc.).

    No external dependencies required.
### Author

    Mxz-11

This project demonstrates structured C++ programming by integrating file handling, user input validation, and bitmap image generation.


