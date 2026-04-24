
public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, 
	Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, 
	Float:fRotX, Float:fRotY, Float:fRotZ, 
	Float:fScaleX, Float:fScaleY, Float:fScaleZ) {

	if(DT_PlayerData[playerid][dtp_AttachedObject] && (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)) {

		if(response == EDIT_RESPONSE_FINAL) {

			new DT_string[144];
			DT_SendSucc(playerid, "SetPlayerAttachedObject(");

			format(DT_string, sizeof(DT_string), "%d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f);", 
				index, 
				modelid, 
				boneid, 
				fOffsetX, fOffsetY, fOffsetZ, 
				fRotX, fRotY, fRotZ, 
				fScaleX, fScaleY, fScaleZ);
			DT_SendSucc(playerid, DT_string);
			

			printf("SetPlayerAttachedObject(playerid, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f);", 
				index, 
				modelid, 
				boneid, 
				fOffsetX, fOffsetY, fOffsetZ, 
				fRotX, fRotY, fRotZ, 
				fScaleX, fScaleY, fScaleZ);


			DT_PlayerData[playerid][dtp_AttachedOffsetX] = fOffsetX;
			DT_PlayerData[playerid][dtp_AttachedOffsetY] = fOffsetY;
			DT_PlayerData[playerid][dtp_AttachedOffsetZ] = fOffsetZ;

			DT_PlayerData[playerid][dtp_AttachedRotX] = fRotX; 
			DT_PlayerData[playerid][dtp_AttachedRotY] = fRotY; 
			DT_PlayerData[playerid][dtp_AttachedRotZ] = fRotZ; 

			DT_PlayerData[playerid][dtp_AttachedScaleX] = fScaleX;
			DT_PlayerData[playerid][dtp_AttachedScaleY] = fScaleY;
			DT_PlayerData[playerid][dtp_AttachedScaleZ] = fScaleZ;
		}

		DT_PlayerData[playerid][dtp_AttachedObject] = false;
	}

    #if defined OnPlayerEditAttachedO_DT
        return OnPlayerEditAttachedO_DT(playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
	#else 
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerEditAttachedObject
    #undef OnPlayerEditAttachedObject
#else
    #define _ALS_OnPlayerEditAttachedObject
#endif

#define OnPlayerEditAttachedObject OnPlayerEditAttachedO_DT
#if defined OnPlayerEditAttachedO_DT
    forward OnPlayerEditAttachedO_DT(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ);
#endif