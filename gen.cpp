#include <cstdint>
#include <cstdio>

#include "gen.h"
#include "moves.h"

const Link initial_link = {
    0.0f, -7075.98633f, 0, 0.0f
};

const f32 min_z = -6571.845f-0.00025f;
const f32 max_z = -6571.845f+0.00025f;

const f32 z_limit_min = -7075.98633;

const uint8_t max_depth = 6;

void recurse(Link link, uint8_t depth) {
    if (link.z >= min_z && link.z <= max_z) {
        printf("SOLUTION x: %f z: %f d: %d m: ", link.x, link.z, depth);
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
        bool success = moves[i].execute(linkcopy, z_limit_min);

        if (success) {
            linkcopy.zs[depth] = linkcopy.z;
            linkcopy.moves[depth] = i;
            recurse(linkcopy, depth+1);
        }
    }
}

int main() {
    recurse(initial_link, 0);
    return 0;
}
