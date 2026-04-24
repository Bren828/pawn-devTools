//raknet

static const DT_VEHICLE_SYNC = 200, 
	DT_PLAYER_SYNC = 207,
	DT_PASSENGER_SYNC = 211;


IPacket:DT_PLAYER_SYNC(playerid, BitStream:bs) { 

    new onFootData[PR_OnFootSync];
    BS_IgnoreBits(bs, 8);
    BS_ReadOnFootSync(bs, onFootData);

	if(DT_PlayerData[playerid][dtp_RaknetPlayerIDStats] != INVALID_PLAYER_ID) {

		new targetid = DT_PlayerData[playerid][dtp_RaknetPlayerIDStats];

		static const dt_text[] = 
			"~y~RakNet: Player Data[%d] - %02d:%02d:%02d ~w~~n~\
			lrKey: %d ~n~\
			udKey: %d ~n~\
			keys: %d ~n~\
			position: %.2f %.2f %.2f ~n~\
			quaternion: %.2f %.2f %.2f %.2f ~n~\
			health: %d ~n~\
			armour: %d ~n~\
			additionalKey: %d ~n~\
			weaponId: %d ~n~\
			specialAction: %d ~n~\
			velocity: %.2f %.2f %.2f ~n~\
			surfingOffsets: %.2f %.2f %.2f ~n~\
			surfingVehicleId: %d ~n~\
			animationId: %d ~n~\
			animationFlags: %d~n~";

		new DT_string[sizeof(dt_text) + (11 * 10)], 
			dt_hour, 
			dt_minute, 
			dt_second;
		gettime(dt_hour, dt_minute, dt_second);

		format(DT_string, sizeof(DT_string), dt_text, 
			playerid, dt_hour, dt_minute, dt_second, 
			onFootData[PR_lrKey], 
			onFootData[PR_udKey], 
			onFootData[PR_keys], 
			onFootData[PR_position][0], onFootData[PR_position][1], onFootData[PR_position][2], 
			onFootData[PR_quaternion][0], onFootData[PR_quaternion][1], onFootData[PR_quaternion][2], onFootData[PR_quaternion][3], 
			onFootData[PR_health], 
			onFootData[PR_armour],
			onFootData[PR_additionalKey], 
			onFootData[PR_weaponId], 
			onFootData[PR_specialAction], 
			onFootData[PR_velocity][0], onFootData[PR_velocity][1], onFootData[PR_velocity][2], 
			onFootData[PR_surfingOffsets][0], onFootData[PR_surfingOffsets][1], onFootData[PR_surfingOffsets][2], 
			onFootData[PR_surfingVehicleId], 
			onFootData[PR_animationId], 
			onFootData[PR_animationFlags]);
			
		PlayerTextDrawSetString(targetid, 
			DT_PlayerData[targetid][dtp_RaknetPlayerStatsTD], 
			DT_string);
	}
    return 1;
}


IPacket:DT_VEHICLE_SYNC(playerid, BitStream:bs) {

	new inCarData[PR_InCarSync];
	BS_IgnoreBits(bs, 8);
	BS_ReadInCarSync(bs, inCarData);

	if(DT_PlayerData[playerid][dtp_RaknetVehicleIDStats] != INVALID_PLAYER_ID) {

		new targetid = DT_PlayerData[playerid][dtp_RaknetVehicleIDStats];

		static const dt_text[] = 
			"~y~RakNet: Vehicle Sync[%d] - %02d:%02d:%02d:~w~~n~\
			vehicleId: %d~n~\
			lrKey: %d~n~\
			udKey: %d~n~\
			keys: %d~n~\
			quaternion: %.2f %.2f %.2f %.2f~n~\
			position: %.2f %.2f %.2f~n~\
			velocity: %.2f %.2f %.2f~n~\
			vehicleHealth: %.2f~n~\
			playerHealth: %d~n~\
			armour: %d~n~\
			additionalKey: %d~n~\
			weaponId: %d~n~\
			sirenState: %d~n~\
			landingGearState: %d ~n~\
			trailerId: %d~n~\
			trainSpeed: %.2f";

		new DT_string[sizeof(dt_text) + (11 * 10)], 
			dt_hour, 
			dt_minute, 
			dt_second;
		gettime(dt_hour, dt_minute, dt_second);

		format(DT_string, sizeof(DT_string), dt_text,
			playerid, dt_hour, dt_minute, dt_second,
			inCarData[PR_vehicleId],
			inCarData[PR_lrKey],
			inCarData[PR_udKey],
			inCarData[PR_keys],
			inCarData[PR_quaternion][0], inCarData[PR_quaternion][1], inCarData[PR_quaternion][2], inCarData[PR_quaternion][3],
			inCarData[PR_position][0], inCarData[PR_position][1], inCarData[PR_position][2],
			inCarData[PR_velocity][0], inCarData[PR_velocity][1], inCarData[PR_velocity][2], 
			inCarData[PR_vehicleHealth],
			inCarData[PR_playerHealth],
			inCarData[PR_armour],
			inCarData[PR_additionalKey],
			inCarData[PR_weaponId],
			inCarData[PR_sirenState],
			inCarData[PR_landingGearState],
			inCarData[PR_trailerId],
			inCarData[PR_trainSpeed]);

		PlayerTextDrawSetString(targetid, 
			DT_PlayerData[targetid][dtp_RaknetVehicleStatsTD], 
			DT_string);
	}

	return 1;
}


IPacket:DT_PASSENGER_SYNC(playerid, BitStream:bs) {

    new passengerData[PR_PassengerSync];
    BS_IgnoreBits(bs, 8);
    BS_ReadPassengerSync(bs, passengerData);

	if(DT_PlayerData[playerid][dtp_RaknetPassengerIDStats] != INVALID_PLAYER_ID) {

		new targetid = DT_PlayerData[playerid][dtp_RaknetPassengerIDStats];

		static const dt_text[] =
			"~y~RakNet: Vehicle Passenger Sync[%d] - %02d:%02d:%02d:~w~~n~\
			vehicleId: %d~n~\
			driveBy: %d~n~\
			seatId: %d~n~\
			additionalKey: %d~n~\
			weaponId: %d~n~\
			playerHealth: %d~n~\
			playerArmour: %d~n~\
			lrKey: %d~n~\
			udKey: %d~n~\
			keys: %d~n~\
			position: %.2f %.2f %.2f";

		new DT_string[sizeof(dt_text) + (10 * 10)], 
			dt_hour, 
			dt_minute, 
			dt_second;
		gettime(dt_hour, dt_minute, dt_second);

		format(DT_string, sizeof(DT_string), dt_text,
			playerid, dt_hour, dt_minute, dt_second,
			passengerData[PR_vehicleId],
			passengerData[PR_driveBy],
			passengerData[PR_seatId],
			passengerData[PR_additionalKey],
			passengerData[PR_weaponId],
			passengerData[PR_playerHealth],
			passengerData[PR_playerArmour],
			passengerData[PR_lrKey],
			passengerData[PR_udKey],
			passengerData[PR_keys],
			passengerData[PR_position][0], passengerData[PR_position][1], passengerData[PR_position][2]);

		PlayerTextDrawSetString(targetid, 
			DT_PlayerData[targetid][dtp_RaknetPassengerStatsTD], 
			DT_string);
	}
	return 1;
}

