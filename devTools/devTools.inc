/*
*
*
*
*   ---------------------------------------------------
*
*	Creater - @Bren828 					
*									25 April 2026
*
*   Version: 1.0
*
*   ---------------------------------------------------
*
*
*	https://github.com/Bren828/pawn-devTools
*
*
*
*/

#if defined _devTools_included 
	#endinput
#endif
#define _devTools_included


#define DT_NAME 					"Dev Tools"
#define DT_VERSION 					"v1.0"
#define DT_AUTHOR 					"Bren828"

#define DT_MAX_PLAYER_COMMANDS 		30
#define DT_MAX_VEHICLE_COMMANDS 	12
#define DT_MAX_OBJECT_COMMANDS 		32

#define DT_COMMAND_DESC_LENGTH 		50
#define DT_COMMAND_MAX_LENGTH 		14


#if !defined DT_DISABLE_COMMANDS
	//#define DT_DISABLE_COMMANDS
#endif

#if !defined DT_DISABLE_OBJECT_EDITOR
	//#define DT_DISABLE_OBJECT_EDITOR
#endif

#if !defined DT_ENABLE_IGNORE_PUNISHMENTS
	//#define DT_ENABLE_IGNORE_PUNISHMENTS
#endif

#if !defined DT_INTERFACE_LANGUAGE
	#define DT_INTERFACE_LANGUAGE 0 // 0 - English | 1 - Russian 
#endif

#if !defined DT_MAX_OBJECT
	#define DT_MAX_OBJECT 200
#endif

#if !defined DT_MIN_VEHICLE_MODEL
	#define DT_MIN_VEHICLE_MODEL 400
#endif

#if !defined DT_MAX_VEHICLE_MODEL
	#define DT_MAX_VEHICLE_MODEL 611
#endif

#if !defined DT_MIN_SKIN_MODEL
	#define DT_MIN_SKIN_MODEL 0
#endif

#if !defined DT_MAX_SKIN_MODEL
	#define DT_MAX_SKIN_MODEL 311
#endif

#if !defined DT_OBJECTS_FOLDER
	#define DT_OBJECTS_FOLDER "devTools_Maps"
#endif

#if !defined DT_LENGTH_PROJECT_NAME
	#define DT_LENGTH_PROJECT_NAME 32
#endif

#if !defined DT_VEHICLE_SPEED_MULTIPLIER
	#define DT_VEHICLE_SPEED_MULTIPLIER 179.28625
#endif

#if !defined DT_COLOR_MAIN
	#define DT_COLOR_MAIN 0xfbbaa8FF
#endif

#if !defined DT_MAIN_COLOR_TAG
	#define DT_MAIN_COLOR_TAG "{fbbaa8}" //FFD700
#endif

#if !defined DT_WHITE_COLOR_TAG
	#define DT_WHITE_COLOR_TAG "{FFFFFF}"
#endif

#if !defined DT_RED_COLOR_TAG
	#define DT_RED_COLOR_TAG "{f44747}"
#endif

#if !defined DT_GREEN_COLOR_TAG
	#define DT_GREEN_COLOR_TAG "{61dd61}"
#endif

#define DT_TEXT_ON  ""DT_GREEN_COLOR_TAG"On"
#define DT_TEXT_OFF ""DT_RED_COLOR_TAG"Off"

#define DT_TAG_HINT  "["DT_NAME"]: "DT_WHITE_COLOR_TAG""
#define DT_TAG_ERROR "["DT_NAME"]: "DT_RED_COLOR_TAG""

#if !DT_INTERFACE_LANGUAGE
	#include "lang\en.inc"
#else 
	#include "lang\ru.inc"
#endif


enum DT_E_PLAYER_DATA {

	dtp_Name[MAX_PLAYER_NAME],
	dtp_Access,

//public
	bool:dtp_PublicAnimation,
	bool:dtp_PublicKey,
	bool:dtp_PublicTakeDamage,
	bool:dtp_PublicGiveDamage,
	bool:dtp_PublicWeaponShot,
	bool:dtp_PublicDeath,
	bool:dtp_PublicSpawn,
	bool:dtp_PublicStateChange,
	bool:dtp_PublicEnterVehicle,
	bool:dtp_PublicExitVehicle,

//Stats
	//Stats player
	dtp_PlayerIDStats, 
	dtp_PlayerStatsTimer, 
	PlayerText:dtp_PlayerStatsTD,
 
	//Stats vehicle
	dtp_VehicleIDStats, 
	dtp_VehicleStatsTimer, 
	PlayerText:dtp_VehicleStatsTD,

	//Stats raknet player
	dtp_RaknetPlayerIDStats,
	PlayerText:dtp_RaknetPlayerStatsTD,

