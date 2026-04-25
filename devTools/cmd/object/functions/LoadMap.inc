

stock DT_LoadMap(playerid, const fileName[], const mapName[]) {

    new File:handle = fopen(fileName, io_read);
	if(!handle) {
		DT_SendError(playerid, DT_TEXT_PROJECT_NOT_FOUND);
        return 0;
	}

    new DT_string[350];

	new modelid,
		Float:x, Float:y, Float:z, 
		Float:rx, Float:ry, Float:rz,
		worldid,
		interiorid,
		Float:streamdistance, 
		last_objectid;
		
	new materialIndex, 
		m_modelid, 
		txdName[64], 
		textureName[64], 
		materialColor;
		
	new mt_text[144], 
		textSizeMaterial[32],
		materialSize = OBJECT_MATERIAL_SIZE_256x128, 
		fontFace[64] = "Arial", 
		fontSize = 24, 
		bold = 1, 
		fontColor = 0xFFFFFFFF, 
		backColor = 0, 
		textAlignment = 0;


	// delete Object
	DT_DestroyAllObjects(playerid);

	new totalIndex;

	// load and create object
	while(fread(handle, DT_string)) {

		if(totalIndex >= DT_MAX_OBJECT) {
			return DT_SendError(playerid, DT_TEXT_LIMIT_OBJECTS);
		}

		if(strlen(DT_string) <= 10) {
			continue;
		}

		if(totalIndex) {
			if(!strcmp(DT_string, "SetDynamicObjectMaterialText", true, 28)) {

				sscanf(DT_string, "P<(),>{s[64]}{s[9]}ds[144]s[32]s[64]ddddd", 
					materialIndex, mt_text, textSizeMaterial, fontFace, fontSize, bold, fontColor, backColor, textAlignment);

                //Deletion ""
				strdel(mt_text, 0, 1);
				strdel(mt_text, strlen(mt_text) - 1, strlen(mt_text));

				strdel(fontFace, 0, 1);
				strdel(fontFace, strlen(fontFace) - 1, strlen(fontFace));

				if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_32x32")) materialSize = OBJECT_MATERIAL_SIZE_32x32;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_64x32")) materialSize = OBJECT_MATERIAL_SIZE_64x32;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_64x64")) materialSize = OBJECT_MATERIAL_SIZE_64x64;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_128x32")) materialSize = OBJECT_MATERIAL_SIZE_128x32;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_128x64")) materialSize = OBJECT_MATERIAL_SIZE_128x64;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_128x128")) materialSize = OBJECT_MATERIAL_SIZE_128x128;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_256x32")) materialSize = OBJECT_MATERIAL_SIZE_256x32;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_256x64")) materialSize = OBJECT_MATERIAL_SIZE_256x64;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_256x128")) materialSize = OBJECT_MATERIAL_SIZE_256x128;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_256x256")) materialSize = OBJECT_MATERIAL_SIZE_256x256;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_512x64")) materialSize = OBJECT_MATERIAL_SIZE_512x64;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_512x128")) materialSize = OBJECT_MATERIAL_SIZE_512x128;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_512x256")) materialSize = OBJECT_MATERIAL_SIZE_512x256;
				else if(!strcmp(textSizeMaterial, "OBJECT_MATERIAL_SIZE_512x512")) materialSize = OBJECT_MATERIAL_SIZE_512x512;
				else materialSize = strval(textSizeMaterial);
			
				SetDynamicObjectMaterialText(last_objectid, materialIndex, mt_text, materialSize, fontFace, fontSize, bold, fontColor, backColor, textAlignment);
				continue;
			}
			else if(!strcmp(DT_string, "SetDynamicObjectMaterial", true, 24)) {

				sscanf(DT_string, "P<(),>{s[64]}{s[9]}dds[64]s[64]d", materialIndex, m_modelid, txdName, textureName, materialColor);

                //Deletion ""
				strdel(txdName, 0, 1);
				strdel(txdName, strlen(txdName) - 1, strlen(txdName));

				strdel(textureName, 0, 1);
				strdel(textureName, strlen(textureName) - 1, strlen(textureName));

				SetDynamicObjectMaterial(last_objectid, materialIndex, m_modelid, txdName, textureName, materialColor);
				continue;
			}
		}

		sscanf(DT_string, "P<(),>{s[64]}dffffffdd{d}f", modelid, x, y, z, rx, ry, rz, worldid, interiorid, streamdistance);

		if(modelid == 0) {
			continue;
		}

		if(streamdistance == 0.0) {
			streamdistance = 300.0;
		}

		DT_CreateObject(playerid, totalIndex, modelid, x, y, z, rx, ry, rz, worldid, interiorid, streamdistance);
	
		last_objectid = DT_PlayerObjectData[playerid][dto_Object][totalIndex];
		totalIndex++;
	}
	fclose(handle);

	if(totalIndex == 0) {
		return DT_SendError(playerid, DT_TEXT_OBJECT_NOT_CREATED);
	}

	format(DT_string, 144, DT_TEXT_LOADING_MAP, mapName, totalIndex);
	DT_SendSucc(playerid, DT_string);

	format(DT_PlayerObjectData[playerid][dto_ProjectName], DT_LENGTH_PROJECT_NAME, mapName);
    return 1;
}