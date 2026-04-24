

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {

	switch(dialogid) {

		case DT_DIALOGID_MENU: {
			if(!response || !GetAccessDevTools(playerid)) { 
				return 1;
			}

			switch(listitem) {

				case 0: {// Point Distance
				
					if(!DT_PlayerData[playerid][dtp_EnableDistancePoint]) {
						DT_PlayerData[playerid][dtp_EnableDistancePoint] = true;

						GetPlayerPos(playerid, 
							DT_PlayerData[playerid][dtp_PointDistancePosX], 
							DT_PlayerData[playerid][dtp_PointDistancePosY], 
							DT_PlayerData[playerid][dtp_PointDistancePosZ]);

						DT_PlayerData[playerid][dtp_PointText3D] = CreateDynamic3DTextLabel("Point", DT_COLOR_MAIN, 
							DT_PlayerData[playerid][dtp_PointDistancePosX], 
							DT_PlayerData[playerid][dtp_PointDistancePosY], 
							DT_PlayerData[playerid][dtp_PointDistancePosZ], 
							6000.0, 
							INVALID_PLAYER_ID, 
							INVALID_VEHICLE_ID, 
							0, -1, -1, 
							playerid, 6000.0);	
					}
					else {
						DT_PlayerData[playerid][dtp_EnableDistancePoint] = false;

						DestroyDynamic3DTextLabel(DT_PlayerData[playerid][dtp_PointText3D]);
						DT_PlayerData[playerid][dtp_PointText3D] = Text3D:INVALID_3DTEXT_ID;
					}
				}

				case 1: { //Teleport by mark
					DT_PlayerData[playerid][dtp_EnableTeleportByMark] = !DT_PlayerData[playerid][dtp_EnableTeleportByMark];
				}

				case 2: { // Animation Index
					DT_PlayerData[playerid][dtp_PublicAnimation] = !DT_PlayerData[playerid][dtp_PublicAnimation];
				}

				case 3: { //Ignore Punishments

					#if !defined DT_ENABLE_IGNORE_PUNISHMENTS
						DT_SendError(playerid, DT_TEXT_IGNORING_PUNISHMENT);
					#endif

					DT_PlayerData[playerid][dtp_IgnorePunishments] = !DT_PlayerData[playerid][dtp_IgnorePunishments];
				}

				case 4: { //God Mode
					DT_PlayerData[playerid][dtp_EnableGodMode] = !DT_PlayerData[playerid][dtp_EnableGodMode];

					if(DT_PlayerData[playerid][dtp_EnableGodMode]) {
						SetPlayerHealth(playerid, 0x7F800000);
					}
					else {
						SetPlayerHealth(playerid, 100.0);
					}
				}

				case 5: { // Camera Target
					DT_PlayerData[playerid][dtp_EnableCameraTarget] = !DT_PlayerData[playerid][dtp_EnableCameraTarget];
					EnablePlayerCameraTarget(playerid, DT_PlayerData[playerid][dtp_EnableCameraTarget]);
				}

				case 6: { // Double Jump
					DT_PlayerData[playerid][dtp_EnableDoubleJump] = !DT_PlayerData[playerid][dtp_EnableDoubleJump];
					DT_PlayerData[playerid][dtp_DoubleJumpDelay] = GetTickCount()+300;
				}

				case 7: { //MegaBullet
					DT_PlayerData[playerid][dtp_EnableExplosiveShooting] = !DT_PlayerData[playerid][dtp_EnableExplosiveShooting];
				}

				case 8: { // public
					DT_PlayerData[playerid][dtp_BackButton] = true;
					DT_Public(playerid);
					return 1;
				}

				case 9: { // Player Stats

					if(DT_PlayerData[playerid][dtp_PlayerIDStats] != INVALID_PLAYER_ID) {
						DT_PlayerData[playerid][dtp_PlayerIDStats] = INVALID_PLAYER_ID;

						KillTimer(DT_PlayerData[playerid][dtp_PlayerStatsTimer]);
						DT_PlayerData[playerid][dtp_PlayerStatsTimer] = 0;

						PlayerTextDrawDestroy(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD]);
						DT_PlayerData[playerid][dtp_PlayerStatsTD] = PlayerText:INVALID_TEXT_DRAW;
					}

					ShowPlayerDialog(playerid, DT_DIALOGID_PLAYER_STATS, DIALOG_STYLE_INPUT, DT_DIALOG_PLAYER_STATS_HEADER, 
						DT_DIALOG_PLAYER_STATS, 
						DT_SELECT_BUTTON, 
						DT_BACK_BUTTON);
					return 1;
				}

				case 10: { // Vehicle Stats

					if(DT_PlayerData[playerid][dtp_VehicleIDStats] != INVALID_VEHICLE_ID) {
						DT_PlayerData[playerid][dtp_VehicleIDStats] = INVALID_VEHICLE_ID;
						
						KillTimer(DT_PlayerData[playerid][dtp_VehicleStatsTimer]);
						DT_PlayerData[playerid][dtp_VehicleStatsTimer] = 0;

						PlayerTextDrawDestroy(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD]);
						DT_PlayerData[playerid][dtp_VehicleStatsTD] = PlayerText:INVALID_TEXT_DRAW;
					}

					ShowPlayerDialog(playerid, DT_DIALOGID_VEHICLE_STATS, DIALOG_STYLE_INPUT, DT_DIALOG_VEHICLE_STATS_HEADER, 
						DT_DIALOG_VEHICLE_STATS, 
						DT_SELECT_BUTTON, 
						DT_BACK_BUTTON);
					return 1;
				}

				case 11: { // Raknet Player Stats
				
					#if defined PAWNRAKNET_INC_
						new targetid = DT_PlayerData[playerid][dtp_RaknetPlayerIDStats];

						if(targetid != INVALID_PLAYER_ID) {
							DT_PlayerData[playerid][dtp_RaknetPlayerIDStats] = INVALID_PLAYER_ID;
							DT_PlayerData[targetid][dtp_RaknetPlayerIDStats] = INVALID_PLAYER_ID;
							
							PlayerTextDrawDestroy(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD]);
							DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD] = PlayerText:INVALID_TEXT_DRAW;
						}

						ShowPlayerDialog(playerid, DT_DIALOGID_RAKNET_PLAYER, DIALOG_STYLE_INPUT, DT_DIALOG_PLAYER_STATS_HEADER, 
							DT_DIALOG_PLAYER_STATS, 
							DT_SELECT_BUTTON, 
							DT_BACK_BUTTON);
					#else 
						DT_Menu(playerid);
						DT_SendError(playerid, DT_TEXT_NO_RAKNET_PLUGIN);
					#endif
					return 1;
				}

				case 12: { // Raknet Vehicle Stats
				
					#if defined PAWNRAKNET_INC_
						new targetid = DT_PlayerData[playerid][dtp_RaknetVehicleIDStats];

						if(targetid != INVALID_PLAYER_ID) {
							DT_PlayerData[targetid][dtp_RaknetVehicleIDStats] = INVALID_PLAYER_ID;
							DT_PlayerData[playerid][dtp_RaknetVehicleIDStats] = INVALID_PLAYER_ID;

							PlayerTextDrawDestroy(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD]);
							DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD] = PlayerText:INVALID_TEXT_DRAW;
						}

						ShowPlayerDialog(playerid, DT_DIALOGID_RAKNET_VEHICLE, DIALOG_STYLE_INPUT, DT_DIALOG_VEHICLE_STATS_HEADER, 
							DT_DIALOG_PLAYER_STATS, 
							DT_SELECT_BUTTON, 
							DT_BACK_BUTTON);
					#else 
						DT_Menu(playerid);
						DT_SendError(playerid, DT_TEXT_NO_RAKNET_PLUGIN);
					#endif
					return 1;
				}

				case 13: { // Raknet Passenger Stats
					#if defined PAWNRAKNET_INC_
						new targetid = DT_PlayerData[playerid][dtp_RaknetPassengerIDStats];

						if(targetid != INVALID_PLAYER_ID) {
							DT_PlayerData[targetid][dtp_RaknetPassengerIDStats] = INVALID_PLAYER_ID;
							DT_PlayerData[playerid][dtp_RaknetPassengerIDStats] = INVALID_PLAYER_ID;

							PlayerTextDrawDestroy(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD]);
							DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD] = PlayerText:INVALID_TEXT_DRAW;
						}

						ShowPlayerDialog(playerid, DT_DIALOGID_RAKNET_PASSENGER, DIALOG_STYLE_INPUT, DT_DIALOG_VEHICLE_STATS_HEADER, 
							DT_DIALOG_PLAYER_STATS, 
							DT_SELECT_BUTTON, 
							DT_BACK_BUTTON);
					#else 
						DT_Menu(playerid);
						DT_SendError(playerid, DT_TEXT_NO_RAKNET_PLUGIN);
					#endif
					return 1;
				}

				case 14: {
					#if !defined DT_DISABLE_COMMANDS
						DT_PlayerData[playerid][dtp_BackButton] = true;
						DT_Command(playerid);
					#endif
					return 1;
				}
			}

			DT_Menu(playerid);
			return 1;
		}

		case DT_DIALOGID_PUBLIC: {

			if(!GetAccessDevTools(playerid)) {
				return 1;
			}

			if(!response) {
				if(!DT_PlayerData[playerid][dtp_BackButton]) {
					return 1;
				}

				DT_Menu(playerid);
				return 1;
			}

			switch(listitem) {

				case 0: { //Log KeyStateChange
					DT_PlayerData[playerid][dtp_PublicKey] = !DT_PlayerData[playerid][dtp_PublicKey];
				}
				case 1: {//Log TakeDamage
					DT_PlayerData[playerid][dtp_PublicTakeDamage] = !DT_PlayerData[playerid][dtp_PublicTakeDamage];
				}
				case 2: {//Log GiveDamage
					DT_PlayerData[playerid][dtp_PublicGiveDamage] = !DT_PlayerData[playerid][dtp_PublicGiveDamage];
				}
				case 3: {//Log WeaponShot
					DT_PlayerData[playerid][dtp_PublicWeaponShot] = !DT_PlayerData[playerid][dtp_PublicWeaponShot];
				}
				case 4: { //Log Death
					DT_PlayerData[playerid][dtp_PublicDeath] = !DT_PlayerData[playerid][dtp_PublicDeath];
				}
				case 5: {//Log Spawn
					DT_PlayerData[playerid][dtp_PublicSpawn] = !DT_PlayerData[playerid][dtp_PublicSpawn];
				}
				case 6: { //Log State Change
					DT_PlayerData[playerid][dtp_PublicStateChange] = !DT_PlayerData[playerid][dtp_PublicStateChange];
				}
				case 7: {//Log EnterVehicle
					DT_PlayerData[playerid][dtp_PublicEnterVehicle] = !DT_PlayerData[playerid][dtp_PublicEnterVehicle];
				}
				case 8: { //Log ExitVehicle
					DT_PlayerData[playerid][dtp_PublicExitVehicle] = !DT_PlayerData[playerid][dtp_PublicExitVehicle];
				}
			}
			
			DT_Public(playerid);
			return 1;
		}

		case DT_DIALOGID_PLAYER_STATS: {

			if(!GetAccessDevTools(playerid)) {
				return 1;
			}

			if(!response) {
				DT_Menu(playerid);
				return 1;
			}	

			new targetid = strval(inputtext);

			if(!strlen(inputtext) || !IsPlayerConnected(targetid)) {

				ShowPlayerDialog(playerid, DT_DIALOGID_PLAYER_STATS, DIALOG_STYLE_INPUT, DT_DIALOG_PLAYER_STATS_HEADER, 
					DT_DIALOG_PLAYER_STATS, 
					DT_SELECT_BUTTON, 
					DT_BACK_BUTTON);

				if(strlen(inputtext)) {
					DT_SendError(playerid, DT_TEXT_INVALID);
				}
				return 1;
			}

			DT_PlayerData[playerid][dtp_PlayerIDStats] = targetid;
			DT_PlayerData[playerid][dtp_PlayerStatsTimer] = SetTimerEx("DT_PlayerStatTimer", 100, true, "d", playerid);

			DT_PlayerData[playerid][dtp_PlayerStatsTD] = CreatePlayerTextDraw(playerid, 3.0, 55.0, "No data");
			PlayerTextDrawBackgroundColor(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], 0x000000FF);
			PlayerTextDrawFont(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], 1);
			PlayerTextDrawLetterSize(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], 0.20, 1.00);
			PlayerTextDrawColor(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], 0xFFFFFFFF);
			PlayerTextDrawSetProportional(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], true);
			PlayerTextDrawSetShadow(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], 1);
			PlayerTextDrawUseBox(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], true);
			PlayerTextDrawBoxColor(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], 0x00000077);
			PlayerTextDrawTextSize(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD], 125.00, 109.00);
			PlayerTextDrawShow(playerid, DT_PlayerData[playerid][dtp_PlayerStatsTD]);
			return 1;
		}

		case DT_DIALOGID_VEHICLE_STATS: {

			if(!GetAccessDevTools(playerid)) {
				return 1;
			}

			if(!response) {
				DT_Menu(playerid);
				return 1;
			}

			new vehicleid = strval(inputtext);

			if(vehicleid <= 0 || vehicleid >= MAX_VEHICLES || !strlen(inputtext)) {

				ShowPlayerDialog(playerid, DT_DIALOGID_VEHICLE_STATS, DIALOG_STYLE_INPUT, DT_DIALOG_VEHICLE_STATS_HEADER, 
					DT_DIALOG_VEHICLE_STATS, 
					DT_SELECT_BUTTON, 
					DT_BACK_BUTTON);
				return 1;
			}

			if(!GetVehicleModel(vehicleid)) {

				ShowPlayerDialog(playerid, DT_DIALOGID_VEHICLE_STATS, DIALOG_STYLE_INPUT, DT_DIALOG_VEHICLE_STATS_HEADER, 
					DT_DIALOG_VEHICLE_STATS, 
					DT_SELECT_BUTTON, 
					DT_BACK_BUTTON);
				
				DT_SendError(playerid, DT_TEXT_INVALID);
				return 1;
			}

			DT_PlayerData[playerid][dtp_VehicleIDStats] = vehicleid;
			DT_PlayerData[playerid][dtp_VehicleStatsTimer] = SetTimerEx("DT_VehicleStatTimer", 100, true, "d", playerid);

			DT_PlayerData[playerid][dtp_VehicleStatsTD] = CreatePlayerTextDraw(playerid, 385.0, 5.0, "No data");
			PlayerTextDrawBackgroundColor(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], 0x000000FF);
			PlayerTextDrawFont(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], 1);
			PlayerTextDrawLetterSize(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], 0.20, 1.00);
			PlayerTextDrawColor(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], 0xFFFFFFFF);
			PlayerTextDrawSetProportional(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], true);
			PlayerTextDrawSetShadow(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], 1);
			PlayerTextDrawUseBox(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], true);
			PlayerTextDrawBoxColor(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], 0x00000077);
			PlayerTextDrawTextSize(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD], 507.00, 109.00);
			PlayerTextDrawShow(playerid, DT_PlayerData[playerid][dtp_VehicleStatsTD]);
			return 1;
		}

		#if defined PAWNRAKNET_INC_
		case DT_DIALOGID_RAKNET_PLAYER: {

			if(!GetAccessDevTools(playerid)) {
				return 1;
			}

			if(!response) {
				DT_Menu(playerid);
				return 1;
			}

			new targetid = strval(inputtext);

			if(!strlen(inputtext) || !IsPlayerConnected(targetid)) {
				ShowPlayerDialog(playerid, DT_DIALOGID_RAKNET_PLAYER, DIALOG_STYLE_INPUT, DT_DIALOG_PLAYER_STATS_HEADER, 
					DT_DIALOG_PLAYER_STATS, 
					DT_SELECT_BUTTON, 
					DT_BACK_BUTTON);

				if(strlen(inputtext)) {
					DT_SendError(playerid, DT_TEXT_INVALID);
				}
				return 1;
			}
			
			DT_PlayerData[playerid][dtp_RaknetPlayerIDStats] = targetid;
			DT_PlayerData[targetid][dtp_RaknetPlayerIDStats] = playerid;

			DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD] = CreatePlayerTextDraw(playerid, 515.0, 290.0, "No data");
			PlayerTextDrawBackgroundColor(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD], 0x000000FF);
			PlayerTextDrawFont(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD], 1);
			PlayerTextDrawLetterSize(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD], 0.20, 1.00);
			PlayerTextDrawColor(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD], 0xFFFFFFFF);
			PlayerTextDrawSetProportional(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD], true);
			PlayerTextDrawSetShadow(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD], 1);
			PlayerTextDrawUseBox(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD], true);
			PlayerTextDrawBoxColor(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD], 0x00000077);
			PlayerTextDrawTextSize(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD], 637.00, 109.00);
			PlayerTextDrawShow(playerid, DT_PlayerData[playerid][dtp_RaknetPlayerStatsTD]);
			return 1;
		}

		case DT_DIALOGID_RAKNET_VEHICLE: {
			if(!GetAccessDevTools(playerid)) {
				return 1;
			}

			if(!response) {
				DT_Menu(playerid);
				return 1;
			}

			new targetid = strval(inputtext);

			if(!strlen(inputtext) || !IsPlayerConnected(targetid)) {
				ShowPlayerDialog(playerid, DT_DIALOGID_RAKNET_VEHICLE, DIALOG_STYLE_INPUT, DT_DIALOG_VEHICLE_STATS_HEADER, 
					DT_DIALOG_PLAYER_STATS, 
					DT_SELECT_BUTTON, 
					DT_BACK_BUTTON);

				if(strlen(inputtext)) {
					DT_SendError(playerid, DT_TEXT_INVALID);
				}
				return 1;
			}

			DT_PlayerData[playerid][dtp_RaknetVehicleIDStats] = targetid;
			DT_PlayerData[targetid][dtp_RaknetVehicleIDStats] = playerid;

			DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD] = CreatePlayerTextDraw(playerid, 515.0, 5.0, "No data");
			PlayerTextDrawBackgroundColor(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD], 0x000000FF);
			PlayerTextDrawFont(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD], 1);
			PlayerTextDrawLetterSize(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD], 0.20, 1.00);
			PlayerTextDrawColor(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD], 0xFFFFFFFF);
			PlayerTextDrawSetProportional(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD], true);
			PlayerTextDrawSetShadow(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD], 1);
			PlayerTextDrawUseBox(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD], true);
			PlayerTextDrawBoxColor(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD], 0x00000077);
			PlayerTextDrawTextSize(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD], 637.00, 109.00);
			PlayerTextDrawShow(playerid, DT_PlayerData[playerid][dtp_RaknetVehicleStatsTD]);
		
			return 1;
		}

		case DT_DIALOGID_RAKNET_PASSENGER:{

			if(!GetAccessDevTools(playerid)) {
				return 1;
			}

			if(!response) {
				DT_Menu(playerid);
				return 1;
			}

			new targetid = strval(inputtext);

			if(!strlen(inputtext) || !IsPlayerConnected(targetid)) {
				ShowPlayerDialog(playerid, DT_DIALOGID_RAKNET_PASSENGER, DIALOG_STYLE_INPUT, DT_DIALOG_VEHICLE_STATS_HEADER, 
					DT_DIALOG_PLAYER_STATS, 
					DT_SELECT_BUTTON, 
					DT_BACK_BUTTON);

				if(strlen(inputtext)) {
					DT_SendError(playerid, DT_TEXT_INVALID);
				}
				return 1;
			}

			DT_PlayerData[playerid][dtp_RaknetPassengerIDStats] = targetid;
			DT_PlayerData[targetid][dtp_RaknetPassengerIDStats] = playerid;
			
			DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD] = CreatePlayerTextDraw(playerid, 515.0, 170.0, "No data");
			PlayerTextDrawBackgroundColor(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD], 0x000000FF);
			PlayerTextDrawFont(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD], 1);
			PlayerTextDrawLetterSize(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD], 0.20, 1.00);
			PlayerTextDrawColor(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD], 0xFFFFFFFF);
			PlayerTextDrawSetProportional(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD], true);
			PlayerTextDrawSetShadow(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD], 1);
			PlayerTextDrawUseBox(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD], true);
			PlayerTextDrawBoxColor(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD], 0x00000077);
			PlayerTextDrawTextSize(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD], 637.00, 109.00);
			PlayerTextDrawShow(playerid, DT_PlayerData[playerid][dtp_RaknetPassengerStatsTD]);
			return 1;
		}
		#endif

		#if !defined DT_DISABLE_COMMANDS
		case DT_DIALOGID_CMD: {
			if(!GetAccessDevTools(playerid)) {
				return 1;
			}

			if(!response) {
				if(!DT_PlayerData[playerid][dtp_BackButton]) {
					return 1;
				}

				DT_Menu(playerid);
				return 1;
			}
			
			DT_PlayerData[playerid][dtp_CommandPage] = 1;
			DT_PlayerData[playerid][dtp_CommandType] = listitem;

			DT_ShowCommandsList(playerid);
			return 1;
		}

		case DT_DIALOGID_CMD_BACK:{

			if(!GetAccessDevTools(playerid)) {
				return 0;
			}

			if(!response) {
				if(DT_PlayerData[playerid][dtp_CommandPage] <= 1) {
					DT_Command(playerid);
					return 1;
				}
				else {
					DT_PlayerData[playerid][dtp_CommandPage]--;
				}
			}
			else {
				if(DT_PlayerData[playerid][dtp_CommandNextPage]) {
					DT_PlayerData[playerid][dtp_CommandPage]++;
				}
			}

			DT_ShowCommandsList(playerid);
			return 1;
		}

		case DT_DIALOGID_SET_OBJECT: {

			if(!GetAccessDevTools(playerid)) {
				return 1;
			}

			new index = DT_PlayerData[playerid][dtp_NewAttachedIndex];
			new modelid = DT_PlayerData[playerid][dtp_NewAttachedModel];
			new bone = DT_PlayerData[playerid][dtp_NewAttachedBone];
			new color = DT_PlayerData[playerid][dtp_NewAttachedColor];

			if(!response) {
				DT_PlayerData[playerid][dtp_AttachedOffsetX] = 0.0;
				DT_PlayerData[playerid][dtp_AttachedOffsetY] = 0.0;
				DT_PlayerData[playerid][dtp_AttachedOffsetZ] = 0.0;

				DT_PlayerData[playerid][dtp_AttachedRotX] = 0.0; 
				DT_PlayerData[playerid][dtp_AttachedRotY] = 0.0; 
				DT_PlayerData[playerid][dtp_AttachedRotZ] = 0.0; 

				DT_PlayerData[playerid][dtp_AttachedScaleX] = 1.0;
				DT_PlayerData[playerid][dtp_AttachedScaleY] = 1.0;
				DT_PlayerData[playerid][dtp_AttachedScaleZ] = 1.0;
			}
			else {
				DT_PlayerData[playerid][dtp_AttachedIndex] = index;
				DT_PlayerData[playerid][dtp_AttachedModel] = modelid;
				DT_PlayerData[playerid][dtp_AttachedBone] = bone;
				DT_PlayerData[playerid][dtp_AttachedColor] = color;
			}

			DT_PlayerData[playerid][dtp_AttachedObject] = true;

			SetPlayerAttachedObject(playerid, index, modelid, bone, 
				DT_PlayerData[playerid][dtp_AttachedOffsetX],
				DT_PlayerData[playerid][dtp_AttachedOffsetY],
				DT_PlayerData[playerid][dtp_AttachedOffsetZ],

				DT_PlayerData[playerid][dtp_AttachedRotX], 
				DT_PlayerData[playerid][dtp_AttachedRotY], 
				DT_PlayerData[playerid][dtp_AttachedRotZ], 

				DT_PlayerData[playerid][dtp_AttachedScaleX],
				DT_PlayerData[playerid][dtp_AttachedScaleY],
				DT_PlayerData[playerid][dtp_AttachedScaleZ],
				color);
			
			EditAttachedObject(playerid, index);
			return 1;
		}
		#endif
	}

	#if defined OnDialogResponse_DT
        return OnDialogResponse_DT(playerid, dialogid, response, listitem, inputtext);
    #else 
		return 1;
    #endif
}
#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif
#define OnDialogResponse OnDialogResponse_DT
#if defined OnDialogResponse_DT
    forward OnDialogResponse_DT(playerid, dialogid, response, listitem, inputtext[]);
#endif