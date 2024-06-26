//FCAI – Structured Programming – 2024 - Assignment 3.
// File: CS112_A3_part1_28_20230573_20231175_20231154.cpp
// Purpose:This program is baby Photoshop and contains some filters that can modify images as you like
// Author1: Youssef Ahmed Fathi , ID1 : 20230573 .
// Author2: Manar Sameh Abdel Samad , ID2 : 20231175 .
// Author3: Mahmoud Alaa Mahmoud , ID3 : 20231154 .
// Emails: Youssefkeashta@gmail.com ,manarsameh274@gmail.com, mahmoudalaa0001234@gmail.com .
// ID1:20230573 _ he did  [Filter 1 ( GrayScale Conversion ), Filter 4 ( Merge Images ), Filter 7 ( Darken and Lighten Image ), Filter 10 ( Detect Image Edges ), Filter 13 ( Sunlight Effect )]
// ID2:20231175 _ she did [Filter 3 (Invert Image) , Filter 6 ( Rotate Image ), Filter 9 ( picture Frame ), Filter 12 ( Blur 2 Images ), Filter 16  ( purble filter )]
// ID3:20231154 _ he did  [Filter 2 (Black And White) , Filter 5 (Flip Image) , Filter 8 (Cropped Image) , Filter 11 (Resize Image )  , Filter 15 (DenDen_Mushi_Filter)]

// ---------------------the link of digram--------------------------
//https://drive.google.com/file/d/1-H-aXNevYcrJmrZ_kwKYjjufES66-GYP/view?usp=sharing


// ------------------------START PROGRAM----------------

#include <iostream>
#include <string>
#include "vector"
#include "Image_Class.h"
#include <cmath>


using namespace std;
// Function to apply the Den Den Mushi filter to the image
int apply_DenDen_Mushi_Filter(Image& image) {
    srand(time(NULL));

    // Add static noise
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                // Add random noise with a certain probability
                if (rand() % 100 < 5) {
                    unsigned char noise = rand() % 256;
                    image.setPixel(x, y, c, noise);
                }
            }
        }
    }
    // Ask the user for the output image file name
    string output_filename;
    cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
    cin >> output_filename;

    // Save the inverted image
    image.saveImage(output_filename);
    system(output_filename.c_str());
    return 0;
}

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
int merge_images(const string& image1, const string& image2) {
    Image my_image_1(image1);
    Image my_image_2(image2);
    int size_h = max(my_image_2.height, my_image_1.height);
    int size_w = max(my_image_1.width, my_image_2.width);
    // create an image to merge 2 images in.
    Image merged_Image(size_h, size_w);
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

// ------------PURBLE IMAGE FILTER ------------------

int purble_image(const string& image_name) {
    Image image(image_name);

    // Convert the image to purple by adjusting the color channels
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Increase red and blue channels and reduce green channel
            image(i, j, 0) = std::min(255, static_cast<int>(image(i, j, 0) * 1.5));  // Red
            image(i, j, 1) = std::max(0, static_cast<int>(image(i, j, 1) * 0.5));    // Green
            image(i, j, 2) = std::min(255, static_cast<int>(image(i, j, 2) * 1.5));  // Blue
        }
    }

    string output_filename;
    cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
    cin >> output_filename;
    image.saveImage(output_filename);
    system(output_filename.c_str());

    return 0;
}



//-------------LIGHT & DARK FILTER --------------
int light_darkfilter(const string& image_name) {
    Image image(image_name);

    int choice;
    cout << "Choose an option:\n";
    cout << "1. Darken the image by 50%\n";
    cout << "2. Lighten the image by 50%\n";
    cin >> choice;

    // Apply Darken or Lighten filter based on user choice
    if (choice == 1) {
        // Darken the image by reducing each color channel by 50%
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image(i, j, k) = std::max(0, static_cast<int>(image(i, j, k) * 0.5));
                }
            }
        }
    }
    else if (choice == 2) {
        // Lighten the image by increasing each color channel by 50%
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image(i, j, k) = std::min(255, static_cast<int>(image(i, j, k) * 1.5));
                }
            }
        }
    }
    else {
        cout << "Invalid choice\n";
        return 1;
    }

    string output_filename;
    cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
    cin >> output_filename;
    image.saveImage(output_filename);
    system(output_filename.c_str());

    return 0;
}

//---------------Detect_ImageEdges-------------

