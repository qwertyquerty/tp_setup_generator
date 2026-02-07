#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "mtps.h"
#include "moves.h"
#include "SimpleIni.h"

#define VERSION "1.2"

#define TURN_MOVE_ID 0xFF

uint64_t nodes;
float min_z;
float max_z;
float z_limit_min;
float z_limit_max;
uint8_t max_depth;
uint8_t max_cost;
const char* output_filename;
std::ofstream output_file;
bool turn_disabled = false;

const char* get_movename(int move) {
    return move == TURN_MOVE_ID ? "TURN" : moves[move].name;
}

void recurse(Link link, uint8_t depth) {
    nodes++;

    if (link.z >= min_z && link.z <= max_z) {
        std::cout << "[zf: "<<link.z<<"\txf: "<<link.x<<"\tn: "<<nodes<<"\tc: "<<(int)link.cost<<"\td: "<<(int)depth<<"]\t";
        for (uint8_t i = 0; i < depth; i++) {
            std::cout << " " << get_movename(link.moves[i]) << "(" << link.zs[i] << ")";
        }

        output_file << "[zf: "<<link.z<<"\txf: "<<link.x<<"\tn "<<nodes<<"\tc: "<<(int)link.cost<<"\td: "<<(int)depth<<"]\t";
        for (uint8_t i = 0; i < depth; i++) {
            output_file << " " << get_movename(link.moves[i]) << "(" << link.zs[i] << ")";
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
        if (moves[i].enabled && (link.cost + moves[i].cost) <= max_cost) {
            bool success = moves[i].execute(linkcopy, z_limit_min, z_limit_max);
            if (success) {
                linkcopy.zs[depth] = linkcopy.z;
                linkcopy.moves[depth] = i;
                recurse(linkcopy, depth+1);
            }
        }
    }

    if (!turn_disabled && (depth == 0 || link.moves[depth-1] != TURN_MOVE_ID)) {
        Link linkcopy = link;
        linkcopy.orientation *= -1;
        linkcopy.moves[depth] = TURN_MOVE_ID;
        linkcopy.zs[depth] = linkcopy.z;
        recurse(linkcopy, depth+1);
    }
}

int main() {
    std::cout << "Madeline's Twilight Princess Setup Tool v" << VERSION << std::endl << std::endl;

	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile("config.ini");

	if (rc < 0) {
        std::cout << "Could not find config.ini in the same folder as mtps.exe!" << std::endl;
        system("pause");
        return 1;
    }

    Link initial_link;

    std::cout << std::setprecision(7) << std::fixed;

    try {
        const char* pv;
        pv = ini.GetValue("config", "link_pos", "0.0");

        initial_link = {
            0.0f, std::stof(pv), 0, 0.0f
        };

        pv = ini.GetValue("config", "link_orientation", "1");
        initial_link.orientation = std::stoi(pv);

        nodes = 0;

        pv = ini.GetValue("config", "goal_min", "0.0");
        min_z = std::stof(pv);

        pv = ini.GetValue("config", "goal_max", "0.0");
        max_z = std::stof(pv);

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

        pv = ini.GetValue("config", "disabled_moves", "");
        std::stringstream dmss;
        dmss << pv;

        while(dmss.good()) {
            std::string movename;
            std::getline(dmss, movename, ',');
            for (uint8_t i = 0; i < sizeof(moves)/sizeof(Move); i++) {
                if (strcmp(moves[i].name, movename.c_str()) == 0) {
                    printf("Disabling %s\n", movename.c_str());
                    moves[i].enabled = false;
                }
                if (strcmp("TURN", movename.c_str()) == 0) {
                    turn_disabled = true;
                }
            }
        }
    }
    catch (...) {
        std::cout << "Failed to parse config.ini" << std::endl;
        system("pause");
        return 1;
    }

    output_file << std::setprecision(7) << std::fixed;

    std::cout << std::endl;

    system("pause");

    std::cout << std::endl << "\nGenerating setups..." << std::endl << std::endl;

    recurse(initial_link, 0);

    std::cout << std::endl << "Search complete! Made with <3 by Maddie" << std::endl << std::endl;

    system("pause");

    return 0;
}
