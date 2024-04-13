// FCAI – Structured Programming – 2024 - Assignment 3.
// File: CS112_A3_part1_28_20230573_20231175_20231154.cpp
// Purpose:This program is baby Photoshop and contains some filters that can modify images as you like
// Author1: Youssef Ahmed Fathi , ID1 : 20230573 .
// Author2: Manar Sameh Abdel Samad , ID2 : 20231175 .
// Author3: Mahmoud Alaa Mahmoud , ID3 : 20231154 .
// Emails: Youssefkeashta@gmail.com ,manarsameh274@gmail.com, mahmoudalaa0001234@gmail.com .
// ID1:20230573 _ he did  [Filter 1 ( GrayScale Conversion ), Filter 6 ( Rotate Image ), Filter 11 ( Resize Image ), Filter 9 ( Picture Frame ), Filter 13 ( Sunlight Effect )]
// ID2:20231175 _ she did [Filter 3 (Invert Image)]
// ID3:20231154 _ he did  [Filter 2 (Black And White) , Filter 5 (Flip Image) , Filter 8 (Cropped Image)]


#include <iostream>
#include <string>
#include "vector"
#include "Image_Class.h"
#include <cmath>


using namespace std;


// Function to apply blur using 2D prefix sum
void applyBlur(Image& image, int blur_radius) {
    int rows = image.height;
    int cols = image.width;

    vector<vector<int>> blurred_image(rows, vector<int>(cols, 0));

    // Calculate prefix sum for the image
    vector<vector<int>> prefix_sum(rows + 1, vector<int>(cols + 1, 0));
    for (int i = 1; i <= rows; ++i) {
        for (int j = 1; j <= cols; ++j) {
            prefix_sum[i][j] = image(i - 1, j - 1, 0) + prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1];
        }
    }

    // Apply blur effect
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x1 = max(0, i - blur_radius);
            int y1 = max(0, j - blur_radius);
            int x2 = min(rows - 1, i + blur_radius);
            int y2 = min(cols - 1, j + blur_radius);
            int area = (x2 - x1 + 1) * (y2 - y1 + 1);

            blurred_image[i][j] = (prefix_sum[x2 + 1][y2 + 1] - prefix_sum[x2 + 1][y1] - prefix_sum[x1][y2 + 1] + prefix_sum[x1][y1]) / area;
        }
    }

    // Copy the blurred image data back to the original image
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            image(i, j, 0) = blurred_image[i][j];
            image(i, j, 1) = blurred_image[i][j];
            image(i, j, 2) = blurred_image[i][j];
        }
    }
    // Ask the user for the output image file name
    string output_filename;
    cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
    cin >> output_filename;

    // Save the inverted image
    image.saveImage(output_filename);
    system(output_filename.c_str());
}



// Function to Merge 2 images.
int merge_images (const string &image1,const string &image2) {
    Image my_image_1 (image1) ;
    Image my_image_2 (image2) ;
    int size_h = max(my_image_2.height,my_image_1.height) ;
    int size_w = max(my_image_1.width,my_image_2.width) ;
    // create an image to merge 2 images in.
    Image merged_Image (size_h,size_w) ;
    for (int i = 0; i < size_h; ++i) {
        for (int j = 0; j < size_w; ++j) {
            for (int k = 0; k < 3; ++k) {
                int pixel_value_1 = 0;
                int pixel_value_2 = 0;
                if (i < my_image_1.height && j < my_image_1.width) {
                    pixel_value_1 = my_image_1(i, j, k);
                }
                if (i < my_image_2.height && j < my_image_2.width) {
                    pixel_value_2 = my_image_2(i, j, k);
                }
                merged_Image(i, j, k) = (pixel_value_1 + pixel_value_2) / 2;
            }
        }
    }
    // Ask the user for the output image file name
    string output_filename = "merged_Image.png";
    // Save the inverted image
    merged_Image.saveImage(output_filename);
    system(output_filename.c_str());

    return 0;
}