void Detect_filter(const string& image_name) {
    // Convert the image to black and white
    Image image(image_name);
    int avg = 0;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            avg += (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
        }
    }
    avg /= image.width * image.height;

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int pixelValue = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;

            if (pixelValue > avg)
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255;
            else
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 0;
        }
    }

    // Find edges
    for (int i = 0; i < image.width - 1; ++i) {
        for (int j = 0; j < image.height - 1; ++j) {
            if (image(i + 1, j, 0) != image(i, j, 0) || image(i, j + 1, 0) != image(i, j, 0))
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 0;
            else
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255;
        }
    }
    string output_filename;
    cout << "Please enter the output image name with extension (.jpg, .bmp, .png, .tga): ";
    cin >> output_filename;
    image.saveImage(output_filename);
    system(output_filename.c_str());
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

int Grayscale_Conversion(const string& File_Name) {
    Image img(File_Name);
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += img(i, j, k);
                avg / 3;
                img(i, j, 0) = avg;
                img(i, j, 1) = avg;
                img(i, j, 2) = avg;

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
int Rotate_Image(const string& image_name) {
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
        system(Res.c_str());

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
        system(Res.c_str());

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
        system(Res.c_str());
    }
    return 0;
}

// ============================================================ //
// Filter 11: Resizing an image involves changing the dimensions of the entire image while maintaining the same image details

int Resize_Image(const string& image_name) {
    Image image(image_name);
    cout << "Current Width and Height of image is: \n";
    cout << "Width: " << image.width << endl;
    cout << "Height: " << image.height << endl;
    int newWidth, newHeight;
    cout << "Enter the new dimensions you wish to use for your image: \n";
    cout << "Width: ";
    cin >> newWidth;
    cout << "Height: ";
    cin >> newHeight;
    Image resized_img(newWidth, newHeight);
    float scaleW = (1.0f * image.width / newWidth), scaleH = (1.0f * image.height / newHeight);
    for (int i = 0; i < resized_img.height; ++i) {
        for (int j = 0; j < resized_img.width; ++j) {
            for (int k = 0; k < resized_img.channels; ++k) {
                resized_img(j, i, k) = image(round((j * scaleW)), round((i * scaleH)), k);
            }
        }
    }
    cout << "What would you like to name the result file?\n";
    cout << "Type name and format you would like file to be saved as\n";
    string Res;
    cin >> Res;
    resized_img.saveImage(Res);
    system(Res.c_str());
    return 0;
}

// ============================================================ //
// Filter 9: Adding a frame to a picture
// This is one of the frame options which is a function to add a single border to the image

int SingleBorderImg(const string& image_name) {
    Image image(image_name);
    int BWidth, BHeight;
    cout << "Insert Width and Height of the Frame Border: \n";
    cout << "Width: \n";
    cin >> BWidth;
    cout << "Height: \n";
    cin >> BHeight;
    int BW2 = BWidth * 2, BH2 = 2 * BHeight;
    int R, G, B;
    cout << "Insert Values for R G B for the Frame Border: \n";
    cout << "Red: \n";
    cin >> R;
    cout << "Green: \n";
    cin >> G;
    cout << "Blue: \n";
    cin >> B;
    Image image1(image.width + BW2, image.height + BH2);
    for (int i = 0; i < BWidth; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < BHeight; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = image1.width - 1; i > image1.width - BWidth - 1; --i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = 0; i < image1.width; ++i) {
        for (int j = image1.height - 1; j > image1.height - BHeight - 1; --j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = BWidth; i < image1.width - BWidth; ++i) {
        for (int j = BHeight; j < image1.height - BHeight; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                image1(i, j, k) = image(i - BWidth, j - BHeight, k);
            }
        }
    }
    string Res;
    cout << "What would you like to name the result file? (Include the format in the naming)\n";
    cin >> Res;
    image1.saveImage(Res);
    system(Res.c_str());
    return 0;
}

// This is another one of the frame options which is a function to add a double border to the image

