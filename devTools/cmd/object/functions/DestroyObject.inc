

stock DT_DestroyObject(playerid, index) {

    if(!DT_IsObjectCreated(playerid, index)) {
        return 0;
    }

    DestroyDynamicObject(DT_PlayerObjectData[playerid][dto_Object][index]);
	DT_PlayerObjectData[playerid][dto_Object][index] = 0;

	DestroyDynamic3DTextLabel(DT_PlayerObjectData[playerid][dto_Text3D][index]);
	DT_PlayerObjectData[playerid][dto_Text3D][index] = Text3D:INVALID_3DTEXT_ID;

    return 1;
}


stock DT_DestroyAllObjects(playerid) {

    new count = 0;

    for(new index; index < DT_MAX_OBJECT; index ++) {
        if(DT_PlayerObjectData[playerid][dto_Object][index]) {
            DT_DestroyObject(playerid, index);
            count++;
        }
    }

    DT_PlayerObjectData[playerid][dto_ProjectName][0] = '\0';

    return count;
}


stock DT_IsObjectCreated(playerid, index) {

    if(!(0 <= index <= DT_MAX_OBJECT)) {
        return false;
    }

    return DT_PlayerObjectData[playerid][dto_Object][index] != 0;
}