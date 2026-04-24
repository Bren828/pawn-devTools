
#if defined DT_ENABLE_IGNORE_PUNISHMENTS
    stock DT_Kick(playerid) {

        if(DT_PlayerData[playerid][dtp_IgnorePunishments]) {
            DT_TextPunishment(playerid, "Kick");
            return 1;
        }

        return Kick(playerid);
    }

    #if defined _ALS_Kick
        #undef Kick
    #else
        #define _ALS_Kick
    #endif
    #define Kick DT_Kick


    stock DT_Ban(playerid) {

        if(DT_PlayerData[playerid][dtp_IgnorePunishments]) {
            DT_TextPunishment(playerid, "Ban");
            return 0;
        }

        return Ban(playerid);
    }

    #if defined _ALS_Ban
        #undef Ban
    #else
        #define _ALS_Ban
    #endif
    #define Ban DT_Ban


    stock DT_BanEx(playerid, const reason[]) {

        if(DT_PlayerData[playerid][dtp_IgnorePunishments]) {
            DT_TextPunishment(playerid, "BanEx");
            return 0;
        }

        return BanEx(playerid, reason);
    }

    #if defined _ALS_BanEx
        #undef BanEx
    #else
        #define _ALS_BanEx
    #endif
    #define BanEx DT_BanEx

    
    static stock DT_TextPunishment(playerid, const action[]) {
        new DT_string[128];

        strcat(DT_string, DT_TEXT_IGNORING_PUNISHMENT);

        format(DT_string, sizeof(DT_string), DT_string, action);
        DT_SendSucc(playerid, DT_string);
        return 1;
    }
#endif
