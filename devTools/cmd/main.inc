

CMD:dtcmd(playerid) {
	if(!GetAccessDevTools(playerid)) {
		return 0;
	}

	DT_PlayerData[playerid][dtp_BackButton] = false;
	DT_Command(playerid);
	return 1;
}


stock DT_Command(playerid) {
	if(!GetAccessDevTools(playerid)) {
		return 0;
	}

	ShowPlayerDialog(playerid, DT_DIALOGID_CMD, DIALOG_STYLE_LIST, ""DT_NAME" by "DT_MAIN_COLOR_TAG""DT_AUTHOR" "DT_VERSION"", 
		DT_DIALOG_COMMANDS, 
		DT_SELECT_BUTTON, 
		DT_CLOSE_BUTTON);
	return 1;
}


stock DT_ShowCommandsList(playerid) {

	new type = DT_PlayerData[playerid][dtp_CommandType];
    new DT_string[(DT_COMMAND_MAX_LENGTH + DT_COMMAND_DESC_LENGTH + 8 + 8) * 20];
    
    if(!DT_BuildCommandsList(playerid, type, DT_string, sizeof(DT_string))) {
        return 0;
    }

	ShowPlayerDialog(playerid, DT_DIALOGID_CMD_BACK, DIALOG_STYLE_MSGBOX, ""DT_NAME" by "DT_MAIN_COLOR_TAG""DT_AUTHOR" "DT_VERSION"",
        DT_string, 
		DT_NEXT_BUTTON,
		DT_BACK_BUTTON);
	return 1;
}


// Универсальная функция генерации списка элементов
static stock DT_BuildCommandsList(playerid, type, string[], size) {

    new page = DT_PlayerData[playerid][dtp_CommandPage];
    
    new max_page = 20,
        bool:next = false,
        totalLines;
    
    new totalPage = 0;
    string[0] = EOS;

    new maxSlots, 
		itemName[DT_COMMAND_MAX_LENGTH + DT_COMMAND_DESC_LENGTH + 8 + 8];
    
    switch(type) {
        case 0: {
            maxSlots = DT_MAX_PLAYER_COMMANDS;
        }
        case 1: {
            maxSlots = DT_MAX_VEHICLE_COMMANDS;
        }
        case 2: {
            maxSlots = DT_MAX_OBJECT_COMMANDS;
        }
    }

    for(new slot; slot < maxSlots; slot++) {

		switch(type) {

            case 0: {
				format(itemName, sizeof(itemName), ""DT_MAIN_COLOR_TAG"/%s - "DT_WHITE_COLOR_TAG"%s",
					DT_PLAYER_COMMANDS[slot][0], 
					DT_PLAYER_COMMANDS[slot][1]);
            }
            case 1: {
				format(itemName, sizeof(itemName), ""DT_MAIN_COLOR_TAG"/%s - "DT_WHITE_COLOR_TAG"%s",
					DT_VEHICLE_COMMANDS[slot][0], 
					DT_VEHICLE_COMMANDS[slot][1]);
            }
			#if !defined DT_DISABLE_OBJECT_EDITOR
				case 2: {
					format(itemName, sizeof(itemName), ""DT_MAIN_COLOR_TAG"/%s - "DT_WHITE_COLOR_TAG"%s",
						DT_OBJECT_COMMANDS[slot][0], 
						DT_OBJECT_COMMANDS[slot][1]);
				}
			#endif
		}

        if(totalLines >= (page * max_page) && totalLines < (page * max_page) + max_page) {
            next = true;
        }

        if(totalLines >= (page - 1) * max_page && totalLines < ((page - 1) * max_page) + max_page) {

            format(string, size, "%s%s\n", string, itemName);
            totalPage++;
        }

        totalLines++;
    }

	DT_PlayerData[playerid][dtp_CommandNextPage] = next;
    return totalPage;
}



#include "player.inc"
#include "vehicle.inc"

#if !defined DT_DISABLE_OBJECT_EDITOR
	#include "object\main.inc"
#endif


#if defined PAWNCMD_INC_

	//Fix for old versions of pawn.cmd
    #define alias_dt:%0(%1); \
		forward pc_alias_dt_%0(); \
		public pc_alias_dt_%0() \
		PC_RegAlias(#%0, %1);

//player
	alias_dt:dt("devTools", "dtools"); 
	alias_dt:dtpublic("dtpub");

	alias_dt:dtgotopos("tppos");
	alias_dt:dtgoto("gotp");
	alias_dt:dtgethere("geth");
	alias_dt:dtsetint("setinterior");
	alias_dt:dtspawn("setspawn");

	alias_dt:dtsethp("sethealth");
	alias_dt:dtsetar("setarmour");

	alias_dt:dtgiveweapon("givegun", "setweapon", "aweapon");
	alias_dt:dtgivemoney("setmoney");

	alias_dt:dtplaysound("setsound");
	alias_dt:dtexplosion("boom", "setexplosion");

	alias_dt:dtsettime("worldtime");
	alias_dt:dtsetweather("setwea");

	alias_dt:dtplayanim("setanim", "playanimation", "setanimation");
	alias_dt:dtgetcam("camerapos", "campos");

	alias_dt:dtsetaction("saction", "specialaction");
	alias_dt:dtfstyle("fightstyle");
	alias_dt:dtsetdrunk("setdrunklevel", "drunklevel");

	alias_dt:dtattedit("setattach");
	alias_dt:dtweaponskill("setweaponskill");
	alias_dt:dtsetwanted("setwantedLevel");
	alias_dt:dtplaycrime("setcrime");
	alias_dt:dtcursor("tdselect");


//vehicle
	alias_dt:dtveh("acar", "createveh", "cvhe");
	alias_dt:dtdelveh("dveh");
	alias_dt:dtgotoveh("tpveh");
	alias_dt:dtgethereveh("getveh");

	alias_dt:dtrepairveh("fixcar");
	alias_dt:dtsetvehhp("setvhp");
	alias_dt:dtsetvehcolor("vcolor", "setvc");
	alias_dt:dtsetcomp("setcomponent", "vcomponent", "vcomp");
	alias_dt:dtremcomp("remcomponent", "delcomp");

	alias_dt:dtvehen("vehengine", "vehicleengine");
	alias_dt:dtvehli("vehlights", "vehiclelights");
	alias_dt:dtvehdo("vehdoor", "vehicledoor");
	

//object
	#if !defined DT_DISABLE_OBJECT_EDITOR
		alias_dt:dtocreate("ocre", "cobject");

		alias_dt:dtodel("delo", "dobject", "delobj"); 
		alias_dt:dtodelall("delallo");

		alias_dt:dtoedit("edito", "editobject");
		alias_dt:dtloadmap("loadproject");
		alias_dt:dtsavemap("saveproject");

		alias_dt:dtosetmt("mtset");
		alias_dt:dtormt("rindex");
		alias_dt:dtormtt("robject");
	#endif
	
#endif

