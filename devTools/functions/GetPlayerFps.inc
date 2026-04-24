

stock DT_GetPlayerFps(playerid) {
    
    SetPVarInt(playerid, "DT_DrunkL", GetPlayerDrunkLevel(playerid));

    if(GetPVarInt(playerid, "DT_DrunkL") > 100 && GetPVarInt(playerid, "DT_LDrunkL") != GetPVarInt(playerid, "DT_DrunkL")) {
        
        SetPVarInt(playerid, "DT_FPS", GetPVarInt(playerid, "DT_LDrunkL") - GetPVarInt(playerid, "DT_DrunkL"));
        SetPVarInt(playerid, "DT_LDrunkL", GetPVarInt(playerid, "DT_DrunkL"));

        if(GetPVarInt(playerid, "DT_FPS") >= 2 && GetPVarInt(playerid, "DT_FPS") < 256) {
            SetPVarInt(playerid, "DT_FPS_CACHE", GetPVarInt(playerid, "DT_FPS")-1);
        }
    }
    else {
        SetPlayerDrunkLevel(playerid, 2000);
    }

    return GetPVarInt(playerid, "DT_FPS_CACHE");
}