int DoubleBorderImg(const string& image_name) {
    Image image(image_name);
    int BWidth, BHeight;
    cout << "Insert Width and Height of the Frame Inner Border: \n";
    cout << "Width: \n";
    cin >> BWidth;
    cout << "Height: \n";
    cin >> BHeight;
    int BW2 = BWidth * 2, BH2 = 2 * BHeight;
    int R, G, B;
    cout << "Insert Values for R G B for the Frame Inner Border: \n";
    cout << "Red: \n";
    cin >> R;
    cout << "Green: \n";
    cin >> G;
    cout << "Blue: \n";
    cin >> B;
    Image image1(image.width + BW2, image.height + BH2);
    for (int i = 0; i < BWidth; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < BHeight; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = image1.width - 1; i > image1.width - BWidth - 1; --i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = 0; i < image1.width; ++i) {
        for (int j = image1.height - 1; j > image1.height - BHeight - 1; --j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = BWidth; i < image1.width - BWidth; ++i) {
        for (int j = BHeight; j < image1.height - BHeight; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                image1(i, j, k) = image(i - BWidth, j - BHeight, k);
            }
        }
    }
    int BWidth2, BHeight2;
    cout << "Insert Width and Height of the Frame Outer Border: \n";
    cout << "Width: \n";
    cin >> BWidth2;
    cout << "Height: \n";
    cin >> BHeight2;
    int B2W2 = BWidth2 * 2, B2H2 = 2 * BHeight2;
    int R2, G2, B2;
    cout << "Insert Values for R G B for the Frame Outer Border: \n";
    cout << "Red: \n";
    cin >> R2;
    cout << "Green: \n";
    cin >> G2;
    cout << "Blue: \n";
    cin >> B2;
    Image image2(image1.width + B2W2, image1.height + B2H2);
    for (int i = 0; i < BWidth2; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k == 0) {
                    image2(i, j, k) = R2;
                }
                else if (k == 1) {
                    image2(i, j, k) = G2;
                }
                else if (k == 2) {
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < BHeight2; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k == 0) {
                    image2(i, j, k) = R2;
                }
                else if (k == 1) {
                    image2(i, j, k) = G2;
                }
                else if (k == 2) {
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = image2.width - 1; i > image1.width - BWidth2 - 1; --i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k == 0) {
                    image2(i, j, k) = R2;
                }
                else if (k == 1) {
                    image2(i, j, k) = G2;
                }
                else if (k == 2) {
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image2.width; ++i) {
        for (int j = image2.height - 1; j > image2.height - BHeight2 - 1; --j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k == 0) {
                    image2(i, j, k) = R2;
                }
                else if (k == 1) {
                    image2(i, j, k) = G2;
                }
                else if (k == 2) {
                    image2(i, j, k) = B2;
                }
            }
        }
    }

    for (int i = BWidth2; i < image2.width - BWidth2; ++i) {
        for (int j = BHeight2; j < image2.height - BHeight2; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                image2(i, j, k) = image1(i - BWidth2, j - BHeight2, k);
            }
        }
    }
    string Res;
    cout << "What would you like to name the result file? (Include the format in the naming)\n";
    cin >> Res;
    image2.saveImage(Res);
    system(Res.c_str());
    return 0;
}

// This is another one of the frame options which is a function to add a spaced double border to the image

