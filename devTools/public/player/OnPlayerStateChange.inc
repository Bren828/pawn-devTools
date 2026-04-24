

public OnPlayerStateChange(playerid, newstate, oldstate) {

	if(DT_PlayerData[playerid][dtp_PublicStateChange]) {
		static const text[] = "["DT_NAME" State Change]: "DT_WHITE_COLOR_TAG"newstate: %d | oldstate: %d | vehicleid: %d";
    	new DT_string[sizeof(text) + 10 + 10 + 10];

    	format(DT_string, sizeof(DT_string), text, newstate, oldstate, GetPlayerVehicleID(playerid));
		SendClientMessage(playerid, DT_COLOR_MAIN, DT_string);
	}

    #if defined OnPlayerStateChange_DT
        return OnPlayerStateChange_DT(playerid, newstate, oldstate);
    #else 
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerStateChange
    #undef OnPlayerStateChange
#else
    #define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange OnPlayerStateChange_DT
#if defined OnPlayerStateChange_DT
    forward OnPlayerStateChange_DT(playerid, newstate, oldstate);
#endif
