#if defined _devTools_lang_included
	#endinput
#endif
#define _devTools_lang_included


new DT_DIALOG_MENU[] = 
	"Get distance from point \t %s\t\n\
	Teleport to waypoint \t %s\n\
	Get animation index \t %s\n\
	Disable Kick/Ban functions \t %s\n\
	GodMode \t %s\n\
	Camera target \t %s\n\
	Double jump \t %s\n\
	Mega bullet \t %s\n\
	{6fa8dc}Public log\n\
	Player statistics \t %s\n\
	Vehicle statistics \t %s\n\
	{366c90}Rak{f69d1d}Net: {FFFFFF}Player stats \t %s\n\
	{366c90}Rak{f69d1d}Net: {FFFFFF}Vehicle stats \t %s\n\
	{366c90}Rak{f69d1d}Net: {FFFFFF}Vehicle passenger stats \t %s";


new DT_DIALOG_PUBLICS[] = 
	"Key State Change \t %s\n\
	Take Damage \t %s\n\
	Give Damage \t %s\n\
	Weapon Shot \t %s\n\
	Death \t %s\n\
	Spawn \t %s\n\
	State Change \t %s\n\
	Enter Vehicle \t %s\n\
	Exit Vehicle \t %s";


new 
	DT_SELECT_BUTTON[] = 				"Select",
	DT_CLOSE_BUTTON[] = 				"Close",
	DT_BACK_BUTTON[] = 					"Back",
	DT_TEXT_INVALID[] = 				"Invalid ID";


#if defined DT_ENABLE_IGNORE_PUNISHMENTS
	new 
		DT_TEXT_IGNORING_PUNISHMENT[] = "The '%s' attempt was ignored.";
#else
	new 
		DT_TEXT_IGNORING_PUNISHMENT[] = "Enable '#define DT_ENABLE_IGNORE_PUNISHMENTS' to use this feature";
#endif


//Dialog
	new 
		DT_DIALOG_PLAYER_STATS_HEADER[] = 	"Player Statistics",
		DT_DIALOG_PLAYER_STATS[] = 			"{FFFFFF}Enter Player ID:",

		DT_DIALOG_VEHICLE_STATS_HEADER[] = 	"Vehicle Statistics",
		DT_DIALOG_VEHICLE_STATS[] = 		"{FFFFFF}Enter Vehicle ID:";


#if !defined PAWNRAKNET_INC_
	new 
		DT_TEXT_NO_RAKNET_PLUGIN[] = "Connect the 'PawnRaknet by katursis' plugin for this feature to work.";
#endif


#if !defined DT_DISABLE_COMMANDS

	new DT_DIALOG_COMMANDS[] =
		"Player Commands\n\
		Vehicle Commands\n\
		Object Commands";

	new 
		DT_NEXT_BUTTON[] = 		"Further",
		DT_CONFIRM_BUTTON[] = 	"Yes",
		DT_CANCEL_BUTTON[] = 	"No",
		DT_LIST_COMMANDST[] = 	"List of commands";


// Player
	new DT_PLAYER_COMMANDS[DT_MAX_PLAYER_COMMANDS][2][DT_COMMAND_DESC_LENGTH] = {
		{"dt",					"Dev Tools menu"},
		{"dtpublic",			"Publics call menu"},
		{"gotopos",				"Teleport to X Y Z positions"},
		{"goto",				"Teleport to player"},
		{"gethere",				"Teleport player to you"},
		{"setint",				"Change interior"},
		{"setworld",			"Change virtual world"},
		{"spawn",				"Spawn player"},
		{"sethp",				"Set player health"},
		{"setar",				"Set player armor"},
		{"giveweapon",			"Give weapon to player"},
		{"givemoney",			"Give money to player"},
		{"setscore",			"Set player score"},
		{"setskin",				"Set player skin"},
		{"playsound",			"Play sound"},
		{"playcrime",			"Play crime sound"},
		{"explosion",			"Create explosion"},
		{"settime",				"Change time"},
		{"setweather",			"Change weather"},
		{"playanim",			"Play animation"},
		{"getcam",				"Get current camera position"},
		{"attedit",				"Create attached object"},
		{"setaction",			"Set special action"},
		{"startrecord",			"Start bot recording"},
		{"stoprecord",			"Stop bot recording"},
		{"fstyle",				"Set fighting style"},
		{"setdrunk",			"Set drunk level"},
		{"weaponskill",			"Set weapon skill level"},
		{"setwanted",			"Set wanted level"},
		{"cursor",				"Show cursor"}
	};


// Vehicle
	new DT_VEHICLE_COMMANDS[DT_MAX_VEHICLE_COMMANDS][2][DT_COMMAND_DESC_LENGTH] = {	
		{"veh",					"Create vehicle"},
		{"delveh",				"Delete vehicle"},
		{"repairveh",			"Repair vehicle"},
		{"setvehhp",			"Set vehicle health"},
		{"gotoveh",				"Teleport to vehicle"},
		{"gethereveh",			"Teleport vehicle to you"},
		{"setvehcolor",			"Change vehicle color"},
		{"setcomp",				"Install tuning component"},
		{"remcomp",				"Remove tuning component"},
		{"vehen",				"Start/stop engine"},
		{"vehli",				"Turn on/off lights"},
		{"vehdo",				"Open/close doors"}
	};


// object
	#if !defined DT_DISABLE_OBJECT_EDITOR
		new DT_OBJECT_COMMANDS[DT_MAX_OBJECT_COMMANDS][2][DT_COMMAND_DESC_LENGTH] = {	
			{"loadmap",			"Load map"},
			{"savemap",			"Save map"},
			{"ocreate",			"Create object"},
			{"odel",			"Delete object"},
			{"odelall",			"Delete all objects"},
			{"oedit",			"Edit object"},
			{"oselect", 		"Select object with cursor"},
			{"ocopy",			"Copy object"},
			{"ogoto",			"Teleport to object"},
			{"ogethere",		"Teleport object to you"},
			{"oinfo",			"Object information"},
			{"otextdis",		"Set 3D text distance"},
			{"otextdetal",		"Display detailed info about objects"},
			{"oworld", 			"Set virtual world for object"},
			{"oworldall",		"Set virtual world for all objects"},
			{"oint", 			"Set interior for object"},
			{"ointall", 		"Set interior for all objects"},
			{"odis", 			"Set distance for object"},
			{"odisall", 		"Set distance for all objects"},
			{"osetm", 			"Set material"},
			{"osetmt", 			"Set text material"},
			{"ormt", 			"Remove material"},
			{"ormtt", 			"Remove text material"},
			{"ox", 				"Set X position"},
			{"oy", 				"Set Y position"},
			{"oz", 				"Set Z position"},
			{"orx", 			"Set RX rotation"},
			{"ory", 			"Set RY rotation"},
			{"orz",				"Set RZ rotation"},
			{"oxall", 			"Set X position for all objects"},
			{"oyall", 			"Set Y position for all objects"},
			{"ozall", 			"Set Z position for all objects"}
		};
	#endif


//Other text
	new 
		DT_TEXT_USE[] = 					"Use",
		DT_TEXT_YOUR[] = 					"Your",
		DT_TEXT_INVALID_COLOR[] = 			"Invalid color (0 - 255)",
		DT_TEXT_INVALID_PAINTJOB[] = 		"Invalid paintjob (0 - 3)",
		DT_TEXT_INVALID_MODEL[] = 			"Invalid model",
		DT_TEXT_INVALID_WEAPON_ID[] = 		"Invalid weapon id",
		DT_TEXT_INVALID_SKIN_ID[] = 		"Invalid skin id",
		DT_TEXT_INVALID_LENGTH[] = 			"Length from 2 to %d characters",
		DT_TEXT_NOT_FOUND[] = 				"Vehicle is not found",
		DT_TEXT_FAILED_CREATE_VEHICLE[] = 	"Failed to create transport";


