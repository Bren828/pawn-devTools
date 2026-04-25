

CMD:dtocreate(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new modelid;

	if(sscanf(params, "d", modelid)) {
		DT_SendHint(playerid, "/ocreate [modelid]");
		return 1;
	}

	if(modelid < 311) {
		DT_SendError(playerid, DT_TEXT_INVALID_MODEL);
		return 1;
	}

	new index = DT_GetFreeObjectIndex(playerid);

	if(index == DT_INVALID_OBJECT_INDEX) {
		DT_SendError(playerid, DT_TEXT_LIMIT_OBJECTS);
		return 1;
	}

	new Float:x, 
		Float:y, 
		Float:z, 
		Float:ang;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

	DT_ApplyOffset(x, y, z, ang, .xOffset = 0.0, .yOffset = 4.0);

	if(!DT_CreateObject(playerid, index, modelid, x, y, z, 0.0, 0.0, 0.0, .worldid = -1, .interiorid = -1)) {
		return 1;
	}

	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

	new DT_string[sizeof(DT_CMD_TEXT_OCREATE) + 10 + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OCREATE, modelid, index);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtodel(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index;

	if(sscanf(params, "d", index)) {
		DT_SendHint(playerid, "/odel [index]");
		return 1;
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
		return 1;
	}

	DT_DestroyObject(playerid, index);

	new DT_string[sizeof(DT_CMD_TEXT_ODEL) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_ODEL, index);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtodelall(playerid) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new count = DT_DestroyAllObjects(playerid);

	if(!count) {
		DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
		return 1;
	}

	new DT_string[sizeof(DT_CMD_TEXT_ODELALL) + 10];
	
	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_ODELALL, count);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtocopy(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index;

	if(sscanf(params, "d", index)) {
		return DT_SendHint(playerid, "/ocopy [index]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}


	new Float:x, Float:y, Float:z,
		Float:rx, Float:ry,Float:rz;
	
	new modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_MODEL_ID),
		worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_WORLD_ID),
		interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_INTERIOR_ID);
	
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_X, x);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_Y, y);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_Z, z);

	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_X, rx);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_Y, ry);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_Z, rz);
	

	new newIndex = DT_GetFreeObjectIndex(playerid);

	if(newIndex == DT_INVALID_OBJECT_INDEX) {
		DT_SendError(playerid, DT_TEXT_LIMIT_OBJECTS);
		return 1;
	}

	if(!DT_CreateObject(playerid, newIndex, modelid, x, y, z, rx, ry, rz, worldid, interiorid)) {
		return 1;
	}

	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

	//Copy materials
	new txdName[64], 
		textureName[64], 
		materialColor;

	new materialText[144], 
		materialSize, 
		fontFace[64], 
		fontSize, 
		bold, 
		fontColor, 
		backColor, 
		textAlignment;
		
	for(new material; material <= 16; material ++) {

		if(IsDynamicObjectMaterialUsed(DT_PlayerObjectData[playerid][dto_Object][index], material)) {

			GetDynamicObjectMaterial(DT_PlayerObjectData[playerid][dto_Object][index], 
				material, modelid, txdName, textureName, materialColor);

			SetDynamicObjectMaterial(DT_PlayerObjectData[playerid][dto_Object][newIndex], 
				material, modelid, txdName, textureName, materialColor);
		}

		if(IsDynamicObjectMaterialTextUsed(DT_PlayerObjectData[playerid][dto_Object][index], material)) {

			GetDynamicObjectMaterialText(DT_PlayerObjectData[playerid][dto_Object][index], 
				material, materialText, materialSize, fontFace, fontSize, bold, fontColor, backColor, textAlignment);

			SetDynamicObjectMaterialText(DT_PlayerObjectData[playerid][dto_Object][newIndex], 
				material, materialText, materialSize, fontFace, fontSize, bold, fontColor, backColor, textAlignment);
		}
	}

	new DT_string[sizeof(DT_CMD_TEXT_OCOPY) + 10 + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OCOPY, modelid, newIndex);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtoedit(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index;

	if(sscanf(params, "d", index)) {
		return DT_SendHint(playerid, "/oedit [index]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	DT_PlayerObjectData[playerid][dto_IsSelected] = false;
	DT_PlayerObjectData[playerid][dto_EditingIndex] = index + 1;

	EditDynamicObject(playerid, DT_PlayerObjectData[playerid][dto_Object][index]);	
	return 1;
}


CMD:dtoinfo(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index;

	if(sscanf(params, "d", index)) {
		return DT_SendHint(playerid, "/oinfo [index]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new DT_string[144];


	//line 1
	new modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_MODEL_ID);

	format(DT_string, sizeof(DT_string), "Modelid: %d", modelid);
	DT_SendSucc(playerid, DT_string);


	//line 1.1
	new Float:x, Float:y, Float:z,
		Float:rx, Float:ry, Float:rz;

	GetDynamicObjectPos(DT_PlayerObjectData[playerid][dto_Object][index], x, y, z);
	GetDynamicObjectRot(DT_PlayerObjectData[playerid][dto_Object][index], rx, ry, rz);

	format(DT_string, sizeof(DT_string), "Position: %f, %f, %f, %f, %f, %f", 
		x, y, z,
		rx, ry, rz);
	DT_SendSucc(playerid, DT_string); 


	// line 2
	new Float:distance;
	new worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_WORLD_ID);
	new interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_INTERIOR_ID);

	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_STREAM_DISTANCE, distance);

	format(DT_string, sizeof(DT_string), "World: %d | Interior: %d | Distance: %.2f", 
		worldid,
		interiorid,
		distance);
	DT_SendSucc(playerid, DT_string);


	//line 3
	new txdName[64], 
		textureName[64], 
		materialColor;

	for(new materialIndex; materialIndex <= 16; materialIndex ++) {
		if(!IsDynamicObjectMaterialUsed(DT_PlayerObjectData[playerid][dto_Object][index], materialIndex)) {
			continue;
		}

		DT_SendSucc(playerid, "");

		GetDynamicObjectMaterial(DT_PlayerObjectData[playerid][dto_Object][index], 
			materialIndex, modelid, txdName, textureName, materialColor);
		
		format(DT_string, sizeof(DT_string), "Material index: %d | Modelid: %d | Material color: %d",
			materialIndex,
			modelid, 
			materialColor);
		DT_SendSucc(playerid, DT_string);

		format(DT_string, sizeof(DT_string), "Txd name: %s", txdName);
		DT_SendSucc(playerid, DT_string);

		format(DT_string, sizeof(DT_string), "Texture name: %s", textureName);
		DT_SendSucc(playerid, DT_string);
	}


	//line 4
	new text[144], 
		materialSize, 
		fontFace[64], 
		fontSize, 
		bold, 
		fontColor, 
		backColor, 
		textAlignment;

	for(new materialIndex; materialIndex <= 16; materialIndex ++) {
		if(!IsDynamicObjectMaterialTextUsed(DT_PlayerObjectData[playerid][dto_Object][index], materialIndex)) {
			continue;
		}

		DT_SendSucc(playerid, "");
	
		GetDynamicObjectMaterialText(DT_PlayerObjectData[playerid][dto_Object][index], 
			materialIndex, text, materialSize, fontFace, fontSize, bold, fontColor, backColor, textAlignment);

		format(DT_string, sizeof(DT_string), "Material index: %d | Material size: %d | fontSize: %d | Bold: %d | Text alignment: %d",
			materialIndex, 
			materialSize, 
			fontSize, 
			bold, 
			textAlignment);
		DT_SendSucc(playerid, DT_string);

		format(DT_string, sizeof(DT_string), "Text: %s", text);
		DT_SendSucc(playerid, DT_string);

		format(DT_string, sizeof(DT_string), "FontFace: %s", fontFace);
		DT_SendSucc(playerid, DT_string);

		format(DT_string, sizeof(DT_string), "Font color: %d | Back color: %d", fontColor, backColor);
		DT_SendSucc(playerid, DT_string);

		DT_SendSucc(playerid, "");
	}

	return 1;
}


