

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


#if defined PAWNCMD_INC_ && !defined DT_DISABLE_COMMAND_ALIASES
	#include "aliases.inc"
#endif

