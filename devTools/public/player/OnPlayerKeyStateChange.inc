


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

	if(DT_PlayerData[playerid][dtp_PublicKey]) {

		static const text[] = "["DT_NAME" Key]: "DT_WHITE_COLOR_TAG"newkeys: "DT_MAIN_COLOR_TAG"%d "DT_WHITE_COLOR_TAG"| oldkeys: "DT_MAIN_COLOR_TAG"%d";
    	new string[sizeof(text) + 10 + 10];

		format(string, sizeof(string), text, newkeys, oldkeys);
	    SendClientMessage(playerid, DT_COLOR_MAIN, string);
 	}


	if(DT_PlayerData[playerid][dtp_EnableDoubleJump] && newkeys == KEY_JUMP && !IsPlayerInAnyVehicle(playerid)) {

		if(DT_PlayerData[playerid][dtp_DoubleJumpDelay] < GetTickCount() && DT_PlayerData[playerid][dtp_DoubleJumpDelay] != 0) {
			DT_PlayerData[playerid][dtp_DoubleJumpDelay] = 0;
		}

		if(DT_PlayerData[playerid][dtp_DoubleJumpDelay] != 0 && DT_PlayerData[playerid][dtp_DoubleJumpDelay] > GetTickCount()) {
			new Float:X, 
				Float:Y, 
				Float:Z;
				
			GetPlayerVelocity(playerid, X, Y, Z);

			if(Z == 0.0) {
				SetPlayerVelocity(playerid, X, Y, 3.0);
				return 1;
			}
		}
		else {
			DT_PlayerData[playerid][dtp_DoubleJumpDelay] = GetTickCount()+300;
		}
	}

    #if defined OnPlayerKeyStateChange_DT
        return OnPlayerKeyStateChange_DT(playerid, newkeys, oldkeys);
    #else 
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange OnPlayerKeyStateChange_DT
#if defined OnPlayerKeyStateChange_DT
    forward OnPlayerKeyStateChange_DT(playerid, newkeys, oldkeys);
#endif