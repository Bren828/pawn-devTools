


CMD:dtgotopos(playerid, params[]) { //tppos

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:x,
		Float:y,
		Float:z,
		Float:ang,
		world,
		interior,
		vehicleid = GetPlayerVehicleID(playerid);

	if(sscanf(params, "p<,>fffI(-1)I(-1)", x, y, z, world, interior)) {
		DT_SendHint(playerid, "/gotopos [X] [Y] [Z] [World] [Interior]");

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, ang);

		new DT_string[144];
		format(DT_string, sizeof(DT_string), "Player pos - %.4f, %.4f, %.4f, %.4f, %d, %d", x, y, z, ang, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
		DT_SendSucc(playerid, DT_string);

		if(IsPlayerInAnyVehicle(playerid)) {
		    GetVehiclePos(vehicleid, x, y, z);
			GetVehicleZAngle(vehicleid, ang);

			format(DT_string, sizeof(DT_string), "Vehicle pos - %.4f, %.4f, %.4f, %.4f", x, y, z, ang);
			DT_SendSucc(playerid, DT_string);
		}
		return 1;
	}

	if(x != -1.0 && y != -1.0 && z != -1.0) {
		if(IsPlayerInAnyVehicle(playerid)) {
			SetVehiclePos(vehicleid, x, y, z);
		}
		else {
			SetPlayerPos(playerid, x, y, z);
		}
	}

	if(world != -1) {
		SetPlayerVirtualWorld(playerid, world);
	}
	else {
		world = GetPlayerVirtualWorld(playerid);
	}

	if(interior != -1) {
		SetPlayerInterior(playerid, interior);
	}
	else {
		interior = GetPlayerInterior(playerid);
	}

	new DT_string[sizeof(DT_CMD_TEXT_GOTOPOS) + 5 * 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_GOTOPOS, x, y, z, world, interior);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtgoto(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/goto [id]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	new Float:x, 
		Float:y, 
		Float:z;

	GetPlayerPos(params[0], x, y, z);

	if(IsPlayerInAnyVehicle(playerid)) {
		SetVehiclePos(GetPlayerVehicleID(playerid), x + 0.2, y + 0.2, z);
	}
	else {
		SetPlayerPos(playerid, x + 0.2, y + 0.2, z);
	}

	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));
	SetPlayerInterior(playerid, GetPlayerInterior(params[0]));

	new DT_string[sizeof(DT_CMD_TEXT_GOTO) + MAX_PLAYER_NAME + 2];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_GOTO, DT_GetName(params[0]), params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtgethere(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/gethere [id]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	new Float:x,
		Float:y, 
		Float:z;

	GetPlayerPos(playerid, x, y, z);

	if(IsPlayerInAnyVehicle(params[0])) {
		SetVehiclePos(GetPlayerVehicleID(params[0]), x + 0.2, y + 0.2, z);
	}
	else {
		SetPlayerPos(params[0], x, y, z);
	}

	SetPlayerVirtualWorld(params[0], GetPlayerVirtualWorld(playerid));
	SetPlayerInterior(params[0], GetPlayerInterior(playerid));

	new DT_string[sizeof(DT_CMD_TEXT_GETHERE) + MAX_PLAYER_NAME + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_GETHERE, DT_GetName(params[0]), params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtsetint(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/setint [id interior]");
	}

	new DT_string[sizeof(DT_CMD_TEXT_SETINT) + 10 + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETINT, params[0], GetPlayerInterior(playerid));
 	DT_SendSucc(playerid, DT_string);

	SetPlayerInterior(playerid, params[0]);
	return 1;
}



CMD:dtsetworld(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/setworld [id world]");
	}

	new DT_string[sizeof(DT_CMD_TEXT_SETWORLD) + 10 + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETWORLD, params[0], GetPlayerVirtualWorld(playerid));
 	DT_SendSucc(playerid, DT_string);

	SetPlayerVirtualWorld(playerid, params[0]);
	return 1;
}



