

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {

	if(DT_PlayerData[playerid][dtp_PublicEnterVehicle]) {
        
		static const text[] = "["DT_NAME" Enter Vehicle]: "DT_WHITE_COLOR_TAG"playerid: %d | vehicleid: %d | ispassenger: %d";
    	new DT_string[sizeof(text) + 3 * 10];

    	format(DT_string, sizeof(DT_string), text, playerid, vehicleid, ispassenger);
		SendClientMessage(playerid, DT_COLOR_MAIN, DT_string);
	}

    #if defined OnPlayerEnterVehicle_DT
        return OnPlayerEnterVehicle_DT(playerid, vehicleid, ispassenger);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerEnterVehicle
    #undef OnPlayerEnterVehicle
#else
    #define _ALS_OnPlayerEnterVehicle
#endif

#define OnPlayerEnterVehicle OnPlayerEnterVehicle_DT
#if defined OnPlayerEnterVehicle_DT
    forward OnPlayerEnterVehicle_DT(playerid, vehicleid, ispassenger);
#endif