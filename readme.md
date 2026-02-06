# Madeline's TP Setup Generator

## How to use

Run the exe in the same folder as a config.ini file

## Example config.ini

```
[config]
# links starting position along the axis he is facing
link_pos=-13015.9883

# 1 if he is facing positive on that axis, -1 if he is facing negative on that axis
link_orientation=1

# minimum value of the goal positional range
goal_min=-12977.2773

# maximum value of the goal positional range
goal_max=-12977.2734

# lowest coordinate link can travel to during the setup before he hits a wall / falls / etc.
collision_limit_min=-13015.9883

# highest coordinate link can travel to during the setup before he hits a wall / falls / etc.
collision_limit_max=-10000

# maximum number of actions to consider in a setup, recommended to be no more than 9 or your search will be very long
max_depth=6

# maximum cost of the setup, based on weighted cost of specific actions, recommended to be no more than 2 times your max depth and should be no less than your max depth
cost_max=10

# name of the output file to store the generated setups
output_filename=tp_setups.txt

# comma separated list of move names, no spaces, like NEUTRAL_SLASH,IB_NEUTRAL_SLASH
disabled_moves=PLACE_BOMB_DAMAGE,PLACE_BOMB_SHIELD
```