// Function to invert colors of an image
int invert_image(const string& image_name) {
    // Open the image
    Image my_image(image_name);

    // Loop through each pixel of the image
    for (int i = 0; i < my_image.width; ++i) {
        for (int j = 0; j < my_image.height; ++j) {
            // For each pixel, loop through RGB channels
            for (int k = 0; k < 3; ++k) {
                // Invert the color value by subtracting it from 255
                my_image(i, j, k) = 255 - my_image(i, j, k);
            }
        }
    }

    // Ask the user for the output image file name
    string output_filename;
    cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
    cin >> output_filename;

    // Save the inverted image
    my_image.saveImage(output_filename);
    system(output_filename.c_str());
    return 0;
}

// ============================================================ //

// Function to convert an image to black and white
int black_and_white(const string& image_name) {
    // Open the image
    Image image(image_name);

    int threshold;
    // Ask the user to input the threshold value for black and white conversion
    cout << "Please enter the threshold value (0 to 255): ";
    cin >> threshold;

    // Ensure threshold value is within valid range (0 to 255)
    threshold = max(0, min(255, threshold));

    // Convert image to grayscale
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Convert each pixel to grayscale by taking the average of RGB values
            int gray = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            // Set all RGB channels to the grayscale value
            image(i, j, 0) = gray;
            image(i, j, 1) = gray;
            image(i, j, 2) = gray;
        }
    }

    // Apply threshold to convert grayscale to black and white
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // If grayscale value is below the threshold, set pixel to black
            if (image(i, j, 0) < threshold) {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
                // Otherwise, set pixel to white
            else {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }

    // Ask the user for the output image file name
    string output_filename;
    cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
    cin >> output_filename;
    // Save the black and white image
    image.saveImage(output_filename);
    system(output_filename.c_str());
    return 0;
}

// ============================================================ //

// Function to flip an image horizontally or vertically
int flip_image(const string& image_name) {
    // Open the image
    Image image(image_name);

    char flipDirection;
    // Ask the user to choose flip direction (horizontal or vertical)
    cout << "Please choose flip direction ('H' for horizontal, 'V' for vertical): ";
    cin >> flipDirection;

    // Ensure valid flip direction
    flipDirection = toupper(flipDirection); // Convert to uppercase
    while (flipDirection != 'H' && flipDirection != 'V') {
        cout << "Invalid flip direction. Please enter 'H' for horizontal or 'V' for vertical: ";
        cin >> flipDirection;
        flipDirection = toupper(flipDirection);
    }

    // Flip the image based on user's choice
    if (flipDirection == 'H') { // Horizontal flip
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Swap pixels between left and right sides of the image
                    swap(image(i, j, k), image(image.width - 1 - i, j, k));
                }
            }
        }
    }
    else { // Vertical flip
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Swap pixels between top and bottom sides of the image
                    swap(image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }
    }

    // Ask the user for the output image file name
    string output_filename;
    cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
    cin >> output_filename;
    // Save the flipped image
    image.saveImage(output_filename);
    system(output_filename.c_str());
    return 0;
}

// ============================================================ //

// Function to crop an image
int Cropping_Image(const string& image_name) {
    // Open the image
    Image My_Image(image_name);

    // Declare variables for width and height of cropping
    short w, h;
    cout << " Enter The Width And Height Of Cropping : ";
    cin >> w >> h;

    // Check if cropping area is within the image bounds
    if (w <= My_Image.width && h <= My_Image.height && w > 0 && h > 0) {
        // Create a new image for cropped result
        Image Cropped_Image(w, h);

        // Loop through the cropping area
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                // Copy pixel values from original image to cropped image
                for (int k = 0; k < 3; ++k) {
                    Cropped_Image(i, j, k) = My_Image(i, j, k);
                }
            }
        }

        // Ask the user for the output image file name
        string output_filename;
        cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
        cin >> output_filename;

        // Save the cropped image
        Cropped_Image.saveImage(output_filename);
        system(output_filename.c_str());
    }
    else {
        cout << "Invalid cropping dimensions. Please ensure width and height are within the image bounds and greater than zero.\n";
    }

    return 0;
}


