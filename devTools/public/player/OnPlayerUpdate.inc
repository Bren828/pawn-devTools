

public OnPlayerUpdate(playerid) {

	if(DT_PlayerData[playerid][dtp_EnableDistancePoint]) {

	    new DT_stirng[30];
		new Float:FromPoint = GetPlayerDistanceFromPoint(playerid, 
			DT_PlayerData[playerid][dtp_PointDistancePosX], 
			DT_PlayerData[playerid][dtp_PointDistancePosY], 
			DT_PlayerData[playerid][dtp_PointDistancePosZ]);

	    format(DT_stirng, sizeof(DT_stirng), "~r~~h~~h~~h~~h~~h~%.4f", FromPoint);
	    GameTextForPlayer(playerid, DT_stirng, 1000, 4);
	}


    if(DT_PlayerData[playerid][dtp_PublicAnimation] && GetPlayerAnimationIndex(playerid) != 0) {

		static const text[] = "Index: "DT_MAIN_COLOR_TAG"%d "DT_WHITE_COLOR_TAG"| AnimLib: "DT_MAIN_COLOR_TAG"%s "DT_WHITE_COLOR_TAG"| AnimName: "DT_MAIN_COLOR_TAG"%s";
        
		new DT_stirng[sizeof(text) + 10 + 32 + 32];
		new animLib[32], 
			animName[32],
			animationIndex = GetPlayerAnimationIndex(playerid);

        GetAnimationName(animationIndex, animLib, sizeof(animLib), animName, sizeof(animName));

        format(DT_stirng, sizeof(DT_stirng), text, animationIndex, animLib, animName);
	    DT_SendSucc(playerid, DT_stirng);
    }


	if(DT_PlayerData[playerid][dtp_EnableGodMode] && GetPlayerState(playerid) != PLAYER_STATE_WASTED) {
		new Float:health;
		GetPlayerHealth(playerid, health);

		if(health <= 0x7F800000 - 10.0) {
			SetPlayerHealth(playerid, 0x7F800000);
		}
	}


    #if defined OnPlayerUpdate_DT
        return OnPlayerUpdate_DT(playerid);
    #else 
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate OnPlayerUpdate_DT
#if defined OnPlayerUpdate_DT
    forward OnPlayerUpdate_DT(playerid);
#endif