CMD:dtspawn(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/spawn [id]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	if(GetPlayerState(params[0]) == PLAYER_STATE_SPECTATING) {
		TogglePlayerSpectating(params[0], false);
	}
	else if(GetPlayerState(params[0]) == PLAYER_STATE_DRIVER || GetPlayerState(params[0]) == PLAYER_STATE_PASSENGER) {
		new Float:x,
			Float:y,
			Float:z;

		GetVehiclePos(GetPlayerVehicleID(params[0]), x, y, z),
		SetPlayerPos(params[0], x, y, z);
		SpawnPlayer(params[0]);
	}
	else {
		SpawnPlayer(params[0]);
	}

	new DT_string[sizeof(DT_CMD_TEXT_SPAWN) + MAX_PLAYER_NAME + 4];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SPAWN, DT_GetName(params[0]), params[0]);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtsethp(playerid, params[]) {
	
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:health;
	if(sscanf(params, "df", params[0], health)) {
		return DT_SendHint(playerid, "/sethp [id] [health]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	SetPlayerHealth(params[0], health);
	
	new DT_string[sizeof(DT_CMD_TEXT_SETHP) + MAX_PLAYER_NAME + 10 + 4];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETHP, health, DT_GetName(params[0]), params[0]);
 	DT_SendSucc(playerid,  DT_string);
	return 1;
}



CMD:dtsetar(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:armour;
	if(sscanf(params, "df", params[0], armour)) {
		return DT_SendHint(playerid, "/setar [id] [armour]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	SetPlayerArmour(params[0], armour);
	
	new DT_string[sizeof(DT_CMD_TEXT_SETAR) + MAX_PLAYER_NAME + 10 + 4];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETAR, armour, DT_GetName(params[0]), params[0]);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtgiveweapon(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "ddd", params[0], params[1], params[2])) {
		return DT_SendHint(playerid, "/giveweapon [id] [weapon id] [ammo]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}
	
	if(params[1] < 0 || params[1] > 46 || params[1] >= 19 && params[1] <= 21) {
		return DT_SendError(playerid, DT_TEXT_INVALID_WEAPON_ID);
	}

	GivePlayerWeapon(params[0], params[1], params[2]);
	
	new DT_string[sizeof(DT_CMD_TEXT_GIVEWEAPON) + 10 + MAX_PLAYER_NAME + 4];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_GIVEWEAPON, params[1], params[2], DT_GetName(params[0]), params[0]);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtgivemoney(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "dd", params[0], params[1])) {
		return DT_SendHint(playerid, "/givemoney [id] [money]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	ResetPlayerMoney(params[0]);
	GivePlayerMoney(params[0], params[1]);
	
	new DT_string[sizeof(DT_CMD_TEXT_GIVEMONEY) + 10 + MAX_PLAYER_NAME + 4];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_GIVEMONEY, params[1], DT_GetName(params[0]), params[0]);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtsetscore(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "dd", params[0], params[1])) {
		return DT_SendHint(playerid, "/setscore [id] [score]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	SetPlayerScore(params[0], params[1]);
	
	new DT_string[sizeof(DT_CMD_TEXT_SETSCORE) + 10 + MAX_PLAYER_NAME + 4];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETSCORE, params[1], DT_GetName(params[0]), params[0]);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtsetskin(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "dd", params[0], params[1])) {
		return DT_SendHint(playerid, "/setskin [id] [skin id]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	if(params[1] < DT_MIN_SKIN_MODEL || params[1] > DT_MAX_SKIN_MODEL || params[1] == 74) {
		return DT_SendError(playerid, DT_TEXT_INVALID_SKIN_ID);
	}

	SetPlayerSkin(params[0], params[1]);
	
	new DT_string[sizeof(DT_CMD_TEXT_SETSKIN) + 3 + MAX_PLAYER_NAME + 4];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETSKIN, params[1], DT_GetName(params[0]), params[0]);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtplaysound(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/playsound [sound id]");
	}

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	PlayerPlaySound(playerid, params[0], x, y, z);

	new DT_string[sizeof(DT_CMD_TEXT_PLAYSOUND) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_PLAYSOUND, params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtexplosion(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:radius;

	if(sscanf(params, "ddf", params[0], params[1], radius)) {
		return DT_SendHint(playerid, "/explosion [id] [explosion] [radius]");
	}

	if(!IsPlayerConnected(params[0])) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	new Float:x, Float:y, Float:z;
	GetPlayerPos(params[0], x, y, z);

	CreateExplosion(x, y, z, params[1], radius);

	new DT_string[sizeof(DT_CMD_TEXT_EXPLOSION) + MAX_PLAYER_NAME + 4];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_EXPLOSION, params[1], DT_GetName(params[0]), params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtsettime(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/settime [hour]");
	}

	SetWorldTime(params[0]);

	new DT_string[sizeof(DT_CMD_TEXT_SETTIME) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETTIME, params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtsetweather(playerid, params[]) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/setweather [weather id]");
	}

	SetWeather(params[0]);

	new DT_string[sizeof(DT_CMD_TEXT_SETWEATHER) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETWEATHER, params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}


CMD:dtplayanim(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new animlib[32], 
		animname[32], 
		Float:fDelta,
		loop, 
		lockx, 
		locky, 
		freeze, 
		time, 
		forcesync;

	if(sscanf(params, "s[32]s[32]fdddddd", animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync)) {
		return DT_SendHint(playerid, "/playanim [animlib] [animname] [fDelta] [loop] [lockx] [locky] [freeze] [time] [forcesync]");
	}

    ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
	return 1;
}



CMD:dtgetcam(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:X, Float:Y, Float:Z,
		Float:VX, Float:VY, Float:VZ;

	new Float:fScale = 5.0;

	GetPlayerCameraPos(playerid, X, Y, Z);
	GetPlayerCameraFrontVector(playerid, VX, VY, VZ);

	new Float:FX = X + floatmul(VX, fScale);
	new Float:FY = Y + floatmul(VY, fScale);
	new Float:FZ = Z + floatmul(VZ, fScale);

	static const text[] = "Pos: %f, %f, %f | Vector: %f, %f, %f";
	new DT_string[sizeof(text) + 6 * 10];

	format(DT_string, sizeof(DT_string), text, X, Y, Z, FX, FY, FZ);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtsetaction(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/setaction [action id]");
	}

	SetPlayerSpecialAction(playerid, params[0]);

	new DT_string[sizeof(DT_CMD_TEXT_SETACTION) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETACTION, params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtstartrecord(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(!strlen(params)) {
		return DT_SendHint(playerid, "/startrecord [recordname]");
	}

	if(!(2 <= strlen(params) <= 32)) {
		new DT_string[sizeof(DT_TEXT_INVALID_LENGTH) + 2];
		
		format(DT_string, sizeof(DT_string), DT_TEXT_INVALID_LENGTH, 32);
		return DT_SendError(playerid, DT_string);
	}

	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
		StartRecordingPlayerData(playerid, PLAYER_RECORDING_TYPE_ONFOOT, params);
    } 
	else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		StartRecordingPlayerData(playerid, PLAYER_RECORDING_TYPE_DRIVER, params);
	}

	DT_SendSucc(playerid, DT_CMD_TEXT_STARTRECORD);
	return 1;
}



CMD:dtstoprecord(playerid) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	StopRecordingPlayerData(playerid);

	DT_SendSucc(playerid, DT_CMD_TEXT_STOPRECORD);
	return 1;
}



CMD:dtfstyle(playerid, params[]) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/fstyle [style]");
	}

	SetPlayerFightingStyle(playerid, params[0]);

	new DT_string[sizeof(DT_CMD_TEXT_FSTYLE) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_FSTYLE, params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtsetdrunk(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/setdrunk [level]");
	}

	SetPlayerDrunkLevel(playerid, params[0]);

	new DT_string[sizeof(DT_CMD_TEXT_SETDRUNK) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETDRUNK, params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtattedit(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new index = -1, 
		modelid = 0, 
		bone = 0, 
		color = 0xFFFFFFFF;

	sscanf(params, "ddd", index, modelid, bone);

	if(index == -1 || modelid == 0 || bone == 0) {
		return DT_SendHint(playerid, "/attedit [index] [modelid] [bone]");
	}

	DT_PlayerData[playerid][dtp_NewAttachedIndex] = index;
	DT_PlayerData[playerid][dtp_NewAttachedModel] = modelid;
	DT_PlayerData[playerid][dtp_NewAttachedBone] = bone;
	DT_PlayerData[playerid][dtp_NewAttachedColor] = color;
	
	if(DT_PlayerData[playerid][dtp_AttachedModel] == modelid) {

		ShowPlayerDialog(playerid, DT_DIALOGID_SET_OBJECT, DIALOG_STYLE_MSGBOX, DT_CMD_TEXT_ATTEDIT_INFO, 
			DT_CMD_TEXT_ATTEDIT_CAPTION, 
			DT_CONFIRM_BUTTON, 
			DT_CANCEL_BUTTON);
		return 1;	
	}

	DT_PlayerData[playerid][dtp_AttachedObject] = true;
	DT_PlayerData[playerid][dtp_AttachedIndex] = index;
	DT_PlayerData[playerid][dtp_AttachedModel] = modelid;
	DT_PlayerData[playerid][dtp_AttachedBone] = bone;
	DT_PlayerData[playerid][dtp_AttachedColor] = color;

	DT_PlayerData[playerid][dtp_AttachedOffsetX] = 0.0;
	DT_PlayerData[playerid][dtp_AttachedOffsetY] = 0.0;
	DT_PlayerData[playerid][dtp_AttachedOffsetZ] = 0.0;

	DT_PlayerData[playerid][dtp_AttachedRotX] = 0.0; 
	DT_PlayerData[playerid][dtp_AttachedRotY] = 0.0; 
	DT_PlayerData[playerid][dtp_AttachedRotZ] = 0.0;

	DT_PlayerData[playerid][dtp_AttachedScaleX] = 1.0;
	DT_PlayerData[playerid][dtp_AttachedScaleY] = 1.0;
	DT_PlayerData[playerid][dtp_AttachedScaleZ] = 1.0;

	SetPlayerAttachedObject(playerid, index, modelid, bone, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, color);
	EditAttachedObject(playerid, index);
	return 1;
}



CMD:dtweaponskill(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "dd", params[0], params[1])) {
		return DT_SendHint(playerid, "/weaponskill [weapon id] [level]");
	}

	SetPlayerSkillLevel(playerid, params[0], params[1]);

	new DT_string[sizeof(DT_CMD_TEXT_WEAPONSKILL) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_WEAPONSKILL, params[0], params[1]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtsetwanted(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "d", params[0])) {
		return DT_SendHint(playerid, "/setwanted [level]");
	}

	SetPlayerWantedLevel(playerid, params[0]);

	new DT_string[sizeof(DT_CMD_TEXT_SETWANTED) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETWANTED, params[0]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtplaycrime(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	if(sscanf(params, "dd", params[0], params[1])) {
		return DT_SendHint(playerid, "/playcrime [suspect id] [crime]");
	}

	PlayCrimeReportForPlayer(playerid, params[0], params[1]);

	new DT_string[sizeof(DT_CMD_TEXT_PLAYCRIME) + 10 + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_PLAYCRIME, params[0], params[1]);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtcursor(playerid) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	SelectTextDraw(playerid, 0xfbbaa8AA);
	return 1;
}