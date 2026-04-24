

public OnGameModeInit() {

	for(new i; i < MAX_VEHICLES; i ++) {
		DT_Vehicles[i] = INVALID_VEHICLE_ID;
	}


	// Function to rename commands.
	// Initially all commands come with the "dt" prefix, but if the command does not exist, the prefix will be removed.
	// This is done to make the command more recognizable.

	#if defined PAWNCMD_INC_ && !defined DT_DISABLE_COMMANDS
		DT_RenameCommandList(DT_PLAYER_COMMANDS, sizeof(DT_PLAYER_COMMANDS), .start = 2);
		DT_RenameCommandList(DT_VEHICLE_COMMANDS, sizeof(DT_VEHICLE_COMMANDS));

		#if !defined DT_DISABLE_OBJECT_EDITOR
			DT_RenameCommandList(DT_OBJECT_COMMANDS, sizeof(DT_OBJECT_COMMANDS));
		#endif
	#endif

    #if defined OnGameModeInit_DT
        return OnGameModeInit_DT();
    #else 
		return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit OnGameModeInit_DT
#if defined OnGameModeInit_DT
    forward OnGameModeInit_DT();
#endif


