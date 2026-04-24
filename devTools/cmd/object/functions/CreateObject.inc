

stock DT_CreateObject(playerid, index, modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, Float:streamdistance = 300.0) {

//Object
    new objectid = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, worldid, interiorid, -1, streamdistance, streamdistance);
    if(objectid == INVALID_OBJECT_ID) {
        DT_SendError(playerid, DT_TEXT_FAILED_CREATE_OBJECT);
        return 0;
    }

    DT_PlayerObjectData[playerid][dto_Object][index] = objectid;


//3DText
    DT_PlayerObjectData[playerid][dto_Text3D][index] = CreateDynamic3DTextLabel(" ", -1, 
		x, y, z, 
		DT_PlayerObjectData[playerid][dto_Tex3dDistance], 
		INVALID_PLAYER_ID, 
		INVALID_VEHICLE_ID,
		0,
		worldid, interiorid);

    DT_UpdateObjectText3D(playerid, index);
    return 1;
}
