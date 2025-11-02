#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>


const int steps = 100;  // Number of Steps to create a cirle
const float pi = 3.1415926; // PIEEE
const float angle = 2.0f*pi/steps; // 2*pi(360 Degree) divided by Steps {Angle of a triagle that makes a circle}


class Planet {   // Planet Class 
    public:
        float posX, posY;  // Position of the Center of the Planet
        float velX, velY;  // Velocity of the planet
        float mass;        // Mass of the Planet
        float radius;      // Radius of the Planet
        float color[3];    // Color of the Planet

        Planet (float x, float y, float vx, float vy, float m, float r, float colorRed, float colorGreen, float colorBlue) {
            posX = x;
            posY = y;
            velX = vx;
            velY = vy;
            mass = m;
            radius = r;
            color[0] = colorRed;
            color[1] = colorGreen;
            color[2] = colorBlue;
        }

        void drawPlanet() {   // This thing makes a circle
            glBegin(GL_TRIANGLES);
            glColor3f(color[0], color[1], color[2]);

            for (int i =0; i< steps; i++) {
                float theta = i*angle;
                float beta = (i+1)*angle;

                glVertex2f( posX, posY);
                glVertex2f(posX + radius*cos(theta), posY + radius*sin(theta));
                glVertex2f(posX + radius*cos(beta), posY + radius*sin(beta));
            }
            glEnd();
        }
};

std::vector<Planet> planets;

 




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


    planets.push_back(Planet(0.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.2f, 1.0f, 0.0f, 0.0f));  // Central star
    planets.push_back(Planet(0.8f, 0.0f, 0.0f, 0.5f, 1.0f, 0.08f, 0.0f, 1.0f, 0.0f));   // Orbiting planet
    planets.push_back(Planet(-0.5f, 0.0f, 0.0f, -0.7f, 0.5f, 0.06f, 0.0f, 0.0f, 1.0f)); // Another planet


    
    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.259f, 0.529f, 0.961f, 1.0f);  // Screen Color
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto& planet : planets) {
            planet.drawPlanet();
        }

        
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

