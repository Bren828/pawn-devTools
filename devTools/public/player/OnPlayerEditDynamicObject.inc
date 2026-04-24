
#if !defined DT_DISABLE_COMMANDS && !defined DT_DISABLE_OBJECT_EDITOR

	public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {

		if(DT_PlayerObjectData[playerid][dto_EditingIndex] != 0 && (response == EDIT_RESPONSE_CANCEL || response == EDIT_RESPONSE_FINAL)) {

			new index = DT_PlayerObjectData[playerid][dto_EditingIndex] - 1;
			DT_PlayerObjectData[playerid][dto_EditingIndex] = 0;	

			if(response == EDIT_RESPONSE_FINAL) {

				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_X, x);
				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_Y, y);
				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_Z, z);

				SetDynamicObjectPos(objectid, x, y, z);
				SetDynamicObjectRot(objectid, rx, ry, rz);

				DT_UpdateObjectText3D(playerid, index);
			}
			else {
				new Float:last_x, Float:last_y, Float:last_z,
					Float:last_rx, Float:last_ry, Float:last_rz;

				GetDynamicObjectPos(objectid, last_x, last_y, last_z);
				GetDynamicObjectRot(objectid, last_rx, last_ry, last_rz);

				SetDynamicObjectPos(objectid, last_x, last_y, last_z);
				SetDynamicObjectRot(objectid, last_rx, last_ry, last_rz);
			}
			return 1;
		}
		
		#if defined OnPlayerEditDynamicObject_DT
			return OnPlayerEditDynamicObject_DT(playerid, objectid, response, x, y, z, rx, ry, rz);
		#else 
			return 1;
		#endif
	}

	#if defined _ALS_OnPlayerEditDynamicObject
		#undef OnPlayerEditDynamicObject
	#else
		#define _ALS_OnPlayerEditDynamicObject
	#endif

	#define OnPlayerEditDynamicObject OnPlayerEditDynamicObject_DT
	#if defined OnPlayerEditDynamicObject_DT
		forward OnPlayerEditDynamicObject_DT(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
	#endif
#endif