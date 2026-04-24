

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {

	if(DT_PlayerData[playerid][dtp_PublicWeaponShot]) {
    	new DT_string[144];
		
    	format(DT_string, sizeof(DT_string), "["DT_NAME" Weapon Shot]: "DT_WHITE_COLOR_TAG"weaponid %d | hittype: %i | hitid: %i | fX: %f | fY: %f | fZ: %f", 
			weaponid, 
			hittype, 
			hitid, 
			fX, 
			fY, 
			fZ);
			
		SendClientMessage(playerid, DT_COLOR_MAIN, DT_string);
	}
	
	if(DT_PlayerData[playerid][dtp_EnableExplosiveShooting] && fX != 0.0 && fY != 0.0 && fZ != 0.0) {
        CreateExplosion(fX, fY, fZ, 0, 5.0);
 	}

    #if defined OnPlayerWeaponShot_DT
        return OnPlayerWeaponShot_DT(playerid, weaponid, hittype, hitid, fX, fY, fZ);
    #else 
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerWeaponShot
    #undef OnPlayerWeaponShot
#else
    #define _ALS_OnPlayerWeaponShot
#endif

#define OnPlayerWeaponShot OnPlayerWeaponShot_DT
#if defined OnPlayerWeaponShot_DT
    forward OnPlayerWeaponShot_DT(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif