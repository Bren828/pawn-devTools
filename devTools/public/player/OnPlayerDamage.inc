

#if defined _INC_WEAPON_CONFIG 

	public OnPlayerDamageDone(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart) {

		if(DT_PlayerData[playerid][dtp_PublicTakeDamage] || issuerid != INVALID_PLAYER_ID && DT_PlayerData[issuerid][dtp_PublicGiveDamage]) {
			new DT_string[144];

			format(DT_string, sizeof(DT_string), "["DT_NAME" Damage]: "DT_WHITE_COLOR_TAG"playerid: %d | amount: %f | issuerid: %d | weapon: %d | bodypart: %d", 
				playerid, 
				amount, 
				issuerid, 
				weapon, 
				bodypart);
			
			if(DT_PlayerData[playerid][dtp_PublicTakeDamage]) {
				SendClientMessage(playerid, DT_COLOR_MAIN, DT_string);
			}

			if(issuerid != INVALID_PLAYER_ID && DT_PlayerData[issuerid][dtp_PublicGiveDamage]) {
				SendClientMessage(issuerid, DT_COLOR_MAIN, DT_string);
			}
		}

		#if defined OnPlayerDamageDone_DT
			return OnPlayerDamageDone_DT(playerid, amount, issuerid, weapon, bodypart);
		#else
			return 1;
		#endif
	}

	#if defined _ALS_OnPlayerDamageDone
		#undef OnPlayerDamageDone
	#else
		#define _ALS_OnPlayerDamageDone
	#endif

	#define OnPlayerDamageDone OnPlayerDamageDone_DT
	#if defined OnPlayerDamageDone_DT
		forward OnPlayerDamageDone_DT(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart);
	#endif

#else

	public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {

		new DT_string[144];

		if(issuerid != INVALID_PLAYER_ID && DT_PlayerData[issuerid][dtp_PublicTakeDamage]) {

			format(DT_string, sizeof(DT_string), "["DT_NAME" Take Damage]: "DT_WHITE_COLOR_TAG"playerid: %d | issuerid: %d | damage: %f | weapon: %d | bodypart: %d", 
				playerid, 
				issuerid, 
				amount, 
				weaponid, 
				bodypart);
			SendClientMessage(issuerid, DT_COLOR_MAIN, DT_string);
		}

		if(DT_PlayerData[playerid][dtp_PublicTakeDamage]) {

			format(DT_string, sizeof(DT_string), "["DT_NAME" Take Damage]: "DT_WHITE_COLOR_TAG"playerid: %d | issuerid: %d | damage: %f | weapon: %d | bodypart: %d", 
				playerid, 
				issuerid, 
				amount, 
				weaponid, 
				bodypart);
			SendClientMessage(playerid, DT_COLOR_MAIN, DT_string);
		}

		#if defined OnPlayerTakeDamage_DT
			return OnPlayerTakeDamage_DT(playerid, issuerid, amount, weaponid, bodypart);
		#else 
			return 1;
		#endif
	}
	#if defined _ALS_OnPlayerTakeDamage
		#undef OnPlayerTakeDamage
	#else
		#define _ALS_OnPlayerTakeDamage
	#endif

	#define OnPlayerTakeDamage OnPlayerTakeDamage_DT
	#if defined OnPlayerTakeDamage_DT
		forward OnPlayerTakeDamage_DT(playerid, issuerid, Float:amount, weaponid, bodypart);
	#endif


	public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart) {

		if(DT_PlayerData[playerid][dtp_PublicGiveDamage]) {
			new DT_string[144];

			format(DT_string, sizeof(DT_string), "["DT_NAME" Give Damage]: "DT_WHITE_COLOR_TAG"playerid: %d | damagedid: %d | damage: %f | weapon: %d | bodypart: %d", 
				playerid, 
				damagedid, 
				amount, 
				weaponid, 
				bodypart);
			SendClientMessage(playerid, DT_COLOR_MAIN, DT_string);
		}
		
		#if defined OnPlayerGiveDamage_DT
			return OnPlayerGiveDamage_DT(playerid, damagedid, amount, weaponid, bodypart);
		#else 
			return 1;
		#endif
	}
	#if defined _ALS_OnPlayerGiveDamage
		#undef OnPlayerGiveDamage
	#else
		#define _ALS_OnPlayerGiveDamage
	#endif

	#define OnPlayerGiveDamage OnPlayerGiveDamage_DT
	#if defined OnPlayerGiveDamage_DT
		forward OnPlayerGiveDamage_DT(playerid, damagedid, Float:amount, weaponid, bodypart);
	#endif

#endif