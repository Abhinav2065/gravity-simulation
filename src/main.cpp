#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <math.h>


const int steps = 100;  // Number of Steps to create a cirle
const float pi = 3.1415926; // PIEEE
const float angle = 2.0f*pi/steps; // 2*pi(360 Degree) divided by Steps {Angle of a triagle that makes a circle}

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 3.0f;
 

// This function makes a circle
void makeCircle(float CENTER_X, float CENTER_Y, float radius) {  
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);

    for (int i =0; i < steps; i++) {
        float theta = i*angle;
        float beta = (i+1)*angle;

        glVertex2f(CENTER_X + radius*cos(theta), CENTER_Y + radius*sin(theta));
        glVertex2f(CENTER_X + radius*cos(beta), CENTER_Y + radius*sin(beta));
        glVertex2f(CENTER_X, CENTER_Y);
    }

    glEnd();
}




int main() {
    
    if (glfwInit() == false) {
        std::cerr << "Error Starting the opengl library" << std::endl;
        return -1;
    }

    int width = 600;
    int height = 600;
    const char *title = "Gravity Simulator";

    


    GLFWwindow* window = glfwCreateWindow(width, height,title, NULL, NULL);

    if (!window) {
        std::cerr << "Error Starting the Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    
    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.259f, 0.529f, 0.961f, 1.0f);  // Screen Color
        glClear(GL_COLOR_BUFFER_BIT);

        makeCircle(0.0f, 0.0f, 0.1f);
        
        glfwSwapBuffers(window);        

        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {  // If ESC is pressed then the window closes.
            glfwSetWindowShouldClose(window,true);
        }
        
        
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}

