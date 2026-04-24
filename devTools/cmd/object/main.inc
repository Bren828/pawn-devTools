
//Object editor

enum DT_E_PLAYER_OBJECT_DATA {

	dto_ProjectName[DT_LENGTH_PROJECT_NAME],

	dto_EditingIndex,
	bool:dto_IsSelected,

	Float:dto_Tex3dDistance,
	bool:dto_ShowObjectDetails,

	dto_Object[DT_MAX_OBJECT],
	Text3D:dto_Text3D[DT_MAX_OBJECT],
}
new DT_PlayerObjectData[MAX_PLAYERS][DT_E_PLAYER_OBJECT_DATA];


#define DT_INVALID_OBJECT_INDEX -1


#include "cmd.inc"

#include "functions\CreateObject.inc"
#include "functions\DestroyObject.inc"

#include "functions\GetFreeObjectIndex.inc"
#include "functions\GetAllObjectsCount.inc"
#include "functions\UpdateObjectText3D.inc"

#include "functions\SaveMap.inc"
#include "functions\LoadMap.inc"