//Command text

	// Player
	new 
		DT_CMD_TEXT_GOTOPOS[] = 			"Teleport | X: %.4f | Y: %.4f | Z: %.4f | World: %d | Interior: %d",
		DT_CMD_TEXT_GOTO[] = 				"You have been teleported to %s(%d)",
		DT_CMD_TEXT_GETHERE[] = 			"You teleported %s(%d) to yourself",
		DT_CMD_TEXT_SETINT[] = 				"New interior: %d | Old interior: %d",
		DT_CMD_TEXT_SETWORLD[] = 			"New virtual world: %d | Old virtual world: %d",
		DT_CMD_TEXT_SPAWN[] = 				"You spawned player %s(%d)",
		DT_CMD_TEXT_SETHP[] = 				"You set %.1f health for %s(%d)",
		DT_CMD_TEXT_SETAR[] = 				"You set %.1f armor for %s(%d)",
		DT_CMD_TEXT_GIVEWEAPON[] = 			"You gave weapon %d with %d ammo to %s(%d)",
		DT_CMD_TEXT_GIVEMONEY[] = 			"You gave $%d to player %s(%d)",
		DT_CMD_TEXT_SETSCORE[] = 			"You set %d score for %s(%d)",
		DT_CMD_TEXT_SETSKIN[] = 			"You gave skin %d to player %s(%d)",
		DT_CMD_TEXT_PLAYSOUND[] = 			"Sound %d played",
		DT_CMD_TEXT_EXPLOSION[] = 			"Explosion %d created for player %s(%d)",
		DT_CMD_TEXT_SETTIME[] = 			"Time set to %d",
		DT_CMD_TEXT_SETWEATHER[] = 			"Weather set to %d",
		DT_CMD_TEXT_SETACTION[] = 			"Action set to %d",
		DT_CMD_TEXT_STARTRECORD[] = 		"You started bot recording",
		DT_CMD_TEXT_STOPRECORD[] = 			"You stopped bot recording. File was saved in 'scriptfiles' folder",
		DT_CMD_TEXT_FSTYLE[] = 				"You changed fighting style to %d",
		DT_CMD_TEXT_SETDRUNK[] = 			"You set drunk level to %d",
		DT_CMD_TEXT_ATTEDIT_INFO[] = 		"Editing object on player",
		DT_CMD_TEXT_ATTEDIT_CAPTION[] = 	"{FFFFFF}Continue editing previous object?",
		DT_CMD_TEXT_WEAPONSKILL[] = 		"You set weapon skill level %d to %d",
		DT_CMD_TEXT_SETWANTED[] = 			"You set wanted level to %d",
		DT_CMD_TEXT_PLAYCRIME[] = 			"Crime sound played | Suspect: %d | Crime: %d";


	// Vehicle
	new 
		DT_CMD_TEXT_VEH[] = 				"Vehicle model %d has been created",
		DT_CMD_TEXT_DELVEH[] = 				"Deleted %d vehicles",
		DT_CMD_TEXT_GOTOVEH[] = 			"You teleported to vehicle ID: %d",
		DT_CMD_TEXT_GETHEREVEH[] =			"You teleported vehicle ID: %d to yourself",
		DT_CMD_TEXT_REPAIRVEH[] = 			"Vehicle repaired",
		DT_CMD_TEXT_SETVEHHP[] =  			"You set %.1f health for the vehicle",
		DT_CMD_TEXT_SETVEHCOLOR[] = 		"You changed vehicle color | Color 1: %d | Color 2: %d | Paintjob: %d",
		DT_CMD_TEXT_SETCOMP[] = 			"You installed component %d",
		DT_CMD_TEXT_REMCOMP[] = 			"You removed component %d",
		DT_CMD_TEXT_VEHEN_ON[] = 			"You started the engine",
		DT_CMD_TEXT_VEHEN2_OFF[] = 			"You turned off the engine",
		DT_CMD_TEXT_VEHLI_ON[] = 			"You turned on the lights",
		DT_CMD_TEXT_VEHLI_OFF[] = 			"You turned off the lights",
		DT_CMD_TEXT_VEHDO_CLOSED[] = 		"You closed the doors",
		DT_CMD_TEXT_VEHDO_OPENED[] = 		"You opened the doors";


	// Object
	#if !defined DT_DISABLE_OBJECT_EDITOR
		new 
			DT_TEXT_OBJECT_NOT_CREATED[] = 		"Object not created",
			DT_TEXT_LIMIT_OBJECTS[] = 			"Object creation limit reached",
			DT_TEXT_PROJECT_NOT_FOUND[] = 		"Project not found",
			DT_TEXT_INVALID_FOLDER[] = 			"Create folder '"#DT_OBJECTS_FOLDER"' in 'scriptfiles' directory",
			DT_TEXT_INVALID_MATERIAL_INDEX[] = 	"Invalid material index (0 - 15)",
			DT_TEXT_LOADING_MAP[] = 			"Project '%s' loaded with %d objects",
			DT_TEXT_SAVING_MAP[] = 				"Project '%s' with %d objects saved to scriptfiles\\"#DT_OBJECTS_FOLDER"",
			DT_TEXT_FAILED_CREATE_OBJECT[] = 	"Failed to create object";

		#if !defined RemoveDynamicObjectMaterialText
			new 
				DT_TEXT_OLD_VERSION_PLUGIN[] = "To use this command, update Streamer plugin to v2.9.5 or higher.";
		#endif


		new 
			DT_CMD_TEXT_OCREATE[] = 			"Object %d created under index %d",
			DT_CMD_TEXT_ODEL[] = 				"Object under index %d deleted",
			DT_CMD_TEXT_ODELALL[] = 			"All %d objects deleted",
			DT_CMD_TEXT_OCOPY[] = 				"Object %d copied to index %d",
			DT_CMD_TEXT_OGOTO[] = 				"You teleported to object under index %d",
			DT_CMD_TEXT_OGETHERE[] = 			"Object index %d teleported to you",
			DT_CMD_TEXT_OTEXTDIS[] = 			"3D text distance changed to %.1f",
			DT_CMD_TEXT_OTEXTDETAL_ON[] = 		"Detailed information enabled",
			DT_CMD_TEXT_OTEXTDETAL_OFF[] = 		"Detailed information disabled",
			DT_CMD_TEXT_OWORLD[] = 				"You changed object virtual world to %d",
			DT_CMD_TEXT_OWORLDALL[] = 			"You changed virtual world to %d for all objects",
			DT_CMD_TEXT_OINT[] = 				"You changed object interior to %d",
			DT_CMD_TEXT_OINTALL[] = 			"You changed interior to %d for all objects",
			DT_CMD_TEXT_ODIS[] = 				"You set distance for object index %d to %.2f",
			DT_CMD_TEXT_ODISALL[] = 			"You set distance %.2f for all objects",
			DT_CMD_TEXT_OSETM[] = 				"Object material index %d changed | Material index: %d | Modelid: %d | Material color: %d",
			DT_CMD_TEXT_OSETM_TXD_LEN[] = 		"'Txd name' length from 1 to 64 characters",
			DT_CMD_TEXT_OSETM_TEXTURE_LEN[] = 	"'Texture name' length from 1 to 64 characters",
			DT_CMD_TEXT_OSETMT[] = 				"Object text index %d changed",
			DT_CMD_TEXT_OSETMT_TEXT_LEN[] = 	"Text length from 1 to 144 characters",
			DT_CMD_TEXT_OSETMT_FONT_LEN[] = 	"'FontFace' length from 1 to 64 characters",
			DT_CMD_TEXT_ORMT[] = 				"Object index %d material in slot %d removed",
			DT_CMD_TEXT_ORMTT[] = 				"Object index %d text in slot %d removed",
			DT_CMD_TEXT_OX[] = 					"X position of object index %d changed from %f to %f",
			DT_CMD_TEXT_OY[] = 					"Y position of object index %d changed from %f to %f",
			DT_CMD_TEXT_OZ[] = 					"Z position of object index %d changed from %f to %f",
			DT_CMD_TEXT_ORX[] = 				"RX position of object index %d changed from %f to %f",
			DT_CMD_TEXT_ORY[] = 				"RY position of object index %d changed from %f to %f",
			DT_CMD_TEXT_ORZ[] = 				"RZ position of object index %d changed from %f to %f",
			DT_CMD_TEXT_OXALL[] = 				"X position of all objects changed to %f",
			DT_CMD_TEXT_OYALL[] = 				"Y position of all objects changed to %f",
			DT_CMD_TEXT_OZALL[] = 				"Z position of all objects changed to %f";
	#endif
#endif