int SpacedDoubleBorderImg(const string& image_name) {
    Image image(image_name);
    int BWidth, BHeight;
    cout << "Insert Width and Height of the Frame Inner Border: \n";
    cout << "Width: \n";
    cin >> BWidth;
    cout << "Height: \n";
    cin >> BHeight;
    int Space;
    cout << "Insert the value of the Space between the two borders: \n";
    cin >> Space;
    int R, G, B;
    cout << "Insert Values for R G B for the Frame Inner Border: \n";
    cout << "Red: \n";
    cin >> R;
    cout << "Green: \n";
    cin >> G;
    cout << "Blue: \n";
    cin >> B;
    Image image1(image.width, image.height);
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                image1(i, j, k) = image(i, j, k);
            }
        }
    }
    for (int i = Space - 1; i < BWidth + Space; ++i) {
        for (int j = Space - 1; j < image1.height - Space; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = Space - 1; i < image1.width - Space; ++i) {
        for (int j = Space - 1; j < BHeight + Space; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = image1.width - (Space + 1); i > image1.width - (BWidth + 1 + Space); --i) {
        for (int j = Space - 1; j < image1.height - Space; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    for (int i = Space - 1; i < image1.width - Space; ++i) {
        for (int j = image1.height - (Space + 1); j > image1.height - (BHeight + Space + 1); --j) {
            for (int k = 0; k < image1.channels; ++k) {
                if (k == 0) {
                    image1(i, j, k) = R;
                }
                else if (k == 1) {
                    image1(i, j, k) = G;
                }
                else if (k == 2) {
                    image1(i, j, k) = B;
                }
            }
        }
    }
    int BWidth2, BHeight2;
    cout << "Insert Width and Height of the Frame Outer Border: \n";
    cout << "Width: \n";
    cin >> BWidth2;
    cout << "Height: \n";
    cin >> BHeight2;
    int B2W2 = BWidth2 * 2, B2H2 = 2 * BHeight2;
    int R2, G2, B2;
    cout << "Insert Values for R G B for the Frame Outer Border: \n";
    cout << "Red: \n";
    cin >> R2;
    cout << "Green: \n";
    cin >> G2;
    cout << "Blue: \n";
    cin >> B2;
    Image image2(image1.width + B2W2, image1.height + B2H2);
    for (int i = 0; i < BWidth2; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k == 0) {
                    image2(i, j, k) = R2;
                }
                else if (k == 1) {
                    image2(i, j, k) = G2;
                }
                else if (k == 2) {
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < BHeight2; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k == 0) {
                    image2(i, j, k) = R2;
                }
                else if (k == 1) {
                    image2(i, j, k) = G2;
                }
                else if (k == 2) {
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = image2.width - 1; i > image1.width - BWidth2 - 1; --i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k == 0) {
                    image2(i, j, k) = R2;
                }
                else if (k == 1) {
                    image2(i, j, k) = G2;
                }
                else if (k == 2) {
                    image2(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image2.width; ++i) {
        for (int j = image2.height - 1; j > image2.height - BHeight2 - 1; --j) {
            for (int k = 0; k < image2.channels; ++k) {
                if (k == 0) {
                    image2(i, j, k) = R2;
                }
                else if (k == 1) {
                    image2(i, j, k) = G2;
                }
                else if (k == 2) {
                    image2(i, j, k) = B2;
                }
            }
        }
    }

    for (int i = BWidth2; i < image2.width - BWidth2; ++i) {
        for (int j = BHeight2; j < image2.height - BHeight2; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                image2(i, j, k) = image1(i - BWidth2, j - BHeight2, k);
            }
        }
    }
    string Res;
    cout << "What would you like to name the result file? (Include the format in the naming)\n";
    cin >> Res;
    image2.saveImage(Res);
    system(Res.c_str());
    return 0;
}

// This is another frame option which adds a German Flag as a border

int GermanBorderImg(const string& image_name) {
    Image image(image_name);
    int BWidth, BHeight;
    cout << "Insert Width and Height of the Frame Border: \n";
    cout << "Width: \n";
    cin >> BWidth;
    cout << "Height: \n";
    cin >> BHeight;
    int BWidth3 = BWidth / 3, BHeight3 = BHeight / 3;
    for (int i = 0; i < BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = image.width - 1; i > image.width - BWidth3 - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - 1; j > image.height - BHeight3 - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = BWidth3; i < 2 * BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3; j < 2 * BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = image.width - BWidth3 - 1; i > image.width - (2 * BWidth3) - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - BHeight3 - 1; j > image.height - (BHeight3 * 2) - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = BWidth3 * 2; i < BWidth; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3 * 2; j < BHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = image.width - (BWidth3 * 2) - 1; i > image.width - BWidth - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - (BHeight3 * 2) - 1; j > image.height - BHeight - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    string Res;
    cout << "What would you like to name the result file? (Include the format in the naming)\n";
    cin >> Res;
    image.saveImage(Res);
    system(Res.c_str());
    return 0;
}

// This is another frame option which adds an Egyptian Flag as a border

int EgyptBorderImg(const string& image_name) {
    Image image(image_name);
    int BWidth, BHeight;
    cout << "Insert Width and Height of the Frame Border: \n";
    cout << "Width: \n";
    cin >> BWidth;
    cout << "Height: \n";
    cin >> BHeight;
    int BWidth3 = BWidth / 3, BHeight3 = BHeight / 3;
    for (int i = 0; i < BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = image.width - 1; i > image.width - BWidth3 - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - 1; j > image.height - BHeight3 - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = BWidth3; i < 2 * BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3; j < 2 * BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = image.width - BWidth3 - 1; i > image.width - (2 * BWidth3) - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - BHeight3 - 1; j > image.height - (BHeight3 * 2) - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = BWidth3 * 2; i < BWidth; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3 * 2; j < BHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = image.width - (BWidth3 * 2) - 1; i > image.width - BWidth - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - (BHeight3 * 2) - 1; j > image.height - BHeight - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    string Res;
    cout << "What would you like to name the result file? (Include the format in the naming)\n";
    cin >> Res;
    image.saveImage(Res);
    system(Res.c_str());
    return 0;
}

// This is another frame option which adds the RGB colors as a border

int RGBBorderImg(const string& image_name) {
    Image image(image_name);
    int BWidth, BHeight;
    cout << "Insert Width and Height of the Frame Border: \n";
    cout << "Width: \n";
    cin >> BWidth;
    cout << "Height: \n";
    cin >> BHeight;
    int BWidth3 = BWidth / 3, BHeight3 = BHeight / 3;
    for (int i = 0; i < BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = image.width - 1; i > image.width - BWidth3 - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - 1; j > image.height - BHeight3 - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = BWidth3; i < 2 * BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3; j < 2 * BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = image.width - BWidth3 - 1; i > image.width - (2 * BWidth3) - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - BHeight3 - 1; j > image.height - (BHeight3 * 2) - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 255;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = BWidth3 * 2; i < BWidth; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3 * 2; j < BHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = image.width - (BWidth3 * 2) - 1; i > image.width - BWidth - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - (BHeight3 * 2) - 1; j > image.height - BHeight - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    string Res;
    cout << "What would you like to name the result file? (Include the format in the naming)\n";
    cin >> Res;
    image.saveImage(Res);
    system(Res.c_str());
    return 0;
}

// This is another frame option which adds some nicely compatible colors as a border

int NiceBorderImg(const string& image_name) {
    Image image(image_name);
    int BWidth, BHeight;
    cout << "Insert Width and Height of the Frame Border: \n";
    cout << "Width: \n";
    cin >> BWidth;
    cout << "Height: \n";
    cin >> BHeight;
    int BWidth3 = BWidth / 3, BHeight3 = BHeight / 3;
    for (int i = 0; i < BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 225;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 157;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 225;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 157;
                }
            }
        }
    }
    for (int i = image.width - 1; i > image.width - BWidth3 - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 225;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 157;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - 1; j > image.height - BHeight3 - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 225;
                }
                else if (k == 1) {
                    image(i, j, k) = 0;
                }
                else if (k == 2) {
                    image(i, j, k) = 157;
                }
            }
        }
    }
    for (int i = BWidth3; i < 2 * BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 247;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3; j < 2 * BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 247;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = image.width - BWidth3 - 1; i > image.width - (2 * BWidth3) - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 247;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - BHeight3 - 1; j > image.height - (BHeight3 * 2) - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 0;
                }
                else if (k == 1) {
                    image(i, j, k) = 247;
                }
                else if (k == 2) {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = BWidth3 * 2; i < BWidth; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 245;
                }
                else if (k == 1) {
                    image(i, j, k) = 204;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3 * 2; j < BHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 245;
                }
                else if (k == 1) {
                    image(i, j, k) = 204;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = image.width - (BWidth3 * 2) - 1; i > image.width - BWidth - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 245;
                }
                else if (k == 1) {
                    image(i, j, k) = 204;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - (BHeight3 * 2) - 1; j > image.height - BHeight - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = 245;
                }
                else if (k == 1) {
                    image(i, j, k) = 204;
                }
                else if (k == 2) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
    string Res;
    cout << "What would you like to name the result file? (Include the format in the naming)\n";
    cin >> Res;
    image.saveImage(Res);
    system(Res.c_str());
    return 0;
}

