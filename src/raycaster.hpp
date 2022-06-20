#include <array>
#include <vector>
#include <glm.hpp>


class Raycaster {
    private:
        float FOV;
        int RAY_COUNT;
        int MAX_DEPTH;

        float HALF_FOV;
        float STEP_ANGLE;

        std::vector<std::array<float, 4>> MAP;

        bool line_intersect_map(glm::vec2 point) {
            for (int i = 0; i < MAP.size(); i++) {
                float x = MAP[i][0];
                float y = MAP[i][1];
                float w = MAP[i][2];
                float h = MAP[i][3];

                if (point.x > x && point.x < (x + w)) {
                    if (point.y > y && point.y < (y + h)) {
                        return true;
                    }
                }
            }
            
            return false;
        }

    public:
        Raycaster(std::vector<std::array<float, 4>> MAP, float fov, int rays, int max_depth);

        void cast_rays(glm::vec2 player, float player_angle);
};