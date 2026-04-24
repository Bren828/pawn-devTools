
CMD:dtveh(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 0;
	}

	new modelid,
		color1,
		color2,
		paintjob,
		Float:x,
		Float:y,
		Float:z,
		Float:ang;

	if(sscanf(params, "dI(-1)I(-1)I(-1)", modelid, color1, color2, paintjob)) {
		return DT_SendHint(playerid, "/veh [model] [color 1] [color 2] [paintjob]");
	}

	if(modelid < DT_MIN_VEHICLE_MODEL || modelid > DT_MAX_VEHICLE_MODEL) {
		return DT_SendError(playerid, DT_TEXT_INVALID_MODEL);
	}

	if(color1 < -1 || color1 > 255 || color2 < -1 || color2 > 255) {
		return DT_SendError(playerid, DT_TEXT_INVALID_COLOR);
	}

	if(paintjob < -1 || paintjob > 3) {
		return DT_SendError(playerid, DT_TEXT_INVALID_PAINTJOB);
	}

	if(color1 == -1) {
		color1 = random(255);
	}
	
	if(color2 == -1) {
		color2 = random(255);
	}

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

	new vehicleid = AddStaticVehicle(modelid, x, y, z, ang, color1, color2);
	if(vehicleid == INVALID_VEHICLE_ID) {
		return DT_SendError(playerid, DT_TEXT_FAILED_CREATE_VEHICLE);
	}

	DT_Vehicles[vehicleid] = vehicleid;

	SetVehicleParamsEx(vehicleid, true, false, false, false, false, false, false);
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));

	if(paintjob != -1) {
		ChangeVehiclePaintjob(vehicleid, paintjob);
	}
	PutPlayerInVehicle(playerid, vehicleid, 0);

	new DT_string[sizeof(DT_CMD_TEXT_VEH) + 5];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_VEH, modelid);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtdelveh(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new Float:radius,
		Float:x,
		Float:y,
		Float:z,
		count;

	if(sscanf(params, "f", radius)) {
		return DT_SendHint(playerid, "/delveh [radius (use -1 to remove all transport)]");
	}

	for(new i; i < MAX_VEHICLES; i++) {
		if(DT_Vehicles[i] == INVALID_VEHICLE_ID) 
			continue;

		if(radius != -1.0) {
			GetVehiclePos(DT_Vehicles[i], x, y, z);

			if(!IsPlayerInRangeOfPoint(playerid, radius, x, y, z)) {
				continue;
			}
		}

		DestroyVehicle(DT_Vehicles[i]);

		DT_Vehicles[i] = INVALID_VEHICLE_ID;
		count ++;
	}

	new DT_string[sizeof(DT_CMD_TEXT_DELVEH) + 4];
	
	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_DELVEH, count);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtgotoveh(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid;

	if(sscanf(params, "d", vehicleid)) {
		return DT_SendHint(playerid, "/gotoveh [vehicle id]");
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	if(GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	new Float:x,
		Float:y, 
		Float:z;

	GetVehiclePos(vehicleid, x, y, z);

	if(IsPlayerInAnyVehicle(playerid)) {
		SetVehiclePos(GetPlayerVehicleID(playerid), x + 3.0, y + 3.0, z);
	}
	else {
		SetPlayerPos(playerid, x + 2.0, y + 2.0, z);
	}

	SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(vehicleid));

	new DT_string[sizeof(DT_CMD_TEXT_GOTOVEH) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_GOTOVEH, vehicleid);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtgethereveh(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid;

	if(sscanf(params, "d", vehicleid)) {
		return DT_SendHint(playerid, "/gethereveh [vehicle id]");
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES) {
		return DT_SendError(playerid, DT_TEXT_INVALID);
	}

	if(GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	new Float:x,
		Float:y, 
		Float:z;

	GetPlayerPos(playerid, x, y, z);

	SetVehiclePos(vehicleid, x + 2.0, y + 2.0, z);
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));

	new DT_string[sizeof(DT_CMD_TEXT_GETHEREVEH) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_GETHEREVEH, vehicleid);
	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtrepairveh(playerid, params[]) {

	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid;

	if(sscanf(params, "d", vehicleid)) { 

		new DT_string[144];
		new myVehicleId = GetPlayerVehicleID(playerid);

		if(myVehicleId) {
			format(DT_string, sizeof(DT_string), " "DT_MAIN_COLOR_TAG"(%s id: %d)"DT_WHITE_COLOR_TAG"", DT_TEXT_YOUR, myVehicleId);
		}

		format(DT_string, sizeof(DT_string), "/repairveh [vehicle id%s]", DT_string);
		DT_SendHint(playerid, DT_string);
		return 1;
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES || GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	RepairVehicle(vehicleid);
	
 	DT_SendSucc(playerid, DT_CMD_TEXT_REPAIRVEH);
	return 1;
}



CMD:dtsetvehhp(playerid, params[]) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid,
		Float:health;

	if(sscanf(params, "df", vehicleid, health)) { 

		new DT_string[144];
		new myVehicleId = GetPlayerVehicleID(playerid);

		if(myVehicleId) {
			format(DT_string, sizeof(DT_string), " "DT_MAIN_COLOR_TAG"(%s id: %d)"DT_WHITE_COLOR_TAG"", DT_TEXT_YOUR, myVehicleId);
		}

		format(DT_string, sizeof(DT_string), "/setvehhp [vehicle id%s] [health]", DT_string);
		DT_SendHint(playerid, DT_string);
		return 1;
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES || GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	SetVehicleHealth(vehicleid, health);
	
	new DT_string[sizeof(DT_CMD_TEXT_SETVEHHP) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETVEHHP, health);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtsetvehcolor(playerid, params[]) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid,
		color1, color2, paintjob;

	if(sscanf(params, "ddI(-1)I(-1)", vehicleid, color1, color2, paintjob)) { 

		new DT_string[144];
		new myVehicleId = GetPlayerVehicleID(playerid);

		if(myVehicleId) {
			format(DT_string, sizeof(DT_string), " "DT_MAIN_COLOR_TAG"(%s id: %d)"DT_WHITE_COLOR_TAG"", DT_TEXT_YOUR, myVehicleId);
		}

		format(DT_string, sizeof(DT_string), "/setvehcolor [vehicle id%s] [color 1] [color 2] [paintjob]", DT_string);
		DT_SendHint(playerid, DT_string);
		return 1;
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES || GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	if(color1 < -1 || color1 > 255 || color2 < -1 || color2 > 255) {
		return DT_SendError(playerid, DT_TEXT_INVALID_COLOR);
	}

	if(paintjob < -1 || paintjob > 3) {
		return DT_SendError(playerid, DT_TEXT_INVALID_PAINTJOB);
	}

	if(color1 == -1) {
		color1 = random(255);
	}
	
	if(color2 == -1) {
		color2 = random(255);
	}

	ChangeVehicleColor(vehicleid, color1, color2);

	if(paintjob != -1) {
		ChangeVehiclePaintjob(vehicleid, paintjob);
	}
	
	new DT_string[sizeof(DT_CMD_TEXT_SETVEHCOLOR) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETVEHCOLOR, color1, color2, paintjob);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtsetcomp(playerid, params[]) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid,
		componentid;

	if(sscanf(params, "dd", vehicleid, componentid)) { 

		new DT_string[144];
		new myVehicleId = GetPlayerVehicleID(playerid);

		if(myVehicleId) {
			format(DT_string, sizeof(DT_string), " "DT_MAIN_COLOR_TAG"(%s id: %d)"DT_WHITE_COLOR_TAG"", DT_TEXT_YOUR, myVehicleId);
		}

		format(DT_string, sizeof(DT_string), "/setcomp [vehicle id%s] [component id]", DT_string);
		DT_SendHint(playerid, DT_string);
		return 1;
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES || GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	AddVehicleComponent(vehicleid, componentid);
	
	new DT_string[sizeof(DT_CMD_TEXT_SETCOMP) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_SETCOMP, componentid);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtremcomp(playerid, params[]) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid,
		componentid;

	if(sscanf(params, "dd", vehicleid, componentid)) { 

		new DT_string[144];
		new myVehicleId = GetPlayerVehicleID(playerid);

		if(myVehicleId) {
			format(DT_string, sizeof(DT_string), " "DT_MAIN_COLOR_TAG"(%s id: %d)"DT_WHITE_COLOR_TAG"", DT_TEXT_YOUR, myVehicleId);
		}

		format(DT_string, sizeof(DT_string), "/remcomp [vehicle id%s] [component id]", DT_string);
		DT_SendHint(playerid, DT_string);
		return 1;
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES || GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	RemoveVehicleComponent(vehicleid, componentid);
	
	new DT_string[sizeof(DT_CMD_TEXT_REMCOMP) + 10];

	format(DT_string, sizeof(DT_string), DT_CMD_TEXT_REMCOMP, componentid);
 	DT_SendSucc(playerid, DT_string);
	return 1;
}



CMD:dtvehen(playerid, params[]) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid;

	if(sscanf(params, "d", vehicleid)) { 

		new DT_string[144],
			myVehicleId = GetPlayerVehicleID(playerid);

		if(myVehicleId) {
			format(DT_string, sizeof(DT_string), " "DT_MAIN_COLOR_TAG"(%s id: %d)"DT_WHITE_COLOR_TAG"", DT_TEXT_YOUR, myVehicleId);
		}

		format(DT_string, sizeof(DT_string), "/vehen [vehicle id%s]", DT_string);
		DT_SendHint(playerid, DT_string);
		return 1;
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES || GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	if(DT_ToggleEngine(vehicleid)) {
 		DT_SendSucc(playerid, DT_CMD_TEXT_VEHEN_ON);
	}
	else {
 		DT_SendSucc(playerid, DT_CMD_TEXT_VEHEN2_OFF);
	}
	return 1;
}



CMD:dtvehli(playerid, params[]) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid;

	if(sscanf(params, "d", vehicleid)) { 

		new DT_string[144],
			myVehicleId = GetPlayerVehicleID(playerid);

		if(myVehicleId) {
			format(DT_string, sizeof(DT_string), " "DT_MAIN_COLOR_TAG"(%s id: %d)"DT_WHITE_COLOR_TAG"", DT_TEXT_YOUR, myVehicleId);
		}

		format(DT_string, sizeof(DT_string), "/vehli [vehicle id%s]", DT_string);
		DT_SendHint(playerid, DT_string);
		return 1;
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES || GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	if(DT_ToggleLight(vehicleid)) {
 		DT_SendSucc(playerid, DT_CMD_TEXT_VEHLI_ON);
	}
	else {
 		DT_SendSucc(playerid, DT_CMD_TEXT_VEHLI_OFF);
	}
	return 1;
}



CMD:dtvehdo(playerid, params[]) {
	if(!GetAccessDevTools(playerid)) {
		return 1;
	}

	new vehicleid;

	if(sscanf(params, "d", vehicleid)) { 

		new DT_string[144],
			myVehicleId = GetPlayerVehicleID(playerid);

		if(myVehicleId) {
			format(DT_string, sizeof(DT_string), " "DT_MAIN_COLOR_TAG"(%s id: %d)"DT_WHITE_COLOR_TAG"", DT_TEXT_YOUR, myVehicleId);
		}

		format(DT_string, sizeof(DT_string), "/vehdo [vehicle id%s]", DT_string);
		DT_SendHint(playerid, DT_string);
		return 1;
	}

	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES || GetVehicleModel(vehicleid) <= 0) {
		return DT_SendError(playerid, DT_TEXT_NOT_FOUND);
	}

	if(DT_ToggleDoor(vehicleid)) {
 		DT_SendSucc(playerid, DT_CMD_TEXT_VEHDO_CLOSED);
	}
	else {
 		DT_SendSucc(playerid, DT_CMD_TEXT_VEHDO_OPENED);
	}
	return 1;
}