// ============================================================ //
// Grayscale Conversion Filter

int Grayscale_Conversion (const string& File_Name ) {
    Image img (File_Name) ;
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += img(i,j,k) ;
                avg / 3 ;
                img(i,j,0) = avg ;
                img(i,j,1) = avg ;
                img(i,j,2) = avg ;

            }

        }

    }
    // Ask the user for the output image file name
    string output_filename;
    cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
    cin >> output_filename;

    // Save the cropped image
    img.saveImage(output_filename);
    system(output_filename.c_str());



    return 0;

}
// ============================================================ //
// Filter 6: This filter allows the user to rotate the image clockwise by 90, 180 or 270 degrees as the user chooses
int Rotate_Image(const string& image_name){
    Image image(image_name);
    int newWidth = image.height; // New width after rotation
    int newHeight = image.width; // New height after rotation
    Image rotatedImage(newWidth, newHeight);
    int newWidth2 = rotatedImage.height; // New width after rotation
    int newHeight2 = rotatedImage.width; // New height after rotation
    Image rotatedImage2(newWidth2, newHeight2);
    cout << "Welcome to filter 6: Rotate Image\n";
    cout << "What angle of rotation would you like to execute?\n";
    cout << "A) 90\n" << "B) 180\n" << "C) 270\n";

    char c;
    cin >> c;
    c = toupper(c);

    while (c != 'A' && c != 'B' && c != 'C') {
        cout << "Please choose a valid option!\n";
        cout << "What angle of rotation would you like to execute?\n";
        cout << "A) 90\n" << "B) 180\n" << "C) 270\n";
        cin >> c;
        c = toupper(c);
    }

    if (c == 'A') { // Rotate the image by 90 degrees clockwise
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    rotatedImage(image.height - 1 - j, i, k) = image(i, j, k);
                }
            }
        }
        // Save the rotated image
        string Res;
        cout << "What would you like to name the result file?\n";
        cout << "Type name and format you would like file to be saved as\n";
        cin >> Res;
        rotatedImage.saveImage(Res);

    }
    else if (c == 'B') { // Rotate the image by 180 degrees clockwise
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    rotatedImage(image.height - 1 - j, i, k) = image(i, j, k);
                }
            }
        }
        for (int i = 0; i < rotatedImage.width; ++i) {
            for (int j = 0; j < rotatedImage.height; ++j) {
                for (int k = 0; k < rotatedImage.channels; ++k) {
                    rotatedImage2(rotatedImage.height - 1 - j, i, k) = rotatedImage(i, j, k);
                }
            }
        }
        // Save the rotated image
        string Res;
        cout << "What would you like to name the result file?\n";
        cout << "Type name and format you would like file to be saved as\n";
        cin >> Res;
        rotatedImage2.saveImage(Res);

    }
    else if (c == 'C') { // Rotate the image by 270 degrees clockwise
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    rotatedImage(j, image.width - 1 - i, k) = image(i, j, k);
                }
            }
        }
        // Save the rotated image
        string Res;
        cout << "What would you like to name the result file?\n";
        cout << "Type name and format you would like file to be saved as\n";
        cin >> Res;
        rotatedImage.saveImage(Res);
    }
    return 0;
}

// ============================================================ //
// Filter 11: Resizing an image involves changing the dimensions of the entire image while maintaining the same image details

