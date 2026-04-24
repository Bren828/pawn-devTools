

stock DT_GetVehicleSpeed(vehicleid) {
    
    new Float:x,
        Float:y,
        Float:z;
        
    GetVehicleVelocity(vehicleid, x, y, z);
    
	return floatround(floatsqroot(floatpower(x, 2.0) + floatpower(y, 2.0) + floatpower(z, 2.0)) * DT_VEHICLE_SPEED_MULTIPLIER);
}