#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <math.h>


const int steps = 100;  // Number of Steps to create a cirle
const float pi = 3.1415926; // PIEEE
const float angle = 2.0f*pi/steps; // 2*pi(360 Degree) divided by Steps {Angle of a triagle that makes a circle}

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

    float radius = 0.1f;
    float xPos = 0.2f;
    float yPos = 0.8f;
    float velocity = 0.0f;
    float acceleration = 0.00098f;
    float floorLevel = -0.9f;
    float ceilingLevel = 0.9f;

    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.259f, 0.529f, 0.961f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);


        for (int i =0; i<steps; i++) {

            float theta = i*angle;  // Angle for first triangle
            float beta = (i+1)*angle; // Angle for Second Trignalge
            
            glVertex2f(xPos + radius*cos(theta), yPos + radius*sin(theta));
            glVertex2f(xPos + radius*cos(beta), yPos + radius*sin(beta));
            glVertex2f(xPos, yPos);
            
        }
        glEnd();
        
        velocity = velocity + acceleration;

        yPos -= velocity;

        if (yPos - radius < floorLevel) {
            yPos = floorLevel + radius;
            velocity = -velocity;
        }

        if (yPos + radius > ceilingLevel) {
            yPos = ceilingLevel - radius;
            velocity = -velocity;
        }

        
        glfwWaitEventsTimeout(1.0);
        glfwSwapBuffers(window);        

        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window,true);
        }

        
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}

