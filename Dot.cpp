#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

// Function to read pixel data and find the black dot
std::pair<int, int> findBlackDot(int width, int height) {
    std::vector<unsigned char> pixels(width * height * 3); // RGB format
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

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
    const int width = 800;
    const int height = 600;

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(width, height, "Black Dot Finder", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Set up OpenGL viewport
    glViewport(0, 0, width, height);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Render your blank image with a black dot here
        // Example: Draw a black dot at (400, 300)
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f); // Black color
        glVertex2f(0.0f, 0.0f);      // Center of the screen
        glEnd();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // Find the black dot
        auto [x, y] = findBlackDot(width, height);
        if (x != -1 && y != -1) {
            std::cout << "Black dot found at: (" << x << ", " << y << ")" << std::endl;
            break;
        }
    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}