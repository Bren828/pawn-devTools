

public OnPlayerDisconnect(playerid, reason) {
	
    if(DT_PlayerData[playerid][dtp_PlayerStatsTimer]) {
		KillTimer(DT_PlayerData[playerid][dtp_PlayerStatsTimer]);
	}
	
	if(DT_PlayerData[playerid][dtp_VehicleStatsTimer]) {
		KillTimer(DT_PlayerData[playerid][dtp_VehicleStatsTimer]);
	}

	if(DT_PlayerData[playerid][dtp_EnableDistancePoint]) {
		DestroyDynamic3DTextLabel(DT_PlayerData[playerid][dtp_PointText3D]);
	}
	

	#if !defined DT_DISABLE_COMMANDS && !defined DT_DISABLE_OBJECT_EDITOR
		if(DT_GetAllObjectsCount(playerid)) {

			if(strlen(DT_PlayerObjectData[playerid][dto_ProjectName]) <= 1) {
				new dt_hour, dt_minute, dt_second,
					dt_year, dt_month, dt_day;

				gettime(dt_hour, dt_minute, dt_second);
				getdate(dt_year, dt_month, dt_day);

				static const dt_text[] = "AutoSave_%s_%d-%02d-%02d_%02d-%02d-%02d";
				new mapName[sizeof(dt_text) + MAX_PLAYER_NAME];
				
				format(mapName, sizeof(mapName), dt_text, DT_GetName(playerid), dt_year, dt_month, dt_day, dt_hour, dt_minute, dt_second);
				DT_SaveMap(playerid, mapName, true);
			}
			else {
				DT_SaveMap(playerid, DT_PlayerObjectData[playerid][dto_ProjectName], true);
			}
		}
	#endif

	DT_PlayerData[playerid] = DT_NullPlayerData;

    #if defined OnPlayerDisconnect_DT
        return OnPlayerDisconnect_DT(playerid, reason);
	#else 
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect OnPlayerDisconnect_DT
#if defined OnPlayerDisconnect_DT
    forward OnPlayerDisconnect_DT(playerid, reason);
#endif