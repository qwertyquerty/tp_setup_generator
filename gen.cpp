#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

#include "gen.h"
#include "moves.h"
#include "SimpleIni.h"

#define TURN_MOVE_ID 0xFF

uint64_t nodes;
f32 min_z;
f32 max_z;
f32 z_limit_min;
f32 z_limit_max;
uint8_t max_depth;
uint8_t max_cost;
const char* output_filename;
std::ofstream output_file;

void recurse(Link link, uint8_t depth) {
    nodes++;

    if (link.z >= min_z && link.z <= max_z) {
        std::cout << "pos_fin: "<<link.z<<"\tside_fin: "<<link.x<<"\tnodes: "<<nodes<<"\tdepth: "<<(int)depth<<"\tcost: "<<link.cost<<"\tmoves:";
        for (uint8_t i = 0; i < depth; i++) {
            std::cout << " " << moves[link.moves[i]].name << "(" << link.zs[i] << ")";
        }

        output_file << "pos_fin: "<<link.z<<"\tside_fin: "<<link.x<<"\tnodes: "<<nodes<<"\tdepth: "<<(int)depth<<"\tcost: "<<link.cost<<"\tmoves:";
        for (uint8_t i = 0; i < depth; i++) {
            output_file << " " << moves[link.moves[i]].name << "(" << link.zs[i] << ")";
        }

        std::cout << std::endl << std::endl;
        output_file << std::endl << std::endl;

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

    if (link.moves[depth]) {
        Link linkcopy = link;
    }
}

int main() {
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile("config.ini");

	if (rc < 0) {
        std::cout << "Could not find config.ini in the same folder as mtps.exe!";
        system("pause");
        return 1;
    }

    Link initial_link;

    try {
        const char* pv;
        pv = ini.GetValue("config", "link_pos", "0.0");

        initial_link = {
            0.0f, std::stof(pv), 0, 0.0f
        };

        pv = ini.GetValue("config", "link_orientation", "1");
        initial_link.orientation = std::stoi(pv);

        uint64_t nodes = 0;

        pv = ini.GetValue("config", "goal_min", "0.0");
        min_z = std::stof(pv);

        pv = ini.GetValue("config", "goal_max", "0.0");
        min_z = std::stof(pv);

        pv = ini.GetValue("config", "collision_limit_min", "0.0");
        z_limit_min = std::stof(pv);

        pv = ini.GetValue("config", "collision_limit_max", "0.0");
        z_limit_max = std::stof(pv);

        pv = ini.GetValue("config", "max_depth", "5");
        max_depth = std::stoi(pv);

        pv = ini.GetValue("config", "cost_max", "10");
        max_cost = std::stoi(pv);

        output_filename = ini.GetValue("config", "output_filename", "tp_setups.txt");
        output_file = std::ofstream(output_filename);
    }
    catch (...) {
        std::cout << "Failed to parse config.ini" << std::endl;
        system("pause");
        return 1;
    }

    std::cout << "Generating setups..." << std::endl;

    recurse(initial_link, 0);

    return 0;
}
