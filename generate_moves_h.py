import os
import re
import numpy as np

trans_re = re.compile("^.*trans: x:(.*) z:(.*)$")
speedF_re = re.compile("^.*speedF: x:(.*) z:(.*)$")

h_lines = ["#pragma once\n\n", "#include \"gen.h\"\n\n", "Move moves[] = {\n",]

MOVES_DIR = "moves"

def zipped_sum(a, b):
    t = np.float32(0.0)

    for i in range(len(a)):
        t = t + a[i]
        t = t + b[i]

    return t

for movefile in os.listdir(MOVES_DIR):
    with open(os.path.join(MOVES_DIR, movefile), "r") as f:
        lines = f.readlines()

        x_trans = np.array([], dtype=np.float32)
        z_trans = np.array([], dtype=np.float32)

        x_speed = np.array([], dtype=np.float32)
        z_speed = np.array([], dtype=np.float32)


        for line in lines:
            m = trans_re.match(line)

            if m:
                x_trans = np.append(x_trans, np.float32(m.group(1)))
                z_trans = np.append(z_trans, np.float32(m.group(2)))

            m = speedF_re.match(line)

            if m:
                x_speed = np.append(x_speed, np.float32(m.group(1)))
                z_speed = np.append(z_speed, np.float32(m.group(2)))
                
                if len(x_speed) > len(x_trans):
                    x_trans = np.append(x_trans, np.float32(0))
                    z_trans = np.append(z_trans, np.float32(0))

    print("\nMOVE:", movefile, "\nX_TRANS:", *x_trans, "\nX_SPEED:", *x_speed, "\nZ_TRANS:", *z_trans, "\nZ_SPEED:", *z_speed, "\nNAIVE SUM:", zipped_sum(x_trans, x_speed), zipped_sum(z_trans, z_speed))

    h_lines.append(f"{{\"{movefile}\", {{{', '.join([str(x) for x in x_trans])}}}, {{{', '.join([str(z) for z in z_trans])}}}, {{{', '.join([str(x) for x in x_speed])}}}, {{{', '.join([str(z) for z in z_speed])}}}, {len(z_speed)}}},\n")

h_lines.append("};\n")

with open("moves.h", "w") as h_file:
    h_file.writelines(h_lines)
