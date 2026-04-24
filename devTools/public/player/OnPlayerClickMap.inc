

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {

	if(DT_PlayerData[playerid][dtp_EnableTeleportByMark]) {
        
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
            SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);
        }
        else {
            SetPlayerPos(playerid, fX, fY, fZ);
        }
        return 1;
	}

    #if defined OnPlayerClickMap_DT
        return OnPlayerClickMap_DT(playerid, fX, fY, fZ);
    #else 
        return 1;
    #endif
}
#if defined _ALS_OnPlayerClickMap
    #undef OnPlayerClickMap
#else
    #define _ALS_OnPlayerClickMap
#endif

#define OnPlayerClickMap OnPlayerClickMap_DT
#if defined OnPlayerClickMap_DT
    forward OnPlayerClickMap_DT(playerid, Float:fX, Float:fY, Float:fZ);
#endif
