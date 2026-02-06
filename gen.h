#pragma once

#include <cstdint>
#include "types.h"

struct Link {
    f32 x = 0;
    f32 z = 0;
    int8_t orientation = 0;
    f32 speedF = 0;
    uint8_t moves[20];
    f32 zs[20];
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

    bool execute(Link& link, f32 z_limit_min, f32 z_limit_max) const {
        for (uint8_t i = 0; i < length; i++) {
            link.x += x_trans[i] * link.orientation;
            link.z += z_trans[i] * link.orientation;
            link.x += x_speed[i] * link.orientation;
            link.z += z_speed[i]*  link.orientation;

            if (link.z < z_limit_min || link.z > z_limit_max) {
                return false;
            }
        }
        link.cost += cost;
        return true;
    }
};