	//Stats raknet vehicle
	dtp_RaknetVehicleIDStats, 
	PlayerText:dtp_RaknetVehicleStatsTD,

	//Stats raknet passenger
	dtp_RaknetPassengerIDStats, 
	PlayerText:dtp_RaknetPassengerStatsTD,

//other
	//Camera Target
	bool:dtp_EnableCameraTarget,

	//Double Jump
	bool:dtp_EnableDoubleJump, 
	dtp_DoubleJumpDelay,

	//Distance Point
	bool:dtp_EnableDistancePoint, 
	Float:dtp_PointDistancePosX, 
	Float:dtp_PointDistancePosY, 
	Float:dtp_PointDistancePosZ, 
	Text3D:dtp_PointText3D,

	//Teleport by mark
	bool:dtp_EnableTeleportByMark,

	//Explosive Shooting
	bool:dtp_EnableExplosiveShooting,

	//Back button in public, menu
	bool:dtp_BackButton,

	//Ignore Punishments
	bool:dtp_IgnorePunishments,

	//GodMode
	bool:dtp_EnableGodMode,

//Attached object
	bool:dtp_AttachedObject,
	dtp_AttachedIndex,
	dtp_AttachedModel,
	dtp_AttachedBone,
	dtp_AttachedColor,
	
	dtp_NewAttachedIndex,
	dtp_NewAttachedModel,
	dtp_NewAttachedBone,
	dtp_NewAttachedColor,

	Float:dtp_AttachedOffsetX,
	Float:dtp_AttachedOffsetY,
	Float:dtp_AttachedOffsetZ,
	Float:dtp_AttachedRotX, 
	Float:dtp_AttachedRotY, 
	Float:dtp_AttachedRotZ, 
	Float:dtp_AttachedScaleX,
	Float:dtp_AttachedScaleY,
	Float:dtp_AttachedScaleZ,

//Command
	dtp_CommandPage,
	dtp_CommandType,
	bool:dtp_CommandNextPage,

}

new DT_PlayerData[MAX_PLAYERS][DT_E_PLAYER_DATA];
new const DT_NullPlayerData[DT_E_PLAYER_DATA];

new DT_Vehicles[MAX_VEHICLES];


enum (<<= 1) {
	DT_DIALOGID_MENU = 32000,

	DT_DIALOGID_PLAYER_STATS = 32001,
	DT_DIALOGID_VEHICLE_STATS = 32002,

	DT_DIALOGID_RAKNET_PLAYER = 32003,
	DT_DIALOGID_RAKNET_VEHICLE = 32004,
	DT_DIALOGID_RAKNET_PASSENGER = 32005,

	DT_DIALOGID_CMD = 32006,
	DT_DIALOGID_CMD_BACK = 32007,

	DT_DIALOGID_PUBLIC = 32008,
	DT_DIALOGID_SET_OBJECT = 32009
}


#define SetAccessDevTools(%0,%1) \
	DT_PlayerData[%0][dtp_Access] = %1

#define GetAccessDevTools(%0) \
	(DT_PlayerData[%0][dtp_Access])

#define DT_GetName(%0) \
	(DT_PlayerData[%0][dtp_Name])


//functions
#include "functions\GetPlayerFps.inc"
#include "functions\GetVehicleSpeed.inc"
#include "functions\RenameCommandList.inc"
#include "functions\Punishments.inc"
#include "functions\ApplyOffset.inc"
#include "functions\SendMessage.inc"

#include "menu\menu.inc"


//Commands
#if !defined DT_DISABLE_COMMANDS
	#include "cmd\main.inc"

	#include "functions\ToggleEngine.inc"
	#include "functions\ToggleLight.inc"
	#include "functions\ToggleDoor.inc"
#endif


//Player
#include "public\player\OnAttachedObject.inc"
#include "public\player\OnDialogResponse.inc"
#include "public\player\OnPlayerClickMap.inc"
#include "public\player\OnPlayerConnect.inc"
#include "public\player\OnPlayerDamage.inc"
#include "public\player\OnPlayerDeath.inc"
#include "public\player\OnPlayerDisconnect.inc"
#include "public\player\OnPlayerKeyStateChange.inc"
#include "public\player\OnPlayerSpawn.inc"
#include "public\player\OnPlayerStateChange.inc"
#include "public\player\OnPlayerUpdate.inc"
#include "public\player\OnPlayerWeaponShot.inc"
#include "public\player\OnPlayerSelectDynamicObject.inc"
#include "public\player\OnPlayerEditDynamicObject.inc"


//Vehicle
#include "public\vehicle\OnPlayerEnterVehicle.inc"
#include "public\vehicle\OnPlayerExitVehicle.inc"
#include "public\vehicle\OnVehicleDeath.inc"


//others
#include "public\OnGameModeInit.inc"
