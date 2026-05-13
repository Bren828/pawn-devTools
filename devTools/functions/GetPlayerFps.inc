

stock DT_GetPlayerFps(playerid) {

    new dt_Fps = GetPVarInt(playerid, "DT_FPS");
    SetPVarInt(playerid, "DT_DrunkL", GetPlayerDrunkLevel(playerid));

    if(GetPVarInt(playerid, "DT_DrunkL") < 100) {
        SetPlayerDrunkLevel(playerid, 2000);
    }
    else {
        if(GetPVarInt(playerid, "DT_LDrunkL") != GetPVarInt(playerid, "DT_DrunkL")) {
            SetPVarInt(playerid, "DT_FPS", (GetPVarInt(playerid, "DT_LDrunkL") - GetPVarInt(playerid, "DT_DrunkL")));
            SetPVarInt(playerid, "DT_LDrunkL", GetPVarInt(playerid, "DT_DrunkL"));

            if((GetPVarInt(playerid, "DT_FPS") > 0) && (GetPVarInt(playerid, "DT_FPS") < 256)) {
                dt_Fps = GetPVarInt(playerid, "DT_FPS");
            }
        }
    }

    if(dt_Fps < 0) {
        dt_Fps = 0;
    }

    return dt_Fps;
}