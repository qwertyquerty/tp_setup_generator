# Madeline's TP Setup Generator

## How to use

Run the exe in the same folder as a config.ini file

## Example config.ini

```
[config]
# links starting positions along the axis he is facing, separate each by comma
link_pos=-13015.9883,-13015.9922

# 1 if he is facing positive on that axis, -1 if he is facing negative on that axis
link_orientation=1

# if true, will also simulate facing opposite of orientation specified
try_both_orientations=false

# min/max values of the goal positional range - separate min and max by : and then each range by ;
goal_ranges=-12977.2773:-12977.2734;-12917.2773:-12917.2734

# lowest coordinate link can travel to during the setup before he hits a wall / falls / etc.
collision_limit_min=-13015.9883

# highest coordinate link can travel to during the setup before he hits a wall / falls / etc.
collision_limit_max=-10000

# maximum number of actions to consider in a setup, recommended to be no more than 9 or your search will be very long
max_depth=5

# maximum cost of the setup, based on weighted cost of specific actions, recommended to be no more than 2 times your max depth and should be no less than your max depth
cost_max=9

# name of the output file to store the generated setups
output_filename=tp_setups.txt

# comma separated list of move names, no spaces, like NEUTRAL_SLASH,IB_NEUTRAL_SLASH
# support regular expressions, for example .*ABR.* will disable all abridged moves
disabled_moves=.*SHIELD_ATTACK.*,.*JUMP_STRIKE.*,.*BOMB.*
```