int Resize_Image(const string& image_name){
    Image image(image_name);
    cout<<"Current Width and Height of image is: \n";
    cout<<"Width: "<<image.width<<endl;
    cout<<"Height: "<<image.height<<endl;
    int newWidth, newHeight;
    cout<<"Enter the new dimensions you wish to use for your image: \n";
    cout<<"Width: ";
    cin>>newWidth;
    cout<<"Height: ";
    cin>>newHeight;
    Image resized_img(newWidth, newHeight);
    float scaleW = (1.0f*image.width/newWidth), scaleH = (1.0f*image.height/newHeight);
    for (int i = 0; i < resized_img.height; ++i) {
        for (int j = 0; j < resized_img.width; ++j) {
            for (int k = 0; k <resized_img.channels; ++k) {
                resized_img(j, i, k) = image(round((j*scaleW)), round((i*scaleH)), k);
            }
        }
    }
    cout<<"What would you like to name the result file?\n";
    cout<<"Type name and format you would like file to be saved as\n";
    string Res;
    cin>>Res;
    resized_img.saveImage(Res);
    return 0;
}

// ============================================================ //
// Filter 9: Adding a frame to a picture
// This is one of the frame options which is a function to add a single border to the image

int SingleBorderImg(const string& Image_Name){
    Image image(Image_Name);
    int BWidth, BHeight;
    cout<<"Insert Width and Height of the Frame Border: ";
    cin>>BWidth>>BHeight;
    int BW2 = BWidth*2, BH2 = 2*BHeight;
    int R, G, B;
    cout<<"Insert Values for R G B for the Frame Border: ";
    cin>>R>>G>>B;
    Image image1(image.width+BW2, image.height+BH2);
    for (int i = 0; i < BWidth; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R;
                }
                else if (k==1){
                    image1(i, j, k) = G ;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < BHeight; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R ;
                }
                else if (k==1){
                    image1(i, j, k) = G ;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    for (int i = image1.width-1; i >image1.width-BWidth-1; --i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R ;
                }
                else if (k==1){
                    image1(i, j, k) = G;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    for (int i = 0; i < image1.width; ++i) {
        for (int j = image1.height-1; j > image1.height - BHeight-1; --j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R;
                }
                else if (k==1){
                    image1(i, j, k) = G ;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    for (int i = BWidth; i < image1.width-BWidth; ++i) {
        for (int j = BHeight; j <image1.height-BHeight; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                image1(i, j, k) = image(i-BWidth, j-BHeight, k);
            }
        }
    }
    string Res;
    cout<<"What would you like to name the result file? (Include the format in the naming)\n";
    cin>>Res;
    image1.saveImage(Res);
    return 0;
}

// This is another one of the frame options which is a function to add a double border to the image

int DoubleBorderImg(const string& Image_Name){
    Image image(Image_Name);
    int BWidth, BHeight;
    cout<<"Insert Width and Height of the Frame Inner Border: ";
    cin>>BWidth>>BHeight;
    int BW2 = BWidth*2, BH2 = 2*BHeight;
    int R, G, B;
    cout<<"Insert Values for R G B for the Frame Inner Border: ";
    cin>>R>>G>>B;
    Image image1(image.width+BW2, image.height+BH2);
    for (int i = 0; i < BWidth; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R;
                }
                else if (k==1){
                    image1(i, j, k) = G ;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < BHeight; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R ;
                }
                else if (k==1){
                    image1(i, j, k) = G ;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    for (int i = image1.width-1; i >image1.width-BWidth-1; --i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R ;
                }
                else if (k==1){
                    image1(i, j, k) = G;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    for (int i = 0; i < image1.width; ++i) {
        for (int j = image1.height-1; j > image1.height - BHeight-1; --j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R;
                }
                else if (k==1){
                    image1(i, j, k) = G ;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    for (int i = BWidth; i < image1.width-BWidth; ++i) {
        for (int j = BHeight; j <image1.height-BHeight; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                image1(i, j, k) = image(i-BWidth, j-BHeight, k);
            }
        }
    }
    int BWidth2, BHeight2;
    cout<<"Insert Width and Height of the Frame Outer Border: ";
    cin>>BWidth2>>BHeight2;
    int B2W2 = BWidth2*2, B2H2 = 2*BHeight2;
    int R2, G2, B2;
    cout<<"Insert Values for R G B for the Frame Outer Border: ";
    cin>>R2>>G2>>B2;
    Image image2(image1.width+B2W2, image1.height+B2H2);
    for (int i = 0; i < BWidth2; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k==0){
                    image2(i, j, k) = R2;
                }
                else if (k==1){
                    image2(i, j, k) = G2;
                }
                else if (k==2){
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < BHeight2; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k==0){
                    image2(i, j, k) = R2;
                }
                else if (k==1){
                    image2(i, j, k) = G2;
                }
                else if (k==2){
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = image2.width-1; i >image1.width-BWidth2-1; --i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k==0){
                    image2(i, j, k) = R2;
                }
                else if (k==1){
                    image2(i, j, k) = G2;
                }
                else if (k==2){
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image2.width; ++i) {
        for (int j = image2.height-1; j > image2.height - BHeight2-1; --j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k==0){
                    image2(i, j, k) = R2;
                }
                else if (k==1){
                    image2(i, j, k) = G2;
                }
                else if (k==2){
                    image2(i, j, k) = B2;
                }
            }
        }
    }

    for (int i = BWidth2; i < image2.width-BWidth2; ++i) {
        for (int j = BHeight2; j <image2.height-BHeight2; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                image2(i, j, k) = image1(i-BWidth2, j-BHeight2, k);
            }
        }
    }
    string Res;
    cout<<"What would you like to name the result file? (Include the format in the naming)\n";
    cin>>Res;
    image2.saveImage(Res);
    return 0;
}

// This is another one of the frame options which is a function to add a spaced double border to the image

int SpacedDoubleBorderImg(const string& Image_Name){
    Image image(Image_Name);
    int BWidth, BHeight;
    cout<<"Insert Width and Height of the Frame Inner Border: ";
    cin>>BWidth>>BHeight;
    int Space;
    cout<<"Insert the value of the Space between the two borders: ";
    cin>>Space;
    int R, G, B;
    cout<<"Insert Values for R G B for the Frame Inner Border: ";
    cin>>R>>G>>B;
    Image image1(image.width, image.height);
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j <image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                image1(i, j, k) = image(i, j, k);
            }
        }
    }
    for (int i = Space-1; i < BWidth+Space; ++i) {
        for (int j = Space-1; j < image1.height-Space; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R;
                }
                else if (k==1){
                    image1(i, j, k) = G;
                }
                else if (k==2){
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = Space-1; i < image1.width-Space; ++i) {
        for (int j = Space-1; j < BHeight+Space; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R;
                }
                else if (k==1){
                    image1(i, j, k) = G;
                }
                else if (k==2){
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = image1.width-(Space+1); i >image1.width-(BWidth+1+Space); --i) {
        for (int j = Space-1; j < image1.height-Space; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R ;
                }
                else if (k==1){
                    image1(i, j, k) = G;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    for (int i = Space-1; i < image1.width-Space; ++i) {
        for (int j = image1.height-(Space+1); j > image1.height - (BHeight+Space+1); --j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k==0){
                    image1(i, j, k) = R;
                }
                else if (k==1){
                    image1(i, j, k) = G ;
                }
                else if (k==2){
                    image1(i, j, k) = B ;
                }
            }
        }
    }
    int BWidth2, BHeight2;
    cout<<"Insert Width and Height of the Frame Outer Border: ";
    cin>>BWidth2>>BHeight2;
    int B2W2 = BWidth2*2, B2H2 = 2*BHeight2;
    int R2, G2, B2;
    cout<<"Insert Values for R G B for the Frame Outer Border: ";
    cin>>R2>>G2>>B2;
    Image image2(image1.width+B2W2, image1.height+B2H2);
    for (int i = 0; i < BWidth2; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k==0){
                    image2(i, j, k) = R2;
                }
                else if (k==1){
                    image2(i, j, k) = G2;
                }
                else if (k==2){
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < BHeight2; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k==0){
                    image2(i, j, k) = R2;
                }
                else if (k==1){
                    image2(i, j, k) = G2;
                }
                else if (k==2){
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = image2.width-1; i >image1.width-BWidth2-1; --i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k==0){
                    image2(i, j, k) = R2;
                }
                else if (k==1){
                    image2(i, j, k) = G2;
                }
                else if (k==2){
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image2.width; ++i) {
        for (int j = image2.height-1; j > image2.height - BHeight2-1; --j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k==0){
                    image2(i, j, k) = R2;
                }
                else if (k==1){
                    image2(i, j, k) = G2;
                }
                else if (k==2){
                    image2(i, j, k) = B2;
                }
            }
        }
    }

    for (int i = BWidth2; i < image2.width-BWidth2; ++i) {
        for (int j = BHeight2; j <image2.height-BHeight2; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                image2(i, j, k) = image1(i-BWidth2, j-BHeight2, k);
            }
        }
    }
    string Res;
    cout<<"What would you like to name the result file? (Include the format in the naming)\n";
    cin>>Res;
    image2.saveImage(Res);
    return 0;
}

