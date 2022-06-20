#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>
#include <array>

#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "raycaster.hpp"

// constants
const int WINDOW_WIDTH  = 480;
const int WINDOW_HEIGHT = 480;

const int RENDER_TARGET_W = 480;
const int RENDER_TARGET_H = 480;

// player angle and position
float player_angle = 0.0f;

glm::vec2 player = glm::vec2(
    RENDER_TARGET_W / 2,
    RENDER_TARGET_H / 2
);


// map of rectangles that make up the space
std::vector<std::array<float, 4>> MAP = {
    { 0.0f,   0.0f,   480.0f, 60.0f  },
    { 0.0f,   60.0f,  60.0f,  360.0f },
    { 420.0f, 60.0f,  60.0f,  360.0f },
    { 0.0f,   420.0f, 480.0f, 60.0f  },
    { 120.0f, 60.0f,  60.0f,  120.0f },
    { 320.0f, 120.0f, 120.0f, 60.0f  },
    { 180.0f, 300.0f, 120.0f, 60.0f  },
    { 240.0f, 360.0f, 60.0f,  60.0f  }
};


void render_player(glm::vec2 player) {
    glColor3f(0.0f, 0.75f, 0.0f);
    glRectf(player.x-5, player.y-5, player.x+5, player.y+5);
}


void render_map() {
    for (int i = 0; i < MAP.size(); i++) {
        float x = MAP[i][0];
        float y = MAP[i][1];
        float w = MAP[i][2];
        float h = MAP[i][3];

        glColor3f(0.9f, 0.9f, 0.9f);
        glRectf(x, y, x+w, y+h);
    }
}


bool point_collide_map(float x, float y) {
    for (int i = 0; i < MAP.size(); i++) {
        float x = MAP[i][0];
        float y = MAP[i][1];
        float w = MAP[i][2];
        float h = MAP[i][3];

        if (player.x > x && player.x < (x + w)) {
            if (player.y > y && player.y < (y + h)) {
                return true;
            }
        }
    }
    return false;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_LEFT) {
            player_angle = player_angle + 0.05f;
        }

        else if (key == GLFW_KEY_RIGHT) {
            player_angle = player_angle - 0.05f;
        }

        else if (key == GLFW_KEY_UP) {
            float target_x;
            float target_y;

            target_x = player.x + (-sin(player_angle) * 2.5f);
            target_y = player.y + ( cos(player_angle) * 2.5f);

            if (point_collide_map(target_x, target_y) != true) {
                player.x = target_x;
                player.y = target_y;
            }
        }

        else if (key == GLFW_KEY_DOWN) {
            float target_x;
            float target_y;
            
            target_x = player.x - (-sin(player_angle) * 2.5f);
            target_y = player.y - ( cos(player_angle) * 2.5f);

            if (point_collide_map(target_x, target_y) != true) {
                player.x = target_x;
                player.y = target_y;
            }
        }
    }    
}


int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "Raycaster",
        NULL,
        NULL
    );

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, 0);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // set viewport projection for the window
    glViewport(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // create an ortho projection matrix to be multiplied with each coordinate
    // tldr: create normal coordinatete system instead of -1.0 to 1.0
    glOrtho(0, RENDER_TARGET_W, 0, RENDER_TARGET_H, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    Raycaster caster = Raycaster(
        MAP,
        M_PI / 3,   // FOV
        120,        // RAY_COUNT
        300         // MAX_DEPTH
    );

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        render_map();
        
        caster.cast_rays(player, player_angle);
        
        render_player(player);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}