// This is another frame option which allows the user to choose the colors himself for the border

int CustomBorderImg(const string& image_name) {
    Image image(image_name);
    int BWidth, BHeight;
    cout << "Insert Width and Height of the Frame Border: \n";
    cout << "Width: \n";
    cin >> BWidth;
    cout << "Height: \n";
    cin >> BHeight;
    int R1, G1, B1;
    cout << "Insert Values for R G B for your outer custom Frame: \n";
    cout << "Red: \n";
    cin >> R1;
    cout << "Green: \n";
    cin >> G1;
    cout << "Blue: \n";
    cin >> B1;
    int BWidth3 = BWidth / 3, BHeight3 = BHeight / 3;
    for (int i = 0; i < BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R1;
                }
                else if (k == 1) {
                    image(i, j, k) = G1;
                }
                else if (k == 2) {
                    image(i, j, k) = B1;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R1;
                }
                else if (k == 1) {
                    image(i, j, k) = G1;
                }
                else if (k == 2) {
                    image(i, j, k) = B1;
                }
            }
        }
    }
    for (int i = image.width - 1; i > image.width - BWidth3 - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R1;
                }
                else if (k == 1) {
                    image(i, j, k) = G1;
                }
                else if (k == 2) {
                    image(i, j, k) = B1;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - 1; j > image.height - BHeight3 - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R1;
                }
                else if (k == 1) {
                    image(i, j, k) = G1;
                }
                else if (k == 2) {
                    image(i, j, k) = B1;
                }
            }
        }
    }
    int R2, G2, B2;
    cout << "Insert Values for R G B for your middle custom Frame: \n";
    cout << "Red: \n";
    cin >> R2;
    cout << "Green: \n";
    cin >> G2;
    cout << "Blue: \n";
    cin >> B2;
    for (int i = BWidth3; i < 2 * BWidth3; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R2;
                }
                else if (k == 1) {
                    image(i, j, k) = G2;
                }
                else if (k == 2) {
                    image(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3; j < 2 * BHeight3; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R2;
                }
                else if (k == 1) {
                    image(i, j, k) = G2;
                }
                else if (k == 2) {
                    image(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = image.width - BWidth3 - 1; i > image.width - (2 * BWidth3) - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R2;
                }
                else if (k == 1) {
                    image(i, j, k) = G2;
                }
                else if (k == 2) {
                    image(i, j, k) = B2;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - BHeight3 - 1; j > image.height - (BHeight3 * 2) - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R2;
                }
                else if (k == 1) {
                    image(i, j, k) = G2;
                }
                else if (k == 2) {
                    image(i, j, k) = B2;
                }
            }
        }
    }
    int R3, G3, B3;
    cout << "Insert Values for R G B for your inner custom Frame: \n";
    cout << "Red: \n";
    cin >> R3;
    cout << "Green: \n";
    cin >> G3;
    cout << "Blue: \n";
    cin >> B3;
    for (int i = BWidth3 * 2; i < BWidth; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R3;
                }
                else if (k == 1) {
                    image(i, j, k) = G3;
                }
                else if (k == 2) {
                    image(i, j, k) = B3;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = BHeight3 * 2; j < BHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R3;
                }
                else if (k == 1) {
                    image(i, j, k) = G3;
                }
                else if (k == 2) {
                    image(i, j, k) = B3;
                }
            }
        }
    }
    for (int i = image.width - (BWidth3 * 2) - 1; i > image.width - BWidth - 1; --i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R3;
                }
                else if (k == 1) {
                    image(i, j, k) = G3;
                }
                else if (k == 2) {
                    image(i, j, k) = B3;
                }
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - (BHeight3 * 2) - 1; j > image.height - BHeight - 1; --j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    image(i, j, k) = R3;
                }
                else if (k == 1) {
                    image(i, j, k) = G3;
                }
                else if (k == 2) {
                    image(i, j, k) = B3;
                }
            }
        }
    }
    string Res;
    cout << "What would you like to name the result file? (Include the format in the naming)\n";
    cin >> Res;
    image.saveImage(Res);
    system(Res.c_str());
    return 0;
}

