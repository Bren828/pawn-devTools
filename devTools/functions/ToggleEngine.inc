

stock DT_ToggleEngine(vehicleid) {

	new DT_engine, 
		DT_lights, 
		DT_alarm, 
		DT_doors, 
		DT_bonnet, 
		DT_boot, 
		DT_objective;

	GetVehicleParamsEx(vehicleid, DT_engine, DT_lights, DT_alarm, DT_doors, DT_bonnet, DT_boot, DT_objective);

	DT_engine = (DT_engine) ? 0 : 1;
	SetVehicleParamsEx(vehicleid, DT_engine, DT_lights, DT_alarm, DT_doors, DT_bonnet, DT_boot, DT_objective);

	return DT_engine;
}