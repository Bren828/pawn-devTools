

public OnPlayerSpawn(playerid) { 
	
	if(DT_PlayerData[playerid][dtp_PublicSpawn]) {
		static const text[] = "["DT_NAME" Spawn]: "DT_WHITE_COLOR_TAG"playerid: %d";
    	new DT_string[sizeof(text) + 10];

		format(DT_string, sizeof(DT_string), text, playerid);
		SendClientMessage(playerid, DT_COLOR_MAIN, DT_string);
	}
	
    #if defined OnPlayerSpawn_DT
        return OnPlayerSpawn_DT(playerid);
    #else 
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn OnPlayerSpawn_DT
#if defined OnPlayerSpawn_DT
    forward OnPlayerSpawn_DT(playerid);
#endif