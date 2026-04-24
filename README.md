# pawn-devTools

## Installation

Include in your code and begin using the library:
```pawn
#define DT_DISABLE_OBJECT_EDITOR // optional

#include <devTools\devTools>
```

## Functions
#### SetAccessDevTools(playerid, status)
> Assigns a specific access status to a player
> * `playerid` - The ID of the player
> * `status` - The access level value to set (0 for disabled, 1 for enabled).

#### GetAccessDevTools(playerid)
> Retrieves the current access status of a player
> * `playerid` - The ID of the player
> * Returns the current `status`


## Definition
<details>
<summary>Click to expand the list</summary>

```pawn
#define DT_DISABLE_COMMANDS
#define DT_DISABLE_OBJECT_EDITOR
#define DT_ENABLE_IGNORE_PUNISHMENTS

#define DT_INTERFACE_LANGUAGE 0 // 0 - English | 1 - Russian 

#define DT_MAX_OBJECT 200
#define DT_MIN_VEHICLE_MODEL 400
#define DT_MAX_VEHICLE_MODEL 611
#define DT_MIN_SKIN_MODEL 0
#define DT_MAX_SKIN_MODEL 311
#define DT_OBJECTS_FOLDER "devTools_Maps"
#define DT_LENGTH_PROJECT_NAME 32
#define DT_VEHICLE_SPEED_MULTIPLIER 179.28625

#define DT_COLOR_MAIN 0xfbbaa8FF
#define DT_MAIN_COLOR_TAG "{fbbaa8}"
#define DT_WHITE_COLOR_TAG "{FFFFFF}"
#define DT_RED_COLOR_TAG "{f44747}"
#define DT_GREEN_COLOR_TAG "{61dd61}"
```

</details