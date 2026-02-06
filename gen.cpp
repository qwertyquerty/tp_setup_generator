#include <cstdint>
#include <cstdio>

#include "gen.h"
#include "moves.h"

const Link initial_link = {
    0.0f, -3390.98608, 0, 0.0f
};

const f32 min_z = -3369.531;
const f32 max_z = -3369.5255;

const f32 z_limit_min = -3390.98608;
const f32 z_limit_max = 10000;

const uint8_t max_depth = 10;
const uint8_t max_time = 100;

void recurse(Link link, uint8_t depth) {
    if (link.z >= min_z && link.z <= max_z) {
        printf("SOLUTION x: %f z: %f d: %d t: %d m: ", link.x, link.z, depth, link.time);
        for (uint8_t i = 0; i < depth; i++) {
            printf("%s %f ", moves[link.moves[i]].name, link.zs[i]);
        }
        printf("\n");
        return;
    }

    if (depth >= max_depth) {
        return;
    }

    for (uint8_t i = 0; i < sizeof(moves)/sizeof(Move); i++) {
        Link linkcopy = link;
        if ((link.time + moves[i].length) <= max_time) {
            bool success = moves[i].execute(linkcopy, z_limit_min, z_limit_max);
            if (success) {
                linkcopy.zs[depth] = linkcopy.z;
                linkcopy.moves[depth] = i;
                recurse(linkcopy, depth+1);
            }
        }
    }
}

int main() {
    recurse(initial_link, 0);
    return 0;
}
