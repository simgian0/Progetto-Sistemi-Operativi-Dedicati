#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // Include stb_image for image loading

// Function to find the black dot in the image
std::pair<int, int> findBlackDotInImage(const std::vector<unsigned char>& pixels, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 3;
            unsigned char r = pixels[index];
            unsigned char g = pixels[index + 1];
            unsigned char b = pixels[index + 2];

            // Check if the pixel is black
            if (r == 0 && g == 0 && b == 0) {
                return {x, height - y - 1}; // OpenGL's origin is bottom-left
            }
        }
    }

    return {-1, -1}; // Return -1, -1 if no black dot is found
}

int main() {
    const char* imagePath = "blank_image_with_black_dot.png"; // Path to the input image
    int width, height, channels;

    // Load the image using stb_image
    unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 3); // Force 3 channels (RGB)
    if (!data) {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return -1;
    }

    // Convert the image data to a vector for easier processing
    std::vector<unsigned char> pixels(data, data + (width * height * 3));
    stbi_image_free(data); // Free the image memory

    // Find the black dot in the image
    auto [x, y] = findBlackDotInImage(pixels, width, height);
    if (x != -1 && y != -1) {
        std::cout << "Black dot found at: (" << x << ", " << y << ")" << std::endl;
    } else {
        std::cout << "No black dot found in the image." << std::endl;
    }

    return 0;
}