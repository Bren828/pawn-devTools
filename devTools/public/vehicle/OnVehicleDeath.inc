

public OnVehicleDeath(vehicleid, killerid) {

	if(DT_Vehicles[vehicleid] != INVALID_VEHICLE_ID) {
		DestroyVehicle(vehicleid);
		DT_Vehicles[vehicleid] = INVALID_VEHICLE_ID;
	}

    #if defined OnVehicleDeath_DT
        return OnVehicleDeath_DT(vehicleid, killerid);
    #else 
        return 1;
    #endif
}
#if defined _ALS_OnVehicleDeath
    #undef OnVehicleDeath
#else
    #define _ALS_OnVehicleDeath
#endif

#define OnVehicleDeath OnVehicleDeath_DT
#if defined OnVehicleDeath_DT
    forward OnVehicleDeath_DT(vehicleid, killerid);
#endif