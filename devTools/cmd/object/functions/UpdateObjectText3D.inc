

stock DT_UpdateObjectText3D(playerid, index) {

    if(!DT_IsObjectCreated(playerid, index)) {
        return 0;
    }

    if(DT_PlayerObjectData[playerid][dto_Text3D][index] == Text3D:INVALID_3DTEXT_ID) {
        return 0;
    }

    new DT_string[144];

    if(DT_PlayerObjectData[playerid][dto_ShowObjectDetails]) {

        new Float:x, Float:y, Float:z, 
            Float:rx, Float:ry, Float:rz;

        new modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_MODEL_ID);

        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_X, x);
        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_Y, y);
        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_Z, z);

        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_X, rx);
        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_Y, ry);
        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_Z, rz);

		format(DT_string, sizeof(DT_string), "Index: "DT_MAIN_COLOR_TAG"%d\n"DT_WHITE_COLOR_TAG"%d\n%f, %f, %f\n%f, %f, %f", 
			index, 
			modelid, 
			x, y, z,
			rx, ry, rz);
	}
	else {
        format(DT_string, sizeof(DT_string), "Index: "DT_MAIN_COLOR_TAG"%d", index);
    }

    UpdateDynamic3DTextLabelText(DT_PlayerObjectData[playerid][dto_Text3D][index], -1, DT_string);
    return 1;
}