// This is the function which combines all the other filters in one function

int Frame_Image(){
    while (true){
        char c;
        cout<<"Choose Frame: \n"<<"A) Single Border\n"<<"B) Double Border\n"<<"C) Spaced Double Border\n"<<"D) Back to Main Menu\n";
        cin>>c;
        c = toupper(c);
        if(c=='A'){
            string Image_Name;
            cout<<"Insert the name of the image file you would like to use (Include the format in the name)\n";
            cin>>Image_Name;
            SingleBorderImg(Image_Name);

        }
        else if (c=='B'){
            string Image_Name;
            cout<<"Insert the name of the image file you would like to use (Include the format in the name)\n";
            cin>>Image_Name;
            DoubleBorderImg(Image_Name);
        }
        else if(c=='C'){
            string Image_Name;
            cout<<"Insert the name of the image file you would like to use (Include the format in the name)\n";
            cin>>Image_Name;
            SpacedDoubleBorderImg(Image_Name);
        }
        else if (c=='D'){
            break;
        }
        else{
            cout<<"Please choose valid option!";
        }
    }
    return 0;
}



int main() {
    char choice;
    string image_name;
    string image_name_2 ;
    while (true) {
        cout << "                              \t\t*/* Welcome to our program */*\n";
        cout << "this program is a baby Photo Shop that can apply some filters in your photo ";
        cout << "What would you like to do?\n";
        cout << "A: Apply a filter to an image.\n"
             << "B: Exit.\n";
        cin >> choice;
        if (choice == 'A') {
            cout << "Which filter would you like to apply?\n";
            cout << "1. Invert Image.\n";
            cout << "2. Black and White.\n";
            cout << "3. Flip Image.\n";
            cout << "4. Cropping_Image.\n";
            cout << "5. Grayscale Conversion.\n" ;
            cout << "6. Merge Images.\n";
            cout << "7. Blur Image.\n";
            char filter_choice;
            cin >> filter_choice;
            cout << "Please enter the image name: ";
            cin >> image_name;
            switch (filter_choice) {
                case '1':
                    invert_image(image_name);
                    break;
                case '2':
                    black_and_white(image_name);
                    break;
                case '3':
                    flip_image(image_name);
                    break;
                case '4':
                    Cropping_Image(image_name);
                    break;
                case '5':
                    Grayscale_Conversion(image_name);
                    break;
                case '6' :
                    cout << " Enter The Image 2 Name : ";
                    cin >> image_name_2 ;
                    merge_images(image_name,image_name_2) ;
                    break;
                case '7' : {
                    Image my_image(image_name);

                    // Blur radius
                    int blur_radius = 3;

                    // Apply blur to the image
                    applyBlur(my_image, blur_radius);

                    // Save the blurred image

                    applyBlur(my_image, blur_radius);
                    break;
                }
                default : {
                    cout << " Invalid Input.";
                    break;
                }
            }
        } else if (choice == 'B') {
            cout << "Thank you for using our filters.\n";
            break;
        } else {
            cout << "Please enter a valid input.\n";
            break;
        }
    }
    cout << "*/* Thank you */*\n";

    return 0;
}

