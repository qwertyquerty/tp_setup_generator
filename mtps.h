#pragma once

#include <cstdint>

struct Link {
    float x = 0;
    float z = 0;
    int8_t orientation = 0;
    float speedF = 0;
    uint8_t moves[20];
    float zs[20];
    uint16_t cost = 0;
};

struct Move {
    char name[32];
    float x_trans[80];
    float z_trans[80];
    float x_speed[80];
    float z_speed[80];
    uint8_t length;
    uint8_t cost;
    bool enabled = true;

    bool execute(Link& link, float z_limit_min, float z_limit_max) const {
        for (uint8_t i = 0; i < length; i++) {
            link.x += x_trans[i] * link.orientation;
            link.z += z_trans[i] * link.orientation;
            link.x += x_speed[i] * link.orientation;
            link.z += z_speed[i] * link.orientation;

            if (link.z < z_limit_min || link.z > z_limit_max) {
                return false;
            }
        }
        link.cost += cost;
        return true;
    }

    void estimated_offset(float& x, float& z) {
        for (uint8_t i = 0; i < length; i++) {
            x += x_trans[i];
            z += z_trans[i];
            x += x_speed[i];
            z += z_speed[i];
        }
    }
};
