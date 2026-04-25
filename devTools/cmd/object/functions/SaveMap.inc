

stock DT_SaveMap(playerid, const mapName[], bool:deleteObjects = false) {
	
	if(!fexist(DT_OBJECTS_FOLDER)) {
		DT_SendError(playerid, DT_TEXT_PROJECT_NOT_FOUND);
		return 0;
	}
	
	new DT_string[350];

	new fileName[32 + DT_LENGTH_PROJECT_NAME],
		totalIndex;
	
	new Float:x, Float:y, Float:z,
		Float:rx, Float:ry, Float:rz,
		modelid,
		worldid,
		interiorid,
		Float:distance;
		
	new m_modelid, 
		txdName[64], 
		textureName[64], 
		materialColor;

	new mt_text[144], 
		materialSize, 
		textSizeMaterial[32],
		fontFace[64], 
		fontSize, 
		bold, 
		fontColor, 
		backColor, 
		textAlignment;

	for(new index; index < DT_MAX_OBJECT; index ++) {

		if(!DT_PlayerObjectData[playerid][dto_Object][index]) {
			continue;
		}

		totalIndex ++;
		break;
	}

	if(!totalIndex) {
		DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
		return 0;
	}
	totalIndex = 0;


	format(fileName, sizeof(fileName), "%s/%s.txt", DT_OBJECTS_FOLDER, mapName);
 	new File:File = fopen(fileName, io_write);

	for(new index; index < DT_MAX_OBJECT; index ++) {

		if(!DT_PlayerObjectData[playerid][dto_Object][index]) {
			continue;
		}

	//Object
		GetDynamicObjectPos(DT_PlayerObjectData[playerid][dto_Object][index], x, y, z);
		GetDynamicObjectRot(DT_PlayerObjectData[playerid][dto_Object][index], rx, ry, rz);

		modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_MODEL_ID);
		worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_WORLD_ID);
		interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_INTERIOR_ID);

		Streamer_GetFloatData(STREAMER_TYPE_OBJECT, DT_PlayerObjectData[playerid][dto_Object][index], E_STREAMER_STREAM_DISTANCE, distance);

		format(DT_string, sizeof(DT_string), "tmpobjid = CreateDynamicObject(%d, %f, %f, %f, %f, %f, %f, %d, %d, -1, %f, %f);\r\n", 
			modelid, 
			x, y, z, 
			rx, ry, rz, 
			worldid, 
			interiorid,
			distance,
			distance);
		fwrite(File, DT_string);


	//Material
		for(new materialIndex; materialIndex <= 16; materialIndex ++) {

			if(IsDynamicObjectMaterialUsed(DT_PlayerObjectData[playerid][dto_Object][index], materialIndex)) {
				
				GetDynamicObjectMaterial(DT_PlayerObjectData[playerid][dto_Object][index], 
					materialIndex, m_modelid, txdName, textureName, materialColor);

				format(DT_string, sizeof(DT_string), "SetDynamicObjectMaterial(tmpobjid, %d, %d, \"%s\", \"%s\", %d);\r\n",
					materialIndex, 
					m_modelid, 
					txdName, 
					textureName, 
					materialColor);

				fwrite(File, DT_string);
			}

			if(IsDynamicObjectMaterialTextUsed(DT_PlayerObjectData[playerid][dto_Object][index], materialIndex)) {

				GetDynamicObjectMaterialText(DT_PlayerObjectData[playerid][dto_Object][index], 
					materialIndex, mt_text, materialSize, fontFace, fontSize, bold, fontColor, backColor, textAlignment);

				switch(materialSize) {
					case OBJECT_MATERIAL_SIZE_32x32: textSizeMaterial = "OBJECT_MATERIAL_SIZE_32x32";
					case OBJECT_MATERIAL_SIZE_64x32: textSizeMaterial = "OBJECT_MATERIAL_SIZE_64x32";
					case OBJECT_MATERIAL_SIZE_64x64: textSizeMaterial = "OBJECT_MATERIAL_SIZE_64x64";
					case OBJECT_MATERIAL_SIZE_128x32: textSizeMaterial = "OBJECT_MATERIAL_SIZE_128x32";
					case OBJECT_MATERIAL_SIZE_128x64: textSizeMaterial = "OBJECT_MATERIAL_SIZE_128x64";
					case OBJECT_MATERIAL_SIZE_128x128: textSizeMaterial = "OBJECT_MATERIAL_SIZE_128x128";
					case OBJECT_MATERIAL_SIZE_256x32: textSizeMaterial = "OBJECT_MATERIAL_SIZE_256x32";
					case OBJECT_MATERIAL_SIZE_256x64: textSizeMaterial = "OBJECT_MATERIAL_SIZE_256x64";
					case OBJECT_MATERIAL_SIZE_256x128: textSizeMaterial = "OBJECT_MATERIAL_SIZE_256x128";
					case OBJECT_MATERIAL_SIZE_256x256: textSizeMaterial = "OBJECT_MATERIAL_SIZE_256x256";
					case OBJECT_MATERIAL_SIZE_512x64: textSizeMaterial = "OBJECT_MATERIAL_SIZE_512x64";
					case OBJECT_MATERIAL_SIZE_512x128: textSizeMaterial = "OBJECT_MATERIAL_SIZE_512x128";
					case OBJECT_MATERIAL_SIZE_512x256: textSizeMaterial = "OBJECT_MATERIAL_SIZE_512x256";
					case OBJECT_MATERIAL_SIZE_512x512: textSizeMaterial = "OBJECT_MATERIAL_SIZE_512x512";
					default: format(textSizeMaterial, sizeof(textSizeMaterial), "%d", materialSize);
				}

				format(DT_string, sizeof(DT_string), "SetDynamicObjectMaterialText(tmpobjid, %d, \"%s\", %s, \"%s\", %d, %d, %d, %d, %d);\r\n",
					materialIndex, 
					mt_text, 
					textSizeMaterial, 
					fontFace, 
					fontSize, 
					bold, 
					fontColor, 
					backColor, 
					textAlignment);

				for(new i; i < strlen(DT_string); i ++) {
					fputchar(File, DT_string[i], false);
				}
			}
		}

		totalIndex ++;

		if(deleteObjects) {
			DT_DestroyObject(playerid, index);
		}
	}
	fclose(File);


	if(totalIndex == 0) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	format(DT_string, sizeof(DT_string), DT_TEXT_SAVING_MAP, mapName, totalIndex);
	DT_SendSucc(playerid, DT_string);
	return 1;
}