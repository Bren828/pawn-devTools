

public OnPlayerDeath(playerid, killerid, reason) {

	if(DT_PlayerData[playerid][dtp_PublicDeath] || killerid != INVALID_PLAYER_ID && DT_PlayerData[killerid][dtp_PublicDeath]) {

		static const text[] = "["DT_NAME" Death]: "DT_WHITE_COLOR_TAG"playerid: %d | killerid: %d | reason: %d";
    	new DT_string[sizeof(text) + 3 * 10];

		format(DT_string, sizeof(DT_string), text, playerid, killerid, reason);
		
		if(killerid == INVALID_PLAYER_ID) {
			SendClientMessage(playerid, DT_COLOR_MAIN, DT_string);
		} 
		else {
			SendClientMessage(killerid, DT_COLOR_MAIN, DT_string);
		}
	}
	
    #if defined OnPlayerDeath_DT
        return OnPlayerDeath_DT(playerid, killerid, reason);
	#else 
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerDeath
    #undef OnPlayerDeath
#else
    #define _ALS_OnPlayerDeath
#endif

#define OnPlayerDeath OnPlayerDeath_DT
#if defined OnPlayerDeath_DT
    forward OnPlayerDeath_DT(playerid, killerid, reason);
#endif
