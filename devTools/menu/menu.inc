

CMD:dt(playerid) {
	if(!GetAccessDevTools(playerid)) {
		return 0;
	}

	DT_Menu(playerid);
   	return 1;
}

CMD:dtpublic(playerid) {
	if(!GetAccessDevTools(playerid)) {
		return 0;
	}

	DT_PlayerData[playerid][dtp_BackButton] = false;
	DT_Public(playerid);
   	return 1;
}

#if defined PAWNRAKNET_INC_
	#include "raknet.inc"
#endif

stock DT_Menu(playerid) {
	
	new DT_string[sizeof(DT_DIALOG_MENU) + (13 * 12) + 32];

    format(DT_string, sizeof(DT_string), DT_DIALOG_MENU,
		DT_PlayerData[playerid][dtp_EnableDistancePoint] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_EnableTeleportByMark] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_PublicAnimation] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_IgnorePunishments] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_EnableGodMode] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),

		DT_PlayerData[playerid][dtp_EnableCameraTarget] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_EnableDoubleJump] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_EnableExplosiveShooting] == false ? (DT_TEXT_OFF):(DT_TEXT_ON), 

		DT_PlayerData[playerid][dtp_PlayerIDStats] == INVALID_PLAYER_ID ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_VehicleIDStats] == INVALID_VEHICLE_ID ? (DT_TEXT_OFF):(DT_TEXT_ON),

		DT_PlayerData[playerid][dtp_RaknetPlayerIDStats] == INVALID_PLAYER_ID ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_RaknetVehicleIDStats] == INVALID_PLAYER_ID ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_RaknetPassengerIDStats] == INVALID_PLAYER_ID ? (DT_TEXT_OFF):(DT_TEXT_ON)
	);

	#if !defined DT_DISABLE_COMMANDS
		strcat(DT_string, "\n");
		strcat(DT_string, DT_LIST_COMMANDST);
	#endif

	ShowPlayerDialog(playerid, DT_DIALOGID_MENU, DIALOG_STYLE_TABLIST, ""DT_NAME" by "DT_MAIN_COLOR_TAG""DT_AUTHOR" "DT_VERSION"", DT_string, 
		DT_SELECT_BUTTON, 
		DT_CLOSE_BUTTON);

	return 1;
}


stock DT_Public(playerid, bool:back = true) {

	new DT_string[sizeof(DT_DIALOG_PUBLICS) + (9 * 12)];

    format(DT_string, sizeof(DT_string), DT_DIALOG_PUBLICS,
		DT_PlayerData[playerid][dtp_PublicKey] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_PublicTakeDamage] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_PublicGiveDamage] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_PublicWeaponShot] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_PublicDeath] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_PublicSpawn] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_PublicStateChange] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_PublicEnterVehicle] == false ? (DT_TEXT_OFF):(DT_TEXT_ON),
		DT_PlayerData[playerid][dtp_PublicExitVehicle] == false ? (DT_TEXT_OFF):(DT_TEXT_ON)
	);

	ShowPlayerDialog(playerid, DT_DIALOGID_PUBLIC, DIALOG_STYLE_TABLIST, ""DT_NAME" by "DT_MAIN_COLOR_TAG""DT_AUTHOR" "DT_VERSION"", DT_string, 
		DT_SELECT_BUTTON, 
		(!back) ? DT_CLOSE_BUTTON : DT_BACK_BUTTON);

	return 1;
}



