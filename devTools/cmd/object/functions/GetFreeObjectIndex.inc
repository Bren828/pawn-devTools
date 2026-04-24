

stock DT_GetFreeObjectIndex(playerid) {
	
	for(new index; index < DT_MAX_OBJECT; index ++) {
		if(!DT_PlayerObjectData[playerid][dto_Object][index]) {
			return index;
		}
	}
    
	return DT_INVALID_OBJECT_INDEX;
}


