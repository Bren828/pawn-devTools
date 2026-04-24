

public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z) {

	#if !defined DT_DISABLE_COMMANDS && !defined DT_DISABLE_OBJECT_EDITOR
		if(DT_PlayerObjectData[playerid][dto_IsSelected]) {

			for(new index; index < DT_MAX_OBJECT; index ++) {
				if(DT_PlayerObjectData[playerid][dto_Object][index] == 0) {
					continue;
				}

				if(DT_PlayerObjectData[playerid][dto_Object][index] != objectid) {
					continue;
				}

				DT_PlayerObjectData[playerid][dto_IsSelected] = false;
				DT_PlayerObjectData[playerid][dto_EditingIndex] = index + 1;
				EditDynamicObject(playerid, DT_PlayerObjectData[playerid][dto_Object][index]);
				return 1;
			}
		}
	#endif

    #if defined OnPSelectDynamicObject_DT
        return OnPSelectDynamicObject_DT(playerid, objectid, modelid, x, y, z);
    #else 
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerSelectDynamicObjec
    #undef OnPlayerSelectDynamicObject
#else
    #define _ALS_OnPlayerSelectDynamicObjec
#endif

#define OnPlayerSelectDynamicObject OnPSelectDynamicObject_DT
#if defined OnPSelectDynamicObject_DT
    forward OnPSelectDynamicObject_DT(playerid, objectid, modelid, Float:x, Float:y, Float:z);
#endif