forward DT_PlayerStatTimer(playerid);
public DT_PlayerStatTimer(playerid) {

	new targetid = DT_PlayerData[playerid][dtp_PlayerIDStats];

	if(targetid == INVALID_PLAYER_ID) {
		return 0;
	}

	if(!IsPlayerConnected(targetid)) {
		PlayerTextDrawSetString(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], "~r~~h~Player disconnected");
		return 0;
	}

	static const DT_text[] = 
		"~y~Player Data: %s(%d)~w~~n~\
		Health: %.2f, Armour: %.2f~n~\
		World: %d, INT: %d~n~\
		Ping: %d, FPS: %d~n~\
		Version: %s~n~\
		Score: %d~n~\
		Drunk Level: %d~n~\
		Color: %d~n~\
		Skin: %d~n~\
		State: %d~n~\
		Time: %d:%d~n~\
		Wanted Level: %d~n~\
		Fighting Style: %d~n~\
		Special Action: %d~n~\
		Keys: %d, Updown: %d, Leftright: %d~n~\
		VehicleID: %d, Seat: %d~n~\
		Surfing VehicleID: %d~n~\
		Surfing ObjectID: %d~n~\
		Animation Index: %d~n~\
		Weapon: %d~n~\
		Ammo: %d~n~\
		Weapon State: %d~n~\
		~n~\
		Camera:~n~\
		Mode: %d~n~\
		Zoom: %.1f~n~\
		Target Player %d~n~\
		Camera Pos: %.2f, %.2f, %.2f~n~\
		Front Vector: %.2f, %.2f, %.2f~n~\
		~n~\
		Camera Target:~n~\
		Object: %d~n~\
		ObjectDyn: %d~n~\
		Vehicle: %d~n~\
		Player: %d~n~\
		Actor: %d~n~\
		Aspect Ratio: %f~n~\
		~n~\
		Position:~n~\
		%.2f %.2f %.2f %.2f~n~\
		~n~\
		Velocity:~n~\
		%.2f %.2f %.2f";
	
	new DT_string[sizeof(DT_text) + 200], 
		Float:x,
		Float:y,
		Float:z,
		Float:ang,
		Float:health,
		Float:armour,
		dt_keys, 
		updown, 
		leftright,
		version[24], 
		name[MAX_PLAYER_NAME],
		dt_hour, 
		dt_minute,
		Float:cam_x, Float:cam_y, Float:cam_z,
		Float:camV_x, Float:camV_y, Float:camV_z,
		Float:VX, Float:VY, Float:VZ;


	GetPlayerHealth(targetid, health);
	GetPlayerArmour(targetid, armour);

	GetPlayerVersion(targetid, version, sizeof(version));
	GetPlayerTime(targetid, dt_hour, dt_minute);

	GetPlayerCameraPos(targetid, cam_x, cam_y, cam_z);
	GetPlayerCameraFrontVector(targetid, camV_x, camV_y, camV_z);

	GetPlayerName(targetid, name, MAX_PLAYER_NAME);
	GetPlayerKeys(targetid, dt_keys, updown, leftright);

	GetPlayerPos(targetid, x, y, z);
	GetPlayerFacingAngle(targetid, ang);

	GetPlayerVelocity(playerid, VX, VY, VZ);
	//GetPlayerLastShotVectors(playerid, &Float:fOriginX, &Float:fOriginY, &Float:fOriginZ, &Float:fHitPosX, &Float:fHitPosY, &Float:fHitPosZ)
	
	format(DT_string, sizeof(DT_string), DT_text,
		name, targetid,
		health, armour,
		GetPlayerVirtualWorld(targetid), GetPlayerInterior(targetid),
		GetPlayerPing(targetid), DT_GetPlayerFps(targetid),
		version,
		GetPlayerScore(targetid),
		GetPlayerDrunkLevel(targetid),
		GetPlayerColor(targetid),
		GetPlayerSkin(targetid),
		GetPlayerState(targetid),
		dt_hour, dt_minute,
		GetPlayerWantedLevel(targetid),
		GetPlayerFightingStyle(targetid),
		GetPlayerSpecialAction(targetid),
		dt_keys, updown, leftright,
		GetPlayerVehicleID(targetid),
		GetPlayerVehicleSeat(targetid),
		GetPlayerSurfingVehicleID(targetid),
		GetPlayerSurfingObjectID(targetid),
		GetPlayerAnimationIndex(targetid),

		GetPlayerWeapon(targetid),
		GetPlayerAmmo(targetid),
		GetPlayerWeaponState(targetid),
		
		GetPlayerCameraMode(targetid),
		GetPlayerCameraZoom(targetid),
		GetPlayerTargetPlayer(playerid),
		cam_x, cam_y, cam_z,
		camV_x, camV_y, camV_z,
		GetPlayerCameraTargetObject(targetid),
		GetPlayerCameraTargetDynObject(targetid),
		GetPlayerCameraTargetVehicle(targetid),
		GetPlayerCameraTargetPlayer(targetid),
		GetPlayerCameraTargetActor(targetid),
		GetPlayerCameraAspectRatio(targetid),

		x, y, z, ang,
		VX, VY, VZ);

	PlayerTextDrawSetString(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], DT_string);
	return 1;
}


forward DT_VehicleStatTimer(playerid);
public DT_VehicleStatTimer(playerid) {

	new vehicleid = DT_PlayerData[playerid][dtp_VehicleIDStats];

	if(!GetVehicleModel(vehicleid)) {
		PlayerTextDrawSetString(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], "~r~~h~Vehicle destroyed");
		return 0;
	}

	static const d_stats[] = 
		"~y~Vehicle Data: %d~w~~n~\
		Model: %d~n~\
		Speed: %d~n~\
		Health: %.2f~n~\
		World: %d~n~~n~\
		Engine: %d, Lights: %d~n~\
		Alarm: %d, Doors: %d~n~\
		Bonnet: %d, Boot: %d~n~\
		Objective: %d~n~\
		~n~\
		Position:~n~\
		%.2f, %.2f, %.2f, %.2f~n~\
		~n~\
		Velocity:~n~\
		%.2f, %.2f, %.2f";

	new DT_string[sizeof(d_stats) + (4 * 10)], 
		Float:x, Float:y, Float:z,
		Float:z_angle,
		Float:VX, Float:VY, Float:VZ,
		Float:health,
		DT_engine, DT_lights, DT_alarm, DT_doors, DT_bonnet, DT_boot, DT_objective;


	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, z_angle);
	GetVehicleHealth(vehicleid, health);
	GetVehicleParamsEx(vehicleid, DT_engine, DT_lights, DT_alarm, DT_doors, DT_bonnet, DT_boot, DT_objective);
	GetVehicleVelocity(vehicleid, VX, VY, VZ);
	

	format(DT_string, sizeof(DT_string), d_stats, 
		vehicleid,
		GetVehicleModel(vehicleid), 
		DT_GetVehicleSpeed(vehicleid), 
		health, 
		GetVehicleVirtualWorld(vehicleid), 
		DT_engine, DT_lights, 
		DT_alarm, DT_doors, 
		DT_bonnet, DT_boot, 
		DT_objective,
		x, y, z, z_angle,
		VX, VY, VZ);

	PlayerTextDrawSetString(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], DT_string);
	return 1;
}
