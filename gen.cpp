#include <cstdint>
#include <cstdio>

#include "gen.h"
#include "moves.h"

const Link initial_link = {
    0.0f, -3390.98608, 0, 0.0f
};

uint64_t nodes = 0;

const f32 min_z = -3369.531;
const f32 max_z = -3369.5255;

const f32 z_limit_min = -3390.98608;
const f32 z_limit_max = 10000;

const uint8_t max_depth = 7;
const uint8_t max_cost = 11;

void recurse(Link link, uint8_t depth) {
    nodes++;

    if (link.z >= min_z && link.z <= max_z) {
        printf("xfin: %f\tzfin: %f\t node: %llu\tdepth: %d\tcost: %d\tmoves: ", link.x, link.z, nodes, depth, link.cost);
        for (uint8_t i = 0; i < depth; i++) {
            printf("%s(%f), ", moves[link.moves[i]].name, link.zs[i]);
        }
        printf("\n\n");
        return;
    }

    if (depth >= max_depth) {
        return;
    }

    for (uint8_t i = 0; i < sizeof(moves)/sizeof(Move); i++) {
        Link linkcopy = link;
        if ((link.cost + moves[i].cost) <= max_cost) {
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
