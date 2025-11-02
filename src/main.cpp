#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>


const int steps = 100;  // Number of Steps to create a cirle
const float pi = 3.1415926; // PIEEE
const float angle = 2.0f*pi/steps; // 2*pi(360 Degree) divided by Steps {Angle of a triagle that makes a circle}
const float G = 0.0001; // Universal Gravitational Constant (G)

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

        void updatePos(float dt) {
            posX += velX*dt;      // Velocity = Distance/Time
            posY += velY*dt;      // Distance = Velocity*change in time (dt)
        }

        void applyForces(float fX, float fY, float dt) {// get force on x and y direction and change in time
            // f=ma; a=f/m
            float accX = fX/mass;
            float accY = fY/mass;

            velX += accX*dt;   // Changeing the Velocity with time under the act of some force which produced acceleration
            velY += accY*dt;

        } 


};

std::vector<Planet> planets;

 


void calculateGravitationalForces() {
    

    for (int i = 0; i < planets.size(); i++) {
        for (int j = i + 1; j < planets.size(); j++) {
            Planet& p1 = planets[i];
            Planet& p2 = planets[j];



            // from the distance formula distanceSquared = (x2-x1) + (y2-y1)
            //    dsquared = (x2-x1) + (y2-y1)
            //    dx = x2 - x1
            //    dy = y2 - y1
            float dx = p2.posX - p1.posX;
            float dy = p2.posY - p1.posY;
            float distanceSquared = dx*dx + dy*dy; // Just the formula now

            if (distanceSquared < 0.0001f) distanceSquared = 0.0001f;

            float distance = std::sqrt(distanceSquared); 

            // This is the formuala for Gravitational Force between two bodies
            // with mass M1 and M2 having D distance between their center.
            // 
            //  F = (G*M1*M2)/(D^2)

            float Force = G * p1.mass * p2.mass / distanceSquared;

            // Components of force of X and Y component

            float forceX = Force * dx / distance;
            float forceY = Force* dy / distance;


            p1.applyForces(forceX, forceY, 0.01f);
            p2.applyForces(-forceX, -forceY, 0.01f);



        }
    }
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


    planets.push_back(Planet(0.0f, 0.0f, 0.0f, 0.0f, 10000.0f, 0.1f, 1.0f, 0.0f, 0.0f));  // Central star
    planets.push_back(Planet(0.8f, 0.0f, 0.0f, 0.5f, 100.0f, 0.08f, 0.0f, 1.0f, 0.0f));   // Orbiting planet
    planets.push_back(Planet(-0.5f, 0.0f, 0.0f, -0.7f, 0.5f, 0.06f, 0.0f, 0.0f, 1.0f)); // Another planet


    
    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.259f, 0.529f, 0.961f, 1.0f);  // Screen Color
        glClear(GL_COLOR_BUFFER_BIT);

        calculateGravitationalForces();


        for (auto& planet : planets) {
            planet.updatePos(0.01f);
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