CMD:dtogoto(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index;

	if(sscanf(params, "d", index)) {
		return DT_SendHint(playerid, "/ogoto [index]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new Float:x, 
		Float:y, 
		Float:z;

	GetDynamicObjectPos(DT_PlayerObjectData[playerid][dto_Object][index], x, y, z);

	new interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_INTERIOR_ID);
	new worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_WORLD_ID);

	SetPlayerPos(playerid, x, y, z);
	SetPlayerInterior(playerid, (interiorid == -1) ? (0) : (interiorid));
	SetPlayerVirtualWorld(playerid, (worldid == -1) ? (0) : (worldid));

	new DT_string[sizeof(DT_CMD_TEXT_OGOTO) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OGOTO, index);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtogethere(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index;

	if(sscanf(params, "d", index)) {
		return DT_SendHint(playerid, "/ogethere [index]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new Float:x, 
		Float:y, 
		Float:z;

	GetPlayerPos(playerid, x, y, z);

	SetDynamicObjectPos(DT_PlayerObjectData[playerid][dto_Object][index], x, y, z);

	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_X, x);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_Y, y);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_Z, z);

	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	
	new DT_string[sizeof(DT_CMD_TEXT_OGETHERE) + 10];
		
	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OGETHERE, index);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtotextdis(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:distance;

	if(sscanf(params, "f", distance)) {
		return DT_SendHint(playerid, "/otextdis [distance]");
	}

	DT_PlayerObjectData[playerid][dto_Tex3dDistance] = distance;	

	for(new i; i < DT_MAX_OBJECT; i ++) {
		if(DT_PlayerObjectData[playerid][dto_Object][i]) {
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][i], E_STREAMER_DRAW_DISTANCE, distance);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][i], E_STREAMER_STREAM_DISTANCE, distance);
		}
	}

	new DT_string[sizeof(DT_CMD_TEXT_OTEXTDIS) + 10];
		
	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OTEXTDIS, distance);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtotextdetal(playerid) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(!DT_PlayerObjectData[playerid][dto_ShowObjectDetails]) {
		DT_PlayerObjectData[playerid][dto_ShowObjectDetails] = true;
		DT_SendSucc(playerid, DT_CMD_TEXT_OTEXTDETAL_ON);
	}
	else {
		DT_PlayerObjectData[playerid][dto_ShowObjectDetails] = false;
		DT_SendSucc(playerid, DT_CMD_TEXT_OTEXTDETAL_OFF);
	}

	for(new index; index < DT_MAX_OBJECT; index ++) {
		if(DT_PlayerObjectData[playerid][dto_Object][index]) {
			DT_UpdateObjectText3D(playerid, index);
		}
	}

	return 1;
}


