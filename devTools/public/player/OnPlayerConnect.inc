

public OnPlayerConnect(playerid) {

	DT_PlayerData[playerid] = DT_NullPlayerData;
	GetPlayerName(playerid, DT_PlayerData[playerid][dtp_Name], MAX_PLAYER_NAME);

	DT_PlayerData[playerid][dtp_PlayerIDStats] = INVALID_PLAYER_ID;
	DT_PlayerData[playerid][dtp_VehicleIDStats] = INVALID_VEHICLE_ID;
	DT_PlayerData[playerid][dtp_RaknetPlayerIDStats] = INVALID_PLAYER_ID;
	DT_PlayerData[playerid][dtp_RaknetVehicleIDStats] = INVALID_PLAYER_ID;
	DT_PlayerData[playerid][dtp_RaknetPassengerIDStats] = INVALID_PLAYER_ID;

    #if !defined DT_DISABLE_COMMANDS && !defined DT_DISABLE_OBJECT_EDITOR
	    DT_PlayerObjectData[playerid][dto_Tex3dDistance] = 28.0;
    #endif

    #if defined OnPlayerConnect_DT
        return OnPlayerConnect_DT(playerid);
    #else 
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect OnPlayerConnect_DT
#if defined OnPlayerConnect_DT
    forward OnPlayerConnect_DT(playerid);
#endif
