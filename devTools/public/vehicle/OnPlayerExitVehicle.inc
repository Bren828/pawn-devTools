

public OnPlayerExitVehicle(playerid, vehicleid) {

	if(DT_PlayerData[playerid][dtp_PublicExitVehicle]) {

		static const text[] = "["DT_NAME" Exit Vehicle]: "DT_WHITE_COLOR_TAG"playerid: %d | vehicleid: %d";
    	new DT_string[sizeof(text) + 2 * 10];

    	format(DT_string, sizeof(DT_string), text, playerid, vehicleid);
		SendClientMessage(playerid, DT_COLOR_MAIN, DT_string);
	}

    #if defined OnPlayerExitVehicle_DT
        return OnPlayerExitVehicle_DT(playerid, vehicleid);
    #else 
        return 1;
    #endif
}
#if defined _ALS_OnPlayerExitVehicle
    #undef OnPlayerExitVehicle
#else
    #define _ALS_OnPlayerExitVehicle
#endif

#define OnPlayerExitVehicle OnPlayerExitVehicle_DT
#if defined OnPlayerExitVehicle_DT
    forward OnPlayerExitVehicle_DT(playerid, vehicleid);
#endif