CMD:dtoworld(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		worldid;

	if(sscanf(params, "dd", index, worldid)) {
		return DT_SendHint(playerid, "/oworld [index] [world]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_WORLD_ID, worldid);
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_WORLD_ID, worldid);

	new DT_string[sizeof(DT_CMD_TEXT_OWORLD) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OWORLD, worldid);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtoworldall(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new worldid,
		count;

	if(sscanf(params, "d", worldid)) {
		return DT_SendHint(playerid, "/oworldall [world]");
	}

	for(new i; i < DT_MAX_OBJECT; i ++) {
		if(DT_PlayerObjectData[playerid][dto_Object][i]) {
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_WORLD_ID, worldid);
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][i], E_STREAMER_WORLD_ID, worldid);
			count++;
		}
	}

	if(!count) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new DT_string[sizeof(DT_CMD_TEXT_OWORLDALL) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OWORLDALL, worldid);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtoint(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		interiorid;

	if(sscanf(params, "dd", index, interiorid)) {
		return DT_SendHint(playerid, "/oint [index] [interior]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_INTERIOR_ID, interiorid);
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_INTERIOR_ID, interiorid);

	new DT_string[sizeof(DT_CMD_TEXT_OINT) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OINT, interiorid);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtointall(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new interiorid,
		count;

	if(sscanf(params, "d", interiorid)) {
		return DT_SendHint(playerid, "/ointall [interior]");
	}

	for(new i; i < DT_MAX_OBJECT; i ++) {
		if(DT_PlayerObjectData[playerid][dto_Object][i]) {
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_INTERIOR_ID, interiorid);
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][i], E_STREAMER_INTERIOR_ID, interiorid);
			count++;
		}
	}

	if(!count) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new DT_string[sizeof(DT_CMD_TEXT_OINTALL) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OINTALL, interiorid);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtodis(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		Float:distance;

	if(sscanf(params, "df", index, distance)) 
		return DT_SendHint(playerid, "/odis [index] [distance]");

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_DRAW_DISTANCE, distance);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_STREAM_DISTANCE, distance);

	new DT_string[sizeof(DT_CMD_TEXT_ODIS) + 10 + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_ODIS, index, distance);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtodisall(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:distance,
		count;

	if(sscanf(params, "f", distance)) {
		return DT_SendHint(playerid, "/odisall [distance]");
	}

	for(new i; i < DT_MAX_OBJECT; i ++) {
		if(DT_PlayerObjectData[playerid][dto_Object][i]) {
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_DRAW_DISTANCE, distance);
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_STREAM_DISTANCE, distance);
			count++;
		}
	}

	if(!count) { 
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new DT_string[sizeof(DT_CMD_TEXT_ODISALL) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_ODISALL, distance);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtloadmap(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(!fexist(DT_OBJECTS_FOLDER)) {
		return DT_SendError(playerid, DT_TEXT_INVALID_FOLDER);
	}

	new fileName[32 + DT_LENGTH_PROJECT_NAME];

	if(!strlen(params)) {
		return DT_SendHint(playerid, "/loadmap [name]");
	}

	if(!(2 <= strlen(params) <= DT_LENGTH_PROJECT_NAME)) {
		new DT_string[sizeof(DT_TEXT_INVALID_LENGTH) + 2];
		
		format(DT_string, sizeof(DT_string), DT_TEXT_INVALID_LENGTH, DT_LENGTH_PROJECT_NAME);
		return DT_SendError(playerid, DT_string);
	}

	format(fileName, sizeof(fileName), "%s/%s.txt", DT_OBJECTS_FOLDER, params);
	if(!fexist(fileName)) {
		return DT_SendError(playerid, DT_TEXT_PROJECT_NOT_FOUND);
	}

	DT_LoadMap(playerid, fileName, params);

	return 1;
}


CMD:dtsavemap(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(!fexist(DT_OBJECTS_FOLDER)) {
		return DT_SendError(playerid, DT_TEXT_INVALID_FOLDER);
	}

	if(!strlen(params)) {
		return DT_SendHint(playerid, "/savemap [name]");
	}

	if(!(2 <= strlen(params) <= DT_LENGTH_PROJECT_NAME)) {
		new DT_string[sizeof(DT_TEXT_INVALID_LENGTH) + 2];
		
		format(DT_string, sizeof(DT_string), DT_TEXT_INVALID_LENGTH, DT_LENGTH_PROJECT_NAME);
		return DT_SendError(playerid, DT_string);
	}

	DT_SaveMap(playerid, params);
	return 1;
}


CMD:dtosetm(playerid, params[]) { 

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index = -1,
		materialIndex,
		modelid,
		txdName[64],
		textureName[64],
		materialColor = 0;

	sscanf(params, "ddds[64]s[64]m", index, materialIndex, modelid, txdName, textureName, materialColor);
		
	if(index == -1) {
		return DT_SendHint(playerid, "/osetm [index] [material Index] [modelid] [txd name] [texture name] [material color]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	if(!(0 <= materialIndex <= 15)) {
		return DT_SendError(playerid, DT_TEXT_INVALID_MATERIAL_INDEX);
	}

	if(!(1 <= strlen(txdName) <= 64)) {
		return DT_SendError(playerid, DT_CMD_TEXT_OSETM_TXD_LEN);
	}

	if(!(1 <= strlen(textureName) <= 64)) {
		return DT_SendError(playerid, DT_CMD_TEXT_OSETM_TEXTURE_LEN);
	}

	SetDynamicObjectMaterial(DT_PlayerObjectData[playerid][dto_Object][index], 
		materialIndex, 
		modelid, 
		txdName, 
		textureName, 
		materialColor);

	new DT_string[144];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OSETM,
		index,
		materialIndex,
		modelid, 
		materialColor);
	DT_SendSucc(playerid, DT_string);

	format(DT_string, sizeof(DT_string), "Txd name: %s", txdName);
	DT_SendSucc(playerid, DT_string);

	format(DT_string, sizeof(DT_string), "Texture name: %s", textureName);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtosetmt(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index = -1,
		materialIndex,
		text[144], 
		materialSize = OBJECT_MATERIAL_SIZE_256x128,
		fontFace[64] = "Arial", 
		fontSize = 24, 
		bold = 1, 
		fontColor = 0xFFFFFFFF, 
		backColor = 0, 
		textAlignment = 0;

	sscanf(params, "dds[144]ds[64]ddmmd", index, materialIndex, text, materialSize, fontFace, fontSize, bold, fontColor, backColor, textAlignment);
		
	if(index == -1) {
		return DT_SendHint(playerid, "/osetmt [index] [material index] [text] [material size] [font] [font size] [bold] [font color] [back color] [text alignment]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	if(!(0 <= materialIndex <= 15)) {
		return DT_SendError(playerid, DT_TEXT_INVALID_MATERIAL_INDEX);
	}

	if(!(1 <= strlen(text) <= 144)) {
		return DT_SendError(playerid, DT_CMD_TEXT_OSETMT_TEXT_LEN);
	}

	if(!(1 <= strlen(fontFace) <= 64)) {
		return DT_SendError(playerid, DT_CMD_TEXT_OSETMT_FONT_LEN);
	}

	SetDynamicObjectMaterialText(DT_PlayerObjectData[playerid][dto_Object][index], 
		materialIndex,
		text, 
		materialSize,
		fontFace, 
		fontSize, 
		bold, 
		fontColor, 
		backColor, 
		textAlignment);

	new DT_string[144];
	
	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OSETMT, index);
	DT_SendSucc(playerid, DT_string);

	format(DT_string, sizeof(DT_string), "Material index: %d | Material size: %d | fontSize: %d | Bold: %d | Text alignment: %d",
		materialIndex, 
		materialSize, 
		fontSize, 
		bold, 
		textAlignment);
	DT_SendSucc(playerid, DT_string);

	format(DT_string, sizeof(DT_string), "Text: %s", text);
	DT_SendSucc(playerid, DT_string);

	format(DT_string, sizeof(DT_string), "FontFace: %s", fontFace);
	DT_SendSucc(playerid, DT_string);

	format(DT_string, sizeof(DT_string), "Font color: %d | Back color: %d", fontColor, backColor);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtormt(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		materialIndex;

	if(sscanf(params, "dd", index, materialIndex)) {
		return DT_SendHint(playerid, "/ormt [index] [material Index]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	if(!(0 <= materialIndex <= 15)) {
		return DT_SendError(playerid, DT_TEXT_INVALID_MATERIAL_INDEX);
	}

	#if defined RemoveDynamicObjectMaterial
		RemoveDynamicObjectMaterial(DT_PlayerObjectData[playerid][dto_Object][index], materialIndex);
	#else 
		DT_SendError(playerid, DT_TEXT_OLD_VERSION_PLUGIN);
	#endif

	new DT_string[sizeof(DT_CMD_TEXT_ORMT) + 10 + 2];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_ORMT, index, materialIndex);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtormtt(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		materialIndex;

	if(sscanf(params, "dd", index, materialIndex)) {
		return DT_SendHint(playerid, "/ormtt [index] [materialindex]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	if(!(0 <= materialIndex <= 15)) {
		return DT_SendError(playerid, DT_TEXT_INVALID_MATERIAL_INDEX);
	}

	#if defined RemoveDynamicObjectMaterialText
		RemoveDynamicObjectMaterialText(DT_PlayerObjectData[playerid][dto_Object][index], materialIndex);
	#else 
		DT_SendError(playerid, DT_TEXT_OLD_VERSION_PLUGIN);
	#endif

	new DT_string[sizeof(DT_CMD_TEXT_ORMTT) + 10 + 2];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_ORMTT, index, materialIndex);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtox(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		Float:x;

	if(sscanf(params, "df", index, x)) {
		return DT_SendHint(playerid, "/ox [index] [x]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new Float:lastX;
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_X, lastX);

	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_X, x);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_X, x);
	
	new DT_string[sizeof(DT_CMD_TEXT_OX) + 3 * 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OX, index, lastX, x);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtoy(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		Float:y;

	if(sscanf(params, "df", index, y)) {
		return DT_SendHint(playerid, "/oy [index] [y]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new Float:lastY;
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_Y, lastY);

	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_Y, y);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_Y, y);
	
	new DT_string[sizeof(DT_CMD_TEXT_OY) + 3 * 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OY, index, lastY, y);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtoz(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		Float:z;

	if(sscanf(params, "df", index, z)) {
		return DT_SendHint(playerid, "/oz [index] [z]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new Float:lastZ;
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_Z, lastZ);

	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_Z, z);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][index], E_STREAMER_Z, z);

	new DT_string[sizeof(DT_CMD_TEXT_OZ) + 3 * 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OZ, index, lastZ, z);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtorx(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		Float:rx;

	if(sscanf(params, "df", index, rx)) {
		return DT_SendHint(playerid, "/orx [index] [rx]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new Float:lastRx;
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_X, lastRx);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_X, rx);
	
	new DT_string[sizeof(DT_CMD_TEXT_ORX) + 3 * 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_ORX, index, lastRx, rx);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtory(playerid, params[]) { 

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		Float:ry;

	if(sscanf(params, "df", index, ry)) {
		return DT_SendHint(playerid, "/ory [index] [ry]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new Float:lastRy;
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_Y, lastRy);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_Y, ry);
	
	new DT_string[sizeof(DT_CMD_TEXT_ORY) + 3 * 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_ORY, index, lastRy, ry);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtorz(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index,
		Float:rz;

	if(sscanf(params, "df", index, rz)) {
		return DT_SendHint(playerid, "/orz [index] [rz]");
	}

	if(!DT_IsObjectCreated(playerid, index)) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new Float:lastRz;
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_Z, lastRz);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_R_Z, rz);
	
	new DT_string[sizeof(DT_CMD_TEXT_ORZ) + 3 * 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_ORZ, index, lastRz, rz);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtoxall(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:x;

	if(sscanf(params, "f", x)) {
		return DT_SendHint(playerid, "/oxall [x]");
	}

	new count,
		Float:lastX;

	for(new i; i < DT_MAX_OBJECT; i ++) {

		if(DT_PlayerObjectData[playerid][dto_Object][i]) {
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_X, lastX);

			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_X, lastX + x);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][i], E_STREAMER_X, lastX + x);
			count++;
		}
	}

	if(!count) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new DT_string[sizeof(DT_CMD_TEXT_OXALL) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OXALL, x);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtoyall(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:y;

	if(sscanf(params, "f", y)) {
		return DT_SendHint(playerid, "/oyall [y]");
	}

	new count,
		Float:lastY;

	for(new i; i < DT_MAX_OBJECT; i ++) {

		if(DT_PlayerObjectData[playerid][dto_Object][i]) {
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_Y, lastY);

			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_Y, lastY + y );
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][i], E_STREAMER_Y, lastY + y);
			count++;
		}
	}

	if(!count) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new DT_string[sizeof(DT_CMD_TEXT_OYALL) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OYALL, y);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtozall(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) { 
		return 1;
	}

	new Float:z;

	if(sscanf(params, "f", z)) {
		return DT_SendHint(playerid, "/ozall [z]");
	}

	new count,
		Float:lastZ;

	for(new i; i < DT_MAX_OBJECT; i ++) {

		if(DT_PlayerObjectData[playerid][dto_Object][i]) {
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_Z, lastZ);

			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][i], E_STREAMER_Z, lastZ + z);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DT_PlayerObjectData[playerid][dto_Text3D][i], E_STREAMER_Z, lastZ + z);
			count++;
		}
	}

	if(!count) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	new DT_string[sizeof(DT_CMD_TEXT_OZALL) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_OZALL, z);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtoselect(playerid) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	DT_PlayerObjectData[playerid][dto_IsSelected] = true;
	SelectObject(playerid);
	return 1;
}
