#pragma once

#include <cstdint>
#include "c_math.h"
#include "types.h"

struct Link {
    f32 x = 0;
    f32 z = 0;
    s16 angle = 0;
    f32 speedF = 0;
    uint8_t moves[20];
    f32 zs[20];
    uint16_t time = 0;
};


struct Move {
    char name[32];
    float x_trans[80];
    float z_trans[80];
    float x_speed[80];
    float z_speed[80];
    uint8_t length;

    bool execute(Link& link, f32 z_limit_min, f32 z_limit_max) const {
        for (uint8_t i = 0; i < length; i++) {
            link.x += x_trans[i];
            link.z += z_trans[i];
            link.x += x_speed[i];
            link.z += z_speed[i];

            if (link.z < z_limit_min || link.z > z_limit_max) {
                return false;
            }
        }
        link.time += length;
        return true;
    }
};