// This is the function which combines all the other filters in one function

int Frame_Image(const string& image_name) {
    while (true) {
        char c;
        cout << "Choose Frame: \n" << "A) Single Border\n" << "B) Double Border\n" << "C) Spaced Double Border\n" << "D) Triple Border\n" << "E) Back to Main Menu\n";
        cin >> c;
        c = toupper(c);
        if (c == 'A') {

            SingleBorderImg(image_name);

        }
        else if (c == 'B') {

            DoubleBorderImg(image_name);
        }
        else if (c == 'C') {

            SpacedDoubleBorderImg(image_name);
        }
        else if (c == 'D') {
            char ch;
            cout << "Choose Frame: \n" << "A) German Flag Border\n" << "B) Egyptian Flag Border\n" << "C) RGB Colored Border\n" << "D) Nicely Colored Border\n" << "E) Custom Colored Border\n";
            cin >> ch;
            ch = toupper(ch);
            if (ch == 'A') {
                GermanBorderImg(image_name);
            }
            else if (ch == 'B') {
                EgyptBorderImg(image_name);
            }
            else if (ch == 'C') {
                RGBBorderImg(image_name);
            }
            else if (ch == 'D') {
                NiceBorderImg(image_name);
            }
            else if (ch == 'E') {
                CustomBorderImg(image_name);
            }
            else {
                cout << "Invalid Input!\n";
            }
        }
        else if (c == 'E') {
            break;
        }
        else {
            cout << "Please choose valid option!";
        }
    }
    return 0;
}

