#include <cmath>

#include <GLFW/glfw3.h>

#include "raycaster.hpp"


Raycaster::Raycaster(std::vector<std::array<float, 4>> MAP, float FOV, int RAY_COUNT, int MAX_DEPTH) {
    this->MAP = MAP;
    
    this->FOV = FOV;
    this->RAY_COUNT = RAY_COUNT;
    this->MAX_DEPTH = MAX_DEPTH;

    this->HALF_FOV = FOV / 2;
    this->STEP_ANGLE = FOV / RAY_COUNT;
}


void Raycaster::cast_rays(glm::vec2 player, float player_angle) {
    float angle = player_angle - HALF_FOV;
    bool collition;

    glm::vec2 target = glm::vec2(0.0f, 0.0f);

    // set color for all lines    
    glColor3f(1.0f, 1.0f, 0.0f);

    for (int i = 0; i < RAY_COUNT; i++) {
        collition = false;

        for (int depth = 0; depth < MAX_DEPTH; depth++) {
            target.x = player.x - (sin(angle) * depth);
            target.y = player.y + (cos(angle) * depth);
            
            // replace with checking line intersection
            // with each line in rect to avoid missing
            // when moving too far over corners
            if (line_intersect_map(target)) {
                glBegin(GL_LINES);
                glVertex2f(player.x, player.y);
                glVertex2f(target.x, target.y);
                glEnd();
                break;
            }
        }

        angle = angle + STEP_ANGLE;
    }
}