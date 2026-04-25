

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
	alias_dt:dtsetwanted("setwantedlevel");
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