// ============================================================ //
// Filter 13: Sunlight Effect
// This filter adds a yellowish effect to the picture to allow for a 'sunlight' effect

int SunshineEffect(const string& image_name) {
    Image image(image_name);
    Image image1(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (k == 0) {
                    int R = image(i, j, k) * 1.2;
                    image1(i, j, k) = min(R, 255);
                }
                else if (k == 1) {
                    int G = image(i, j, k) * 1.2;
                    image1(i, j, k) = min(G, 255);
                }
                else {
                    int B = image(i, j, k) * 0.8;
                    image1(i, j, k) = max(B, 0);
                }
            }
        }
    }
    string Res;
    cout << "Insert the name of the image file you would like to use (Include the format in the name)\n";
    cin >> Res;
    image1.saveImage(Res);
    system(Res.c_str());
    return 0;
}



int main() {
    char choice;
    string image_name;
    string image_name_2;
    while (true) {
        cout << "                              \t\t*/* Welcome to our program */*\n";
        cout << "this program is a baby Photo Shop that can apply some filters in your photo ";
        cout << "What would you like to do?\n";
        cout << "A: Apply a filter to an image.\n"
            << "B: Exit.\n";
        cin >> choice;
        choice = toupper(choice);
        if (choice == 'A') {
            cout << "Please enter the image name: ";
            cin >> image_name;
            cout << "Which filter would you like to apply?\n";
            cout << "A. Invert Image.\n";
            cout << "B. Black and White.\n";
            cout << "C. Flip Image.\n";
            cout << "D. Cropping_Image.\n";
            cout << "E. Grayscale Conversion.\n";
            cout << "F. Merge Images.\n";
            cout << "G. Blur Image.\n";
            cout << "H. Rotate Image.\n";
            cout << "I. Resize Image.\n";
            cout << "J. Picture Frame.\n";
            cout << "K. Sunlight Effect.\n";
            cout << "L. apply_DenDen_Mushi_Filter.\n";
            cout << "M.purple Filter at night.\n";
            cout << "N.light_darkfilter.\n";
            cout << "o.Detect_ImageEdges.\n";
            char filter_choice;
            cin >> filter_choice;
            filter_choice = toupper(filter_choice);
            switch (filter_choice) {
            case 'A':
                invert_image(image_name);
                break;
            case 'B':
                black_and_white(image_name);
                break;
            case 'C':
                flip_image(image_name);
                break;
            case 'D':
                Cropping_Image(image_name);
                break;
            case 'E':
                Grayscale_Conversion(image_name);
                break;
            case 'F':
                cout << " Enter The Image 2 Name : ";
                cin >> image_name_2;
                merge_images(image_name, image_name_2);
                break;
            case 'G': {
                Image my_image(image_name);

                // Blur radius
                int blur_radius = 3;

                // Apply blur to the image
                applyBlur(my_image, blur_radius);

                // Save the blurred image

                applyBlur(my_image, blur_radius);
                break;
            }
            case 'H': {
                Rotate_Image(image_name);
                break;
            }
            case 'I': {
                Resize_Image(image_name);
                break;
            }
            case 'J': {
                Frame_Image(image_name);
                break;
            }
            case 'K': {
                SunshineEffect(image_name);
                break;
            }
            case 'L': {
                Image my_image(image_name);
                apply_DenDen_Mushi_Filter(my_image);
                break;
            }
            case 'M': {
                purble_image(image_name);
                break;
            }
            case 'N': {
                light_darkfilter(image_name);
                break;
            }
            case 'O': {
                Detect_filter(image_name);
                break;
            }
            default: {
                cout << " Invalid Input.";
                break;
            }
            }
        }
        else if (choice == 'B') {
            cout << "Thank you for using our filters.\n";
            break;
        }
        else {
            cout << "Please enter a valid input.\n";
        }
    }
    cout << "*/* Thank you */*\n";

    return 0;
}
