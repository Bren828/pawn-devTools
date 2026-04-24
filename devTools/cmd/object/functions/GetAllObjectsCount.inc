

stock DT_GetAllObjectsCount(playerid) {

	new count;

	for(new index; index < DT_MAX_OBJECT; index ++) {
		if(DT_PlayerObjectData[playerid][dto_Object][index]) {
			count++;
		}
	}

	return count;
}